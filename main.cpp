
//  Created by Wei-Hsuan Lien on 2018/10/8.
//  Copyright © 2018年 Wei-Hsuan Lien. All rights reserved.


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include "drawFSM.hpp"

using namespace std;
drawFSM drawfsm;
int check = 0;
int Snum = 0;
string compare;
bool once = true;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
int reset = 0;

void StateNUM(string STATE) {
    
    if (check == 1) {
        drawfsm.JSBegin();
    }
    
    if (STATE[0] == 'S') {
        
        size_t found = 0;
        found = compare.find(STATE);
        
        if (found > 100) {
            compare = compare + " " + STATE;
            string SSS;
            SSS = STATE;
            int I1, I2;
            I2 = int(SSS[1]) % 4;
            I1 = int(SSS[1]) / 4;
            
            string color;
            if (reset == 0) {
                color = "#FF0000";
                reset++;
            }
            else
                color = "Yellow";
            
            switch (I2) {
                case 0:
                    drawfsm.drawState(100 + (c1 * 700), 200, STATE, color);
                    c1++;
                    break;
                case 1:
                    drawfsm.drawState(100 + (c2 * 200), 600 + (c2 * 200), STATE, color);
                    c2++;
                    break;
                case 2:
                    drawfsm.drawState(400 + (c3 * 50), 50 + (c3 * 900), STATE, color);
                    c3++;
                    break;
                case 3:
                    drawfsm.drawState(850 + (c4 * 100), 650 + (c4 * 200), STATE, color);
                    c4++;
                    break;
                default:
                    cout << "Invalid grade" << endl;
                    break;
            }
        }
    }
}

void draw(string CURRENT, string NEXT, string INnOUT, double R, int CHECK){
    drawfsm.drawTransition(CURRENT, NEXT, INnOUT, R);
}

int p = 0;
double R = 0;
void analyze(string Line) {
    
    string newLine = Line;
    string input, currentState, nextState;
    string output;
    
    istringstream str(newLine);
    str >> input >> currentState >> nextState >> output; 
    //cout << input << " " << currentState << " " << nextState << " " << output << endl;
    
    if (currentState[0] == 's') {
        currentState[0] = 'S';
        nextState[0] = 'S';
    }
    
    string inNout;
    inNout = input + '/' + output;
    
    if(input != ".e") {
        check++;
        StateNUM(currentState);
        check++;
        StateNUM(nextState);
    }
    
    
    if ((p % 8) == 0 || R == 1.6)
        R = 0;
    draw(currentState, nextState, inNout, R, check);
    R = R + 0.2;
    p--;
}


void readfile(string Kiss){
    
    string filename, temp;
    //cout << Kiss;
    ifstream KissFile(Kiss, ios::in);
    
    if (KissFile.is_open()){
        string line;
        int j = 0;
        for (int i = 0; !KissFile.eof(); i++){
            getline(KissFile, line);
            istringstream str(line);
            string symbol;
            double n;
            str >> symbol >> n;
            //cout << line << endl;
            if (symbol == "#") {
                if (j != 0)
                    j -= 1;
                continue;
            }
            else if (symbol == ".i" || symbol == ".o" || symbol == ".p" || symbol == ".r" || symbol == ".s") {
                if (symbol == ".p") {
                    p = n;
                }
                else if (symbol == ".s")
                    Snum = n;
                continue;
            }
            else if (symbol == ".e")
                drawfsm.JSEnd();
            else 
                analyze(line);
            j++;
        }
    }
    
    else
        cout << "File could not be opened." << endl;
}

void createHTML(string htmlName){
    
    ofstream HTML;
    HTML.open(htmlName, ios::out);
    if (HTML.fail())
        cout << "File could not be opened." << endl;
    else{
        HTML << "<html>" << endl;
        HTML << "<title>drawFSM</title>" << endl;
        HTML << "<head>" << endl;
        HTML << "<script src=\"https://d3js.org/d3.v5.min.js\"></script>" << endl;
        HTML << "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js\"></script>" << endl;
        HTML << "<script src=\"drawFSM.js\"></script>" << endl;
        HTML << "<script src=\"drawFSM_tool.js\"></script>" << endl;
        HTML << "</head>" << endl;
        HTML << "<body>" << endl;
        HTML << "</body>" << endl;
        HTML << "</html>" << endl;
        HTML.close();
    }
}

int main(int argc, char **argv){
    
    createHTML(argv[2]);
    readfile(argv[1]);
    //system("pause");
    return 0;
}


