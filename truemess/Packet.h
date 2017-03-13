#pragma once

#include <SFML/Network.hpp>

class Packet {
public:
	enum Type : sf::Int8 // signed char
	{
		CONNECT,
		DISCONNECT,

		REQUEST,
		RESPONSE,

		MESSAGE
	};
	Packet(Packet::Type type) : m_type(type) {};
	Packet(Packet::Type type, sf::Packet& packet) : m_type(type) {
		packet >> m_type >> m_time;
	};

	virtual sf::Packet getPacket() {
		sf::Packet packet;
		packet << m_type << m_time;
		return packet;
	}

	sf::Int8 getType() const { return m_type; }
	time_t getTime() const { return m_time; }
private:
	sf::Int8 m_type;
	time_t m_time;
};