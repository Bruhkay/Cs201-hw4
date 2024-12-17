#include "PandemicSimulator.h"
#include <iostream>
#include <fstream>
using namespace std;

struct Point {
    int x; // Row index
    int y; // Col index
};

struct Queue {
    Point data[1000]; //capacity of queue
    int front, rear;

    Queue() : front(0), rear(0) {}

    bool empty() {
        return front == rear;
    }

    void push(Point p) {
        data[rear++] = p;
    }

    Point pop() {
        return data[front++];
    }

    Point peek() {
        return data[front];
    }
};
PandemicSimulator::PandemicSimulator(const string cityGridFile) {
    ifstream file(cityGridFile);
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

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 0) {
                cout << "0";
            }
            else if (matrix[i][j] == 1 && daycalculator(i,j) ==-1) {
                cout << "1";
            }
            else if (matrix[i][j] ==2 || daycalculator(i,j)<= time) {
                cout << "2";
            }
            else {
                cout << "1";
            }
        }
        cout << endl;
    }
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
        for (int j = 0; j < cols; ++j) {
            visited[i][j] = -1;
        }
    }

    Queue q;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0;
            }
        }
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int dir[2];

    while (!q.empty()) {
        Point current = q.pop();
        int x = current.x;
        int y = current.y;

        for (int i = 0; i < 4; ++i) {
            dir[0] = directions[i][0];
            dir[1] = directions[i][1];
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

    int** visited = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        visited[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            visited[i][j] = -1;
        }
    }

    Queue q;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0;
            }
        }
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int dir[2];

    while (!q.empty()) {
        Point current = q.pop();
        int x = current.x;
        int y = current.y;

        for (int i = 0; i < 4; ++i) {
            dir[0] = directions[i][0];
            dir[1] = directions[i][1];
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
        for (int j = 0; j < cols; ++j) {
            visited[i][j] = -1;
        }
    }
    Queue q;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = 0;
            }
        }
    }

    int maxDays = 0;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int dir[2];

    while (!q.empty()) {
        Point current = q.pop();
        int x = current.x;
        int y = current.y;

        for (int i = 0; i < 4; ++i) {
            dir[0] = directions[i][0];
            dir[1] = directions[i][1];
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

