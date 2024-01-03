//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Graph Generator
//


#ifndef _GRAPH_GENERATOR_
#define _GRAPH_GENERATOR_

#include "Graph.h"

Graph* GraphGenerateSuccessTopoOrder(unsigned int numVertices, unsigned int numEdges);

Graph* GraphGenerateComplete(unsigned int numVertices);

Graph* GraphGenerateInsuccessTopoOrderWithCycle(unsigned int numVertices, unsigned int numEdges);

#endif  //_GRAPH_GENERATOR_