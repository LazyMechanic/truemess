#include <iostream>
#include <string>

#include <ConsoleConstructor.h>

#include "Server.h"
#include "Client.h"
#include "Truelog.h"
#include "Trueconfig.h"

using console = mech::ConsoleConstructor;


int main(int argc, char* argv[])
{
	bool asServer = false;

	try {
		console::onProgramName("truechat");

		console::on("server", "-s", "--server", "Start \"Truemess\" like the server.");
		console::on("client", "-c", "--client", "Start \"Truemess\" like the client.");
		console::on("port", "-p", "--port", "Set port on which to work the server. Default port is " + std::to_string(Trueconfig::getPort()) + ".");

		int state = console::consoleHandler(argc, argv);
		if (state < 1) {
			return state;
		}

		if (console::getStatusInstruction("server")) {
			asServer = true;
		}
		if (console::getStatusInstruction("client")) {
			asServer = false;
		}
		if (console::getStatusInstruction("port")) {
			if (console::getArguments("port").size() == 0) {
				throw std::exception("Wrong port.");
			}
			Trueconfig::setPort(std::atoi(console::getArguments("port")[0].c_str()));
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
		Truelog::Stream(TruelogStreamType::FILE) << exn.what();
	}

	return 0;
}