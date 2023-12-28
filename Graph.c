//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// Graph - Using a list of adjacency lists representation
//

#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "SortedList.h"
#include "instrumentation.h"

struct _Vertex {
  unsigned int id;
  unsigned int inDegree;
  unsigned int outDegree;
  List* edgesList;
};

struct _Edge {
  unsigned int adjVertex;
  double weight;
};

struct _GraphHeader {
  int isDigraph;
  int isComplete;
  int isWeighted;
  unsigned int numVertices;
  unsigned int numEdges;
  List* verticesList;
};

// The comparator for the VERTICES LIST

int graphVerticesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Vertex*)p1)->id;
  unsigned int v2 = ((struct _Vertex*)p2)->id;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// The comparator for the EDGES LISTS

int graphEdgesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Edge*)p1)->adjVertex;
  unsigned int v2 = ((struct _Edge*)p2)->adjVertex;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

Graph* GraphCreate(unsigned int numVertices, int isDigraph, int isWeighted) {
  Graph* g = (Graph*)malloc(sizeof(struct _GraphHeader));
  if (g == NULL) abort();

  g->isDigraph = isDigraph;
  g->isComplete = 0;
  g->isWeighted = isWeighted;

  g->numVertices = numVertices;
  g->numEdges = 0;

  g->verticesList = ListCreate(graphVerticesComparator);

  for (unsigned int i = 0; i < numVertices; i++) {
    struct _Vertex* v = (struct _Vertex*)malloc(sizeof(struct _Vertex));
    if (v == NULL) abort();

    v->id = i;
    v->inDegree = 0;
    v->outDegree = 0;

    v->edgesList = ListCreate(graphEdgesComparator);

    ListInsert(g->verticesList, v);
  }

  assert(g->numVertices == ListGetSize(g->verticesList));

  return g;
}

Graph* GraphCreateComplete(unsigned int numVertices, int isDigraph) {
  Graph* g = GraphCreate(numVertices, isDigraph, 0);

  g->isComplete = 1;

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    struct _Vertex* v = ListGetCurrentItem(vertices);
    List* edges = v->edgesList;
    for (unsigned int j = 0; j < g->numVertices; j++) {
      if (i == j) {
        continue;
      }
      struct _Edge* new = (struct _Edge*)malloc(sizeof(struct _Edge));
      if (new == NULL) abort();
      new->adjVertex = j;
      new->weight = 1;

      ListInsert(edges, new);
    }
    if (g->isDigraph) {
      v->inDegree = g->numVertices - 1;
      v->outDegree = g->numVertices - 1;
    } else {
      v->outDegree = g->numVertices - 1;
    }
  }
  if (g->isDigraph) {
    g->numEdges = numVertices * (numVertices - 1);
  } else {
    g->numEdges = numVertices * (numVertices - 1) / 2;
  }

  return g;
}

void GraphDestroy(Graph** p) {
  assert(*p != NULL);
  Graph* g = *p;

  List* vertices = g->verticesList;
  if (ListIsEmpty(vertices) == 0) {
    ListMoveToHead(vertices);
    unsigned int i = 0;
    for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
      struct _Vertex* v = ListGetCurrentItem(vertices);

      List* edges = v->edgesList;
      if (ListIsEmpty(edges) == 0) {
        unsigned int i = 0;
        ListMoveToHead(edges);
        for (; i < ListGetSize(edges); ListMoveToNext(edges), i++) {
          struct _Edge* e = ListGetCurrentItem(edges);
          free(e);
        }
      }
      ListDestroy(&(v->edgesList));
      free(v);
    }
  }

  ListDestroy(&(g->verticesList));
  free(g);

  *p = NULL;
}

Graph* GraphCopy(const Graph* g) {
  assert(g != NULL);

  // TO BE COMPLETED !!
  Graph* g_new = (Graph*)malloc(sizeof(struct _GraphHeader)); // can't use GraphCreate/GraphCreateComplete, because we can have Complete Graph weighted
  if (g_new == NULL) abort();

  g_new->isDigraph = g->isDigraph;
  g_new->isComplete = g->isComplete;
  g_new->isWeighted = g->isWeighted;

  g_new->numVertices = g->numVertices;
  // g_new->numEdges = g->numEdges; // _addEdge increments it !!!
  
  g_new->verticesList = ListCreate(graphVerticesComparator);
  
  for (unsigned int i = 0; i < g->numVertices; i++) {
    ListMove(g->verticesList,i);
    struct _Vertex* v_new = (struct _Vertex*)malloc(sizeof(struct _Vertex));
    struct _Vertex* v = ListGetCurrentItem(g->verticesList);
    
    v_new->id = v->id; // only this because _addEdge, increments the other vars
    
    v_new->edgesList = ListCreate(graphEdgesComparator); // allocate memory!

    ListInsert(g_new->verticesList,v_new); // add the copy to the list
  }
  
  // Add adjacent vertices
  // Only after, because the _addEdge needs all vertex in verticesList!
  for (unsigned int i = 0; i < g->numVertices; i++) {
    ListMove(g->verticesList,i);
    struct _Vertex* v = ListGetCurrentItem(g->verticesList);
    List* edgesList = v->edgesList;

    // v->outDegree -> number of adjacent vertices
    for (unsigned int i = 0; i < v->outDegree; i++) {
      ListMove(edgesList,i);
      struct _Edge* e = ListGetCurrentItem(edgesList);

      if (g->isWeighted) {
        GraphAddWeightedEdge(g_new,v->id,e->adjVertex,e->weight);
      } else {
        GraphAddEdge(g_new,v->id,e->adjVertex);
      }
    }
  }

  assert(g_new->numVertices == ListGetSize(g_new->verticesList));

  return g_new;
}

