#ifndef VANETTAPARSER_H
#define VANETTAPARSER_H

#include "DataTypes.h"

class VanettaParser
{
	public:
		static VanettaParser* getInstance();
		void setParseFile(char * fileName);
		void parseFile(TimeState& tgt_buf);

	protected:
		VanettaParser(){};

		static VanettaParser* m_instance;
		char* m_File;
};

#endif
