#include "PandemicSimulator.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring> // For memset
using namespace std;

// Constructor
PandemicSimulator::PandemicSimulator(const string cityGridFile) {
    ifstream file("/Users/burkay/Documents/Github/Cs201-hw4/cityGridFile.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << cityGridFile << endl;
        return;
    }

    file >> rows >> cols;


    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char ch;
            file >> ch;
            matrix[i][j] = ch - '0';
        }
    }

    file.close();
}

PandemicSimulator::~PandemicSimulator() {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


void PandemicSimulator::displayCityState(const int time) {
    cout << "City state at day " << time << ":\n";
    int** temp = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        temp[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (daycalculator(i, j) == 0) {
                temp[i][j] = 2;
            }
            else if (daycalculator(i, j) == -1) {
                temp[i][j] = 0;
            }
            else if (daycalculator(i, j) <= time ) {
                temp[i][j] = 2;
            }
            else {
                temp[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << temp[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}
int PandemicSimulator::daycalculator(const int r, const int c) {
    if (matrix[r][c] == 0) {
        return -1;
    }
    if (matrix[r][c] == 2) {
        return 0;
    }

    int** visited = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        visited[i] = new int[cols];
        memset(visited[i], -1, sizeof(int) * cols); 
    }

    queue<pair<int, int>> q;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0;
            }
        }
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && visited[nx][ny] == -1 && matrix[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    int result = visited[r][c] ;


    for (int i = 0; i < rows; ++i) {
        delete[] visited[i];
    }
    delete[] visited;
    return result;
}



void PandemicSimulator::simulateBlock(const int r, const int c) {
    if (matrix[r][c] == 0) {
        cout << "Time for block (" << r <<", "<< c<<") to be infected: " << -1 <<" days."<<endl;
        return;
    }
    if (matrix[r][c] == 2) {
        cout << "Time for block (" << r <<", "<< c<<") to be infected: " << 0 <<" days."<<endl;
        return;
    }

    // Use BFS to calculate the infection time
    int** visited = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        visited[i] = new int[cols];
        memset(visited[i], -1, sizeof(int) * cols); //-1 for unvisited
    }

    queue<pair<int, int>> q;
    // Enqueue all initially infected blocks
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0; // Start day for infection
            }
        }
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && visited[nx][ny] == -1 && matrix[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "Time for block (" << r <<", "<< c<<") to be infected: " << visited[r][c] <<" days."<<endl;

    for (int i = 0; i < rows; ++i) {
        delete[] visited[i];
    }
    delete[] visited;
}


void PandemicSimulator::simulatePandemic() {
    int** visited = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        visited[i] = new int[cols];
        memset(visited[i], -1, sizeof(int) * cols);
    }

    queue<pair<int, int>> q;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0;
            }
        }
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int maxDays = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && visited[nx][ny] == -1 && matrix[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                maxDays = max(maxDays, visited[nx][ny]);
                q.push({nx, ny});
            }
        }
    }

    // last check for unreachable blocks
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 1 && visited[i][j] == -1) {
                cout << "Pandemic cannot spread to all blocks." << endl;
                for (int k = 0; k < rows; ++k) {
                    delete[] visited[k];
                }
                delete[] visited;
                return;
            }
        }
    }

    cout << "Minimum time for pandemic to spread to all blocks: " << maxDays << " days." << endl;

    for (int i = 0; i < rows; ++i) {
        delete[] visited[i];
    }
    delete[] visited;
}