#include "readFile.h"

using namespace std;

int main(int argc, char **argv){
  // check command arguments
    if(argc != 5 && argc != 6){
        cerr << "Wrong number of command arguments!" << endl;
        exit(EXIT_FAILURE);
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

    Graph g;

    if(argc == 5){
      // if the same as step3, call the Dijkstra
        g.graphWithObs(nodeList, nodeIndex, obsList);
        g.Dijkstra(strtol(argv[3], NULL, 0), strtol(argv[4], NULL, 0));

        nodeList.clear();
        nodeIndex.clear();
        obsList.clear();
        return EXIT_SUCCESS;
    }else{
      // if not the same, check the command argument to see if it is "-a"
        string a = argv[5];
        if(a != "-a"){
	  cerr << "Wrong format of input, use '-a' if you want A* search" << endl;
	exit(EXIT_FAILURE);
        }
        g.graphWithObs(nodeList, nodeIndex, obsList);
        g.AStar(nodeList, strtol(argv[3], NULL, 0), strtol(argv[4], NULL, 0));

        nodeList.clear();
        nodeIndex.clear();
        obsList.clear();
        return EXIT_SUCCESS;
    }
}

