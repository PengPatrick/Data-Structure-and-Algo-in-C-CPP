#include "readFile.h"


using namespace std;

int main(int argc, char **argv){
  // check command arguments
    if(argc != 4){
        cerr << "Wrong number of command arguments!" << endl;
        return EXIT_FAILURE;
    }
    if(!isPosInt(argv[2]) || !isPosInt(argv[3])){
      cerr << "Wrong format of input node!" << endl;
      exit(EXIT_FAILURE);
    }
    vector<Node> nodeList;
    vector<pair<int, int> > nodeIndex;
    pair<vector<int>, double> shortestPath;

    nodeList = readGrid(argv[1]).first;
    nodeIndex = readGrid(argv[1]).second;

    // create Graph and run dijkstra algorithm
    Graph g;
    g.createGraph(nodeList, nodeIndex);
    g.Dijkstra(strtol(argv[2], NULL, 0), strtol(argv[3], NULL, 0));

    nodeList.clear();
    nodeIndex.clear();
    return EXIT_SUCCESS;
}
