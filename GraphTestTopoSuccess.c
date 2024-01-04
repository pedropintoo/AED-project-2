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

  assert(argc == 6);

  TopoInit();
  
  if (atoi(argv[1]) == 0) { // Edges change
    unsigned int NUM_VERTICES = atoi(argv[5]);
    
    for (int numEdges = atoi(argv[2]); numEdges <= atoi(argv[4]); numEdges+= atoi(argv[3])) {
    
      Graph* originalG = GraphGenerateTopoSuccess(NUM_VERTICES,numEdges);

      for (int version = 0; version < VERSIONS; version++) {
          TopoSortFcn sortFcn = topoSortFcns[version];
          //char* sortName = topoSortNames[version];

          Graph *g = GraphCopy(originalG);
          
          //printf("SORT: %s\n", sortName);
          InstrReset();
          GraphTopoSort* result = sortFcn(g);
          InstrPrintTest(numEdges);

          GraphTopoSortDestroy(&result);
          GraphDestroy(&g);
      }
      
      GraphDestroy(&originalG);
    }
  } else { // Vertices change
    unsigned int NUM_EDGES = atoi(argv[5]);

    for (int numVertices = atoi(argv[2]); numVertices <= atoi(argv[4]); numVertices+= atoi(argv[3])) {
    
      Graph* originalG = GraphGenerateTopoSuccess(numVertices,NUM_EDGES);

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
  }
	return 0;
}
