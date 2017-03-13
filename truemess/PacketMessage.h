#pragma once

#include "Packet.h"

class PacketMessage : public Packet {
public:
	PacketMessage(const std::string& name, const std::string& message) :
		Packet(Packet::Type::MESSAGE),
		m_name(name),
		m_message(message) {}
	PacketMessage(sf::Packet& packet) : Packet(Packet::Type::MESSAGE, packet) {
		packet >> m_name >> m_message;
	}

	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();
		packet << m_name << m_message;
		return packet;
	}

	std::string GetName() const { return m_name; }
	std::string GetMessage() const { return m_message; }

private:
	std::string m_name;
	std::string m_message;
};