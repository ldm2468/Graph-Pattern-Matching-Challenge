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

  // check labels
  for (Vertex i = 0; i < vertexCount; i++) {
    if (data.GetLabel(embedding[i]) != query.GetLabel(i)) {
      return false;
    }
  }

  // check every possible edge of the embedding
  for (Vertex i = 0; i < vertexCount; i++) {
    for (Vertex j = i + 1; j < vertexCount; j++) {
      bool queryIsNeighbor = query.IsNeighbor(i, j);
      bool embeddingIsNeighbor = data.IsNeighbor(embedding[i], embedding[j]);
      if (queryIsNeighbor && !embeddingIsNeighbor) {
        return false;
      }
    }
  }
  return true;
#else
  return true;
#endif
}

void Backtrack::PrintAns(const std::vector<Vertex> &embedding) {
  std::cout << "a";
  for (Vertex i = 0; i < queryVertexCount; i++) {
    std::cout << " " << embedding[i];
  }
  std::cout << std::endl;
  printCount++;
}

bool Backtrack::SolveRow(Vertex queryVertex) {
  if (printCount >= MAX_PRINT_NO) {
    return false;
  }
  if (queryVertex == queryVertexCount) {
    if (!Verify(map)) {
      std::cout << "Incorrect embedding found!" << std::endl;
      return false;
    }
    PrintAns(map);
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
    size_t start = query.GetNeighborStartOffset(queryVertex);
    size_t end = query.GetNeighborEndOffset(queryVertex);
    for (size_t j = start; j < end; j++) {
      Vertex queryVertexNeighbor = query.GetNeighbor(j);
      if (queryVertexNeighbor > queryVertex) {
        continue;
      }
      if (!data.IsNeighbor(map[queryVertexNeighbor], dataVertex)) {
        valid = false;
        break;
      }
    }
    if (valid) {
      map[queryVertex] = dataVertex;
      usedDataVertices[dataVertex] = true;
      SolveRow(queryVertex + 1);
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

  map.clear();
  map.resize(queryVertexCount, 0);

  printCount = 0;
  SolveRow(0);
}
