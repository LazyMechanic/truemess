#include <iostream>
#include <string>

#include <ConsoleConstructor.h>

#include "Config.h"
#include "Server.h"
#include "Client.h"
#include "Truelog.h"

using console = mech::ConsoleConstructor;

int main(int argc, char* argv[])
{
	bool asServer = false;

	try {
		console::onProgramName("truechat");

		console::on("-s", "--server", "server", "def");
		console::on("-c", "--client", "client", "ghi");
		console::on("-p", "--port", "port", "klm");

		console::consoleHandler(argc, argv);

		if (console::getStatusInstruction("server")) {
			std::cout << "kek --server\n";
			asServer = true;
		}
		if (console::getStatusInstruction("client")) {
			std::cout << "kek --client\n";
			asServer = false;
		}
		if (console::getStatusInstruction("port")) {
			if (console::getArguments("port").size() == 0) {
				throw std::exception("Wrong port.");
			}
			Config::port = std::atoi(console::getArguments("port")[0].c_str());
			std::cout << "kek --port " << Config::port << "\n";
		}

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

	std::cin.get();
	return 0;
}