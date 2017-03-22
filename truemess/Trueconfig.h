#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <json.hpp>
#include "Room.h"

class Trueconfig {
public:
	enum Type : unsigned char {
		ADD,
		ERASE
	};
	// Get all rooms in config file
	static void Init();

	// Set path to config with config name
	static void setConfigPath(const std::string& path);

	// Set server port
	static void setPort(unsigned short port);

	// Update config in runtime
	static void Update(Trueconfig::Type type, const std::string& str);

	// Get list of rooms
	static std::vector<Room> getRooms();

	// Get server port
	static unsigned short getPort();
private:
	static std::string m_path;
	static std::vector<Room> m_rooms;
	static unsigned short m_port;
};