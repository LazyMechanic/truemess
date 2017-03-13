#include "Server.h"

#include <iostream>

#include "Config.h"

void Server::Run()
{
	if (m_listener.listen(Config::port) != sf::Socket::Done) {
		throw std::runtime_error("Unable to create server on port " + std::to_string(Config::port));
	}

	m_socketSelector.add(m_listener);

	while (true) {
		sf::TcpSocket client;
		if (m_listener.accept(client) == sf::Socket::Done)
		{
			std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
		}

		// Make the selector wait for data on any socket
		if (m_socketSelector.wait())
		{
			// Test the listener
			if (m_socketSelector.isReady(m_listener))
			{
				// The listener is ready: there is a pending connection
				sf::TcpSocket* user = new sf::TcpSocket;
				if (m_listener.accept(*user) == sf::Socket::Done)
				{
					// Add the new client to the clients list
					m_users.push_back(user);
					// Add the new client to the selector so that we will
					// be notified when he sends something
					m_socketSelector.add(*user);
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					delete user;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (int i = 0; i < m_users.size(); i++)
				{
					sf::TcpSocket &user = *m_users[i];
					if (m_socketSelector.isReady(user))
					{
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client.receive(packet) == sf::Socket::Done)
						{
							sf::Int8 type;
							packet >> type;
							switch (type) {
							case Packet::Type::MESSAGE:
								break;
							case Packet::Type::REQUEST:
								break;
							case Packet::Type::RESPONSE:
								break;
							case Packet::Type::DISCONNECT:
								break;
							}
						}
					}
				}
			}
		}

	}
}
