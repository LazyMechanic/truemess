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

	template<class T>
	void PushState() {
		// Test input type
		static_assert(std::is_base_of<State, T>::value, "Type must be base of State");
		std::unique_ptr<T> state = std::make_unique<T>();
		state->m_client = this;
		m_states.push(std::move(state));
	}
	template<class T>
	void ChangeState() {
		// Test input type
		static_assert(std::is_base_of<State, T>::value, "Type must be base of State");
		PopState();
		PushState<T>();
	}
	void PopState();
	State* PeekState();

	sf::TcpSocket* getSocket() { return &m_socket; }
private:

	std::stack<std::unique_ptr<State>> m_states;
	sf::TcpSocket m_socket;
};