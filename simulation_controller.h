#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#include "game_model.h"
#include "game_view.h"
#include <memory>
#include <string>


class SimulationController {
private:
    std::unique_ptr<Game_model> model;
    Game_view view;
    std::string out_file;

public:
    SimulationController();
    SimulationController(const std::string& infile);
    SimulationController(
            const std::string& infile,
            const std::string& ticks,
            const std::string& outfile
    );

    void play_game();
};

#endif // SIMULATION_CONTROLLER_H