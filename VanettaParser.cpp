#include "VanettaParser.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <sstream>

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

	while (true)
	{
		memset(parseBuffer, '0', MAX_LINE);
		parseFile.getline(parseBuffer, MAX_LINE);

		if (parseFile.eof())
		{
			break;
		}

		std::string currentLine(parseBuffer);

		SplitVector splittedLine;
		boost::split(splittedLine, currentLine, boost::is_any_of(" "));

		//Extract the Time and Node ID from the current Trace Line
		double time = 0;
		std::stringstream timestr(splittedLine[0]);
		timestr >> time;

		int nodeId = 0;
		std::stringstream idstr(splittedLine[1]);
		idstr >> nodeId;

		//Extract the nodes Position from the current Trace Line
		double nodeX = 0;
		std::stringstream xstr(splittedLine[2]);
		xstr >> nodeX;

		double nodeY = 0;
		std::stringstream ystr(splittedLine[3]);
		ystr >> nodeY;

		//Extract the neighbors and the topology from the current Line
		neighbor_tuple neighbors;
		link_tuple reachables;
		if (splittedLine.size() > 4)
		{
			extractNeighbors(neighbors, splittedLine[4]);
		}
		if (splittedLine.size() > 5)
		{
			extractTopology(reachables, splittedLine[5]);
		}

		NodeData nodeData;
		nodeData.x_coord = nodeX;
		nodeData.y_coord = nodeY;
		nodeData.neighbors = neighbors;
		nodeData.topology = reachables;

		tgt_buf[time][nodeId] = nodeData;
	}
}

void VanettaParser::extractNeighbors(neighbor_tuple& tgt, std::string& data)
{
	SplitVector neighbors;
	boost::split(neighbors, data, boost::is_any_of(","));

	SplitVector::iterator it;
	for (it = neighbors.begin(); it != neighbors.end(); it ++)
	{
		int neighborID = 0;
		std::stringstream idstr(*it);
		idstr >> neighborID;
		tgt.insert(neighborID);
	}
}

void VanettaParser::extractTopology(link_tuple& tgt, std::string& data)
{
	SplitVector neighbors;
	boost::split(neighbors, data, boost::is_any_of(","));

	if (data.size() < 3)
	{
		return;
	}

	SplitVector::iterator it;
	for (it = neighbors.begin(); it != neighbors.end(); it ++)
	{
		SplitVector links;
		boost::split(links, *it, boost::is_any_of("-"));

		int tgtID = 0;
		std::stringstream tgtStr(links[0]);
		tgtStr >> tgtID;

		int nHopID = 0;
		std::stringstream nHopStr(links[1]);
		nHopStr >> nHopID;

		tgt[tgtID] = nHopID;
	}
}
