#include "Trueconfig.h"

std::string Trueconfig::m_path = "./config.json";
std::vector<Room> Trueconfig::m_rooms;
unsigned short Trueconfig::m_port = 45000;

using JSON = nlohmann::json;

void Trueconfig::Init()
{
	std::ifstream if_config;
	if_config.open(m_path);

	if (if_config.is_open()) {
		JSON j;
		if_config >> j;
		if_config.close();

		unsigned char id = 0;
		for (JSON::iterator it = j["rooms"].begin(); it != j["rooms"].end(); it++, id++) {
			it.value()["id"] = id;
			it.value()["users"].clear();
			m_rooms.push_back(Room(it.key(), id));
		}

		if (j.find("port") == j.end()) {
			j["port"] = m_port;
		}
		else if (m_port != 45000) {
			j["port"] = m_port;
		}
		else {
			m_port = j["port"];
		}

		std::ofstream of_config;
		of_config.open(m_path);
		if (of_config.is_open()) {
			of_config << j.dump(4);
			of_config.close();
		}
		else {
			throw std::exception("Config cannot opened.");
		}
	}
	else {
		throw std::exception("Config cannot opened.");
	}
}

void Trueconfig::setConfigPath(const std::string & path)
{
	m_path = path;
}

void Trueconfig::setPort(unsigned short port)
{
	m_port = port;
}

void Trueconfig::Update(Trueconfig::Type type, const std::string& str)
{
	if (type == Trueconfig::Type::ADD) {
		std::ifstream if_config;
		if_config.open(m_path);

		if (if_config.is_open()) {
			JSON j;
			if_config >> j;
			if_config.close();
			unsigned char id = 0;
			for (JSON::iterator it = j["rooms"].begin(); it != j["rooms"].end(); it++, id++) {
				it.value()["id"] = id;
				m_rooms.push_back(Room(it.key(), id));
			}
			std::ofstream of_config;
			of_config.open(m_path);
			if (of_config.is_open()) {
				of_config << j.dump(4);
				of_config.close();
			}
			else {
				throw std::exception("Config cannot opened.");
			}
		}
		else {

			throw std::exception("Config cannot opened.");
		}
	}
	else if (type == Trueconfig::Type::ERASE) {

	}
	else {
		throw std::exception("Invalid type of update Trueconfig.");
	}
}

std::vector<Room> Trueconfig::getRooms()
{
	return m_rooms;
}

unsigned short Trueconfig::getPort()
{
	return m_port;
}
