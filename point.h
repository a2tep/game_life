#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

// Константы по умолчанию
extern const std::string Default_name;
extern const std::string Default_b_rule;
extern const std::string Default_s_rule;
extern const std::vector<Point> Default_frame;

// Вспомогательные функции
const std::string Digits = "012345678";
int checkNum(const std::string &num);
std::string checkRule(const std::string &rule);

#endif // POINT_H
