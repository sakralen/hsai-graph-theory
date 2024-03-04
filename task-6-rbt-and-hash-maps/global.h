#pragma once

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>
#include <locale>
#include <vector>
#include <vld.h>

using std::cout;
using std::cin;
using std::ostream;
using std::setw;
using std::string;
using std::transform;
using std::vector;

#define stop __asm nop

#define TEXT_COLOR_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define TEXT_COLOR_RED FOREGROUND_RED
#define TEXT_COLOR_GREEN FOREGROUND_GREEN

#define IS_IN_RANGE_CLOSED(x, min, max) ((x >= min) && (x <= max))

#define RBT_OUTPUT_TXT "rbt_output.txt"
#define RBT_INPUT_TXT "rbt_input.txt"
#define HASH_OUTPUT_TXT "hash_output.txt"
#define HASH_INPUT_TXT "hash_input.txt"

#define RX_WORDS "(\\b[a-zA-Z]*\\b)"
#define RX_WORDS_RU "(\\b[à-ÿÀ-ß¸¨]*\\b)"
#define RX_NUMBERS "^(([1-9])([0-9])*)|(0)$"
#define RX_YES_OR_NO "^[YNyn]$"