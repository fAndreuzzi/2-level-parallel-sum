#pragma once

#include <cstddef>

#ifndef SUMMATION_NTHREADS
#define SUMMATION_NTHREADS 4
#endif

/**
 * @brief Sum the first nrows of the given dataset.
 *
 * @param data_start Pointing to the first element of the dataset.
 * @param nrows Number of rows to sum.
 * @param ncols Number of columns in each row.
 * @return double
 */
double sum_rows(double *data_start, std::size_t nrows, std::size_t ncols);
