#pragma once

#include <string>

class Config {
public:
    static Config &getInstance() {
        static Config instance;
        return instance;
    }

    unsigned int windowWidth = 0;
    unsigned int windowHeight = 0;
    bool useGui = false;
    int difficulty = 1;
    int timeLimit = 1000;

    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;

private:
    Config() { loadConfigFile(); }

    void loadConfigFile();

    const std::string configFile = "./resources/settings.ini";

    static void trim(std::string &str);
};
