#pragma once

#include "Packet.h"

class PacketConnection : public Packet {
public:
	PacketConnection(const std::string& name) : Packet(Packet::Type::CONNECT), m_name(name) {};
	PacketConnection(sf::Packet& packet) : Packet(Packet::Type::CONNECT, packet) {
		packet >> m_roomId >> m_name;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_roomId << m_name;
		return packet;
	}

	std::string getName() const { return m_name; }
	sf::Uint8 getRoomId() const { return m_roomId; }
private:
	std::string m_name;
	sf::Uint8 m_roomId;
};