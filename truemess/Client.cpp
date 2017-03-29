#include "Client.h"

#include "Trueconfig.h"

void Client::Run()
{
	initscr();

	noecho();

	start_color();

	// Set non-blocking getch()
	timeout(0);

	refresh();
	
	std::thread input(Input::onHandleEvents);
	input.detach();

	PushState<StateAuthentication>();
	PeekState()->onInit();

	while (!m_states.empty()) {
		State* state;

		if (state = PeekState()) {
			state->onDraw();
		}

		if (state = PeekState()) {
			state->onUpdate();
		}

		if (state = PeekState()) {
			state->HandleEvents();
		}


	}
	endwin();
}

void Client::PopState()
{
	if (!m_states.empty()) {
		m_states.top()->onClose();
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
