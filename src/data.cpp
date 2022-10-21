#include "data.hpp"
#include <future>

void fill_data(double *data, std::size_t nrows, std::size_t ncols,
               bool start_odd) {
  // even rows positive increasing
  for (int row = start_odd; row < nrows; row += 2) {
    std::size_t offset = row * ncols;
    for (int col = 0; col < ncols; ++col) {
      data[offset + col] = col;
    }
  }

  // even rows negative increasing in absolute value
  for (int row = !start_odd; row < nrows; row += 2) {
    std::size_t offset = row * ncols;
    for (int col = 0; col < ncols; ++col) {
      data[offset + col] = -col;
    }
  }
}

dataset generate_data(std::size_t nrows, std::size_t ncols) {
  double *data = new double[nrows * ncols];
  std::size_t nrows_per_thread = nrows / DATA_GENERATION_NTHREADS;
  std::size_t offset = 0;
  std::future<void> futures[DATA_GENERATION_NTHREADS];
  if (nrows_per_thread > 0) {
    for (int i = 0; i < DATA_GENERATION_NTHREADS; ++i) {
      futures[i] =
          std::async(std::launch::async, fill_data, data + offset * ncols,
                     nrows_per_thread, ncols, offset % 2 == 1);
      offset += nrows_per_thread;
    }
  }

  fill_data(data + offset * ncols, nrows % DATA_GENERATION_NTHREADS, ncols,
            offset % 2 == 1);
  if (nrows_per_thread > 0) {
    for (auto &&future : futures) {
      future.wait();
    }
  }

  return std::unique_ptr<double[]>(data);
}
