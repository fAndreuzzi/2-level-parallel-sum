#include "summation.hpp"
#include <future>
#include <iostream>

double sum_rows_subset(double *data, std::size_t nrows, std::size_t ncols) {
  double acc = 0;
  double *end = data + nrows * ncols;
  std::cout << "start" << std::endl;
  while (data != end) {
    acc += *data;
    ++data;
  }
  std::cout << "over" << std::endl;
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

  double acc = sum_rows_subset(data + offset * ncols, nrows_per_thread, ncols);
  if (nrows_per_thread > 0) {
    for (auto &&future : futures) {
      acc += future.get();
    }
  }
  return acc;
}
