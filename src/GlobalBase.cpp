#include "../include/GlobalBase.h"
#include "../include/Database.h"
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <cstring>
#include <iostream>
//public
GlobalBase::GlobalBase()
{
}

GlobalBase::~GlobalBase()
{
}

//init
void GlobalBase::GlobalInit(ConfigReader* reader)
{
	cf = reader;
    hostname_str = reader->GetString("hostname");
    databasename_str = reader->GetString("databasename");
    username_str = reader->GetString("username");
    pass_str = reader->GetString("password");
}
//protected

//mysql
std::vector< std::vector< std::string > > GlobalBase::RawSqlSelect(std::string data)
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

bool GlobalBase::RawSql(std::string data)
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

std::string GlobalBase::convertToString(int number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

std::string GlobalBase::convertToString(double number)
{
    stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

int GlobalBase::convertToInt(std::string data)
{
    int i;
    stringstream ss(data);//create a stringstream
    ss >> i;//add number to the stream
    return i;//return a string with the contents of the stream
}

double GlobalBase::convertToDouble(std::string data)
{
    double i;
    stringstream ss(data);//create a stringstream
    ss >> i;//add number to the stream
    return i;//return a string with the contents of the stream
}


