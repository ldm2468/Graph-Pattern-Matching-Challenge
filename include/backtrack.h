/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include <functional>
#include "candidate_set.h"
#include "common.h"
#include "graph.h"

class Backtrack {
 public:
  Backtrack(const Graph &data, const Graph &query, const CandidateSet &cs);
  ~Backtrack();

  void PrintAllMatches();
 private:
  bool Verify(const std::vector<Vertex> &embedding);
  bool SolveRow(Vertex queryVertex, std::vector<Vertex> map);
  const Graph &data;
  const Graph &query;
  const CandidateSet &cs;
  const size_t dataVertexCount;
  const size_t queryVertexCount;
  std::vector<bool> usedDataVertices;
};

#endif  // BACKTRACK_H_
