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
		void extractNeighbors(neighbor_tuple& tgt, std::string& data);
		void extractTopology(link_tuple& tgt, std::string& data);

		static VanettaParser* m_instance;
		char* m_File;
};

#endif
