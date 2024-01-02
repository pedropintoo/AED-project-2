GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED

  unsigned int numVertices = topoSort->numVertices;
  
  Graph* g_copy = GraphCopy(g);

  // index of sequence
  unsigned int s = 0; 

  // Iterate until all vertices are included in the topological sort
  for (int selected = 1; selected; ) {
    selected = 0;

    // Iterate through vertices to find those with in-degree 0 and that is not marked
    for (unsigned int v = 0; v < numVertices; v++) {
      if (!topoSort->marked[v] && GraphGetVertexInDegree(g_copy, v) == 0) {
        // Save the vertex in the sequence
        topoSort->vertexSequence[s++] = v;
        topoSort->marked[v] = 1;  // Mark the vertex as visited
        selected = 1;  // Set the flag to indicate a vertex is selected

        // Remove outgoing edges from the selected vertex
        unsigned int* adjacentsTo = GraphGetAdjacentsTo(g_copy, v); // allocate memory !!
        for (unsigned int i = 1; i <= adjacentsTo[0]; i++) { // element 0, stores the number of adjacent vertices
          GraphRemoveEdge(g_copy, v, adjacentsTo[i]);
        }
        free(adjacentsTo);

        break; // other selected vertex
      }
    }
  }

  // If the sequence includes all vertices, mark the result as valid
  if (s == numVertices) topoSort->validResult = 1;

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

  unsigned int numVertices = topoSort->numVertices;

  // Start all the incoming edge in aux array
  for (unsigned int i = 0; i < numVertices; i++) {
    topoSort->numIncomingEdges[i] = GraphGetVertexInDegree(g,i);
  }

  // index of sequence
  unsigned int s = 0; 

  // Iterate until all vertices are included in the topological sort
  for (int selected = 1; selected; ) {
    selected = 0;

    // Iterate through vertices to find those with in-degree 0 and that is not marked
    for (unsigned int v = 0; v < numVertices; v++) {
      if (!topoSort->marked[v] && topoSort->numIncomingEdges[v] == 0) {
        // Save the vertex in the sequence
        topoSort->vertexSequence[s++] = v;
        topoSort->marked[v] = 1;  // Mark the vertex as visited
        selected = 1;  // Set the flag to indicate a vertex is selected

        // 
        if(GraphGetVertexOutDegree(g,v) == 0) break; // other selected vertex

        // Decrease incoming edges from the adjacent vertices of selected vertex
        unsigned int* adjacentsTo = GraphGetAdjacentsTo(g, v); // allocate memory !!
        for (unsigned int i = 1; i <= adjacentsTo[0]; i++) {
          // adjacent vertex
          unsigned int w = adjacentsTo[i];

          topoSort->numIncomingEdges[w]--;
        }
        free(adjacentsTo);
        break; // other selected vertex
      }
    }

  }

  // If the sequence includes all vertices, mark the result as valid
  if (s == numVertices) topoSort->validResult = 1;

  return topoSort;
}


GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting

  // TO BE COMPLETED
  
  unsigned int numVertices = topoSort->numVertices;
  
  // Queue of vertices
  Queue* queue = QueueCreate(numVertices);

  // Start all the incoming edge in aux array
  for (unsigned int i = 0; i < numVertices; i++) {
    int inDegree = GraphGetVertexInDegree(g,i);
    topoSort->numIncomingEdges[i] = inDegree;
    if (inDegree == 0) QueueEnqueue(queue,i);
  }

  // index of sequence
  unsigned int s; 

  // Iterate until all vertices are included in the topological sort
  for (s = 0; !QueueIsEmpty(queue); s++){

    // vertex with 0 incomingEdges
    unsigned int v = QueueDequeue(queue);

    // Save the vertex in the sequence
    topoSort->vertexSequence[s] = v;

    // GraphGetAdjacentsTo not handle empty situations!
    if(GraphGetVertexOutDegree(g,v) == 0) continue; 

    // Decrease incoming edges from the adjacent vertices of selected vertex
    unsigned int* adjacentsTo = GraphGetAdjacentsTo(g, v); // allocate memory !!
    for (unsigned int i = 1; i <= adjacentsTo[0]; i++) {
      // adjacent vertex
      unsigned int w = adjacentsTo[i];

      if (--topoSort->numIncomingEdges[w] == 0) QueueEnqueue(queue,w);
    }
    free(adjacentsTo);

  }

  // If the sequence includes all vertices, mark the result as valid
  if (s == numVertices) topoSort->validResult = 1;
  
  QueueDestroy(&queue);

  return topoSort;
}