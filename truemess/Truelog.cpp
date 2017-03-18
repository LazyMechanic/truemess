#include "Truelog.h"

#include <time.h>

std::ofstream Truelog::m_log;

void Truelog::InitFile(const std::string & path)
{
	m_log.open(path);
}

Truelog & Truelog::Stream(TruelogStreamType streamt)
{
	static Truelog log(streamt);
	return log;
}

const std::string Truelog::GetDate()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "[%d.%m.%Y %X]", &tstruct);

	return buf;
}