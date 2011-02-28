#include "../include/Users.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

Users::Users()
{
    NULLvector.push_back("NULL");
}

Users::~Users()
{
    for ( unsigned int i = name.size() -1; 0 >= i; i-- )
    {
        std::cout << "DELETED: NAME: " << name[i]  << std::endl;
        name.erase(name.begin()+i);
        delete u[i];
        u.erase(u.begin()+i);
    }
}

bool Users::AddUser(std::string m_name)
{
    boost::mutex::scoped_lock  lock(User_mutex);
    int i = GetNameIndex(m_name);
    if (i == -1)
    {
        name.push_back (m_name);
        User *tmpuser = new User();
        //tmpuser->SetName(m_name);
        u.push_back (tmpuser);
        return true;
    }
    return false;
}

bool Users::DelUser(std::string m_name)
{
    boost::mutex::scoped_lock  lock(User_mutex);
    int i = GetNameIndex(m_name);
    if (i >= 0)
    {
        name.erase(name.begin()+i);
        u[i]->~User();
        u.erase(u.begin()+i);
        return true;
    }
    return false;
}
/*
void Users::Debug()
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

int Users::GetNameIndex(std::string m_name)
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
