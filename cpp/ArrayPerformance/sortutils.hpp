#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

const std::size_t HOW_MANY_ELEMENTS = 250000;
const std::uint8_t HOW_MANY_TIMES = 25;
using SourceArray = std::array<int, HOW_MANY_ELEMENTS>;
// preSortNames, arrayNames, and printOutWidth made to reduce code for printing out redundant strings
const std::array<std::string, 5> PRE_SORT_NAMES = { "Random Time", "Sorted Time",
                                                    "Reversed Time", "Organ Pipe Time",
                                                    "Rotated Time" };
const auto PRINTOUT_WIDTH = PRE_SORT_NAMES[3].length();

void initializeRawArrayFromStdArray(const std::array<int, HOW_MANY_ELEMENTS>& source, int dest[]);
void organPipeStdArray(std::array<int, HOW_MANY_ELEMENTS>& data);
void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);
void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);
void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);
