#include <iostream>
using namespace std;
#include "Board.h"

int main() {
    cout << "What board dimensions do you want?: ";
    int dimensions;
    cin >> dimensions;
    cout << endl;

    Board board1(dimensions);
    cout << endl;

    board1.Phase1();


    board1.Display();

    if (board1.isComplete()) {
        cout << "This puzzle has been solved." << endl;
    }

    else {
        cout << "This puzzle hasn't been solved yet." << endl;
    }

    return 0;
}
