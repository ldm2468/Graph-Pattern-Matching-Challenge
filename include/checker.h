#ifndef SUBGRAPH_MATCHING_CHECKER_H
#define SUBGRAPH_MATCHING_CHECKER_H

#include "common.h"

class Checker {
 public:
  void Run(const std::string& filename);
 private:
  void RunSingle(const std::string& executable, const std::string &data,
                 const std::string &query, const std::string &cs);
};

#endif //SUBGRAPH_MATCHING_CHECKER_H
