#include <iostream>
#include <mpi.h>
#include <string>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::string user_input;

  std::cin >> user_input;
  while (rank != "quit") {
    // TODO
  }

  MPI_Finalize();
}
