#ifndef Groups_h
#define Groups_h
#include "GlobalBase.h"
#include "Group.h"
#include <boost/thread/mutex.hpp>

class Group;
class Groups : public GlobalBase
{
public:
    Groups();
    ~Groups();

    bool AddGroup(std::string m_name);
    bool DelGroup(std::string m_name);
	std::vector< std::string > GetGroups();

private:
    std::vector< std::string > name;
    std::vector< Group* > g;
    std::vector< std::string > NULLvector;

    boost::mutex Group_mutex;

    int GetNameIndex(std::string m_name);
};

#endif // Groups_h


