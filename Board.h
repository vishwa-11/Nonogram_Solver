//
// Created by Vishweshwar Ramanakumar on 5/14/21.
//

#ifndef NONOGRAM_SOLVER_BOARD_H
#define NONOGRAM_SOLVER_BOARD_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Board {
public:
    int sideLength = 0;
    vector<vector<int>> layout;
    vector<vector<int>> rowCounts;
    vector<vector<int>> columnCounts;

    Board(int dimension);
    void Display();
    void Reset();
    void Phase1();
    bool isComplete();

};

#endif //NONOGRAM_SOLVER_BOARD_H
