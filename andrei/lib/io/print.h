// TODO: Set fixed format floating-point by default somewhere
// TODO: Do we need printing library?

#pragma once

#include <cstdio>
#include <iostream>


#if 0
// Float format: fixed or scientific.
struct IoFloatRepresentation {
  enum Representation {
    Fixed,
    Scientific,
  };

  Representation value;
};

// Floating point precision.
struct IoPrecision {
  int value;
};

// Width. Smaller output will be left-padded with spaces.
struct IoWidth {
  int value;
};

struct OutputFlags {
  IoFloatRepresentation float_representation;
  IoPrecision precision;
  IoWidth width;
};

OutputFlags output_flags;

template<typename IoFlagT>
void operator|(OutputFlags& flags, IoFlagT new_flag);
template<typename IoFloat>
OutputFlags& operator|(OutputFlags& flags, IoFloatRepresentation new_flag)  { flags.float_representation = new_flag;  return flags; }
template<typename IoFloat>
OutputFlags& operator|(OutputFlags& flags, IoPrecision new_flag)  { flags.precision = new_flag;  return flags; }
template<typename IoFloat>
OutputFlags& operator|(OutputFlags& flags, IoWidth new_flag)  { flags.width = new_flag;  return flags; }

template<typename IoFlagT>
void set_output_flag(IoFlagT new_flag) {
  output_flags = output_flags | new_flag;
}

template<typename T>
void print();
template<typename T>
void print(OutputFlags flags);
#endif
