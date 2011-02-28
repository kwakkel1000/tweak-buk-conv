#ifndef TweakZoneConvert_h
#define TweakZoneConvert_h
#include "ModuleBase.h"
#include "Zone.h"

// Predefinitions
class Zone;
class TweakZoneConvert	: 	public ModuleBase
{
public:
    TweakZoneConvert();
    ~TweakZoneConvert();
    void threadloop();
    void Init();

private:

	//vars
	std::string regionfile;
	std::vector< std::string > ZoneIds;
	std::vector< Zone > Zones;

	//functions
	void GetZoneDataDB();
	void ParseZoneDataDB();
	void add_zone(std::string id, std::string name, std::string minz, std::string maxz, std::string tnt, std::string health);
	void add_zone_vertice(std::string id, std::string x, std::string y);
	void add_zone_users(std::string id, std::string m_admins, std::string m_users);
	int get_zone(std::string id);
};

#endif // TweakZoneConvert_h

