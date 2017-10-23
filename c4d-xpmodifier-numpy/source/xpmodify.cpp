#include "c4d.h"
#include "c4d_symbols.h"
#include "main.h"
#include "oxpmodifier.h"
#include "c4d_string.h"

#include "lib_xp.h"
#include "conversion.h"

class XPModifier : public XPModifierObject
{
private:
    
public:
    virtual Bool Init(GeListNode* node);
    virtual Bool Message(GeListNode* node, Int32 type, void* t_data);
    Int32 GetProperties(BaseObject* op);
    virtual Bool InitModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Float timeDiff);
    virtual void FlushModifyXP();
    virtual Bool ModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Int32 startIndex, Int32 endIndex, Float timeDiff);
    static NodeData* Alloc(void) { return NewObjClear(XPModifier); }

};

Bool XPModifier::Init(GeListNode *node)
{
    BaseObject*		 op	= (BaseObject*)node;
    BaseContainer* data = op->GetDataInstance();
    
    data->SetBool(OXPMODIFIER_NUMPY, true);
    if (!testNumpy()) {
        data->SetBool(OXPMODIFIER_NUMPY, false);
    }
    
    // Set initial values
    data->SetBool(OXPMODIFIER_POSITION, true);
    data->SetBool(OXPMODIFIER_VELOCITY, true);
    data->SetBool(OXPMODIFIER_TIME, false);
    data->SetBool(OXPMODIFIER_LIFE, false);
    data->SetBool(OXPMODIFIER_COLOR, false);
    data->SetBool(OXPMODIFIER_RADIUS, false);
    data->SetBool(OXPMODIFIER_MASS, false);
    data->SetBool(OXPMODIFIER_SPEED, false);
    data->SetBool(OXPMODIFIER_GROUPID, false);
    data->SetBool(OXPMODIFIER_ID, false);
    data->SetBool(OXPMODIFIER_DENSITY, false);
    
    data->SetBool(OXPMODIFIER_DISPLAY, false);
    data->SetBool(OXPMODIFIER_MATRIX, false);
    data->SetBool(OXPMODIFIER_ROTATION, false);
    data->SetBool(OXPMODIFIER_DISTANCE, false);
    data->SetBool(OXPMODIFIER_SPIN, false);
    data->SetBool(OXPMODIFIER_TEMPERATURE, false);
    data->SetBool(OXPMODIFIER_FUEL, false);
    data->SetBool(OXPMODIFIER_FIRE, false);
    data->SetBool(OXPMODIFIER_SMOKE, false);
    data->SetBool(OXPMODIFIER_EXPANSION, false);
    data->SetBool(OXPMODIFIER_UVW, false);
    String s;   // python code
    s  = "import c4d\n";
    s += "import numpy as np\n\n";
    s += "# available variables:\n";
    s += "# op, doc, frame, dt, m(=op.GetMg())\n\n";
    s += "def setParticleCount():\n";
    s += "    count = 1000\n";
    s += "    return count\n\n";
    s += "X = Position\n";
    s += "V = Velocity\n";
    s += "V[:,2] -= X[:,2]";
    data->SetString(OXPMODIFIER_CODE, s);
    data->SetInt32(OXPMODIFIER_FRAME, 0);
    
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
            bc.SetString(CODEEDITOR_SETSTRING, data->GetString(OXPMODIFIER_CODE));
            bc.SetInt32(CODEEDITOR_SETMODE, SCRIPTMODE_PYTHON);
            
            res = bc;
            break;
        }
            
        case CODEEDITOR_SETSTRING:
        {
            GePythonGIL gil;
            data->SetString(OXPMODIFIER_CODE, msg.GetString(CODEEDITOR_SETSTRING));
            
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
            
            if (pylib.CheckSyntax(data->GetString(OXPMODIFIER_CODE), &err_row, &err_line, &err_string))
            {
                bc.SetInt32(CODEEDITOR_GETERROR_RES, true);
                bc.SetInt32(CODEEDITOR_GETERROR_LINE, -1);
                bc.SetInt32(CODEEDITOR_GETERROR_POS, -1);
            }
            else
            {
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
            return GeData(CUSTOMDATATYPE_DESCID, DescID(DescLevel(OXPMODIFIER_CODE)));
        }
    }
    
    return res;
}

