#pragma once

#include <stack>

#include <SFML/Network.hpp> 

#include "Packet.h"
#include "User.h"

#include "StateAuthentication.h"
#include "StateMainMenu.h"
#include "StateRoom.h"
#include "State.h"

class Client {
public:
	void Run();

	void PushState(const State& state);
	void ChangeState(const State& state);
	void PopState();
	State* PeekState();

	sf::TcpSocket* getSocket() { return &m_socket; }
private:

	std::stack<std::unique_ptr<State>> m_states;
	sf::TcpSocket m_socket;
};