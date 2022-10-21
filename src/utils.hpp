#pragma once

#include <memory>
#include <cstddef>

// stop triggered by "quit" input
constexpr int GRACEFUL_STOP = -1;
// stop triggered by invalid input
constexpr int ERROR_STOP = -2;

// number of rows per MPI process
#ifndef N
#define N 1000
#endif

// number of columns per rows
#ifndef M
#define M 1000000
#endif

/**
 * @brief Construct an array to inform MPI child processes that they should
 * stop, either gracefully or due to an invalid input
 *
 * @param r Number of MPI processes.
 * @param graceful Flag to communicate graceful or error stop.
 * @return std::unique_ptr<int[]>
 */
std::unique_ptr<int[]> stop_array(int r, bool graceful);

/**
 * @brief Prepare row pairs for each child process.
 *
 * @param r Number of MPI processes.
 * @param x See symbol x in problem specs.
 * @param y See symbol y in problem specs.
 * @return std::unique_ptr<int[]>
 */
std::unique_ptr<int[]> prepare_pairs(int r, std::size_t x, std::size_t y);

/**
 * @brief Check that the given rows make sense.
 *
 * @param r Number of MPI processes.
 * @param x Lower bound.
 * @param y Upper bound.
 * @return bool
 */
bool check_rows(int r, std::size_t x, std::size_t y);
