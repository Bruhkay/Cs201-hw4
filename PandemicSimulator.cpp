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

PandemicSimulator::~PandemicSimulator() {
    for (int i = 0; i < row; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void PandemicSimulator::displayCityState(const int time) {
    cout << "City state at day " << time << ":\n";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

// Simulate the time it takes for a specific block to be infected
void PandemicSimulator::simulateBlock(const int r, const int c) {
    if (matrix[r][c] == 0) {
        cout << -1 << endl; // Empty block
        return;
    }
    if (matrix[r][c] == 2) {
        cout << 0 << endl; // Already infected
        return;
    }

    // Simulate the pandemic using BFS
    int** visited = new int*[row];
    for (int i = 0; i < row; ++i) {
        visited[i] = new int[col];
        memset(visited[i], -1, sizeof(int) * col); // -1 means unvisited
    }

    queue<pair<int, int>> q;
    // Enqueue all infected blocks
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
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

            if (nx >= 0 && nx < row && ny >= 0 && ny < col && visited[nx][ny] == -1 && matrix[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << visited[r][c] << " days" << endl;

}

// Simulate the entire pandemic spread
void PandemicSimulator::simulatePandemic() {
    int** visited = new int*[row];
    for (int i = 0; i < row; ++i) {
        visited[i] = new int[col];
        memset(visited[i], -1, sizeof(int) * col); // -1 means unvisited
    }

    queue<pair<int, int>> q;
    // Enqueue all infected blocks
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
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

            if (nx >= 0 && nx < row && ny >= 0 && ny < col && visited[nx][ny] == -1 && matrix[nx][ny] == 1) {
                visited[nx][ny] = visited[x][y] + 1;
                maxDays = max(maxDays, visited[nx][ny]);
                q.push({nx, ny});
            }
        }
    }

    // Check if there are unreachable healthy blocks
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == 1 && visited[i][j] == -1) {
                cout << "Pandemic cannot spread to all blocks." << endl;

                return;
            }
        }
    }

    cout << "Minimum time for pandemic to spread to all blocks: " << maxDays << " days." << endl;


}