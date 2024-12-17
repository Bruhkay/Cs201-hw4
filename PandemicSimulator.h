//
// Created by Burkay Tunçtürk on 14.12.2024.
//


#ifndef PANDEMICSIMULATOR_H
#define PANDEMICSIMULATOR_H
#include <string>
using namespace std;

class PandemicSimulator{
  public:
    PandemicSimulator(const string cityGridFile);
    ~PandemicSimulator();

    void displayCityState(const int time);
    void simulateBlock(const int row, const int col);
    void simulatePandemic();

    int daycalculator(const int r, const int c);

  private:
    int **matrix;
    int rows, cols;

};
#endif //PANDEMICSIMULATOR_H
