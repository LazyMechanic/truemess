#include "Client.h"

#include "Config.h"

void Client::Run()
{
	if (m_socket.connect(sf::IpAddress("127.0.0.1"), Config::port) != sf::Socket::Done) {
		throw std::exception("Unable to connect to server");
	}


}
