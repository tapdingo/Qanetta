#include "VanettaParser.h"

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

