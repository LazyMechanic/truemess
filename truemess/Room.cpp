#include "Room.h"

#include <thread>

#include "Trueconfig.h"
#include "User.h"

void Room::broadcastPacket(sf::Packet & packet)
{
	for (int i = 0; i < m_users.size(); i++) {
		std::thread([&]() {
			m_users[i]->getSocket()->send(packet);
		}).detach();
	}
}

void Room::handleConnection(sf::Packet & packet, User& user)
{
	PacketConnection packetConnection(packet);
	Trueconfig::Update(Trueconfig::Type::ADD, user.getName());

	m_users.push_back(&user);

	for (int i = 0; i < m_users.size(); i++) {
		std::thread([&]() {
			m_users[i]->getSocket()->send(packetConnection.getPacket());
		}).detach();
	}
}

void Room::handleDisconnection(sf::Packet & packet, User& user)
{
	PacketDisconnection packetDisconnection(packet);
	Trueconfig::Update(Trueconfig::Type::ADD, packetDisconnection.getName());

	for (std::vector<User*>::iterator it = m_users.begin(); it != m_users.end(); it++) {
		if ((*it)->getName() == user.getName()) {
			m_users.erase(it);
			break;
		}
	}

	for (int i = 0; i < m_users.size(); i++) {
		std::thread([&]() {
			m_users[i]->getSocket()->send(packetDisconnection.getPacket());
		}).detach();
	}
}

std::string Room::getName() const
{
	return m_name;
}

sf::Uint8 Room::getId() const
{
	return m_id;
}

std::vector<std::string> Room::getUserNames() const
{
	std::vector<std::string> users;
	for (int i = 0; i < m_users.size(); i++) {
		users.push_back(m_users[i]->getName());
	}
	return users;
}
