#include "../../include/TweakZoneConvert.h"
#include "../../include/GlobalBase.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <cstring>


extern "C" ModuleInterface* create()
{
    return new TweakZoneConvert;
}

extern "C" void destroy(ModuleInterface* x)
{
    delete x;
}

TweakZoneConvert::TweakZoneConvert()
{
}

TweakZoneConvert::~TweakZoneConvert()
{
}

void TweakZoneConvert::Init()
{
	regionfile = cf->GetString("regionfile");
    runthreadloop = true;
}

void TweakZoneConvert::threadloop()
{
	GetGroupsDB();
	GetZoneDataDB();
	ParseZoneDataDB();
    /*while (runthreadloop)
    {
    	usleep(1000000);
    }*/
    cout << "void TweakZoneConvert::threadloop() end" << endl;
}

void TweakZoneConvert::GetGroupsDB()
{
	std::vector< std::vector< std::string > > sql_result;
    std::string sql_string = "SELECT groups.name from groups;";
    sql_result = RawSqlSelect(sql_string);
    unsigned int i;
    for (i = 0 ; i < sql_result.size() ; i++)
    {
    	if (sql_result[i].size() == 1)
    	{
			groups.push_back(sql_result[i][0]);
    	}
    	else
    	{
    		std::cout << "onverwacht resultaat vector.size(): " << sql_result[i].size() << std::endl;
    	}
    }
}

void TweakZoneConvert::GetZoneDataDB()
{
	std::vector< std::vector< std::string > > sql_result;
    std::string sql_string = "SELECT zones.id, zones.name, zones.minz, zones.maxz, zones_vertices.x, zones_vertices.y, zones.admins, zones.users, zones.enablehealth, zones.allowdynamite FROM zones INNER JOIN zones_vertices ON zones.id = zones_vertices.id;";
    sql_result = RawSqlSelect(sql_string);
    unsigned int i;
    for (i = 0 ; i < sql_result.size() ; i++)
    {
    	if (sql_result[i].size() == 10)
    	{
			add_zone(sql_result[i][0], sql_result[i][1], sql_result[i][2], sql_result[i][3], sql_result[i][8], sql_result[i][9]);
			add_zone_vertice(sql_result[i][0], sql_result[i][4], sql_result[i][5]);
			add_zone_users(sql_result[i][0], sql_result[i][6], sql_result[i][7]);
    	}
    	else
    	{
    		std::cout << "onverwacht resultaat vector.size(): " << sql_result[i].size() << std::endl;
    	}
    }
}

