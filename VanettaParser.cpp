#include "VanettaParser.h"
#include <iostream>
#include <fstream>

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
	parseFile();
}

void VanettaParser::parseFile()
{
	std::ifstream parseFile;
	parseFile.open (m_File, std::ios::in);

	if (parseFile.is_open())
	{
		return;
	}
}
