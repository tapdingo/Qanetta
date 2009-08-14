#ifndef DATATYPES_H
#define DATATYPES_H

#include <vector>
#include <map>
#include <string>
#include <set>

typedef std::set<int> neighbor_tuple;
typedef std::map<int, int> link_tuple;
typedef std::vector<std::string> SplitVector;

struct NodeData
{
	double x_coord;
	double y_coord;
	neighbor_tuple neighbors;
	link_tuple topology;
};

//Usage Here: First Field is the Time Stamp, Second Field the Node ID
//The rest is the Node Data to the given time
typedef std::map< double, std::map< int, NodeData> > TimeState;

#endif
