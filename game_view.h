#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game_model.h"
#include <iostream>
#include <string>

class Game_view {
public:
    static void printErr(const std::string& err_message);
    static void printHelp();
    static void printFrame(
            const std::string& name,
            const Field& field,
            int glob_iteration,
            int curr_iteration
    );
};

#endif // GAME_VIEW_H