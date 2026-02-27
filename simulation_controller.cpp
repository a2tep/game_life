#include "simulation_controller.h"
#include <fstream>
#include <sstream>

// для сохранения dump
void printInFile(
        std::ofstream &out,
        const Field &field,
        const std::string &name,
        int glob_iteration
) {
    out << "#Life 1.06" << std::endl;
    out << "#N " << name << std::endl;
    out << "#R B3/S23" << std::endl;

    for (int i = 0; i < field.getSize(); ++i) {
        for (int j = 0; j < field.getSize(); ++j) {
            if (field.getState(i, j)) {
                out << i << " " << j << std::endl;
            }
        }
    }
}

// конструкторы
SimulationController::SimulationController() {
    model = std::make_unique<Game_model>();
}

SimulationController::SimulationController(const std::string& inf)
        : SimulationController(inf, "1", "") {}

SimulationController::SimulationController(
        const std::string& infile,
        const std::string& ticks,
        const std::string& outfile
) {
    int tick;
    std::string name;
    std::string b_rule;
    std::string s_rule;
    std::string str;
    std::vector<Point> coords;
    coords.reserve(1000);
    std::ifstream ifile(infile);

    try {
        if (!ifile.is_open()) {
            throw std::invalid_argument("Cannot open input file");
        }

        tick = checkNum(ticks);
        std::getline(ifile, str);
        if (str != "#Life 1.06") {
            throw std::invalid_argument("Wrong file format. Expected #Life 1.06");
        }

        getline(ifile, str);
        if (str.size() < 3 || str.substr(0, 3) != "#N ") {
            name = "Unnamed Universe";
        } else {
            name = str.substr(3);
        }

        getline(ifile, str);
        if (str.size() < 8 || str.substr(0, 4) != "#R B") {
            throw std::invalid_argument("No transition rules found");
        } else {
            size_t pos = str.find('/');
            if (pos == std::string::npos || str[pos + 1] != 'S') {
                throw std::invalid_argument("Wrong rule format");
            }
            b_rule = checkRule(str.substr(4, pos - 4));
            s_rule = checkRule(str.substr(pos + 2));
        }

        while (getline(ifile, str)) {
            size_t pos = str.find(' ');
            if (pos == std::string::npos) {
                continue;
            }
            int x = checkNum(str.substr(0, pos));
            int y = checkNum(str.substr(pos + 1));
            coords.push_back({x, y});
        }

        out_file = outfile;
        model = std::make_unique<Game_model>(name, b_rule, s_rule, coords);

    } catch (std::invalid_argument& err) {
        view.printErr(err.what());
        throw;
    }
}
// игровой цикл
void SimulationController::play_game() {
    try {
        if (!out_file.empty()) {
            std::ofstream ofile(out_file);
            if (!ofile.is_open()) {
                throw std::invalid_argument("Cannot open output file");
            }
            for (int i = 0; i < model->getGlobIteration(); ++i) {
                model->computeIteration();
            }
            printInFile(ofile, model->getField(), model->getName(), model->getGlobIteration());
            return;
        }
//интерактивный режим
        std::string command;
        while (true) {
            std::cout << "\nEnter command (help for commands): ";
            std::getline(std::cin, command);

            if (command == "exit") {
                break;
            } else if (command.substr(0, 4) == "tick" || command.substr(0, 1) == "t") {
                int num_tick = 1;
                if (command.size() > 4 && command[4] == ' ') {
                    try {
                        num_tick = checkNum(command.substr(5));
                    } catch (std::invalid_argument&) {
                        num_tick = 1;
                    }
                }
                for (int i = 1; i <= num_tick; ++i) {
                    view.printFrame(
                            model->getName(),
                            model->getField(),
                            model->getGlobIteration() + 1,
                            i
                    );
                    model->computeIteration();
                }
            } else if (command.substr(0, 4) == "dump") {
                if (command.size() < 6) {
                    view.printErr("Usage: dump <filename>");
                } else {
                    std::string filename = command.substr(5);
                    std::ofstream ofile(filename);
                    if (ofile.is_open()) {
                        printInFile(ofile, model->getField(), model->getName(), model->getGlobIteration());
                        std::cout << "Universe saved to " << filename << std::endl;
                    } else {
                        view.printErr("Cannot open file for writing");
                    }
                }
            } else if (command == "help") {
                view.printHelp();
            } else if (!command.empty()) {
                view.printErr("Unknown command. Type 'help' for available commands.");
            }
        }
    } catch (std::invalid_argument& err) {
        view.printErr(err.what());
    }
}