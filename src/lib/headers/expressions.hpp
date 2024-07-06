#ifndef EXPRESSIONS
#define EXPRESSIONS

#include <string>

enum class Operator {
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,
    INVALID,
};

struct Predicate {
    Operator op;
    std::string value;
};

#endif