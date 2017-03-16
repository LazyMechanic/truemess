#pragma once

#include "Packet.h"

class PacketResponse : public Packet {
public:
	enum Type {
		ROOMS,
		USERS
	};
	PacketResponse(PacketResponse::Type type, std::vector<std::string> listData) : Packet(Packet::Type::RESPONSE), m_listData(listData), m_resType(type) {}
	PacketResponse(sf::Packet& packet) : Packet(Packet::Type::RESPONSE, packet) {
		packet >> m_resType;

		std::string roomName;
		while (packet >> roomName) {
			m_listData.push_back(roomName);
		}
	}
	
	sf::Packet getPacket() {
		sf::Packet packet = Packet::getPacket();

		packet << m_resType;
		for (unsigned int i = 0; i < m_listData.size(); i++) {
			packet << m_listData[i];
		}
		return packet;
	}

	std::vector<std::string> getListData() const { return m_listData; }

	sf::Int8 getResType() const { return m_resType; }
private:
	std::vector<std::string> m_listData;
	sf::Int8 m_resType;
};