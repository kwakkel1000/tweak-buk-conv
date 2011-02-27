#ifndef GlobalBase_H
#define GlobalBase_H
#include "ConfigReader.h"
#include <vector>

class ConfigReader;
class GlobalBase
{

    public:

                GlobalBase();
                ~GlobalBase();
                //init
                virtual void GlobalInit(ConfigReader* reader);

    //private:
    protected:

                //class objecten
                ConfigReader* cf;

                //vars
                std::string hostname_str;
                std::string databasename_str;
                std::string username_str;
                std::string pass_str;

                //global functions

                //database
                std::vector< std::vector< std::string > > RawSqlSelect(std::string data);
                bool RawSql(std::string data);

                //other
                std::string convertToString(int);
                std::string convertToString(double);
                int convertToInt(std::string);
                double convertToDouble(std::string);

};

#endif // GlobalBase_H





