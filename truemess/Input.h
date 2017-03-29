#pragma once

#include <curses.h>

class Input {
public:
	static void onHandleEvents();
	static int getSymbol();
	static void setUndefinedSymbol();
	static void setCurrentWindow(WINDOW* win);
private:
	static int m_symbol;
	static WINDOW* win_current;
};