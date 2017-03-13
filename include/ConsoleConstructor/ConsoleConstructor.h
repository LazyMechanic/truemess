#pragma once
#include <string>
#include <vector>
#include <map>

namespace mech
{
	class ConsoleConstructor {
	public:
		static void onProgramName(const std::string& name);
		static int on(const std::string& instruction, const std::string& altInstruction, const std::string& meaning, const std::string& comment = "");
		static int on(const std::string& instruction, const std::string& meaning, const std::string& comment = "");
		static int consoleHandler(int argc, char* argv[]);
		static std::vector<std::string> getArguments(const std::string& instruction);
		static bool isInstruction(const std::string& instruction);

		static void getHelp() {
			help();
		}
	private:
		enum STATE {
			NORMAL = 0,
			INVALID_NUMBER = 1,
			WRONG_ARGUMENTS = 2
		};

		static void help(STATE state = STATE::NORMAL);
		static void getHelpText();

		static std::string generateComment(std::string str);

		// Instructions name / Fullname
		static std::map<std::string, std::string> instructions;

		// AltInstruction name / Instructions name
		static std::map<std::string, std::string> altInstructions;

		// Fullname / "Comment"
		static std::map<std::string, std::string> instructionsComments;
		
		// Instructions name / Array of argv
		static std::map<std::string, std::vector<std::string>> arguments;

		static std::map<std::string, bool> asInstructions;

		static std::string programName;
	};
}