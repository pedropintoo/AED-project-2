//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"

struct _GraphTopoSort {
  int* marked;                     // Aux array
  unsigned int* numIncomingEdges;  // Aux array
  unsigned int* vertexSequence;    // The result
  int validResult;                 // 0 or 1
  unsigned int numVertices;        // From the graph
  Graph* graph;
};

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort* _create(Graph* g) {
  assert(g != NULL);

  GraphTopoSort* p = NULL;

  // TO BE COMPLETED
  p = (GraphTopoSort*)malloc(sizeof(GraphTopoSort));
  if (p == NULL) abort();

  // calloc?
  p->marked = (int*)calloc(GraphGetNumVertices(g),sizeof(int));
  p->numIncomingEdges = (unsigned int*)calloc(GraphGetNumEdges(g),sizeof(unsigned int));
  p->vertexSequence = (unsigned int*)calloc(GraphGetNumVertices(g),sizeof(unsigned int));

  p->validResult = 0;
  p->numVertices = GraphGetNumVertices(g);
  p->graph = g;

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  
  Graph* g_copy = GraphCopy(g);

  // index of sequence
  unsigned int s = 0; 

  // Iterate until all vertices are included in the topological sort
  for (int selected = 1; selected; ) {
    selected = 0;

    // Iterate through vertices to find those with in-degree 0 and that is not marked
    for (unsigned int v = 0; v < GraphGetNumVertices(g_copy); v++) {
      if (!topoSort->marked[v] && GraphGetVertexInDegree(g_copy, v) == 0) {
        // Save the vertex in the sequence
        topoSort->vertexSequence[s++] = v;
        topoSort->marked[v] = 1;  // Mark the vertex as visited
        selected = 1;  // Set the flag to indicate a vertex is selected

        // Remove outgoing edges from the selected vertex
        unsigned int* adjacentsTo = GraphGetAdjacentsTo(g_copy, v);
        for (unsigned int i = 1; i <= adjacentsTo[0]; i++) {
          GraphRemoveEdge(g_copy, v, adjacentsTo[i]);
        }

        break; // other selected vertex
      }
    }
  }

  // If the sequence includes all vertices, mark the result as valid
  if (s == topoSort->numVertices) topoSort->validResult = 1;

  GraphDestroy(&g_copy);

  return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV2(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  //...

  return topoSort;
}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  //...

  return topoSort;
}

void GraphTopoSortDestroy(GraphTopoSort** p) {
  assert(*p != NULL);

  GraphTopoSort* aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort* p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int* GraphTopoSortGetSequence(const GraphTopoSort* p) {
  assert(p != NULL);
  // TO BE COMPLETED
  // ...
  return NULL;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort* p) {
  assert(p != NULL);

  if (p->validResult == 0) {
    printf(" *** The topological sorting could not be computed!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort* p) {
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0) {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
