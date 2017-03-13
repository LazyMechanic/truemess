#pragma once

#include <SFML/Network.hpp>
#include <string>
#include <vector>

#include "User.h"
#include "Packet.h"
#include "Room.h"

class Server {
public:
	void Run();
private:
	sf::TcpListener m_listener;
	sf::SocketSelector m_socketSelector;

	std::vector<sf::TcpSocket*> m_users;
	
	std::vector<Room> m_rooms;
};