#pragma once

#include "Packet.h"

class PacketRequest : public Packet {
public:
	enum Type {
		ROOMS,
		USERS
	};
	PacketRequest(const sf::Int8& reqType) : Packet(Packet::Type::REQUEST), m_reqType(reqType) {}
	PacketRequest(sf::Packet& packet) : Packet(Packet::Type::REQUEST, packet) {
		packet >> m_reqType;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_reqType;
		return packet;
	}

	sf::Int8 getReqType() const { return m_reqType; }
private:
	sf::Int8 m_reqType;
};