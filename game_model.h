#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "field.h"
#include <string>
#include <vector>

class Game_model {
private:
    int global_iteration = 0;
    std::string name;
    const std::vector<bool> b_rule;
    const std::vector<bool> s_rule;
    char current_field = 1;
    Field field_1;
    Field field_2;


    static std::vector<bool> ruleToBool(const std::string &rule);
    static int neighbors(const Field &field, int size, int row, int column);

public:
    Game_model();
    Game_model(
            const std::string& name,
            const std::string& brule,
            const std::string& srule,
            const std::vector<Point>& coords
    );

    int getGlobIteration() const;
    void computeIteration();
    const std::string& getName() const;
    const Field& getField() const;
};

#endif // GAME_MODEL_H