#include "utils.hpp"
#include <iostream>

std::unique_ptr<int[]> stop_array(int r, bool graceful) {
  int *array = new int[2 * r];
  for (int i = 0; i < 2 * r; ++i) {
    array[i] = graceful ? GRACEFUL_STOP : ERROR_STOP;
  }
  return std::unique_ptr<int[]>(array);
}

std::unique_ptr<int[]> prepare_pairs(int r, std::size_t x, std::size_t y) {
  int *send_buffer_data = new int[2 * r];

  int i;
  for (i = 0; (i + 1) * N < x + 1; ++i) {
    send_buffer_data[2 * i] = 0;
    send_buffer_data[2 * i + 1] = 0;
  }

  send_buffer_data[2 * i] = x % N;
  for (; (i + 1) * N < y + 1; ++i) {
    send_buffer_data[2 * i + 1] = N - 1;
    send_buffer_data[2 * (i + 1)] = 0;
  }
  send_buffer_data[2 * i + 1] = y % N;

  for (++i; i < r; ++i) {
    send_buffer_data[2 * i] = 0;
    send_buffer_data[2 * i + 1] = 0;
  }

  return std::unique_ptr<int[]>(send_buffer_data);
}

bool check_rows(int r, std::size_t x, std::size_t y) {
  return x <= y && y < r * N;
}
