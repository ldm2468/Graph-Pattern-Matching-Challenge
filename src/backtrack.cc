/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

Backtrack::Backtrack(const Graph &data, const Graph &query, const CandidateSet &cs):
           data(data), query(query), cs(cs),
           dataVertexCount(data.GetNumVertices()),
           queryVertexCount(query.GetNumVertices()) {

}

Backtrack::~Backtrack() {}

bool Backtrack::Verify(const std::vector<Vertex> &embedding) {
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

bool Backtrack::SolveRow(Vertex queryVertex, std::vector<Vertex> map) {
  if (queryVertex == queryVertexCount) {
    if (!Verify(map)) {
      std::cout << "Incorrect embedding found!" << std::endl;
      return false;
    }
    // print answer
    std::cout << "a";
    for (Vertex i = 0; i < queryVertexCount; i++) {
      std::cout << " " << map[i];
    }
    std::cout << std::endl;
    return true;
  }

  size_t candidates = cs.GetCandidateSize(queryVertex);
  for (Vertex i = 0; i < candidates; i++) {
    Vertex dataVertex = cs.GetCandidate(queryVertex, i);
    if (usedDataVertices[dataVertex]) {
      continue;
    }
    // check valid mapping
    bool valid = true;
    for (Vertex j = 0; j < queryVertex; j++) {
      bool queryIsNeighbor = query.IsNeighbor(j, queryVertex);
      bool dataIsNeighbor = data.IsNeighbor(map[j], dataVertex);
      if (queryIsNeighbor != dataIsNeighbor) {
        valid = false;
        break;
      }
    }
    if (valid) {
      map[queryVertex] = dataVertex;
      usedDataVertices[dataVertex] = true;
      SolveRow(queryVertex + 1, map);
      usedDataVertices[dataVertex] = false;
    }
  }
  return false;
}

void Backtrack::PrintAllMatches() {
  std::cout << "t " << query.GetNumVertices() << "\n";

  usedDataVertices.clear();
  for (Vertex i = 0; i < dataVertexCount; i++) {
    usedDataVertices.push_back(false);
  }

  std::vector<Vertex> map(queryVertexCount);

  SolveRow(0, map);
}
