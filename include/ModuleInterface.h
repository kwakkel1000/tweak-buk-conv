#ifndef ModuleInterface_H
#define ModuleInterface_H
#include "ConfigReader.h"
#include "Group.h"

class ConfigReader;
class Group;
class ModuleInterface {

    public:

                ModuleInterface() { }
                virtual void BaseInit(ConfigReader* reader, Group* g)=0;
                virtual void threadloop()=0;
                virtual void stopthreadloop()=0;
                virtual void Init()=0;
};

typedef ModuleInterface* create_tmi();

typedef void destroy_tmi(ModuleInterface*);


#endif // ModuleInterface_H




