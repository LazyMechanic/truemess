#include <iostream>
#include <string>
#include <ConsoleConstructor/ConsoleConstructor.h>

#include "Config.h"
#include "Server.h"
#include "Client.h"

using console = mech::ConsoleConstructor;

void ShowHelp();

int main(int argc, char* argv[])
{
	bool asServer = false;
	/*
	console::onProgramName("truechat");

	console::on("-h", "--help", "help", "abc");
	console::on("-s", "--server", "server", "def");
	console::on("-c", "--client", "client", "ghi");
	console::on("-p", "--port", "port", "klm");

	console::consoleHandler(argc, argv);

	if (console::isInstruction("server")) {
		std::cout << "kek --server";
		asServer = true;
	}
	if (console::isInstruction("client")) {
		std::cout << "kek --client";
		asServer = false;
	}
	if (console::isInstruction("port")) {
		Config::port = std::atoi(console::getArguments("port")[0].c_str());
		std::cout << "kek --port " << Config::port;
	}
	*/
	
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			if (arg == "-h" || arg == "--help") {
				ShowHelp();
				return 1;
			}
			else if (arg == "-s" || arg == "--server") {
				asServer = true;
			}
			else if (arg == "-c" || arg == "--client") {
				asServer = false;
			}
			else if (arg == "-p" || arg == "--port") {
				if (i + 1 < argc && argv[i + 1][0] != '-') {
					std::string port = argv[++i];
					Config::port = std::atoi(port.c_str());
				}
				else {
					ShowHelp();
					return 1;
				}
			}
			else {
				std::cerr << "Wrong arguments\n";
				ShowHelp();
				return 1;
			}
		}
	}
	

	try {
		if (asServer) {
			Server server;
			server.Run();
		}
		else {
			Client client;
			client.Run();
		}
	}
	catch (std::exception& exn) {
		std::cerr << exn.what() << std::endl;
	}
	std::cout << "Hell yeah!!";

	std::cin.get();
	return 0;
}

void ShowHelp() {
	std::cout << "help";
}
