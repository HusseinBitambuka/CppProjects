#pragma once
#include <string>
#include <set>
#include "parser.hpp"
#include "nfa.hpp"
#include "dfa.hpp"
#include "utils.hpp"

/// High-level API: compiles a regex into an internal automaton and tests input
void matchRegex(const DFA &compiledDFA, const std::string &line);

std::vector<std::pair<size_t, size_t>> findAllMatches(const DFA &dfa, const std::string &input);

DFA compileDFA(const std::string &pattern);
