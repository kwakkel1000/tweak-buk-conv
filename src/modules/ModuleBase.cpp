#include "../../include/ModuleBase.h"
#include "../../include/Database.h"
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <cstring>
#include <iostream>
//public
ModuleBase::ModuleBase()
{
}

//init
void ModuleBase::BaseInit(ConfigReader* reader)
{
	cf = reader;
    hostname_str = reader->GetString("hostname");
    databasename_str = reader->GetString("databasename");
    username_str = reader->GetString("username");
    pass_str = reader->GetString("password");
}


//protected

//mysql
std::vector< std::vector<std::string> > ModuleBase::RawSqlSelect(std::string data)
{
    cout << data << endl;
    database *db;
    std::vector< std::vector<std::string> > sql_result;
    db = new database();    // lol whut... connecting for each query? :'D
    int state = db->openConnection(hostname_str.c_str(), databasename_str.c_str(), username_str.c_str(), pass_str.c_str());
    if (state == 200)
    {
        sql_result = db->sql_query( data.c_str() );
    }
    else
    {
        cout << hostname_str << endl;
        cout << databasename_str << endl;
        cout << username_str << endl;
        cout << pass_str << endl;
        cout << "db fail " << state << endl;
		db->disconnect();
		delete db;
		exit(1);
    }
    db->disconnect();
    delete db;
    return sql_result;
}

bool ModuleBase::RawSql(std::string data)
{
    cout << data << endl;
    database *db;
    db = new database();    // lol whut... connecting for each query? :'D
    int state = db->openConnection(hostname_str.c_str(), databasename_str.c_str(), username_str.c_str(), pass_str.c_str());
    if (state == 200)
    {
        db->updateQuery( data.c_str() );
    }
    else
    {
        cout << hostname_str << endl;
        cout << databasename_str << endl;
        cout << username_str << endl;
        cout << pass_str << endl;
        cout << "db fail " << state << endl;
    }
    db->disconnect();
    delete db;
    return true;
}

std::vector<std::string> ModuleBase::lineout(std::vector<std::string> data, unsigned int rowamount, unsigned int length)
{
    std::vector<std::string> return_vector;
    std::string tmpvector;
    unsigned int k = 0;
    for (unsigned int j = 0; j < data.size(); j++)
    {
        if (k < rowamount)
        {
            tmpvector = tmpvector + data[j];
            for (unsigned int l = data[j].size(); l < length; l++)
            {
                tmpvector = tmpvector + " ";
            }
            k++;
        }
        if (k >= rowamount)
        {
            return_vector.push_back(tmpvector);
            tmpvector = "";
            k = 0;
        }
    }
    if (k != 0)
    {
        return_vector.push_back(tmpvector);
    }
    return return_vector;
}

std::string ModuleBase::convertInt(int number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

int ModuleBase::convertString(std::string data)
{
    int i;
    stringstream ss(data);//create a stringstream
    ss >> i;//add number to the stream
    return i;//return a string with the contents of the stream
}

