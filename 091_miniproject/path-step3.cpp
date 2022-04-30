#include "readFile.h"

using namespace std;

int main(int argc, char **argv){
  // check command arguments
    if(argc != 5){
        cerr << "Wrong number of command arguments!" << endl;
        return EXIT_FAILURE;
    }
    if(!isPosInt(argv[3]) || !isPosInt(argv[4])){
      cerr << "Wrong format of input node!" << endl;
      exit(EXIT_FAILURE);
    }
    vector<Node> nodeList;
    vector<pair<int, int> > nodeIndex;
    vector<vector<pair<int, int> > > obsList;

    nodeList = readGrid(argv[1]).first;
    nodeIndex = readGrid(argv[1]).second;
    obsList = readObs(argv[2]);

    // create graph
    Graph g;
    // if there is record show that obstacle exsit, create graph with obstacle
    if(obsList.size() > 0){
      g.graphWithObs(nodeList, nodeIndex, obsList);
    }
    // if there is record show that no obstacle, then the same as step2
    else{
      g.createGraph(nodeList, nodeIndex);
    }

    g.Dijkstra(strtol(argv[3], NULL, 0), strtol(argv[4], NULL, 0));

    nodeList.clear();
    nodeIndex.clear();
    obsList.clear();
    return EXIT_SUCCESS;
}
