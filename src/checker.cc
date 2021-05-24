#include <unistd.h>
#include <sstream>
#include "checker.h"
#include "backtrack.h"

#define PIPE_READ 0
#define PIPE_WRITE 1
#define LINE_BUFFER_SIZE 65536

void Checker::Run(const std::string& filename) {
  std::cout << "Running checker..." << std::endl;

  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cout << "Checker file " << filename << " not found!\n";
    exit(EXIT_FAILURE);
  }

  std::string executable;
  fin >> executable;
  while (!fin.eof()) {
    std::string data, query, cs;
    fin >> data >> query >> cs;
    if (data.empty() || query.empty() || cs.empty()) {
      break;
    }
    RunSingle(executable, data, query, cs);
  }
  fin.close();
}

void Checker::RunSingle(const std::string &executable, const std::string &data,
                        const std::string &query, const std::string &cs) {
  int pp[2];
  pid_t pid;
  if (pipe(pp)) {
    std::cerr << "pipe() failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if (!pid) {
    close(pp[PIPE_READ]);
    dup2(pp[PIPE_WRITE], 1); // stdout
    execl(executable.data(), executable.data(), data.data(), query.data(), cs.data(), NULL);
    std::cerr << "execl() failed!" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    close(pp[PIPE_WRITE]);

    Graph dataGraph(data);
    Graph queryGraph(query, true);
    CandidateSet candidateSet(cs);
    Backtrack backtrack(dataGraph, queryGraph, candidateSet);

    // Unfortunately, there is no way to convert a pipe file descriptor
    // to std::ifstream in standard C++11, so we use a FILE * instead.
    FILE *fp = fdopen(pp[PIPE_READ], "r");

    char buf[LINE_BUFFER_SIZE];

    int32_t embeddingSize = -1;
    char type;

    int32_t correctCount = 0;
    int32_t incorrectCount = 0;

    while (fgets(buf, LINE_BUFFER_SIZE, fp)) {
      std::stringstream stream(buf);
      stream >> type;
      if (type == 't') {
        stream >> embeddingSize;
      } else if (type == 'a') {
        std::vector<Vertex> vertices;
        for (int i = 0; i < embeddingSize; i++) {
          Vertex v;
          stream >> v;
          vertices.push_back(v);
        }

        if (backtrack.Verify(vertices)) {
          correctCount++;
        } else {
          incorrectCount++;
        }
      } else {
        std::cerr << "Invalid output format!" << std::endl;
        break;
      }
    }
    fclose(fp);
    std::cout << "Correct: " << correctCount << std::endl;
    std::cout << "Incorrect: " << incorrectCount << std::endl;
  }
}
