#pragma once

#include <SFML/Network.hpp>

#include <memory>
#include <iostream>

#include "Config.h"
#include "Room.h"

class User {
public:
	User(const User &user) : m_name(std::string("")), m_room(nullptr) {};
	User(std::unique_ptr<sf::TcpSocket> socket) : m_socket(std::move(socket)), m_name(std::string("")), m_room(nullptr) {}
	User(std::unique_ptr<sf::TcpSocket> socket, const std::string& name) : m_socket(std::move(socket)), m_name(name), m_room(nullptr) {}

	void setUserSocket(std::unique_ptr<sf::TcpSocket> socket) { m_socket = std::move(socket); }
	void setUserName(const std::string& name) { m_name = name; }
	void setRoom(Room* room) { m_room = room; }

	sf::TcpSocket* getSocket() { return m_socket.get(); }
	std::string getName() const { return m_name; }
	Room* getRoom() { return m_room; }
private:
	std::unique_ptr<sf::TcpSocket> m_socket;
	std::string m_name;
	Room* m_room;
};