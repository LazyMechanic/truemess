#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum class TruelogType {
	INFO,
	ERROR,
	WARNING,
	DEBUG
};
enum class TruelogStreamType {
	CONSOLE,
	FILE,
	ALL
};

class Truelog {
//private:
	class LogHelper;
public:
	static void InitFile(const std::string& path = "log.txt");

	// Write logs
	static Truelog& Stream(TruelogStreamType streamt = TruelogStreamType::ALL);

	template <class Arg>
	LogHelper & operator<<(const Arg & arg)
	{
		if (m_streamType == TruelogStreamType::ALL) {
			std::cout << std::endl;
			m_log << std::endl;
		}
		else if (m_streamType == TruelogStreamType::CONSOLE) {
			std::cout << std::endl;
		}
		else {
			m_log << std::endl;
		}
		return (LogHelper(this) << arg);
	}
private:
	Truelog() = delete;
	Truelog(const Truelog&) = delete;
	Truelog(TruelogStreamType stream) : m_streamType(stream), m_warningCount(0), m_errorCount(0) {}

	static const std::string GetDate();

	static std::ofstream m_log;

	TruelogStreamType m_streamType;

	unsigned int m_warningCount;
	unsigned int m_errorCount;


	class LogHelper
	{
	public:
		LogHelper(Truelog* owner) : m_owner(owner) {}

		LogHelper& operator<<(const TruelogType& type)
		{
			std::string output;
			switch (type)
			{
			case TruelogType::INFO:
				output = "[INFO] " + GetDate() + ": ";
				break;
			case TruelogType::ERROR:
				output = "[ERROR] " + GetDate() + ": ";
				m_owner->m_errorCount++;
				break;
			case TruelogType::WARNING:
				output = "[WARNING] " + GetDate() + ": ";
				m_owner->m_warningCount++;
				break;
			case TruelogType::DEBUG:
				output = "[DEBUG] " + GetDate() + ": ";
				break;
			default:
				break;
			}

			if (m_owner->m_streamType == TruelogStreamType::ALL) {
				std::cout << output;
				m_log << output;
			}
			else if (m_owner->m_streamType == TruelogStreamType::CONSOLE) {
				std::cout << output;
			}
			else {
				m_log << output;
			}
			return *this;
		}

		template<class Arg>
		LogHelper& operator<<(const Arg& arg)
		{
			if (m_owner->m_streamType == TruelogStreamType::ALL) {
				std::cout << arg << ' ';
				m_log << arg << ' ';
			}
			else if (m_owner->m_streamType == TruelogStreamType::CONSOLE) {
				std::cout << arg << ' ';
			}
			else {
				m_log << arg << ' ';
			}
			return *this;
		}
	private:
		Truelog* m_owner;
	};
};
