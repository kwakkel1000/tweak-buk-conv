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
        //tmpgroup->SetName(m_name);
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
/*
void Groups::Debug()
{
    boost::mutex::scoped_lock  lock(User_mutex);
    for ( unsigned int i = 0 ; i < name.size(); i++ )
    {
        cout << "NICK: " << name[i] << " auth: " << u[i]->GetAuth() << endl;
        vector<string> channels = u[i]->GetChannels();
        cout << "Nick Channels:";
        for ( unsigned int j = 0 ; j < channels.size(); j++ )
        {
            cout << "  " << channels[j];
        }
        std::cout << std::endl;
    }
}
*/

std::vector< std::string > Groups::GetGroups()
{
	return name;
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

