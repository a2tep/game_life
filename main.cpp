#include "simulation_controller.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::unique_ptr<SimulationController> life;

    try {
        if (argc == 1) {
            // интерактивный
            life = std::make_unique<SimulationController>();
            std::cout << "Starting interactive game with default universe..." << std::endl;
            std::cout << "Type 'help' for commands, 'exit' to quit." << std::endl;
            life->play_game();
        }
        else if (argc == 2) {
            //  с загрузкой из файла
            life = std::make_unique<SimulationController>(argv[1]);
            std::cout << "Starting interactive game with universe from: " << argv[1] << std::endl;
            std::cout << "Type 'help' for commands, 'exit' to quit." << std::endl;
            life->play_game();
        }
        else if (argc == 6) {
            // оффлайн режим
            std::string infile, outfile, iterations;

            for (int i = 1; i < argc; i++) {
                std::string arg = argv[i];

                if (arg == "-i" || arg == "--iterations") {
                    if (i + 1 < argc) {
                        iterations = argv[++i];
                    }
                }
                else if (arg == "-o" || arg == "--output") {
                    if (i + 1 < argc) {
                        outfile = argv[++i];
                    }
                }
                else if (arg.find("--iterations=") == 0) {
                    iterations = arg.substr(13);
                }
                else if (arg.find("--output=") == 0) {
                    outfile = arg.substr(9);
                }
                else {
                    infile = arg;
                }
            }

            if (!iterations.empty() && !outfile.empty() && !infile.empty()) {
                std::cout << "Starting offline calculation..." << std::endl;
                std::cout << "Input: " << infile << std::endl;
                std::cout << "Iterations: " << iterations << std::endl;
                std::cout << "Output: " << outfile << std::endl;

                life = std::make_unique<SimulationController>(infile, iterations, outfile);
                life->play_game();

                std::cout << "Calculated " << iterations << " iterations and saved to " << outfile << std::endl;
            } else {
                std::cout << "Error: Missing required parameters!" << std::endl;
                std::cout << "Usage:" << std::endl;
                std::cout << "  Interactive mode: " << argv[0] << " [input_file]" << std::endl;
                std::cout << "  Offline mode: " << argv[0] << " input_file -i iterations -o output_file" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "Usage:" << std::endl;
            std::cout << "  Interactive mode: " << argv[0] << " [input_file]" << std::endl;
            std::cout << "  Offline mode: " << argv[0] << " input_file -i iterations -o output_file" << std::endl;
            return 1;
        }
    }
    catch (std::invalid_argument& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    return 0;
}