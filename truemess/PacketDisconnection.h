#pragma once

#include "Packet.h"

class PacketDisconnection : public Packet {
public:
	PacketDisconnection(const std::string& name) : Packet(Packet::Type::DISCONNECT), m_name(name) {}
	PacketDisconnection(sf::Packet& packet) : Packet(Packet::Type::DISCONNECT, packet) {
		packet >> m_name;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_name;
		return packet;
	}

	std::string getName() const { return m_name; }
private:
	std::string m_name;
};