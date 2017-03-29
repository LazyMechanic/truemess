#include "Input.h"

int Input::m_symbol = -1;
WINDOW * Input::win_current = stdscr;

void Input::onHandleEvents()
{
	while (true) {
		m_symbol = wgetch(win_current);
	}
}

int Input::getSymbol()
{
	return m_symbol;
}

void Input::setUndefinedSymbol()
{
	m_symbol = -1;
}

void Input::setCurrentWindow(WINDOW * win)
{
	win_current = win;
}
