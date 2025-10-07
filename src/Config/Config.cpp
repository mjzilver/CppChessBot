#include "Config.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Config::loadConfigFile() {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file " << configFile << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                trim(key);
                trim(value);
                if (key == "window_width") {
                    windowWidth = std::stoi(value);
                } else if (key == "window_height") {
                    windowHeight = std::stoi(value);
                } else if (key == "use_gui") {
                    useGui = value == "true";
                } else if (key == "difficulty") {
                    difficulty = std::stoi(value);
                } else if (key == "time_limit") {
                    timeLimit = std::stoi(value);
                }
            }
        }
    }
}

void Config::trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
}