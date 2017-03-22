#pragma once

#include "State.h"

#include "Trueconfig.h"

class StateAuthentication : public State {
public:
	StateAuthentication() {
		onInit();
	}

	void onInit();

	void HandleEvents();

	void onUpdate();
	void onDraw();

	void onClose();

private:

};