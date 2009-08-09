#ifndef VANETTAPARSER_H
#define VANETTAPARSER_H

class VanettaParser
{
	public:
		static VanettaParser* getInstance();

	protected:
		static VanettaParser* m_instance;
		VanettaParser(){};
};

#endif
