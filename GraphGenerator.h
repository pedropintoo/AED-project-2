//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Graph Generator
//


#ifndef _GRAPH_GENERATOR_
#define _GRAPH_GENERATOR_

#include "Graph.h"

Graph* GraphGenerateTopoSuccessWorst(unsigned int numVertices);

Graph* GraphGenerateTopoSuccessBest(unsigned int numVertices);

Graph* GraphGenerateTopoInsuccessWorst(unsigned int numVertices);

Graph* GraphGenerateTopoInsuccessBest(unsigned int numVertices);

#endif  //_GRAPH_GENERATOR_