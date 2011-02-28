#include "../../include/ModuleBase.h"

//public
ModuleBase::ModuleBase()
{
}

ModuleBase::~ModuleBase()
{
}


//init
void ModuleBase::BaseInit(ConfigReader* reader, Groups* g, Users* u)
{
	cf = reader;
	groups = g;
	users = u;
    hostname_str = reader->GetString("hostname");
    databasename_str = reader->GetString("databasename");
    username_str = reader->GetString("username");
    pass_str = reader->GetString("password");
}


void ModuleBase::stopthreadloop()
{
    runthreadloop = false;
}
