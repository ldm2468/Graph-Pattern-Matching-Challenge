/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include "candidate_set.h"
#include "common.h"
#include "graph.h"

class Backtrack {
 public:
  Backtrack();
  ~Backtrack();

  bool Verify(const Graph &data, const Graph &query, const std::vector<Vertex> &embedding);
  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);
};

#endif  // BACKTRACK_H_
