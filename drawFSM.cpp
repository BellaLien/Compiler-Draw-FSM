#include "drawFSM.hpp"
using std::endl;

drawFSM::drawFSM() 
{

}
drawFSM::~drawFSM()
{

}

void drawFSM::drawState(int cx,int cy,std::string stateName, std::string color){//傳入圓心的x,y,STATE名稱
	out << "\tdrawState(" << cx << "," << cy << ",\"" << stateName << "\",\"" << color << "\");";
    out << endl;
}

void drawFSM::drawTransition(std::string stateFrom, std::string stateTo, std::string InOut, double radian){//傳入起始STATE,終點STATE,input/output,彎曲程度
	out << "\tdrawTransition(" << "\"" << stateFrom << "\",\"" << stateTo << "\",\"" << InOut << "\"," << radian << ");";
    out << endl;
}

void drawFSM::JSBegin(){
	out.open("drawFSM.js", std::ios::out);
    out << "function drawFSM(){ " << endl;
}

void drawFSM::JSEnd(){
	out << "}";
    out.close();
}
