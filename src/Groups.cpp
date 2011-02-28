#include "../include/Groups.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

Groups::Groups()
{
    NULLvector.push_back("NULL");
}

Groups::~Groups()
{
    for ( unsigned int i = name.size() -1; 0 >= i; i-- )
    {
        std::cout << "DELETED: NAME: " << name[i]  << std::endl;
        name.erase(name.begin()+i);
        delete g[i];
        g.erase(g.begin()+i);
    }
}

bool Groups::AddGroup(std::string m_name)
{
    boost::mutex::scoped_lock  lock(Group_mutex);
    int i = GetNameIndex(m_name);
    if (i == -1)
    {
        name.push_back (m_name);
        Group *tmpgroup = new Group();
        g.push_back (tmpgroup);
        return true;
    }
    return false;
}

bool Groups::DelGroup(std::string m_name)
{
    boost::mutex::scoped_lock  lock(Group_mutex);
    int i = GetNameIndex(m_name);
    if (i >= 0)
    {
        name.erase(name.begin()+i);
        g[i]->~Group();
        g.erase(g.begin()+i);
        return true;
    }
    return false;
}

bool Groups::group_init(std::string m_id, std::string m_name, std::string m_admin, std::string m_canmodifyworld, std::string m_defaultgroup, std::string m_ignorerestrictions)
{
	int GroupIndex = GetNameIndex(m_name);
	if (GroupIndex >= 0)
	{
		g[GroupIndex]->init(m_id, m_name, m_admin, m_canmodifyworld, m_defaultgroup, m_ignorerestrictions);
		return true;
	}
	return false;
}

bool Groups::group_add_commands(std::string m_name, std::string m_commands)
{
	int GroupIndex = GetNameIndex(m_name);
	if (GroupIndex >= 0)
	{
		//g[GroupIndex]->add_commands(m_commands);
		return true;
	}
	return false;
}

bool Groups::group_add_parent(std::string m_name, std::string m_parent)
{
	int GroupIndex = GetNameIndex(m_name);
	if (GroupIndex >= 0)
	{
		g[GroupIndex]->add_inherit_group(m_parent);
		return true;
	}
	return false;
}

std::vector< std::string > Groups::GetGroups()
{
	return name;
}

std::string Groups::group_get_parent(std::string m_name)
{
	int GroupIndex = GetNameIndex(m_name);
	if (GroupIndex >= 0)
	{
		return g[GroupIndex]->get_inheritedgroup();
	}
	return "NULL";
}

bool Groups::is_group(std::string m_name)
{
	if (GetNameIndex(m_name) >= 0)
	{
		return true;
	}
	return false;
}

int Groups::GetNameIndex(std::string m_name)
{
    for ( unsigned int i = 0 ; i < name.size(); i++ )
    {
        if (boost::iequals(name[i],m_name))
        {
            return i;
        }
    }
    return -1;
}

