#ifndef TweakPermissionsConvert_h
#define TweakPermissionsConvert_h
#include "ModuleBase.h"

// Predefinitions
class TweakPermissionsConvert	: 	public ModuleBase
{
public:
    TweakPermissionsConvert();
    ~TweakPermissionsConvert();
    void threadloop();
    void stopthreadloop();
    void Init();

private:

	//vars
	std::string regionfile;
	std::vector< std::string > ZoneIds;
	std::vector< Zone > Zones;
	std::vector< std::string > groups;

	//functions
	void GetGroupsDB();
	void GetZoneDataDB();
	void ParseZoneDataDB();
	void add_zone(std::string id, std::string name, std::string minz, std::string maxz, std::string tnt, std::string health);
	void add_zone_vertice(std::string id, std::string x, std::string y);
	void add_zone_users(std::string id, std::string m_admins, std::string m_users);
	int get_zone(std::string id);
};

#endif // TweakPermissionsConvert_h


