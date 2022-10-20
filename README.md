# 2-level large-scale Sum

In general, this small program should simulate algebra on data, which doesn't
fit into memory on one rank, but can be split and every part would fit into
individua rank's memory:
- a MPI application runnign on #Nr ranks;
- every rank is "responsible" for "its part of data with N rows, indices \[#r\*N
  -> (#r+1)\*N)" ... that it, N rows from rank 0 have incides 0->N-1, from rank
  1 : N->2N-1 etc.
- every rank initializes an array NxM (where N ~ 1-10 000, M ~ 10^6 - 10^9 )
  doubles, with some data (generated or read from file...) ... can be random,
  can be #rank, can be some values. N and M can be small, can be huge, but one
  should no make assumptotion that they are small.... just data should fit into
  memory
- rank 0 listens for input (keyboard eg.)
- if input "sum \[x,y\]", then user would like to sum-up rows with indices X to
  Y...
  - rank 0 "splits" range x-y into ranges for corresponding ranks, and send with
    MPI p2p requests to the ranks with the requred data to sum-up own part of
    data and to return the result.
  - every rank does its part of job and returns result to rank 0
  - rank 0 collects results, performs final summation and displays result.
- input "quit" should stop execution
- every calculaton or request should be independent an C++11 async-task, that it
  , every rank has tasks, which listens to MPI requests and spawns another task,
  which calculates and wich returns results.
