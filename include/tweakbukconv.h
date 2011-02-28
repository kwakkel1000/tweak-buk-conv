#ifndef tweakbukconv_h
#define tweakbukconv_h
#include "ModuleInterface.h"
#include <string>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

// Predefinitions
class ConfigReader;
class Groups;
class Users;
class tweakbukconv
{
public:
    tweakbukconv();
    ~tweakbukconv();

    void Init (string);
    void Run();

private:

	bool LoadModule(string);
	bool UnLoadModule(string);
    void LoadThreadLoop(int i);
	void GetGroupsDB();
	//database
	std::vector< std::vector< std::string > > RawSqlSelect(std::string data);
	bool RawSql(std::string data);



	//vars
	std::string hostname_str;
	std::string databasename_str;
	std::string username_str;
	std::string pass_str;

	//modules
	std::string moduledir;
	std::vector< std::string > modulelist;
	std::vector< void* > modulevector;
	std::vector< ModuleInterface* > moduleinterfacevector;
	std::vector< create_tmi* > createvector;
	std::vector< destroy_tmi* > destroyvector;
    std::vector< boost::shared_ptr< boost::thread> > module_thread_vector;

    ConfigReader* reader;
    Groups* groups;
    Users* users;

	bool tweakloop;
	void tweakrun();
    boost::shared_ptr<boost::thread> tweak_thread;
};


#endif // tweakbukconv_h

