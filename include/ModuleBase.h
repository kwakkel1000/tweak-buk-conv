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
                virtual void BaseInit(ConfigReader* reader, Group* g, User* u);
				virtual void stopthreadloop();

    //private:
    protected:
                //vars
				bool runthreadloop;
                Group* group;
                User* user;
};

#endif // ModuleBase_H




