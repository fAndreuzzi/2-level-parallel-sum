#pragma once

#include <memory>

// number of rows per MPI process
#ifndef NTHREADS
#define NTHREADS 4
#endif

using dataset = std::unique_ptr<double[]>;

/**
 * @brief Generate a dataset according to some rule.
 *
 * @param nrows Number of rows.
 * @param ncols Number of columns
 * @return dataset
 */
dataset generate_data(std::size_t nrows, std::size_t ncols);
