#pragma once

#include "Packet.h"

class PacketResponse : public Packet {
public:
	PacketResponse() :Packet(Packet::Type::RESPONSE) {}
	PacketResponse(sf::Packet& packet) :Packet(Packet::Type::RESPONSE, packet) {
		packet >> m_listData;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_listData;
		return packet;
	}

	std::string getListUsers() {
		return m_listData;
	}
private:
	std::string m_listData;
};