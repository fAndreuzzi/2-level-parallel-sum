#include "summation.hpp"
#include <future>

double sum_rows_subset(double *data, std::size_t nrows, std::size_t ncols) {
  double acc = 0;
  double *end = data + nrows * ncols;
  while (data != end) {
    acc += *data;
    ++data;
  }
  return acc;
}

double sum_rows(double *data, std::size_t nrows, std::size_t ncols) {
  std::size_t nrows_per_thread = nrows / SUMMATION_NTHREADS;
  std::size_t offset = 0;
  std::future<double> futures[SUMMATION_NTHREADS];
  if (nrows_per_thread > 0) {
    for (int i = 0; i < SUMMATION_NTHREADS; ++i) {
      futures[i] = std::async(std::launch::async, sum_rows_subset,
                              data + offset * ncols, nrows_per_thread, ncols);
      offset += nrows_per_thread;
    }
  }

  double acc =
      sum_rows_subset(data + offset * ncols, nrows % SUMMATION_NTHREADS, ncols);
  if (nrows_per_thread > 0) {
    for (auto &&future : futures) {
      acc += future.get();
    }
  }
  return acc;
}
