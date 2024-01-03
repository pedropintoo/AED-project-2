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

int main(void) {

    Graph* g = GraphGenerateSuccessTopoOrder(8000,50000);

    GraphDisplay(g);
    assert(GraphCheckInvariants(g));
    GraphTopoSort* result = GraphTopoSortComputeV3(g);

    //GraphTopoSortDisplaySequence(result);
    printf("Result: %s\n",GraphTopoSortIsValid(result) ? "Valid" : "Not valid");
    
    GraphTopoSortDestroy(&result);
    GraphDestroy(&g);
    

	return 0;
}
