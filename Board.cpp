//
// Created by Vishweshwar Ramanakumar on 5/14/21.
//

#include "Board.h"

Board::Board(int dimension) {
    sideLength = dimension;

    for (int i = 0; i < sideLength; i++) {
        vector<int> layout1;
        for (int j = 0; j < sideLength; j++) {
            layout1.push_back(0);
        }
        layout.push_back(layout1);
    }

    cout << "Input Row Counts" << endl;
    string input;
    vector<int> commaIndices;
    commaIndices.push_back(-1);

    for (int i = 0; i < sideLength; i++) {
        cout << "Row " << i + 1 << ": ";
        cin >> input;
        for (int j = 0; j < input.size(); j++) {
            if (input[j] == ',') {
                commaIndices.push_back(j);
            }
        }

        vector<int> count;

        if (commaIndices.size() == 1) {
            count.push_back(stoi(input));
        }

        else {
            commaIndices.push_back(input.size() - 1);

            for (int k = 0; k < commaIndices.size() - 1; k++) {
                count.push_back(stoi(input.substr(commaIndices[k] + 1, commaIndices[k + 1])));
            }
        }

        if (count[0] != 0 && !count.empty()) {
            rowCounts.push_back(count);

        }



        commaIndices.clear();
        commaIndices.push_back(-1);
    }



    for (int i = 0; i < sideLength; i++) {
        cout << "Column " << i + 1 << ": ";
        cin >> input;
        for (int j = 0; j < input.size(); j++) {
            if (input[j] == ',') {
                commaIndices.push_back(j);
            }
        }
        vector<int> count;
        columnCounts.push_back(count);

        if (commaIndices.size() == 1) {
            columnCounts[i].push_back(stoi(input));
        }

        else {
            commaIndices.push_back(input.size() - 1);

            for (int k = 0; k < commaIndices.size() - 1; k++) {
                columnCounts[i].push_back(stoi(input.substr(commaIndices[k] + 1, commaIndices[k + 1])));
            }
        }


        commaIndices.clear();
        commaIndices.push_back(-1);
    }
}

void Board::Display() {
    if (sideLength == 0) {
        cout << "Board hasn't been initialized yet." << endl;
    }
    else {
        //we need to know the size of the largest rowCount and columnCount vectors
        int maxRowSize = rowCounts[0].size();
        int maxColumnSize = columnCounts[0].size();

        for (int i = 0; i < rowCounts.size(); i++) {
            if (rowCounts[i].size() > maxRowSize) {
                maxRowSize = rowCounts[i].size();
            }
        }

        for (int i = 0; i < columnCounts.size(); i++) {
            if (columnCounts[i].size() > maxColumnSize) {
                maxColumnSize = columnCounts[i].size();
            }
        }

        //we need to print out the column counts as a double vector
        vector<vector<int>> columns;
        for (int i = 0; i < maxColumnSize; i++) {
            vector<int> column;
            for (int j = 0; j < sideLength; j++) {
                column.push_back(0);
            }
            columns.push_back(column);
        }

        int index = 0;

        for (int i = sideLength - 1; i >= 0; i--) {
            index = columnCounts[i].size() - 1;
            for (int j = maxColumnSize - 1; j >= 0; j--) {
                if (index >= 0) {
                    columns[j][i] = columnCounts[i][index];
                }
                index--;
            }
        }

        for (int i = 0; i < columns.size(); i++) {
            for (int j = 0; j < 2 * maxRowSize; j++) {
                cout << " ";
            }
            for (int j = 0; j < columns[i].size(); j++) {
                if (columns[i][j] == 0) {
                    cout << "   ";
                }
                else if (columns[i][j] > 9) {
                    cout << columns[i][j] << " ";
                }
                else {
                    cout << columns[i][j] << "  ";

                }
            }
            cout << endl;
        }


        for (int i = 0; i < 2 * maxRowSize - 1; i++) {
            cout << " ";
        }

        for (int i = 0; i < 3 * sideLength; i++) {
            cout << "-";
        }
        cout << endl;

        for (int i = 0; i < sideLength; i++) {
            for (int j = 0; j < 2 * maxRowSize - 2 * rowCounts[i].size(); j++) {
                cout << " ";
            }
            for (int j = 0; j < rowCounts[i].size(); j++) {
                cout << rowCounts[i][j];
                if (j != rowCounts[i].size() - 1) {
                    cout << " ";
                }
            }

            cout << "|";
            for (int j = 0; j < sideLength; j++) {
                if (j != sideLength - 1) {
                    if (layout[i][j] == -1) {
                        cout << "O  ";
                    }
                    else {
                        cout << "X  ";
                    }
                }

                else {
                    if (layout[i][j] == -1) {
                        cout << "O";
                    }
                    else {
                        cout << "X";
                    }
                }

            }
            cout << "|";
            cout << endl;
        }

        for (int i = 0; i < 2 * maxRowSize - 1; i++) {
            cout << " ";
        }

        for (int i = 0; i < 3 * sideLength; i++) {
            cout << "-";
        }

        cout << endl;
        cout << endl;
    }
}