Graph* GraphFromFile(FILE* f) {
  assert(f != NULL);

  // TO BE COMPLETED !!
  int isDigraph;
  fscanf(f,"%d",&isDigraph);
  int isWeighted;
  fscanf(f,"%d",&isWeighted);
  int numVertices;
  fscanf(f,"%d",&numVertices);
  int numEdges;
  fscanf(f,"%d",&numEdges);
  
  Graph* g = GraphCreate(numVertices,isDigraph,isWeighted);
  
  int vertex, adjVertex;
  double weight;
  for (int i = 0; i < numEdges; i++) {
    fscanf(f,"%d %d",&vertex,&adjVertex);
     
    if (isWeighted) {
      fscanf(f,"%lf",&weight); // must execute even if they are a self-loop
      if (vertex != adjVertex) GraphAddWeightedEdge(g,vertex,adjVertex,weight); 
    } else {
      if (vertex != adjVertex) GraphAddEdge(g,vertex,adjVertex);
    }
    
    
  }
  
  return g;
}

// Graph

int GraphIsDigraph(const Graph* g) { return g->isDigraph; }

int GraphIsComplete(const Graph* g) { return g->isComplete; }

int GraphIsWeighted(const Graph* g) { return g->isWeighted; }

unsigned int GraphGetNumVertices(const Graph* g) { return g->numVertices; }

unsigned int GraphGetNumEdges(const Graph* g) { return g->numEdges; }

//
// For a graph
//
double GraphGetAverageDegree(const Graph* g) {
  assert(g->isDigraph == 0);
  return 2.0 * (double)g->numEdges / (double)g->numVertices;
}

static unsigned int _GetMaxDegree(const Graph* g) {
  List* vertices = g->verticesList;
  if (ListIsEmpty(vertices)) return 0;

  unsigned int maxDegree = 0;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    struct _Vertex* v = ListGetCurrentItem(vertices);
    if (v->outDegree > maxDegree) {
      maxDegree = v->outDegree;
    }
  }
  return maxDegree;
}

//
// For a graph
//
unsigned int GraphGetMaxDegree(const Graph* g) {
  assert(g->isDigraph == 0);
  return _GetMaxDegree(g);
}

//
// For a digraph
//
unsigned int GraphGetMaxOutDegree(const Graph* g) {
  assert(g->isDigraph == 1);
  return _GetMaxDegree(g);
}

// Vertices

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by indices of the adjacent vertices
//
unsigned int* GraphGetAdjacentsTo(const Graph* g, unsigned int v) {
  assert(v < g->numVertices);

  // Node in the list of vertices
  List* vertices = g->verticesList;
  ListMove(vertices, v);  
  struct _Vertex* vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;
  
  unsigned int* adjacent =
      (unsigned int*)calloc(1 + numAdjVertices, sizeof(unsigned int));

  if (numAdjVertices > 0) {
    adjacent[0] = numAdjVertices;
    List* adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++) {
      struct _Edge* ePointer = ListGetCurrentItem(adjList);
      adjacent[i + 1] = ePointer->adjVertex;
    }
  }

  return adjacent;
}

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by the distances to the adjacent vertices
//
double* GraphGetDistancesToAdjacents(const Graph* g, unsigned int v) {
  assert(v < g->numVertices);

  // Node in the list of vertices
  List* vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex* vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  double* distance = (double*)calloc(1 + numAdjVertices, sizeof(double));

  if (numAdjVertices > 0) {
    distance[0] = numAdjVertices;
    List* adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++) {
      struct _Edge* ePointer = ListGetCurrentItem(adjList);
      distance[i + 1] = ePointer->weight;
    }
  }

  return distance;
}

//
// For a graph
//
unsigned int GraphGetVertexDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 0);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexOutDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexInDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->inDegree;
}

// Edges

