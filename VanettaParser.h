#ifndef VANETTAPARSER_H
#define VANETTAPARSER_H

class VanettaParser
{
	public:
		static VanettaParser* getInstance();
		void setParseFile(char * fileName);

	protected:
		void parseFile();
		VanettaParser(){};

		static VanettaParser* m_instance;
		char* m_File;
};

#endif
