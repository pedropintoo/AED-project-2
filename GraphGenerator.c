//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Graph Generator
//

#include "GraphGenerator.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Graph.h"

Graph *GraphGenerateTopoSuccess(unsigned int numVertices, unsigned int numEdges)
{
    assert(numEdges <= numVertices*(numVertices-1)/2); // Max number of edges
    assert(numEdges > 0);

    Graph* g = GraphCreate(numVertices, 1, 0);
    srand(time(NULL));

    GraphAddEdge(g,0,1);

    while (GraphGetNumEdges(g) != numEdges) {
        for (unsigned int v = 0; v < numVertices - 1; v++) { // last vertex don't have adjacents

            unsigned int numAddEdge = rand() % 2;

            if (GraphGetNumEdges(g) + numAddEdge > numEdges) continue; // not possible
            if (GraphGetVertexOutDegree(g,v) + numAddEdge >= numVertices - v) continue;

            unsigned int counter = 0;
            while(counter < numAddEdge) {
                
                unsigned int w = rand() % (numVertices-1-v) + 1 + v;

                if(GraphAddEdge(g,v,w)) counter++;  // vertex added!

            }
        }
    }

    return g;
}

Graph *GraphGenerateTopoInsuccessBest(unsigned int numVertices)
{
    // Generate a complete digraph
    return GraphCreateComplete(numVertices, 1);
}

Graph *GraphGenerateTopoInsuccessWorst(unsigned int numVertices, unsigned int numEdges)
{   
    Graph* originalG = GraphGenerateTopoSuccess(numVertices,numEdges-1);

    GraphAddEdge(originalG,1,0); // add loop in 2 lowest id vertices 
    GraphDisplay(originalG);
    return originalG;
}
