// Assertions.
//
// - CHECK: assertion that is always enabled.
// - CHECK_DEFAULT: check that is by default enabled everywhere.
// - CHECK_DEBUG: check that is by default enabled only during local launches.
// - CHECK_INTERNAL: checks used to spot internal error in the library,
//       expected to be disabled during the contest, even locally.
//
// Warning. Never put statements with side effects in checks other than CHECK!
//
// TODO: Instruction on enabling/disabling checks.
//
// The same as above, in a table form:
//
//                | On server         | On local PC       | In library tests  |
// ---------------+-------------------+-------------------+-------------------+
// CHECK          | Yes               | Yes               | Yes               |
// CHECK_DEFAULT  | Yes by default    | Yes               | Yes/No            |
// CHECK_DEBUG    | No by default     | Yes               | Yes/No            |
// CHECK_INTERNAL | No                | No                | Yes/No            |
//
// Note that library is tested both with checks and without to make sure that
// optional CHECKs don't have side effects.  // TODO: Don't forget to actually do this.

#pragma once

#include "util/macro.h"


namespace internal {
bool library_tests__enable_checks();
}  // namespace internal

// TODO: Print line and file, as assert does.
#define CHECK(EXPRESSION)     \
    do {                      \
      if (!(EXPRESSION))      \
        abort();              \
    } while (false)

#define INTERNAL_CHECK_CONDITIONALLY(EXPRESSION)  \
    do {                                          \
      if (library_tests__enable_checks())         \
        CHECK(EXPRESSION);                        \
    } while (false)


#ifndef CHECK_LEVEL
#  if defined LIBRARY_TEST
#    define CHECK_LEVEL 3
#  elif defined LOCAL_PC
#    define CHECK_LEVEL 2
#  else
#    define CHECK_LEVEL 1
#  endif
#endif

#if CHECK_LEVEL == 0
#  define CHECK_DEFAULT(EXPRESSION)   NOOP()
#  define CHECK_DEBUG(EXPRESSION)     NOOP()
#  define CHECK_INTERNAL(EXPRESSION)  NOOP()
#elif CHECK_LEVEL == 1
#  define CHECK_DEFAULT(EXPRESSION)   CHECK(EXPRESSION)
#  define CHECK_DEBUG(EXPRESSION)     NOOP()
#  define CHECK_INTERNAL(EXPRESSION)  NOOP()
#elif CHECK_LEVEL == 2
#  define CHECK_DEFAULT(EXPRESSION)   CHECK(EXPRESSION)
#  define CHECK_DEBUG(EXPRESSION)     CHECK(EXPRESSION)
#  define CHECK_INTERNAL(EXPRESSION)  NOOP()
#elif CHECK_LEVEL == 3
#  define CHECK_DEFAULT(EXPRESSION)   INTERNAL_CHECK_CONDITIONALLY(EXPRESSION)
#  define CHECK_DEBUG(EXPRESSION)     INTERNAL_CHECK_CONDITIONALLY(EXPRESSION)
#  define CHECK_INTERNAL(EXPRESSION)  INTERNAL_CHECK_CONDITIONALLY(EXPRESSION)
#endif
