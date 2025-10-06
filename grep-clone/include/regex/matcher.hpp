#pragma once
#include <string>
#include <set>
#include "parser.hpp"
#include "nfa.hpp"
#include "dfa.hpp"
#include "utils.hpp"

/// High-level API: compiles a regex into an internal automaton and tests input
bool matchRegex(const std::string &pattern, const std::string &input);

/// Optional utility for debugging DFA execution
bool simulateDFA(const DFA &dfa, const std::string &input);
