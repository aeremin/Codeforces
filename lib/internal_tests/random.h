#pragma once

#include <random>


std::mt19937 random_engine(0);
std::uniform_real_distribution<> canonical_random_double(0., 1.);
