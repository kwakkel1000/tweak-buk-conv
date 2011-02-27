#ifndef tweakbukconv_h
#define tweakbukconv_h
#include "ModuleInterface.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <dlfcn.h>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

// Predefinitions
class ConfigReader;
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

	//modules
	std::string moduledir;
	std::vector< std::string > modulelist;
	std::vector< void* > modulevector;
	std::vector< ModuleInterface* > moduleinterfacevector;
	std::vector< create_tmi* > createvector;
	std::vector< destroy_tmi* > destroyvector;
    std::vector< boost::shared_ptr< boost::thread> > module_thread_vector;

    ConfigReader* reader;


	bool tweakloop;
	void tweakrun();
    boost::shared_ptr<boost::thread> tweak_thread;
};


#endif // tweakbukconv_h