Bool XPModifier::Message(GeListNode *node, Int32 type, void *data)
{
    switch (type) {
        case MSG_XPARTICLES_ISMODIFIER: {
            if (data != nullptr) {
                XPModifierMsgData *msgData = (XPModifierMsgData*)data;
                msgData->_flags |= XP_MODIFIERMSG_FLAG_PLUGIN_MODIFIER | XP_MODIFIERMSG_FLAG_PLUGIN_THREAD;
            }
        }
        case MSG_DESCRIPTION_COMMAND: {
            DescriptionCommand* dc = (DescriptionCommand*) data;
            if (dc->id[0].id == OXPMODIFIER_OPENEDITOR) {
                // get the text in the editor
                CodeEditor_Open((BaseList2D*)node, pythonCallback);
            }
        }
    }
    return true;
}

Int32 XPModifier::GetProperties(BaseObject* op) {
    Int32 PROPERTIES = 0, i=0, j=0;
    BaseContainer *bc = op->GetDataInstance();
    while (true)
    {
        const Int32 id = bc->GetIndexId(i++);
        if (id == NOTOK)
            break;
        else if (id > 3000 && id < 4000) {
            if (bc->GetBool(id)) PROPERTIES |= 1 << j;
            j++;
        }
    }
    return PROPERTIES;
}

Bool XPModifier::InitModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Float timeDiff)
{
    BaseContainer* bc = modObject->GetDataInstance();
    // if numpy is not installed, do not proceed
    if (!bc->GetBool(OXPMODIFIER_NUMPY))
        return false;
    
    return true;
}

void XPModifier::FlushModifyXP()
{
    
}


Bool XPModifier::ModifyXP(BaseDocument *doc, BaseObject *modObject, BaseContainer *modData, XPEmitterObject *emitter, Int32 startIndex, Int32 endIndex, Float timeDiff)
{
    
    BaseContainer* bc = modObject->GetDataInstance();
    
    // start bypass threading: speedup 150% (same as normal xpmodifier)
    Int32 frame = doc->GetTime().GetFrame(doc->GetFps());
    Int32 oldframe = bc->GetInt32(OXPMODIFIER_FRAME);
    if (frame == oldframe) {
        return true;
    }
    bc->SetInt32(OXPMODIFIER_FRAME, frame);
    // end bypass threading
    
    String code = bc->GetString(OXPMODIFIER_CODE);
    
    Int32 PROPERTIES = GetProperties(modObject);
    NumpyArray npArray = NumpyArray(emitter, PROPERTIES); // modObject
    npArray.SetMg(modObject);
    
    // python code here
    PythonLibrary pylib;
    PythonGIL *pyGIL = pylib.AllocGIL();
    PythonBase *pybase = pylib.Alloc();
    
    npArray.addNumpyArrays(pylib, pybase);
    pylib.SetInt32(pybase, "frame", frame);
    pylib.SetFloat(pybase, "dt", timeDiff);
    pylib.SetGeListNode(pybase, "op", modObject, false);
    pylib.SetGeListNode(pybase, "doc", modObject->GetDocument(), false);
    
    
    //run pythoncode
    if (!pylib.Run(code, pybase, "mymodule", XPYCOMPILERINPUT_FILE)) {
        pylib.ErrPrint();
        String gc = "import gc\ngc.collect()\n";
        pylib.Execute(gc);
    }
    
    pylib.Free(pybase);
    pylib.FreeGIL(pyGIL);
    
    npArray.Set(emitter);

    return true;
}

// be sure to use a unique ID obtained from www.plugincafe.com
#define ID_XP_MODIFIER 1040048

//
// Register Plugin Object
//
Bool RegisterXPModifier()
{
    return RegisterObjectPlugin(ID_XP_MODIFIER, "XP Modifier", OBJECT_PARTICLEMODIFIER, XPModifier::Alloc, "Oxpmodifier", AutoBitmap("opython.png"), 0);
}
