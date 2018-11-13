//
//  Minesweeper.hpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/8/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#ifndef Minesweeper_hpp
#define Minesweeper_hpp

#include "board.hpp"
#include <iostream>
using namespace std;
class minesweeper: public board {
public:
    minesweeper(int height=10, int width=10, int bomb_frequency=10);
    void    select_item();
    int     getBombsLeft();
    void    toggle_flag();
    int     getFlaggedSpaces();
protected:
    void    _setNumber();
    void    _revealSpace(int x, int y);
    bool    _isBomb(int x, int y);
    bool    _canSelect(int x, int y);
private:
    static char _flag_print();
    int     _bombsLeft;
    int     _flaggedSpaces;
};

#endif /* Minesweeper_hpp */
