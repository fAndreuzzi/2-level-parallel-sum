#include "utils.hpp"
#include <iostream>
#include <memory>
#include <mpi.h>
#include <regex>
#include <string>

// regex used to extract row indices from user input
const std::regex extract_rows = std::regex("sum \\[(\\d+),(\\d+)\\]");

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int r;
  MPI_Comm_size(MPI_COMM_WORLD, &r);

  int status = 0;

  while (true) {
    std::unique_ptr<int[]> send_buffer = nullptr;
    std::unique_ptr<int[]> recv_buffer = std::unique_ptr<int[]>(new int[2]);

    if (rank == 0) {
      std::smatch match;
      std::string user_input;
      std::getline(std::cin, user_input);
      if (regex_search(user_input, match, extract_rows)) {
        std::cout << match.str(1) << ", " << match.str(2) << std::endl;

        int *send_buffer_data = new int[2 * r];
        for (int i = 0; i < 2 * r; ++i) {
          send_buffer_data[i] = 0;
        }
        send_buffer = std::unique_ptr<int[]>(send_buffer_data);
      } else {
        bool error = user_input != "quit";
        if (error) {
          std::cerr << "Invalid input" << std::endl;
        }
        send_buffer = stop_array(r, !error);
      }
    }

    MPI_Scatter(send_buffer.get(), 2, MPI_INT, recv_buffer.get(), 2, MPI_INT, 0,
                MPI_COMM_WORLD);
    status = recv_buffer[0];
    if (status < 0) {
      break;
    }

    std::cout << recv_buffer[0] << ", " << recv_buffer[1] << " (" << rank << ")"
              << std::endl;
  }

  MPI_Finalize();

  if (status == ERROR_STOP && rank == 0) {
    return 1;
  } else {
    return 0;
  }
}
