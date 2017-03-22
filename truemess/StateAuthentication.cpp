#include "StateAuthentication.h"

#include "Client.h"

void StateAuthentication::onInit()
{
	/*if (m_client->getSocket()->connect(sf::IpAddress("127.0.0.1"), Trueconfig::getPort()) != sf::Socket::Done) {
		throw std::exception("Unable to connect to server");
	}*/

	
	WINDOW* w_name = newwin(3, 32, getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2 - 16);
	box(w_name, 0, 0);
	wrefresh(w_name);

}

void StateAuthentication::HandleEvents()
{
}

void StateAuthentication::onUpdate()
{
}

void StateAuthentication::onDraw()
{
}

void StateAuthentication::onClose()
{
}
