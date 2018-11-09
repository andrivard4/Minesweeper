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
    minesweeper play(30, 10, 20);
    play.print_hidden_board();
    cout << endl;
    cout << play;
    play.select_item();
    cout << play;
    play.toggle_flag();
    cout << play;
    return 0;
}
