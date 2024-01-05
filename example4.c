//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Pedro Pinto, Dez 2023
//
// Graph EXAMPLE
//

#include <stdlib.h>

#include "Graph.h"
#include "GraphGenerator.h"
#include "GraphTopologicalSorting.h"

int main(void) {
  
  Graph* originalG = GraphGenerateTopoInsuccessWorst(10);

  GraphDisplay(originalG);

  GraphTopoSort* topoSort = GraphTopoSortComputeV3(originalG);

  GraphTopoSortDisplaySequence(topoSort);

  GraphTopoSortDestroy(&topoSort);
  GraphDestroy(&originalG);
  // GraphCopy
	// Graph* g01 = GraphCreate(6, 1, 1); // (numVertices, isDigraph, isWeighted)
	// Graph* g01_copy = GraphCopy(g01);
	// GraphAddWeightedEdge(g01, 1, 2,0);
	// GraphAddWeightedEdge(g01, 1, 4,0);
	// GraphAddWeightedEdge(g01, 3, 4,0);
	// printf("The first graph:\n");
	// GraphDisplay(g01);
  // GraphAddWeightedEdge(g01_copy, 2, 4,0.5);
  // printf("The copy graph:\n");
  // GraphDisplay(g01_copy);

	// GraphDestroy(&g01);
	// GraphDestroy(&g01_copy);

  // // GraphGraphFromFile
  // printf("\n\n");
  // FILE* f = fopen("GRAPHS/SWmediumDG.txt","r");
  // Graph* g02 = GraphFromFile(f);
  // GraphDisplay(g02);

  // // GraphRemoveEdge
  // printf("After remove (6,3):\n");
  // GraphRemoveEdge(g02,6,2);
  // GraphDisplay(g02);
  // for (unsigned int i = 0; i < GraphGetNumVertices(g02); i++) {
  //   GraphListAdjacents(g02, i);
  // }

  // GraphDestroy(&g02);
  // fclose(f);

	return 0;
}
