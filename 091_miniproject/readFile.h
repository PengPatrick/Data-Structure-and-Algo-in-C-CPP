#include "pathPlanning.h"

// To locate if "$Edge" is in the file, return the index of line.
// If not exist, report error.
int locate(char *file);

// Read the grid_map.txt file, and return a pair. The first element
// is graph's nodelist, a vector of Node; the second element is
// graph's edgelist, a vector of pair, storing the node's id
pair<vector<Node>, vector<pair<int, int> > > readGrid(char *filename);

// Read the obstacle.txt file, and return a vector of vector of pair.
// Each vector store a vector of obstacle's edge.
// For example, (3 4 5) (12 13 14) are two obstacles. The the vector will store: ((3,4), (4,5),(5,3)) and ((12,13), (13,14), (14,12))
vector<vector<pair<int, int> > > readObs(char *filename);

// After read the $node line, parse the string to store the node
Node parseNode(string str);

// After read the $edge line, parse the string to store the edge
pair<int, int> parseEdge(string str);

// After read the $obstacles line, parse the string to store the obstacles
vector<pair<int, int> > parseObs(string str);

// Check if a string is a number
bool isNum(string str);

// Check if a string is a non-negative integer
bool isPosInt(string str);
