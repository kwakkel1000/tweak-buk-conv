#ifndef Zone_h
#define Zone_h
#include "GlobalBase.h"

class Zone : public GlobalBase
{
	public:
		Zone();
		~Zone();
		void init(std::string m_id, std::string m_name, std::string m_tnt, std::string m_health);
		void set_z(std::string minz, std::string maxz);
		void add_vertice(std::string m_x, std::string m_y);
		void add_admin(std::string m_user);
		void add_user(std::string m_user);
		std::string get_id();
		std::string get_name();
		std::string get_tnt();
		std::string get_health();
		std::string get_zmin();
		std::string get_zmax();
		std::vector< double > get_x();
		std::vector< double > get_y();
		std::vector< std::string > get_admins();
		std::vector< std::string > get_users();

	private:
		std::string id;
		std::string name;
		std::string tnt;
		std::string health;
		std::string zmin;
		std::string zmax;
		std::vector< double > x;
		std::vector< double > y;
		std::vector< std::string > admins;
		std::vector< std::string > users;
};


#endif // Zone_h
