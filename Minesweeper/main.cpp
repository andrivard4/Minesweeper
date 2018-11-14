//
//  main.cpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/6/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#include <iostream>
#include <map>
#include "Minesweeper.hpp"
#include "board.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    minesweeper play(20, 10, 15);
    do {
        cout << endl;
        cout << play;
    } while (!play.select_item());
    play.print_hidden_board();
    return 0;
}
