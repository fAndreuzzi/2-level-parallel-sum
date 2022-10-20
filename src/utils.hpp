#pragma once

#include <memory>

// stop triggered by "quit" input
constexpr int GRACEFUL_STOP = -1;
// stop triggered by invalid input
constexpr int ERROR_STOP = -2;

/**
 * @brief construct an array to inform MPI child processes that they should
 * stop, either gracefully or due to an invalid input
 *
 * @param r Number of MPI processes.
 * @param graceful Flag to communicate graceful or error stop.
 */
std::unique_ptr<int[]> stop_array(int r, bool graceful);
