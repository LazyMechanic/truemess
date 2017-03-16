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
	static std::vector<Room> Init();

	// Set path to config with config name
	static void setConfigPath(const std::string& path);

	// Update config in runtime
	static void Update(Trueconfig::Type type, const std::string& str);

	// Get list of rooms
	static std::vector<Room> getRooms();
private:
	static std::string m_path;
	static std::vector<Room> m_rooms;
};