void TweakZoneConvert::ParseZoneDataDB()
{
	//"gunthertest","cuboid","-77","9","504","-63","16","515","0","u:guntherdw","",""

//	{
//	"cRegions":{
//	"shutup":{
//	"min":{"x":-2266.0,"y":63.0,"z":-1138.0},
//	"max":{"x":-2263.0,"y":63.0,"z":-1133.0},
//	"id":"shutup",
//	"priority":0,
//	"owners":{"groups":["vip"],"players":["guntherdw"]},
//	"members":{"groups":[],"players":[]},
//	"flags":{
//	"flags":{
//	"eal":{},
//	"msg":{}
//	}
//	}
//	},
//	"ohyeah":{
//	"min":{"x":-2258.0,"y":63.0,"z":-1145.0},
//	"max":{"x":-2253.0,"y":81.0,"z":-1138.0},
//	"id":"ohyeah",
//	"priority":0,
//	"owners":{"groups":["serveradmin"],"players":["guntherdw"]},
//	"members":{"groups":[],"players":[]},
//	"flags":{
//	"flags":{
//	"iconomy":{},
//	"spawn":{},
//	"heal":{},
//	"states":{},
//	"creaturespawn":{},
//	"msg":{}
//	}
//	}
//	}
//	},
//	"pRegions":{}
//	}



//
//<GuntherDW>         flagList = new ArrayList<FlagInfo>();
//<GuntherDW>         flagList.add(new FlagInfo("msg", "g", FlagValueType.STRING, "msg", "g"));
//<GuntherDW>         flagList.add(new FlagInfo("msg", "f", FlagValueType.STRING, "msg", "f"));
//<GuntherDW>         flagList.add(new FlagInfo("denyspawn", "*", FlagValueType.STRING, "creaturespawn", "*"));
//<GuntherDW>         flagList.add(new FlagInfo("heal", "delay", FlagValueType.INT, "heal", "delay"));
//<GuntherDW>         flagList.add(new FlagInfo("heal", "amount", FlagValueType.INT, "heal", "amount"));
//<GuntherDW>         flagList.add(new FlagInfo("passthrough", null, FlagValueType.STATE, "states", "passthrough"));
//<GuntherDW>         flagList.add(new FlagInfo("build", null, FlagValueType.STATE, "states", "build"));
//<GuntherDW>         flagList.add(new FlagInfo("pvp", null, FlagValueType.STATE, "states", "pvp"));
//<GuntherDW>         flagList.add(new FlagInfo("mobdamage", null, FlagValueType.STATE, "states", "mobdamage"));
//<GuntherDW>         flagList.add(new FlagInfo("creeper", null, FlagValueType.STATE, "states", "creeper"));
//<GuntherDW>         flagList.add(new FlagInfo("tnt", null, FlagValueType.STATE, "states", "tnt"));
//<GuntherDW>         flagList.add(new FlagInfo("lighter", null, FlagValueType.STATE, "states", "lighter"));
//<GuntherDW>         flagList.add(new FlagInfo("firespread", null, FlagValueType.STATE, "states", "firespread"));
//<GuntherDW>         flagList.add(new FlagInfo("lavafirespread", null, FlagValueType.STATE, "states", "lavafirespread"));
//<GuntherDW>         flagList.add(new FlagInfo("chest", null, FlagValueType.STATE, "states", "chest"));
//<GuntherDW>         flagList.add(new FlagInfo("waterflow", null, FlagValueType.STATE, "states", "waterflow"));
//<GuntherDW>         flagList.add(new FlagInfo("iconomy", "buyable", FlagValueType.BOOLEAN, "iconomy", "buyable"));
//<GuntherDW>         flagList.add(new FlagInfo("iconomy", "price", FlagValueType.INT, "iconomy", "price"));
//<GuntherDW>         flagList.add(new FlagInfo("spawn", "set", FlagValueType.LOCATION, "spawn", ""));
//<GuntherDW>         flagList.add(new FlagInfo("spawn", "delete", FlagValueType.LOCATION, "spawn", ""));
//<GuntherDW>         flagList.add(new FlagInfo("spawn", "allow", FlagValueType.STRING, "spawn", "allow"));
//<GuntherDW>         flagList.add(new FlagInfo("spawn", "deny", FlagValueType.STRING, "spawn", "deny"));
//<GuntherDW>         flagList.add(new FlagInfo("teleport", "set", FlagValueType.LOCATION, "teleport", ""));
//<GuntherDW>         flagList.add(new FlagInfo("teleport", "delete", FlagValueType.LOCATION, "teleport", ""));
//<GuntherDW>         flagList.add(new FlagInfo("teleport", "allow", FlagValueType.STRING, "teleport", "allow"));
//<GuntherDW>         flagList.add(new FlagInfo("teleport", "deny", FlagValueType.STRING, "teleport", "deny"));


//"flags":{"flags":{"msg":{"f":"exited kwakkel","g":"entered kwakkel"},"heal":{},"states":{"waterflow":"ALLOW"},"creaturespawn":{},"iconomy":{},"spawn":{},"teleport":{}}}
	ofstream SaveFile(regionfile.c_str(),ios::out | ios::trunc);
	SaveFile << "{\"cRegions\":{";
	for (unsigned int i = 0; i < Zones.size(); i++)
	{
		std::vector< double > x = Zones[i].get_x();
		std::vector< double > y = Zones[i].get_y();
		/*cout << Zones[i].get_name() << " zmin:" << Zones[i].get_zmin() << " zmax:" << Zones[i].get_zmax() << " vertices:" << x.size() << endl;
		for (unsigned int j = 0; j < x.size(); j++)
		{
			cout << "x: " << x[j] << " y: " << y[j] << endl;
		}*/
		if (x.size() >= 2)
		{
			std::string name = Zones[i].get_name();
			boost::replace_all ( name, " ", "_" );
			boost::to_lower(name);
			std::string allow_tnt;
			std::string allow_creeper;
			std::string allow_waterflow;
			std::string allow_pvp;
			std::string allow_mobdamage;
			std::string owners;
			std::string members;
			std::string x_min;
			std::string x_max;
			std::string y_min;
			std::string y_max;
			std::vector< std::string > owners_group;
			std::vector< std::string > owners_player;
			std::vector< std::string > members_group;
			std::vector< std::string > members_player;
			std::vector< std::string > admins;
			admins = Zones[i].get_admins();
			std::vector< std::string > users;
			users = Zones[i].get_users();
			double tmp_x_min = x[0];
			double tmp_x_max = x[0];
			double tmp_y_min = y[0];
			double tmp_y_max = y[0];
			for (unsigned int x_it = 0; x_it < x.size(); x_it++)
			{
				if (tmp_x_min > x[x_it])
				{
					tmp_x_min = x[x_it];
				}
				if (tmp_x_max < x[x_it])
				{
					tmp_x_max = x[x_it];
				}
			}
			for (unsigned int y_it = 0; y_it < y.size(); y_it++)
			{
				if (tmp_y_min > y[y_it])
				{
					tmp_y_min = y[y_it];
				}
				if (tmp_y_max < y[y_it])
				{
					tmp_y_max = y[y_it];
				}
			}
			x_min = convertToString(tmp_x_min);
			x_max = convertToString(tmp_x_max);
			y_min = convertToString(tmp_y_min);
			y_max = convertToString(tmp_y_max);
			if (admins.size() > 0)
			{
				for (unsigned int admin_access_it = 0; admin_access_it < admins.size() ; admin_access_it++)
				{
					bool isgroup = false;
					for (unsigned int group_it = 0; group_it < groups.size(); group_it++)
					{
						if (boost::iequals(admins[admin_access_it], groups[group_it]))
						{
							isgroup = true;
						}
					}
					if (isgroup)
					{
						owners_group.push_back(admins[admin_access_it]);
					}
					else
					{
						owners_player.push_back(admins[admin_access_it]);
					}
				}
			}
			if (users.size() > 0)
			{
				for (unsigned int user_access_it = 0; user_access_it < users.size() ; user_access_it++)
				{
					bool isgroup = false;
					for (unsigned int group_it = 0; group_it < groups.size(); group_it++)
					{
						if (boost::iequals(users[user_access_it], groups[group_it]))
						{
							isgroup = true;
						}
					}
					if (isgroup)
					{
						members_group.push_back(users[user_access_it]);
					}
					else
					{
						members_player.push_back(users[user_access_it]);
					}
				}
			}
			owners = "\"owners\":{";
			owners = owners + "\"groups\":[";
			if (owners_group.size() > 1)
			{
				for (unsigned int owners_group_it = 1; owners_group_it < owners_group.size() ; owners_group_it++)
				{
					owners = owners + "\"" + owners_group[owners_group_it] + "\",";
				}
			}
			if (owners_group.size() > 0)
			{
				owners = owners + "\"" + owners_group[0] + "\"";
			}
			owners = owners + "],";
			owners = owners + "\"players\":[";
			if (owners_player.size() > 1)
			{
				for (unsigned int owners_player_it = 1; owners_player_it < owners_player.size() ; owners_player_it++)
				{
					owners = owners + "\"" + owners_player[owners_player_it] + "\",";
				}
			}
			if (owners_player.size() > 0)
			{
				owners = owners + "\"" + owners_player[0] + "\"";
			}
			owners = owners + "]},";
			members = "\"members\":{";
			members = members + "\"groups\":[";
			if (members_group.size() > 1)
			{
				for (unsigned int members_group_it = 1; members_group_it < members_group.size() ; members_group_it++)
				{
					members = members + "\"" + members_group[members_group_it] + "\",";
				}
			}
			if (members_group.size() > 0)
			{
				members = members + "\"" + members_group[0] + "\"";
			}
			members = members + "],";
			members = members + "\"players\":[";
			if (members_player.size() > 1)
			{
				for (unsigned int members_player_it = 1; members_player_it < members_player.size() ; members_player_it++)
				{
					members = members + "\"" + members_player[members_player_it] + "\",";
				}
			}
			if (members_player.size() > 0)
			{
				members = members + "\"" + members_player[0] + "\"";
			}
			members = members + "]},";
			if (Zones[i].get_tnt() == "1")
			{
				allow_tnt = "\"tnt\":\"ALLOW\"";
			}
			else
			{
				allow_tnt = "\"tnt\":\"DENY\"";
			}
			if (Zones[i].get_health() == "1")
			{
				allow_pvp = "\"pvp\":\"ALLOW\"";
				allow_mobdamage = "\"mobdamage\":\"ALLOW\"";
			}
			else
			{
				allow_pvp = "\"pvp\":\"DENY\"";
				allow_mobdamage = "\"mobdamage\":\"DENY\"";
			}
			allow_creeper = "\"creeper\":\"NONE\"";
			allow_waterflow = "\"waterflow\":\"DENY\"";
			std::string put_string = "";
			put_string = put_string + "\"" + name + "\":{";
			put_string = put_string + "\"min\":{";
			put_string = put_string + "\"x\":" + x_min + ".0,";
			put_string = put_string + "\"y\":" + Zones[i].get_zmin() + ".0,";
			put_string = put_string + "\"z\":" + y_min + ".0},";
			put_string = put_string + "\"max\":{";
			put_string = put_string + "\"x\":" + x_max + ".0,";
			put_string = put_string + "\"y\":" + Zones[i].get_zmax() + ".0,";
			put_string = put_string + "\"z\":" + y_max + ".0},";
			put_string = put_string + "\"id\": \"" + name + "\",";
			put_string = put_string + "\"priority\":0,";
			put_string = put_string + owners;
			put_string = put_string + members;
			put_string = put_string + "\"flags\":{";
			put_string = put_string + "\"flags\":{";
			put_string = put_string + "\"msg\":{\"f\":\"exited " + Zones[i].get_name() + "\",\"g\":\"entered " + Zones[i].get_name() + "\"},";
			put_string = put_string + "\"states\":{";
			put_string = put_string + allow_tnt;
			put_string = put_string + ",";
			put_string = put_string + allow_creeper;
			put_string = put_string + ",";
			put_string = put_string + allow_waterflow;
			put_string = put_string + ",";
			put_string = put_string + allow_pvp;
			put_string = put_string + ",";
			put_string = put_string + allow_mobdamage;
			put_string = put_string + "}";
			put_string = put_string + "}";
			put_string = put_string + "}";
			if (i == Zones.size()-1)
			{
				put_string = put_string + "}";
			}
			else
			{
				put_string = put_string + "},";
			}
			cout << put_string << endl;
			SaveFile << put_string;
		}
	}
	SaveFile << "},\"pRegions\":{}}";
	SaveFile.close();
}

