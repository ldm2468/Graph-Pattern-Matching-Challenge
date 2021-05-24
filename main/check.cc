#include "checker.h"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << "Usage: ./check <checker file name>" << std::endl;
    return EXIT_FAILURE;
  }
  Checker checker;
  checker.Run(argv[1]);
  return EXIT_SUCCESS;
}
