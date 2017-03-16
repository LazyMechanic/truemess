#pragma once

#include <thread>
#include <string>
#include <vector>
#include <memory>

#include <SFML/Network.hpp>

#include "User.h"
#include "Packet.h"
#include "Room.h"

class Server {
public:
	void Run();
private:
	// Main listener connection and packet
	sf::TcpListener m_listener;
	sf::SocketSelector m_socketSelector;

	// Users wich choose rooms
	std::vector<User*> m_watingUsers;

	// List of rooms
	std::vector<Room> m_rooms;

	std::vector<User> m_users;
};