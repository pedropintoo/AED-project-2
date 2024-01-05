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

#define VERSIONS 3          // Number of different versions of topological sort algorithm

typedef GraphTopoSort* (*TopoSortFcn)(Graph*);

// Pointers to Topological Sort Functions
TopoSortFcn topoSortFcns[VERSIONS] = {
  GraphTopoSortComputeV1,
  GraphTopoSortComputeV2,
  GraphTopoSortComputeV3
};

// Pointers to Topological Sort Functions
TopoSortFcn topoSortFcns[VERSIONS] = {
  GraphTopoSortComputeV1,
  GraphTopoSortComputeV2,
  GraphTopoSortComputeV3
};

int main(int argc, char* argv[]) {

  assert(argc == 5);

  TopoInit();

  unsigned int CASE = atoi(argv[1]); // selected case
  unsigned int MIN_VERTICES = atoi(argv[2]); // start for the for loop
  unsigned int INC_VERTICES = atoi(argv[3]); // increment for the for loop
  unsigned int MAX_VERTICES = atoi(argv[4]); // end for the for loop

  switch (CASE)
  {
  case 0: // Success: Worst Case
    for (int numVertices = MIN_VERTICES; numVertices <= INC_VERTICES; numVertices+= MAX_VERTICES) {
  
      Graph* G = GraphGenerateTopoSuccessWorst(numVertices); // Generate Success Worst Case Graph
      
      for (int version = 0; version < VERSIONS; version++) {
        TopoSortFcn sortFcn = topoSortFcns[version];
        
        InstrReset();
        GraphTopoSort* result = sortFcn(G); // Execute sort algorithm in all versions
        InstrPrintTest(numVertices);  // Display the table

        GraphTopoSortDestroy(&result);
      }
      
      GraphDestroy(&G);
    }
    break;
  case 1: // Success: Best Case
    for (int numVertices = MIN_VERTICES; numVertices <= INC_VERTICES; numVertices+= MAX_VERTICES) {
    
      Graph* G = GraphGenerateTopoSuccessBest(numVertices); // Generate Success Best Case Graph
      
      for (int version = 0; version < VERSIONS; version++) {
        TopoSortFcn sortFcn = topoSortFcns[version];
        
        InstrReset();
        GraphTopoSort* result = sortFcn(G); // Execute sort algorithm in all versions
        InstrPrintTest(numVertices);  // Display the table

        GraphTopoSortDestroy(&result);
      }
      
      GraphDestroy(&G);
    }
    break;
  case 2: // Insuccess: Worst Case
    for (int numVertices = MIN_VERTICES; numVertices <= INC_VERTICES; numVertices+= MAX_VERTICES) {
    
      Graph* G = GraphGenerateTopoInsuccessWorst(numVertices); // Generate Insuccess Worst Case Graph
      
      for (int version = 0; version < VERSIONS; version++) {
        TopoSortFcn sortFcn = topoSortFcns[version];
        
        InstrReset();
        GraphTopoSort* result = sortFcn(G); // Execute sort algorithm in all versions
        InstrPrintTest(numVertices);  // Display the table

        GraphTopoSortDestroy(&result);
      }
      
      GraphDestroy(&G);
    }
    break;
  case 3: // Insuccess: Best Case
    for (int numVertices = MIN_VERTICES; numVertices <= INC_VERTICES; numVertices+= MAX_VERTICES) {
    
      Graph* G = GraphGenerateTopoInsuccessWorst(numVertices); // Generate Insuccess Worst Case Graph
      
      for (int version = 0; version < VERSIONS; version++) {
        TopoSortFcn sortFcn = topoSortFcns[version];
        
        InstrReset();
        GraphTopoSort* result = sortFcn(G); // Execute sort algorithm in all versions
        InstrPrintTest(numVertices);  // Display the table

        GraphTopoSortDestroy(&result);
      }
      
      GraphDestroy(&G);
    }
    break;
  }

	return 0;
}