void Board::Reset() {
    layout.clear();

    for (int i = 0; i < sideLength; i++) {
        vector<int> layout1;
        layout.push_back(layout1);
        for (int j = 0; j < sideLength; j++) {
            layout[i].push_back(0);
        }
    }
}

void Board::Phase1() {
    //setting up the rows

    int size = 0;
    int index1;
    bool bigEnough = false;
    for (int i = 0; i < sideLength; i++) {
        //figuring out the minimum length of shaded pattern in a row
        for (int j = 0; j < rowCounts[i].size(); j++) {
            size += rowCounts[i][j] + 1;
        }

        size--;

        //figuring out if the individual shaded regions are large enough
        for (int j = 0; j < rowCounts[i].size(); j++) {
            if (rowCounts[i][j] > sideLength - size) {
                bigEnough = true;
                break;
            }
        }

        //if there is at least one shaded region big enough, we can commence this phase

        if (bigEnough) {
            //we set the shaded regions
            for (int index = 0; index < sideLength - size + 1; index++) {
                index1 = index;
                for (int j = 0; j < rowCounts[i].size(); j++) {
                    for (int k = 0; k < rowCounts[i][j]; k++) {
                        if (layout[i][index1] != -1) {
                            layout[i][index1]++;
                        }
                        index1++;
                    }

                    if (j != rowCounts[i].size() - 1) {
                        if (layout[i][index1] != -1) {
                            layout[i][index1] = 0;
                        }
                        index1++;
                    }
                }
            }
        }

        for (int j = 0; j < sideLength; j++) {
            if (layout[i][j] < sideLength - size + 1 && layout[i][j] != -1) {
                layout[i][j] = 0;
            }
            else if (layout[i][j] == -1 || layout[i][j] >= sideLength - size + 1) {
                layout[i][j] = -1;
            }
        }

        //reset parameters
        bigEnough = false;
        size = 0;
    }

    //setting up the columns

    for (int i = 0; i < sideLength; i++) {
        //figuring out the minimum length of shaded pattern in a row
        for (int j = 0; j < columnCounts[i].size(); j++) {
            size += columnCounts[i][j] + 1;
        }

        size--;

        bigEnough = false;
        //figuring out if the individual shaded regions are large enough
        for (int j = 0; j < columnCounts[i].size(); j++) {
            if (columnCounts[i][j] > sideLength - size) {
                bigEnough = true;
                break;
            }
        }

        //if there is at least one shaded region big enough, we can commence this phase

        if (bigEnough) {
            //we set the shaded regions in the forward direction
            for (int index = 0; index < sideLength - size + 1; index++) {
                index1 = index;
                for (int j = 0; j < columnCounts[i].size(); j++) {
                    for (int k = 0; k < columnCounts[i][j]; k++) {
                        if (layout[index1][i] != -1) {
                            layout[index1][i]++;
                        }
                        index1++;
                    }
                    if (j != columnCounts[i].size() - 1) {
                        if (layout[index1][i] != -1) {
                            layout[index1][i] = 0;
                        }
                        index1++;
                    }
                }
            }
        }

        for (int j = 0; j < sideLength; j++) {
            if (layout[j][i] < sideLength - size + 1 && layout[j][i] != -1) {
                layout[j][i] = 0;
            }
            else if (layout[j][i] == -1 || layout[j][i] >= sideLength - size + 1) {
                layout[j][i] = -1;
            }
        }

        //reset parameters
        bigEnough = false;
        size = 0;
    }
}

bool Board::isComplete() {
    int size = 0;
    int solvedSize = 0;
    for (int i = 0; i < sideLength; i++) {
        for (int j = 0; j < sideLength; j++) {
            if (layout[i][j] == -1) {
                solvedSize++;
            }
        }

        for (int k = 0; k < rowCounts[i].size(); k++) {
            size += rowCounts[i][k];
        }
        if (size != solvedSize) {
            return false;
        }
    }
    return true;
}
