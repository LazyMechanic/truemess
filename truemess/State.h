#pragma once

#include <curses.h>

class Client;

class State {
public:
	State() {}

	virtual ~State() {}

	virtual void onInit() {}

	virtual void HandleEvents() {}

	virtual void onUpdate() {}
	virtual void onDraw() {}

	virtual void onClose() {}
protected:
	friend class Client;

	Client* m_client;
};