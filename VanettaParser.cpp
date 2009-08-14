#include "VanettaParser.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#define MAX_LINE 1000
VanettaParser* VanettaParser::m_instance = 0;

VanettaParser* VanettaParser::getInstance()
{
	if (m_instance)
	{
		return m_instance;
	}
	m_instance = new VanettaParser();
	return m_instance;
}

void VanettaParser::setParseFile(char* fileName)
{
	m_File = fileName;
}

void VanettaParser::parseFile(TimeState& tgt_buf)
{
	std::ifstream parseFile;
	parseFile.open (m_File, std::ios::in);
	char* parseBuffer = static_cast<char*>(malloc(MAX_LINE));

	if (!parseFile.is_open())
	{
		return;
	}

	while (!parseFile.eof())
	{
		memset(parseBuffer, '0', MAX_LINE);
		parseFile.getline(parseBuffer, MAX_LINE);
		std::string currentLine(parseBuffer);

		SplitVector splittedLine;
		boost::split(splittedLine, currentLine, boost::is_any_of(" "));
	}
}
