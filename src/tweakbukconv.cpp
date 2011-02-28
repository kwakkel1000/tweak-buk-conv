#include "../include/tweakbukconv.h"
#include "../include/ConfigReader.h"
#include "../include/Database.h"
#include <iostream>
#include <cstring>
#include <dlfcn.h>
#include <boost/algorithm/string.hpp>

tweakbukconv::tweakbukconv()
// Initialize all member vars! std::string's will just use their default constructor
: reader( NULL )
{
}

tweakbukconv::~tweakbukconv()
{
    std::cout << "tweakbukconv::~tweakbukconv() begin" << std::endl;
	tweakloop = false;
    delete reader;
    for (unsigned int i = modulelist.size(); i > 0; i--)
    {
        UnLoadModule(modulelist[i-1]);
    }
    std::cout << "tweakbukconv::~tweakbukconv() end" << std::endl;
}

void tweakbukconv::Init(std::string configfile)
{
    reader = new ConfigReader();
    groups = new Groups();
    users = new Users();
    if (reader->ReadFile(configfile))
    {
        std::cout << "W00p config is gelezen \\o/" << std::endl;
    }
    else
    {
        std::cout << "Kon niet lezen :/" << std::endl;
    }

    std::string loadmodsstr;
    loadmodsstr = reader->GetString("loadmods");
    moduledir = reader->GetString("moduledir");
    hostname_str = reader->GetString("hostname");
    databasename_str = reader->GetString("databasename");
    username_str = reader->GetString("username");
    pass_str = reader->GetString("password");
	GetGroupsDB();
    std::vector< std::string > loadmods;
    boost::split( loadmods, loadmodsstr, boost::is_any_of(" "), boost::token_compress_on );
    for (unsigned int i = 0; i < loadmods.size(); i++)
    {
        LoadModule(loadmods[i]);
    }
    tweakloop = true;
    assert(!tweak_thread);
    tweak_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tweakbukconv::tweakrun, this)));
}

bool tweakbukconv::LoadModule(std::string modulename)
{
    bool loaded = false;
    for (unsigned int i = 0; i < modulelist.size(); i++)
    {
        if (modulelist[i] == modulename)
        {
            loaded = true;
        }
    }
    if (!loaded)
    {
        ModuleInterface* mi;
        void* module;
        create_tmi* create_module;
        destroy_tmi* destroy_module;
        std::string modulepath = "./" + moduledir + modulename + ".so";
        // load the library
        module = dlopen(modulepath.c_str(), RTLD_LAZY);
        if (!module) {
            std::cerr << "Cannot load library: " << dlerror() << '\n';
            return false;
			exit(1);
        }

        // load the symbols
        create_module = (create_tmi*) dlsym(module, "create");
        destroy_module = (destroy_tmi*) dlsym(module, "destroy");
        if (!create_module || !destroy_module) {
            cerr << "Cannot load symbols: " << dlerror() << '\n';
            return false;
			exit(1);
        }
        std::cout << "Module " << modulename << " Loaded" << std::endl;
        // create an instance of the class
        mi = create_module();
        mi->BaseInit(reader, groups, users);
        mi->Init();
        modulelist.push_back(modulename);
        modulevector.push_back(module);
        moduleinterfacevector.push_back(mi);
        createvector.push_back(create_module);
        destroyvector.push_back(destroy_module);
        boost::shared_ptr<boost::thread> tmp_thread;
        int modi = -1;
        for (unsigned int i = 0; i < modulelist.size(); i++)
        {
            if (modulelist[i] == modulename)
            {
                modi = i;
            }
        }
        if (modi >= 0)
        {
            assert(!tmp_thread);
            tmp_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tweakbukconv::LoadThreadLoop, this, modi)));
            module_thread_vector.push_back(tmp_thread);
        }
        return true;
    }
    std::cout << "module " << modulename  << " already loaded" << std::endl;
    return false;
}


bool tweakbukconv::UnLoadModule(std::string modulename)
{
    int modi = -1;
    for (unsigned int i = 0; i < modulelist.size(); i++)
    {
        if (modulelist[i] == modulename)
        {
            modi = i;
        }
    }
    if (modi >= 0)
    {
        moduleinterfacevector[modi]->stopthreadloop();
        module_thread_vector[modi]->join();
        module_thread_vector.erase(module_thread_vector.begin()+modi);
        destroyvector[modi](moduleinterfacevector[modi]);
        dlclose(modulevector[modi]);
        modulelist.erase(modulelist.begin()+modi);
        modulevector.erase(modulevector.begin()+modi);
        moduleinterfacevector.erase(moduleinterfacevector.begin()+modi);
        createvector.erase(createvector.begin()+modi);
        destroyvector.erase(destroyvector.begin()+modi);
        std::cout << modulename << " UnLoaded" << std::endl;
        return true;
    }
    return false;
}

void tweakbukconv::LoadThreadLoop(int i)
{
    moduleinterfacevector[i]->threadloop();
}

void tweakbukconv::Run()
{
    tweak_thread->join();
}

void tweakbukconv::tweakrun()
{
	/*while(tweakloop)
	{
		usleep(1000000);
	}*/
    std::cout << "void tweakbukconv::tweakrun() end" << std::endl;
}

void tweakbukconv::GetGroupsDB()
{
	std::vector< std::vector< std::string > > sql_result;
    std::string sql_string = "SELECT groups.id, groups.name, groups.admin, groups.canmodifyworld, groups.defaultgroup, groups.ignoresrestrictions, groups.commands, groups.inheritedgroups from groups;";
    sql_result = RawSqlSelect(sql_string);
    unsigned int i;
    for (i = 0 ; i < sql_result.size() ; i++)
    {
    	if (sql_result[i].size() == 8)
    	{
    		groups->AddGroup(sql_result[i][1]);
    		groups->group_init(sql_result[i][0], sql_result[i][1], sql_result[i][2], sql_result[i][3], sql_result[i][4], sql_result[i][5]);
    		groups->group_add_commands(sql_result[i][1], sql_result[i][6]);
    		groups->group_add_parent(sql_result[i][1], sql_result[i][7]);
    	}
    	else
    	{
    		std::cout << "onverwacht resultaat vector.size(): " << sql_result[i].size() << std::endl;
    	}
    }
}
//mysql
std::vector< std::vector< std::string > > tweakbukconv::RawSqlSelect(std::string data)
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

bool tweakbukconv::RawSql(std::string data)
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
