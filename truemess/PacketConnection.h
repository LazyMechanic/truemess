#pragma once

#include "Packet.h"

class PacketConnection : public Packet {
public:
	PacketConnection(const std::string& name) : Packet(Packet::Type::CONNECT), m_name(name) {};
	PacketConnection(sf::Packet& packet) : Packet(Packet::Type::CONNECT, packet) {
		packet >> m_name >> m_room;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_name << m_room;
		return packet;
	}

	std::string getName() const { return m_name; }
private:
	std::string m_name;
	std::string m_room;
};