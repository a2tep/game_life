#include "point.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

// конст
const std::string Default_name = "Conway's game of life";
const std::string Default_b_rule = "3";
const std::string Default_s_rule = "23";
const std::vector<Point> Default_frame = {
    {0, 0}, {1, 1}, {2, 1}, {2, 3}, {2, 4},
    {3, 2}, {4, 9}, {5, 4}, {5, 8}, {5, 9}, {6, 6},
};

int checkNum(const std::string &num) {
    if (num.empty() || (num[0] == '0' && num.size() > 1)) {
        throw std::invalid_argument("Ticks are zero or negative");
    }
    for (size_t i = 0; i < num.size(); ++i) {
        if (!isdigit(num[i]) && num[i] != '-') {
            throw std::invalid_argument("Tick incorrect");
        }
    }
    return stoi(num);
}

std::string checkRule(const std::string &rule) {
    if (rule.empty() || !std::is_sorted(rule.begin(), rule.end())) {
        throw std::invalid_argument("Rule is incorrect");
    }
    for (const auto &i: rule) {
        if (Digits.find(i) == Digits.npos) {
            throw std::invalid_argument("Rule is incorrect");
        }
    }
    return rule;
}
