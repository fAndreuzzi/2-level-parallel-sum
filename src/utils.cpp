#include "utils.hpp"

std::unique_ptr<int[]> stop_array(int r, bool graceful) {
  int *array = new int[2 * r];
  for (int i = 0; i < 2 * r; ++i) {
    array[i] = graceful ? GRACEFUL_STOP : ERROR_STOP;
  }
  return std::unique_ptr<int[]>(array);
}
