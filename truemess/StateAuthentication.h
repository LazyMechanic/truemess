#pragma once

#include "State.h"

#include <string>
#include <thread>

#include "Client.h"
#include "Input.h"

class StateAuthentication : public State {
public:
	StateAuthentication() : State(), m_login(L""), m_password(L""), m_currentStr(nullptr), m_updateFlag(false) {}

	void onInit() override;

	void HandleEvents() override;

	void onUpdate() override;
	void onDraw() override;

	void onClose() override;
private:
	std::wstring m_login;
	std::wstring m_password;

	WINDOW* win_logo;
	WINDOW* win_login;
	WINDOW* win_passw;
	WINDOW* win_signin;
	WINDOW* win_signup;

	WINDOW* win_badInfo;

	WINDOW* win_current;
	std::wstring* m_currentStr;

	bool m_updateFlag;

	void switchWin();
};