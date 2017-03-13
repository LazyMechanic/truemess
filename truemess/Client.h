#pragma once

#include <SFML/Network.hpp> 

class Client {
public:
	void Run();
private:
	sf::TcpSocket m_socket;
};