#ifndef Users_h
#define Users_h
#include "GlobalBase.h"
#include "User.h"
#include <boost/thread/mutex.hpp>

class User;
class Users : public GlobalBase
{
public:
    Users();
    ~Users();

    bool AddUser(std::string m_name);
    bool DelUser(std::string m_name);
/*
    void Debug();
*/
private:
    std::vector< std::string > name;
    std::vector< User* > u;
    std::vector< std::string > NULLvector;

    boost::mutex User_mutex;
    boost::mutex UsersGetNames_mutex;

    int GetNameIndex(std::string data);
};

#endif // Users_h

