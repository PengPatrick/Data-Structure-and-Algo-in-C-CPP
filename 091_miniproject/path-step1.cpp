#include "readFile.h"

using namespace std;

int main(int argc, char **argv){
  // check command arguments
    if(argc != 2){
      cerr << "Wrong number of command arguments!" << endl;
      return EXIT_FAILURE;
    }

    vector<Node> nodeList;
    vector<pair<int, int> > nodeIndex;

    nodeList = readGrid(argv[1]).first;
    nodeIndex = readGrid(argv[1]).second;

    // create and print the graph
    Graph g;
    g.createGraph(nodeList, nodeIndex);
    g.printGraph(nodeList);

    nodeList.clear();
    nodeIndex.clear();
    return EXIT_SUCCESS;
}