//	hey0
//	ofstream SaveFile("region.txt",ios::out | ios::trunc);
//	for (unsigned int i = 0; i < Zones.size(); i++)
//	{
//		std::vector< std::string > x = Zones[i].get_x();
//		std::vector< std::string > y = Zones[i].get_y();
//		cout << Zones[i].get_name() << " zmin:" << Zones[i].get_zmin() << " zmax:" << Zones[i].get_zmax() << " vertices:" << x.size() << endl;
//		for (unsigned int j = 0; j < x.size(); j++)
//		{
//			cout << "x: " << x[j] << " y: " << y[j] << endl;
//		}
//		if (x.size() == 2)
//		{
//			std::string access;
//			std::string flags = "-z-l-f-F";
//			std::vector< std::string > admins;
//			admins = Zones[i].get_admins();
//			std::vector< std::string > users;
//			users = Zones[i].get_users();
//			if (admins.size() > 0)
//			{
//				for (unsigned int admin_access_it = admins.size()-1; admin_access_it > 0 ; admin_access_it--)
//				{
//					access = access + "u:" + admins[admin_access_it] + ",";
//				}
//				access = access + "u:" + admins[0];
//				access = access + ",";
//			}
//			if (users.size() > 0)
//			{
//				for (unsigned int user_access_it = users.size()-1; user_access_it > 0 ; user_access_it--)
//				{
//					access = access + "u:" + users[user_access_it] + ",";
//				}
//				access = access + "u:" + users[0];
//			}
//			flags = flags + Zones[i].get_tnt();
//			flags = flags + Zones[i].get_health();
//			std::string put_string;
//			put_string = "\"" + Zones[i].get_name() + "\",";
//			put_string = put_string + "\"cuboid\",";
//			put_string = put_string + "\"" + x[0] + "\",";
//			put_string = put_string + "\"" + Zones[i].get_zmin() + "\",";
//			put_string = put_string + "\"" + y[0] + "\",";
//			put_string = put_string + "\"" + x[1] + "\",";
//			put_string = put_string + "\"" + Zones[i].get_zmax() + "\",";
//			put_string = put_string + "\"" + y[1] + "\",";
//			put_string = put_string + "\"0\",";
//			put_string = put_string + "\"" + access + "\",";
//			put_string = put_string + "\"" + flags + "\",";
//			put_string = put_string + "\"now entering: " + Zones[i].get_name() + "\"";
//			cout << put_string << endl;
//			SaveFile << put_string << endl;
//		}
//	}
//	SaveFile.close();

