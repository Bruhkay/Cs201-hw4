//
// Created by Burkay Tunçtürk on 14.12.2024.
//
#include <iostream>
#include <fstream>
#include "PandemicSimulator.h"
using namespace std;
#include "string"

PandemicSimulator::PandemicSimulator(const string cityGridFile){
    std::string filePath = "/Users/burkay/Documents/Github/Cs201-hw4/cityGridFile.txt"; //TODO
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
    }
    file >> row >> col;

    matrix = new int*[row];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[col];
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            char ch;
            file >> ch;
            matrix[i][j] = ch - '0';
        }
    }

    file.close();

}
PandemicSimulator::~PandemicSimulator(){
    for (int i = 0; i < row; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void PandemicSimulator::displayCityState(const int time){}
void PandemicSimulator::simulateBlock(const int row, const int col){}
void PandemicSimulator::siulatePandemic(){}