#include "Server.h"

#include <iostream>

#include "Trueconfig.h"

void Server::Run()
{
	Trueconfig::Init();
	m_rooms = Trueconfig::getRooms();

	if (m_listener.listen(Trueconfig::getPort()) != sf::Socket::Done) {
		throw std::runtime_error("Unable to create server on port " + std::to_string(Trueconfig::getPort()));
	}
	m_socketSelector.add(m_listener);

	while (true) {
		// Make the selector wait for data on any socket
		if (m_socketSelector.wait())
		{
			// Test the listener
			if (m_socketSelector.isReady(m_listener))
			{
				// The listener is ready: there is a pending connection
				std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
				if (m_listener.accept(*client) == sf::Socket::Done)
				{
					/* TEST BEGIN */
					std::cout << "New connection received from " << client->getRemoteAddress() << std::endl;
					/* TEST END */

					// Add the new client to the clients list
					User user(std::move(client));
					m_users.push_back(user);

					m_watingUsers.push_back(&user);

					// Add the new client to the selector so that we will
					// be notified when he sends something
					m_socketSelector.add(*user.getSocket());
				}
			}
			else
			{
				
				// The listener socket is not ready, test all other sockets (the clients)
				for (int i = 0; i < m_users.size(); i++)
				{
					sf::Packet packet;
					sf::TcpSocket *socket = m_users[i].getSocket();
					if (m_socketSelector.isReady(*socket) && socket->receive(packet) == sf::Socket::Done)
					{
						User& user = m_users[i];
						signed char type;
						packet >> type;
						switch (type)
						{
						case Packet::Type::MESSAGE:
						{
							PacketMessage packetMessage(packet);
							m_rooms[packetMessage.getRoomId()].broadcastPacket(packetMessage.getPacket());
							break;
						}
						case Packet::Type::CONNECT:
						{
							PacketConnection packetConnection(packet);
							m_rooms[packetConnection.getRoomId()].handleConnection(packetConnection.getPacket(), user);
							break;
						}
						case Packet::Type::DISCONNECT:
						{
							PacketDisconnection packetDisconnection(packet);
							m_rooms[packetDisconnection.getRoomId()].handleConnection(packetDisconnection.getPacket(), user);
							break;
						}
						case Packet::Type::REQUEST:
						{
							PacketRequest packetRequest(packet);

							if (packetRequest.getReqType() == PacketRequest::Type::ROOMS) {
								std::vector<std::string> roomNames;
								for (auto& room : m_rooms) {
									roomNames.push_back(room.getName());
								}

								std::thread([&]() {
									socket->send(PacketResponse(PacketResponse::Type::ROOMS, roomNames).getPacket());
								}).detach();
							}
							else if (packetRequest.getReqType() == PacketRequest::Type::USERS) {
								std::vector<std::string> userNames = user.getRoom()->getUserNames();

								for (auto& user : m_users) {
									std::thread([&]() {
										user.getSocket()->send(PacketResponse(PacketResponse::Type::USERS, userNames).getPacket());
									}).detach();
								}
							}
							else {
								throw std::exception("Invalid type of request.");
							}

							break;
						}
						default:
							throw std::exception("Invalid type of packet.");
							break;
						}
					}
				}				
			}
		}

	}
}
