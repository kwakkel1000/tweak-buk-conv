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

	bool group_init(std::string m_id, std::string m_name, std::string m_admin, std::string m_canmodifyworld, std::string m_defaultgroup, std::string m_ignorerestrictions);
	bool group_add_commands(std::string m_name, std::string m_commands);
	bool group_add_parent(std::string m_name, std::string m_parent);

	std::string group_get_parent(std::string m_name);

	bool is_group(std::string m_name);

private:
    std::vector< std::string > name;
    std::vector< Group* > g;
    std::vector< std::string > NULLvector;

    boost::mutex Group_mutex;

    int GetNameIndex(std::string m_name);
};

#endif // Groups_h


