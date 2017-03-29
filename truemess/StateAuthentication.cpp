#include "StateAuthentication.h"

#include "Trueconfig.h"
#include "Truelog.h"

void StateAuthentication::onInit()
{
	/*if (m_client->getSocket()->connect(sf::IpAddress("127.0.0.1"), Trueconfig::getPort()) != sf::Socket::Done) {
		throw std::exception("Unable to connect to server");
	}*/

	// Init bad info window
	win_badInfo = newwin(1, getmaxx(stdscr), 0, 0);

	// Init logo window 
	win_logo = newwin(5, 57, 1, getmaxx(stdscr) / 2 - 28);

	// Init login window
	win_login = newwin(3, 32, getmaxy(stdscr) / 2 + 2, getmaxx(stdscr) / 2 - 16);

	// Init password window
	win_passw = newwin(3, 32, getmaxy(stdscr) / 2 + 4 + 2, getmaxx(stdscr) / 2 - 16);

	// Init sign in window
	win_signin = newwin(1, 9, getmaxy(stdscr) / 2 + 4 + 2 + 4, getmaxx(stdscr) / 2 - 5);

	// Init sing up window
	win_signup = newwin(1, 24, getmaxy(stdscr) - 1, 0);
	
	m_currentStr = &m_login;

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_RED);

	init_color(COLOR_BLUE, 0, 0, 900);


	// First window rendering

	const char* logo = "_______                    _______                    \n|_     _|.----.--.--.-----.|   |   |.-----.-----.-----.\n  |   |  |   _|  |  |  -__||       ||  -__|__ --|__ --|\n  |___|  |__| |_____|_____||__|_|__||_____|_____|_____|\n";

	// Logo window
	wborder(win_logo, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	mvwaddstr(win_logo, 1, 1, logo);

	// Login window
	wborder(win_login, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwaddstr(win_login, 0, getmaxx(win_login) / 2 - 5, "Your login:");

	// Password window
	wborder(win_passw, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwaddstr(win_passw, 0, getmaxx(win_passw) / 2 - 7, "Your password:");

	wattron(win_badInfo, COLOR_PAIR(3));
	//mvwaddstr(win_badInfo, 0, 0, "HALO MAFAKA");

	// Sign in window
	// Set color gamma = white and black
	wattron(win_signin, COLOR_PAIR(1));
	mvwaddstr(win_signin, 0, 0, " SIGN IN ");

	// Sign up window
	// Set color gamma = white and black
	wattron(win_signup, COLOR_PAIR(1));
	mvwaddstr(win_signup, 0, 0, " For sign up press <F1> ");

	// Set pointer to first window (login)
	win_current = win_login;

	wmove(win_current, 1, 2);

	wrefresh(win_badInfo);
	wrefresh(win_logo);
	wrefresh(win_login);
	wrefresh(win_passw);
	wrefresh(win_signin);
	wrefresh(win_signup);

	Input::setCurrentWindow(win_login);
}

void StateAuthentication::switchWin()
{
	if (win_current == win_login) {

		win_current = win_passw;
		m_currentStr = &m_password;

		wmove(win_current, 1, m_currentStr->size() + 2);

		Input::setCurrentWindow(win_passw);
	}
	else if (win_current == win_passw) {
		win_current = win_signin;

		// Delete white and black color gamma
		wattroff(win_signin, COLOR_PAIR(1));

		// Add blue and white color gamma
		wattron(win_signin, COLOR_PAIR(2));

		// Update window
		mvwaddstr(win_signin, 0, 0, " SIGN IN ");

		// Set the cursor to invisible
		curs_set(0);

		Input::setCurrentWindow(win_signin);
	}
	else if (win_current == win_signin) {
		// Delete blue and white color gamma
		wattroff(win_signin, COLOR_PAIR(2));
		wattron(win_signin, COLOR_PAIR(1));
		// Update window
		mvwaddstr(win_signin, 0, 0, " SIGN IN ");

		wrefresh(win_signin);

		win_current = win_login;
		m_currentStr = &m_login;

		wmove(win_current, 1, m_currentStr->size() + 2);

		// Set the cursor to visible
		curs_set(1);

		Input::setCurrentWindow(win_login);
	}
}

void StateAuthentication::HandleEvents()
{
	// Input symbol
	int symbol = Input::getSymbol();

	if (symbol > -1) {
		if (symbol == KEY_F(1)) {
			// TODO: create registration state
			//m_client->PushState();
		}
		else {
			m_updateFlag = true;

			if (win_current == win_login || win_current == win_passw) {
				// Cursor position
				int pos_y = 1;
				int pos_x = 2;

				// Indent of a input zone
				int indent_x = 2;

				getyx(win_current, pos_y, pos_x);

				switch (symbol) {

				case 10: // key == ENTER
				case 9: // key == TAB
					switchWin();
					break;
				case 8: // key == BACKSPACE
					if (m_currentStr->size() > 0 && pos_x > 0 + indent_x) {
						m_currentStr->erase(pos_x - 1 - indent_x, 1);

						// Clear input zone (28 spaces)
						mvwaddstr(win_current, 1, indent_x, "                            ");

						if (win_current == win_passw) {
							// Output passw ("****")
							std::wstring passw = L"";
							for (int i = 0; i < m_password.size(); i++) {
								passw += '*';
							}

							// Input current password
							mvwaddwstr(win_current, 1, indent_x, passw.c_str());
						}
						else {
							// Input current login
							mvwaddwstr(win_current, 1, indent_x, m_currentStr->c_str());
						}						

						// Move cursor to new pos
						wmove(win_current, 1, pos_x - 1);
					}
					break;
				case KEY_RIGHT: // key == RIGHT_ARR
					if (pos_x < m_currentStr->size() + indent_x) {
						wmove(win_current, 1, pos_x + 1);
					}
					break;
				case KEY_LEFT: // key == LEFT_ARR
					if (pos_x > 2) {
						wmove(win_current, 1, pos_x - 1);
					}
					break;
				default: // Normal keys
					if (symbol > 31 && symbol < 256 || symbol > 548) {
						if (m_currentStr->size() < 28) {
							m_currentStr->insert(pos_x - indent_x, 1, symbol);

							// Clear input zone (28 spaces)
							mvwaddstr(win_current, 1, indent_x, "                            ");
							
							if (win_current == win_passw) {
								// Output passw ("****")
								std::wstring passw = L"";
								for (int i = 0; i < m_password.size(); i++) {
									passw += '*';
								}

								// Input current password
								mvwaddwstr(win_current, 1, indent_x, passw.c_str());
							}
							else {
								// Input current login
								mvwaddwstr(win_current, 1, indent_x, m_currentStr->c_str());
							}
							// Move cursor to new pos
							wmove(win_current, 1, pos_x + 1);
						}
					}
					break;
				}
			}
			else {

				switch (symbol) {

				case 10: // key == ENTER
					// TODO: create verification state
					if (m_login.size() < 4 || m_password.size() < 4) {
						mvwaddstr(win_badInfo, 0, 0, " Length of login and password must be more 3 symbols ");
						wrefresh(win_badInfo);
					}
					else {
						wclear(win_badInfo);
						wrefresh(win_badInfo);
					}
					break;
				case 9: // key == TAB
					switchWin();
					break;
				}
			}
		}

		Input::setUndefinedSymbol();
	}

	/*--------------------------------WORKING VERSION--------------------------------

	int ch = NULL;
	int y = 0;
	int x = 0;

	int indent_x = 2;	

	curs_set(1);

	wmove(win_login, 1, m_login.size() + indent_x);

	// Loop while pressed button != TAB or ENTER
	while ((ch = wgetch(win_login)) != 10 && ch != 9) {
		getyx(win_login, y, x);

		switch (ch) {
		case 8: // key == BACKSPACE
			if (m_login.size() > 0 && x > 0 + indent_x) {
				m_login.erase(x - 1 - indent_x, 1);

				// Clean input zone (28 spaces)
				mvwaddstr(win_login, 1, indent_x, "                            ");
				
				// Input current login
				mvwaddwstr(win_login, 1, indent_x, m_login.c_str());

				// Move cursor to current pos
				wmove(win_login, 1, x - 1);
			}
			break;
		case KEY_RIGHT: // key right
			if (x < m_login.size() + indent_x) {
				wmove(win_login, 1, x + 1);
			}
			break;
		case KEY_LEFT: // key left
			if (x > 2) {
				wmove(win_login, 1, x - 1);
			}
			break;
		case KEY_F(1): // key f1
			// TODO: create registration state
			break;
		}

		if (ch > 31 && ch < 256 || ch > 548) {
			if (m_login.size() < 28) {
				m_login.insert(x - indent_x, 1, ch);

				// Clean input zone (28 spaces)
				mvwaddstr(win_login, 1, indent_x, "                            ");

				// Input current login
				mvwaddwstr(win_login, 1, indent_x, m_login.c_str());

				// Move cursor to current pos
				wmove(win_login, 1, x + 1);
			}
		}

		// Update login window
		wrefresh(win_login);
	}
	
	// Switch cursor to passw window
	wmove(win_passw, 1, m_password.size() + indent_x);

	// Output passw ("****")
	std::string passw = "";
	for (int i = 0; i < m_password.size(); i++) {
		passw += '*';
	}

	while ((ch = wgetch(win_passw)) != 10 && ch != 9) {
		getyx(win_passw, y, x);

		switch (ch) {
		case 8: // key == BACKSPACE
			if (m_password.size() > 0 && x > 0 + indent_x) {
				m_password.erase(x - 1 - indent_x, 1);
				passw.erase(x - 1 - indent_x, 1);

				// Clean input zone (28 spaces)
				mvwaddstr(win_passw, 1, indent_x, "                            ");

				// Input current passw
				mvwaddstr(win_passw, 1, indent_x, passw.c_str());

				// Move cursor to current pos
				wmove(win_passw, 1, x - 1);
			}
			break;
		case KEY_RIGHT: // key right
			if (x < m_password.size() + indent_x) {
				wmove(win_passw, 1, x + 1);
			}
			break;
		case KEY_LEFT: // key left
			if (x > 2) {
				wmove(win_passw, 1, x - 1);
			}
			break;
		case KEY_F(1): // key f1
			// TODO: create registration state
			break;
		}

		if (ch > 31 && ch < 256 || ch > 548) {
			if (m_password.size() < 28) {
				m_password.insert(x - indent_x, 1, ch);
				passw.insert(x - indent_x, 1, '*');

				// Clean input zone (28 spaces)
				mvwaddstr(win_passw, 1, indent_x, "                            ");

				// Input current login
				mvwaddstr(win_passw, 1, indent_x, passw.c_str());

				// Move cursor to current pos
				wmove(win_passw, 1, x + 1);
			}
		}

		// Update passw window
		wrefresh(win_passw);
	}

	// Set invisibility cursor
	curs_set(0);

	// Delete white-black color
	wattroff(win_signin, COLOR_PAIR(1));

	// Add blue-white color
	wattron(win_signin, COLOR_PAIR(2));

	// Update window
	mvwaddstr(win_signin, 0, 0, " SIGN IN ");
	wrefresh(win_signin);
	
	while ((ch = wgetch(win_login)) != 10 && ch != 9) {
		
		if (ch == 10) {
			//	TODO:
			//	Send information to server
			//	If all ok then m_client.PushState()
			
		}

		if (ch == KEY_F(1)) {
			// TODO: create registration state
			break;
		}
		wrefresh(win_signin);
	}

	// Delete blue-white color
	wattroff(win_signin, COLOR_PAIR(2));

	----------------------------------------------------------------*/
}

void StateAuthentication::onUpdate()
{
}

void StateAuthentication::onDraw()
{
	if (m_updateFlag) {
		wrefresh(win_current);

		m_updateFlag = false;
	}
}

void StateAuthentication::onClose()
{
	delwin(win_logo);
	delwin(win_login);
	delwin(win_passw);
	delwin(win_signin);
	delwin(win_signup);
}
