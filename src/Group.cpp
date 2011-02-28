#include "../include/Group.h"
#include <boost/algorithm/string.hpp>
#include <iostream>


Group::Group()
{

}

Group::~Group()
{

}
void Group::init(std::string m_id, std::string m_name, std::string m_admin, std::string m_canbuild, std::string m_default, std::string m_ignorerestrictions)
{
	id = m_id;
	name = m_name;
	admin = m_admin;
	canbuild = m_canbuild;
	isdefault = m_default;
	ignorerestrictions = m_ignorerestrictions;
}
void Group::add_inherit_group(std::string m_group)
{
	inheritedgroup = m_group;
}
void Group::add_command(std::string m_command)
{
	commands.push_back(m_command);
}
std::string Group::get_id()
{
	return id;
}
std::string Group::get_name()
{
	return name;
}
std::string Group::get_admin()
{
	return admin;
}
std::string Group::get_canbuild()
{
	return canbuild;
}
std::string Group::get_default()
{
	return isdefault;
}
std::string Group::get_ignorerestrictions()
{
	return ignorerestrictions;
}
std::string Group::get_inheritedgroup()
{
	return inheritedgroup;
}
std::vector< std::string > Group::get_commands()
{
	return commands;
}
