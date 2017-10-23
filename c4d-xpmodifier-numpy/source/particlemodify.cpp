//
//  c4dmodify.cpp
//  xpmodifier
//
//  Created by HermenB on 22-10-17.
//  Copyright © 2017 MAXON Computer GmbH. All rights reserved.
//

#include "c4d.h"
#include "c4d_symbols.h"
#include "main.h"
#include "oparticlemodifier.h"
#include "c4d_string.h"

#include "conversion.h"

class PyParticleModifier : public ObjectData
{
private:
    
public:
    virtual Bool Init(GeListNode* node);
    virtual Bool Message(GeListNode* node, Int32 type, void* t_data);
    virtual void ModifyParticles(BaseObject *op, Particle *pp, BaseParticle *ss, Int32 pcnt, Float diff);
    static NodeData* Alloc(void) { return NewObjClear(PyParticleModifier); }
    
};

Bool PyParticleModifier::Init(GeListNode *node)
{
    BaseObject*		 op	= (BaseObject*)node;
    BaseContainer* data = op->GetDataInstance();
    
    data->SetBool(OPARTICLEMODIFIER_NUMPY, true);
    if (!testNumpy()) {
        data->SetBool(OPARTICLEMODIFIER_NUMPY, false);
    }
    
    String s;   // python code
    s  = "import c4d\n";
    s += "import numpy as np\n\n";
    s += "# available variables:\n";
    s += "# op, doc, frame, dt, m(=op.GetMg())\n\n";
    s += "X = Position\n";
    s += "V = Velocity\n";
    s += "V[:,2] -= X[:,2]";
    data->SetString(OPARTICLEMODIFIER_CODE, s);
    
    return true;
    
}

static GeData pythonCallback(BaseList2D* node, const BaseContainer& msg)
{
    // ****************************************************************
    // Callback function provided to c4d's Expression Editor, to pass
    // code back and forth between the Editor and this plugin.
    // ****************************************************************
    GeData res;
    
    BaseContainer* data = node->GetDataInstance();
    if (data == nullptr)
        return res;
    
    switch (msg.GetId())
    {
        case CODEEDITOR_GETSTRING:
        {
            BaseContainer bc;
            bc.SetString(CODEEDITOR_SETSTRING, data->GetString(OPARTICLEMODIFIER_CODE));
            bc.SetInt32(CODEEDITOR_SETMODE, SCRIPTMODE_PYTHON);
            
            res = bc;
            break;
        }
        case CODEEDITOR_SETSTRING:
        {
            GePythonGIL gil;
            data->SetString(OPARTICLEMODIFIER_CODE, msg.GetString(CODEEDITOR_SETSTRING));
            
            res = true;
            break;
        }
        case CODEEDITOR_COMPILE:
        {
            GePythonGIL pygil;
            PythonLibrary pylib;
            
            BaseContainer bc;
            String err_string;
            Int32 err_line = 0, err_row = 0;
            
            if (pylib.CheckSyntax(data->GetString(OPARTICLEMODIFIER_CODE), &err_row, &err_line, &err_string)) {
                bc.SetInt32(CODEEDITOR_GETERROR_RES, true);
                bc.SetInt32(CODEEDITOR_GETERROR_LINE, -1);
                bc.SetInt32(CODEEDITOR_GETERROR_POS, -1);
            }
            else {
                bc.SetInt32(CODEEDITOR_GETERROR_RES, false);
                bc.SetString(CODEEDITOR_GETERROR_STRING, "SyntaxError: "+err_string);
                bc.SetInt32(CODEEDITOR_GETERROR_LINE, err_line);
                bc.SetInt32(CODEEDITOR_GETERROR_POS, err_row);
            }
            
            res = bc;
            break;
        }
        case CODEEDITOR_EXECUTE:
        {
            BaseContainer bc;
            
            EventAdd();
            
            bc.SetInt32(CODEEDITOR_GETERROR_RES, true);
            bc.SetString(CODEEDITOR_GETERROR_STRING, "");
            bc.SetInt32(CODEEDITOR_GETERROR_LINE, -1);
            bc.SetInt32(CODEEDITOR_GETERROR_POS, -1);
            
            res = bc;
            break;
        }
        case CODEEDITOR_GETID:
        {
            return GeData(CUSTOMDATATYPE_DESCID, DescID(DescLevel(OPARTICLEMODIFIER_CODE)));
        }
    }
    return res;
}

Bool PyParticleModifier::Message(GeListNode *node, Int32 type, void *data)
{
    switch (type) {
        case MSG_XPARTICLES_ISMODIFIER:
        {
            if (data != nullptr) {
                XPModifierMsgData *msgData = (XPModifierMsgData*)data;
                msgData->_flags |= XP_MODIFIERMSG_FLAG_PLUGIN_MODIFIER | XP_MODIFIERMSG_FLAG_PLUGIN_THREAD;
            }
        }
        case MSG_DESCRIPTION_COMMAND:
        {
            DescriptionCommand* dc = (DescriptionCommand*) data;
            if (dc->id[0].id == OPARTICLEMODIFIER_OPENEDITOR) {
                // get the text in the editor
                CodeEditor_Open((BaseList2D*)node, pythonCallback);
            }
        }
    }
    return true;
}


void PyParticleModifier::ModifyParticles(BaseObject *op, Particle *pp, BaseParticle *ss, Int32 pcnt, Float diff)
{
    BaseContainer* bc = op->GetDataInstance();
    
    // if numpy is not installed, do not proceed
    if (!bc->GetBool(OPARTICLEMODIFIER_NUMPY)) return;
    
    BaseDocument *doc = op->GetDocument();
    Int32 frame = doc->GetTime().GetFrame(doc->GetFps());
    String code = bc->GetString(OPARTICLEMODIFIER_CODE);
    
    NumpyArray npArray = NumpyArray(pp, pcnt);
    npArray.SetMg(op);
    
    // python code here
    PythonLibrary pylib;
    PythonGIL *pyGIL = pylib.AllocGIL();
    PythonBase *pybase = pylib.Alloc();
    
    npArray.addNumpyArrays(pylib, pybase);
    pylib.SetInt32(pybase, "frame", frame);
    pylib.SetFloat(pybase, "dt", diff);
    pylib.SetGeListNode(pybase, "op", op, false);
    pylib.SetGeListNode(pybase, "doc", op->GetDocument(), false);
    
    //run pythoncode
    if (!pylib.Run(code, pybase, "mymodule", XPYCOMPILERINPUT_FILE)) {
        pylib.ErrPrint();
        String gc = "import gc\ngc.collect()\n";
        pylib.Execute(gc);
    }
    
    pylib.Free(pybase);
    pylib.FreeGIL(pyGIL);
    
    npArray.Set(pp, ss);
}


// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_PY_MODIFIER 1040024

//
// Register Plugin Object
//
Bool RegisterPyParticleModifier()
{
    return RegisterObjectPlugin(ID_PY_MODIFIER, "Py Particle Modifier", OBJECT_PARTICLEMODIFIER, PyParticleModifier::Alloc, "Oparticlemodifier", AutoBitmap("opython.png"), 0);
}
