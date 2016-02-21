#pragma once


enum class IterationResult {
  Done,
  Aborted,
};

enum class IterationControl {
  Proceed,
  AbortGently,
  AbortBluntly,
};
