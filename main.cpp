#include <iostream>
#include "PandemicSimulator.h"
using namespace std;


int main() {
    PandemicSimulator ps("cityGridFile.txt");

    // Display the city state for the first three iterations
    ps.displayCityState(0);
    std::cout << std::endl;
    ps.displayCityState(1);
    std::cout << std::endl;
    ps.displayCityState(2);
    std::cout << std::endl;

    // Simulate specific blocks in the city
    ps.simulateBlock(0, 0);
    ps.simulateBlock(4, 4);
    ps.simulateBlock(0, 4);
    ps.simulateBlock(1, 2);
    ps.simulateBlock(3, 1);

    std::cout << std::endl;

    // Display the city state for iterations 3, 4, and 5
    ps.displayCityState(3);
    std::cout << std::endl;
    ps.displayCityState(4);
    std::cout << std::endl;
    ps.displayCityState(5);
    std::cout << std::endl;

    // Simulate the entire pandemic
    ps.simulatePandemic();
    return 0;
}
