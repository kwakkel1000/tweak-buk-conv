#ifndef Group_h
#define Group_h
#include "GlobalBase.h"

class Group : public GlobalBase
{
	public:
		Group();
		~Group();
		void init(std::string m_id, std::string m_name, std::string m_admin, std::string m_canbuild, std::string m_default, std::string m_ignorerestrictions);
		void add_inherit_group(std::string m_group);
		void add_command(std::string m_command);
		std::string get_id();
		std::string get_name();
		std::string get_admin();
		std::string get_canbuild();
		std::string get_default();
		std::string get_ignorerestrictions();
		std::vector< std::string > get_inheritedgroups();
		std::vector< std::string > get_commands();

	private:
		std::string id;
		std::string name;
		std::string admin;
		std::string canbuild;
		std::string isdefault;
		std::string ignorerestrictions;
		std::vector< std::string > inheritedgroups;
		std::vector< std::string > commands;
};


#endif // Group_h

