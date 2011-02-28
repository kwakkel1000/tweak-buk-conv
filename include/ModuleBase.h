#ifndef ModuleBase_H
#define ModuleBase_H
#include "ModuleInterface.h"
#include "GlobalBase.h"

class ConfigReader;
class ModuleBase : public ModuleInterface, public GlobalBase
{

    public:

                ModuleBase();
                ~ModuleBase();
                //init
                virtual void BaseInit(ConfigReader* reader, Groups* g, Users* u);
				virtual void stopthreadloop();

    //private:
    protected:
                //vars
				bool runthreadloop;
                Groups* groups;
                Users* users;
};

#endif // ModuleBase_H




