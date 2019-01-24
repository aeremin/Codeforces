// A loop to repeat operation several times.
//
// * FOR_TIMES(n)
//   Repeats loop body n times, e.g.:
//   ` print("We all live in a");
//   ` FOR_TIMES(3) {
//   `     print(" yellow submarine");
//   ` }

#pragma once


#define FOR_TIMES(N_TIMES) for (auto __counter = (N_TIMES); __counter > 0; --__counter)
