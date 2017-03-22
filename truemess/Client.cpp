#include "Client.h"

#include "Trueconfig.h"

void Client::Run()
{
	// TODO: add server selection (ip selection/input)

	initscr();

	PushState(StateAuthentication());

	State* state = PeekState();

	while (!m_states.empty()) {
		state->onUpdate();
		state->onDraw();
		//refresh();

		state = PeekState();
	}
	endwin();
}

void Client::PushState(const State& state)
{
	std::unique_ptr<State> st = std::make_unique<State>(state);
	m_states.push(std::move(st));
}

void Client::ChangeState(const State & state)
{
	PopState();
	std::unique_ptr<State> st = std::make_unique<State>(state);
	m_states.push(std::move(st));
}

void Client::PopState()
{
	if (!m_states.empty()) {
		m_states.pop();
	}
}

State * Client::PeekState()
{
	if (!m_states.empty()) {
		return m_states.top().get();
	}
	else {
		return nullptr;
	}
}