void TweakZoneConvert::add_zone(std::string id, std::string name, std::string minz, std::string maxz, std::string tnt, std::string health)
{
    int i = get_zone(id);
    if (i == -1)
    {
        ZoneIds.push_back(id);
        Zone *tmpzone = new Zone();
        tmpzone->init(id, name, tnt, health);
        tmpzone->set_z(minz, maxz);
        Zones.push_back (*tmpzone);
    }
}

void TweakZoneConvert::add_zone_vertice(std::string id, std::string x, std::string y)
{
    int i = get_zone(id);
    if (i != -1)
    {
    	Zones[i].add_vertice(x, y);
    }
}

void TweakZoneConvert::add_zone_users(std::string id, std::string m_admins, std::string m_users)
{
    int i = get_zone(id);
    if (i != -1)
    {
    	std::vector<std::string> admins;
		boost::split( admins, m_admins, boost::is_any_of(";"), boost::token_compress_on );
		for (unsigned int admins_it = 0; admins_it < admins.size(); admins_it++)
		{
			std::vector<std::string> admin;
			boost::split( admin, admins[admins_it], boost::is_any_of(","), boost::token_compress_on );
			if (admin.size() == 2)
			{
				Zones[i].add_admin(admin[1]);
				cout << admin[1] << " ";
			}
		}
		cout << endl;
    	std::vector<std::string> users;
		boost::split( users, m_users, boost::is_any_of(";"), boost::token_compress_on );
		for (unsigned int users_it = 0; users_it < users.size(); users_it++)
		{
			std::vector<std::string> user;
			boost::split( user, users[users_it], boost::is_any_of(","), boost::token_compress_on );
			if (user.size() == 3)
			{
				if (user[2] == "*")
				{
					Zones[i].add_user(user[1]);
					cout << user[1] << " ";
				}
			}
		}
		cout << endl;
    }
}



int TweakZoneConvert::get_zone(std::string id)
{
	for ( unsigned int i = 0 ; i < ZoneIds.size(); i++ )
    {
        if (boost::iequals(ZoneIds[i], id))
        {
            return i;
        }
    }
	return -1;
}
