/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

Backtrack::Backtrack() {}
Backtrack::~Backtrack() {}

bool Backtrack::Verify(const Graph &data, const Graph &query,
                       const std::vector<Vertex> &embedding) {
#ifdef VERIFY_EMBEDDINGS
  size_t vertexCount = query.GetNumVertices();
  if (vertexCount != embedding.size()) {
    // even the size doesn't match
    return false;
  }
  // check every possible edge of the embedding
  for (Vertex i = 0; i < vertexCount; i++) {
    for (Vertex j = i + 1; j < vertexCount; j++) {
      bool queryIsNeighbor = query.IsNeighbor(i, j);
      bool embeddingIsNeighbor = data.IsNeighbor(embedding[i], embedding[j]);
      if (queryIsNeighbor != embeddingIsNeighbor) {
        return false;
      }
    }
  }
  return true;
#else
  return true;
#endif
}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";

  // implement your code here.
}