static int _addEdge(Graph* g, unsigned int v, unsigned int w, double weight) {
  struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
  edge->adjVertex = w;
  edge->weight = weight;

  ListMove(g->verticesList, v);
  struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
  int result = ListInsert(vertex->edgesList, edge);

  if (result == -1) {
    return 0;
  } else {
    g->numEdges++;
    vertex->outDegree++;

    ListMove(g->verticesList, w);
    struct _Vertex* destVertex = ListGetCurrentItem(g->verticesList);
    destVertex->inDegree++;
  }

  if (g->isDigraph == 0) {
    // Bidirectional edge
    struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
    edge->adjVertex = v;
    edge->weight = weight;

    ListMove(g->verticesList, w);
    struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
    result = ListInsert(vertex->edgesList, edge);

    if (result == -1) {
      return 0;
    } else {
      // g->numEdges++; // Do not count the same edge twice on a undirected
      // graph !!
      vertex->outDegree++;
    }
  }

  return 1;
}

int GraphAddEdge(Graph* g, unsigned int v, unsigned int w) {
  assert(g->isWeighted == 0);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, 1.0);
}

int GraphAddWeightedEdge(Graph* g, unsigned int v, unsigned int w,
                         double weight) {
  assert(g->isWeighted == 1);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, weight);
}

// What's supposed to return?
int GraphRemoveEdge(Graph* g, unsigned int v, unsigned int w) {
  assert(g != NULL);

  // TO BE COMPLETED !!
  assert(v < ListGetSize(g->verticesList) && w < ListGetSize(g->verticesList));
  // assert(GraphCheckInvariants(g));

  // Move to the initial vertex
  ListMove(g->verticesList, v);
  struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
  List* edgeList = vertex->edgesList;
  
  // If the edge list is empty, the edge does not exist
  if (ListIsEmpty(edgeList)) return 0; 

  // Move through the edge list to find the specified edge
  ListMoveToHead(edgeList);
  for (unsigned int i = 0; i < ListGetSize(edgeList); ListMoveToNext(edgeList), i++) {
    struct _Edge* edge = ListGetCurrentItem(edgeList);

    // If the adjacent vertex is greater than w, the edge is not in the list (sorted list!)
    if (edge->adjVertex > w) return 0;

    // If the adjacent vertex matches w, remove the edge
    if (edge->adjVertex == w) {
      ListRemoveCurrent(edgeList);
      g->numEdges--;
      vertex->outDegree--;

      // In a directed graph, only remove the edge in one direction
      if (g->isDigraph) {
        ListMove(g->verticesList, w);
        vertex = ListGetCurrentItem(g->verticesList);
        vertex->inDegree--;
      } else {
        // In an undirected graph, remove the inverse direction edge as well
        ListMove(g->verticesList, w);
        vertex = ListGetCurrentItem(g->verticesList);
        edgeList = vertex->edgesList;

        // Move through the edge list to find the inverse direction edge
        ListMoveToHead(edgeList);
        for (unsigned int j = 0; j < ListGetSize(edgeList); ListMoveToNext(edgeList), j++) {
          struct _Edge* inverseEdge = ListGetCurrentItem(edgeList);

          // If the adjacent vertex matches v, remove the inverse direction edge
          if (inverseEdge->adjVertex == v) {
            ListRemoveCurrent(edgeList);
            vertex->outDegree--;
            break;
          }
        }
      }

      return 1; // Edge removed successfully
    }
  }

  return 0; // Edge not found
}

// CHECKING

int GraphCheckInvariants(const Graph* g) {
  assert(g != NULL);

  // TO BE COMPLETED !!
  unsigned int E = g->numEdges;
  unsigned int V = g->numVertices;
  List* verticesList = g->verticesList;

  // ....

  return 1;
}

// DISPLAYING on the console

void GraphDisplay(const Graph* g) {
  printf("---\n");
  if (g->isWeighted) {
    printf("Weighted ");
  }
  if (g->isComplete) {
    printf("COMPLETE ");
  }
  if (g->isDigraph) {
    printf("Digraph\n");
    printf("Max Out-Degree = %d\n", GraphGetMaxOutDegree(g));
  } else {
    printf("Graph\n");
    printf("Max Degree = %d\n", GraphGetMaxDegree(g));
  }
  printf("Vertices = %2d | Edges = %2d\n", g->numVertices, g->numEdges);

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    printf("%2d ->", i);
    struct _Vertex* v = ListGetCurrentItem(vertices);
    if (ListIsEmpty(v->edgesList)) {
      printf("\n");
    } else {
      List* edges = v->edgesList;
      unsigned int i = 0;
      ListMoveToHead(edges);
      for (; i < ListGetSize(edges); ListMoveToNext(edges), i++) {
        struct _Edge* e = ListGetCurrentItem(edges);
        if (g->isWeighted) {
          printf("   %2d(%4.2f)", e->adjVertex, e->weight);
        } else {
          printf("   %2d", e->adjVertex);
        }
      }
      printf("\n");
    }
  }
  printf("---\n");
}

void GraphListAdjacents(const Graph* g, unsigned int v) {
  printf("---\n");

  unsigned int* array = GraphGetAdjacentsTo(g, v);

  printf("Vertex %d has %d adjacent vertices -> ", v, array[0]);

  for (unsigned int i = 1; i <= array[0]; i++) {
    printf("%d ", array[i]);
  }

  printf("\n");

  free(array);

  printf("---\n");
}
