#ifndef ModuleBase_H
#define ModuleBase_H

#include <vector>
#include <string>
#include "ModuleInterface.h"
#include "Database.h"
#include "ConfigReader.h"

using namespace std;

class ConfigReader;
class ModuleBase : public ModuleInterface
{

    public:

                ModuleBase();
                ~ModuleBase();
                //init
                void BaseInit(ConfigReader* reader);

    //private:
    protected:

                //class objecten
                ConfigReader* cf;

                //vars
                std::string hostname_str;
                std::string databasename_str;
                std::string username_str;
                std::string pass_str;

				bool runthreadloop;

                //global functions

                //database
                std::vector< std::vector<std::string> > RawSqlSelect(std::string data);
                bool RawSql(std::string data);

                //other
                std::vector<std::string> lineout(std::vector<std::string> data, unsigned int rowamount, unsigned int length);
                std::string convertInt(int);
                int convertString(std::string);

};

#endif // ModuleBase_H




