//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Pedro Pinto, Dez 2023
//
// Graph EXAMPLE
//

#include <stdlib.h>
#include <assert.h>

#include "Graph.h"
#include "GraphGenerator.h"
#include "GraphTopologicalSorting.h"
#include "instrumentation.h"

#define NUM_VERTICES_MAX 1000
#define NUM_EDGES_MAX 1000
#define VERSIONS 3          // Number of different versions of topological sort algorithm

typedef GraphTopoSort* (*TopoSortFcn)(Graph*);

// Pointers to Topological Sort Functions
TopoSortFcn topoSortFcns[VERSIONS] = {
  GraphTopoSortComputeV1,
  GraphTopoSortComputeV2,
  GraphTopoSortComputeV3
};

// Names of Topological Sort Functions
char *topoSortNames[VERSIONS] = {
  "TopoSortV1",
  "TopoSortV2",
  "TopoSortV3"
};

int main(int argc, char* argv[]) {

  assert(argc == 4);

  TopoInit();
    
  for (int numVertices = atoi(argv[1]); numVertices <= atoi(argv[3]); numVertices+= atoi(argv[2])) {
  
    Graph* originalG = GraphGenerateComplete(numVertices);
    
    for (int version = 0; version < VERSIONS; version++) {
        TopoSortFcn sortFcn = topoSortFcns[version];
        //char* sortName = topoSortNames[version];

        Graph *g = GraphCopy(originalG);
        
        //printf("SORT: %s\n", sortName);
        InstrReset();
        GraphTopoSort* result = sortFcn(g);
        InstrPrintTest(numVertices);

        GraphTopoSortDestroy(&result);
        GraphDestroy(&g);
    }
    
    GraphDestroy(&originalG);
  }

	return 0;
}
