#include "../../include/Zone.h"
#include <boost/algorithm/string.hpp>
#include <iostream>


Zone::Zone()
{

}

Zone::~Zone()
{

}

void Zone::init(std::string m_id, std::string m_name, std::string m_tnt, std::string m_health)
{
	id = m_id;
	name = m_name;
	tnt = m_tnt;
	health = m_health;
}

void Zone::set_z(std::string minz, std::string maxz)
{
	zmin = minz;
	zmax = maxz;
}

void Zone::add_vertice(std::string m_x, std::string m_y)
{
	x.push_back(convertToDouble(m_x));
	y.push_back(convertToDouble(m_y));
}

void Zone::add_admin(std::string m_user)
{
	bool added = false;
	for ( unsigned int i = 0 ; i < admins.size(); i++ )
    {
        if (boost::iequals(admins[i], m_user))
        {
            added = true;
        }
    }
    if (!added)
    {
		admins.push_back(m_user);
    }
}

void Zone::add_user(std::string m_user)
{
	bool added = false;
	for ( unsigned int i = 0 ; i < users.size(); i++ )
    {
        if (boost::iequals(users[i], m_user))
        {
            added = true;
        }
    }
    if (!added)
    {
		users.push_back(m_user);
    }
}

std::string Zone::get_id()
{
	return id;
}

std::string Zone::get_name()
{
	return name;
}

std::string Zone::get_tnt()
{
	return tnt;
}

std::string Zone::get_health()
{
	return health;
}

std::string Zone::get_zmin()
{
	return zmin;
}

std::string Zone::get_zmax()
{
	return zmax;
}

std::vector< double > Zone::get_x()
{
	return x;
}

std::vector< double > Zone::get_y()
{
	return y;
}

std::vector< std::string > Zone::get_admins()
{
	return admins;
}

std::vector< std::string > Zone::get_users()
{
	return users;
}
