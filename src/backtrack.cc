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

bool Backtrack::SolveRow(int current, std::vector<Vertex> map) {
  if (printCount >= MAX_PRINT_NO) {
    return false;
  }
  if (current == queryVertexCount) {
    if (!Verify(map)) {
      std::cout << "Incorrect embedding found!" << std::endl;
      return false;
    }
    PrintAns(map);
    return true;
  }
  Vertex queryVertex = queryVertices[current].first;

  size_t candidates = queryVertices[current].second;
  for (Vertex i = 0; i < candidates; i++) {
    Vertex dataVertex = cs.GetCandidate(queryVertex, i);
    if (usedDataVertices[dataVertex]) {
      continue;
    }
    // check valid mapping
    bool valid = true;
    for (Vertex j = 0; j < current; j++) {
      Vertex prevQueryVertex = queryVertices[j].first;
      bool queryIsNeighbor = query.IsNeighbor(prevQueryVertex, queryVertex);
      bool dataIsNeighbor = data.IsNeighbor(map[prevQueryVertex], dataVertex);
      if (queryIsNeighbor && !dataIsNeighbor) {
        valid = false;
        break;
      }
    }
    if (valid) {
      map[queryVertex] = dataVertex;
      usedDataVertices[dataVertex] = true;
      SolveRow(current + 1, map);
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

  queryVertices.clear();
  for (Vertex i = 0; i < queryVertexCount; i++) {
    queryVertices.emplace_back(i, cs.GetCandidateSize(i));
  }
  std::sort(queryVertices.begin(), queryVertices.end(),
            [](const std::pair<Vertex, size_t> a, const std::pair<Vertex, size_t> b) {
              return a.second < b.second;
            });

  printCount = 0;
  SolveRow(0, map);
}
