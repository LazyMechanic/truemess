#pragma once

#include <string>
#include <vector>

#include "PacketConnection.h"
#include "PacketDisconnection.h"
#include "PacketMessage.h"
#include "PacketRequest.h"
#include "PacketResponse.h"

class User;

class Room {
public:
	Room(const std::string& name, sf::Uint8 id) : m_name(name), m_id(id), m_users(std::vector<User*>()) {};

	void broadcastPacket(sf::Packet& packet);
	void handleConnection(sf::Packet& packet, User& user);
	void handleDisconnection(sf::Packet& packet, User& user);


	std::string getName() const;
	sf::Uint8 getId() const;

	std::vector<std::string> getUserNames() const;
private:
	std::string m_name;
	sf::Uint8 m_id;

	std::vector<User*> m_users;
};