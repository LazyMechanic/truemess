#pragma once

#include "State.h"

#include <vector>

#include "Room.h"

class StateMainMenu : public State {
public:
	StateMainMenu() {}

	void onInit();

	void HandleEvents();

	void onUpdate();
	void onDraw();

	void onClose();
private:
	std::vector<Room> m_rooms;
};