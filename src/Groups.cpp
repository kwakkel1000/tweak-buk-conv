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
		cout << "group: " << m_name << " has parent: " << m_parent << endl;
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

std::vector< std::string > Groups::group_get_childs(std::string m_name)
{
	std::vector< std::string > childs;
	int GroupIndex = GetNameIndex(m_name);
	if (GroupIndex >= 0)
	{
		for (unsigned int group_it = 0; group_it < g.size(); group_it++)
		{
			if (boost::iequals(g[group_it]->get_inheritedgroup(),m_name))
			{
				childs.push_back(g[group_it]->get_name());
				cout << "group: " << m_name << " has child: " << g[group_it]->get_name() << endl;
			}
		}
	}
	if (childs.size() > 0)
	{
		return childs;
	}
	return NULLvector;
}

std::vector< std::string > Groups::group_get_child_tree(std::string m_name, std::vector< std::string > data)
{
	if (is_group(m_name))
	{
		bool exists = false;
		for ( unsigned int i = 0 ; i < data.size(); i++ )
		{
			if (boost::iequals(data[i],m_name))
			{
				exists = true;
			}
		}
		if (!exists)
		{
			std::vector< std::string > childs = group_get_childs(m_name);
			for (unsigned int childs_it = 0; childs_it < childs.size(); childs_it++)
			{
				std::string child = childs[childs_it];
				if (is_group(child))
				{
					data.push_back(child);
					std::vector< std::string > tmpdata = group_get_child_tree(child, data);
					for (unsigned int tmpdata_it = 0; tmpdata_it < tmpdata.size(); tmpdata_it++)
					{
						if (is_group(tmpdata[tmpdata_it]))
						{
							data.push_back(tmpdata[tmpdata_it]);
						}
					}
				}
			}
		}
		return data;
	}
	return NULLvector;
}

void Groups::build_child_tree()
{
	/*for (unsigned int group_it = 0; group_it < g.size(); group_it++)
	{
		std::string current_group = g[group_it]->get_name();
		for (unsigned int group_it2 = 0; group_it2 < g.size(); group_it2++)
		{
			std::vector< std::string > parents = g[group_it2]->get_parents();
			for (unsigned int parents_it = 0; parents_it < parents.size(); parents_it++)
			{
				if (boost::iequals(current_group, parents[parents_it]))
				{
					g[group_it2]->add_parent(current_group);
					cout << g[group_it2]->get_name() << " has parent " << current_group << endl;
				}
			}
		}
	}*/

	for (unsigned int group_it = 0; group_it < g.size(); group_it++)
	{
		std::string current_group = g[group_it]->get_name();
		std::vector< std::string > members_group;
		members_group.push_back(current_group);
		std::string parent = group_get_parent(current_group);
		while (is_group(parent) == true)
		{
			bool exists = false;
			for ( unsigned int i = 0 ; i < members_group.size(); i++ )
			{
				if (!boost::iequals(members_group[i],parent))
				{
					exists = true;
				}
			}
			if (!exists)
			{
				members_group.push_back(parent);
				cout << parent << endl;
			}
			parent = group_get_parent(parent);
			cout << current_group << " has parents: " << parent << endl;
		}
	}
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

