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

#define MAX_PRINT_NO 100000

class Backtrack {
 public:
  Backtrack(const Graph &data, const Graph &query, const CandidateSet &cs);
  ~Backtrack();

  void PrintAllMatches();
  bool Verify(const std::vector<Vertex> &embedding);
 private:
  void PrintAns(const std::vector<Vertex> &embedding);
  bool SolveRow(Vertex queryVertex);
  const Graph &data;
  const Graph &query;
  const CandidateSet &cs;
  const size_t dataVertexCount;
  const size_t queryVertexCount;
  std::vector<bool> usedDataVertices;
  std::vector<Vertex> map;
  int32_t printCount;
};

#endif  // BACKTRACK_H_
