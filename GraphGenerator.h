//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Graph Generator
//


#ifndef _GRAPH_GENERATOR_
#define _GRAPH_GENERATOR_

#include "Graph.h"

Graph* GraphGenerateTopoSuccess(unsigned int numVertices, unsigned int numEdges);

Graph* GraphGenerateTopoInsuccessBest(unsigned int numVertices);

Graph* GraphGenerateTopoInsuccessWorst(unsigned int numVertices, unsigned int numEdges);

#endif  //_GRAPH_GENERATOR_