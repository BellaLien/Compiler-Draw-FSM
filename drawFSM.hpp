#pragma once
#include <fstream>
#include <string>
class drawFSM {

public:
    drawFSM();
    ~drawFSM();
    void JSBegin();
    void JSEnd();

    void drawState(int, int, std::string, std::string);
    void drawTransition(std::string, std::string, std::string, double);
private:
    std::ofstream out;
};
