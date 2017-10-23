#include "c4d.h"
#include <string.h>
#include "main.h"
#include "c4d_libs/lib_py.h"

Bool PluginStart(void)
{
	//VERSIONTYPE versionType = GeGetVersionType();
    if (!RegisterXPModifier())
        return false;
    if (!RegisterPyParticleModifier())
        return false;

	return true;
}

void PluginEnd(void)
{
    
}

Bool PluginMessage(Int32 id, void* data)
{
    switch (id)
    {
        case C4DPL_INIT_SYS:
            if (!resource.Init())
                return false;		// don't start plugin without resource
            
            // register example datatype. This is happening at the earliest possible time
            
            // serial hook example; if used must be registered before PluginStart(), best in C4DPL_INIT_SYS
            
            return true;
            
        case C4DMSG_PRIORITY:
            //react to this message to set a plugin priority (to determine in which order plugins are initialized or loaded
            //SetPluginPriority(data, mypriority);
            return true;
            
        case C4DPL_BUILDMENU:
            //react to this message to dynamically enhance the menu
            //EnhanceMainMenu();
            break;
            
        case C4DPL_COMMANDLINEARGS:
            //sample implementation of command line rendering:
            //CommandLineRendering((C4DPL_CommandLineArgs*)data);
            
            //react to this message to react to command line arguments on startup
            break;
            
        case C4DPL_EDITIMAGE:
             // editimage->return_processed = true; if image was processed
            return false;
        case C4DPL_PYINITTYPES:
            return true;
        case C4DPL_PYINITIALIZE:
            return true;
        case C4DPL_PYENDPLUGINS:
            return true;
        case C4DPL_PYFINALIZE:
            return true;
    }
    
    return false;
}