//
//  Minesweeper.cpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/8/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#include "Minesweeper.hpp"
minesweeper::minesweeper(int height, int width, int bomb_frequency):board(height, width){
    _pushPrintActionList(2, _flag_print);
    srandom(static_cast<int>(time(NULL)));
    //srandom(0);
    _bombsLeft = 0;
    for(int i=0; i<getHeight(); i++) {
        for(int j=0; j<getWidth(); j++) {
            int rand = random()%100;
            if (rand  >= 100-bomb_frequency) {
                _setValueBoardAt(j, i, -1);
                _bombsLeft++;
            }
        }
    }
    // Sets the values of all numbers on the board
    _setNumber();
}

/**
 *  Sets the numarical values of each space baised on where a bomb is
 *  @pre _val_board is intilized with _height x _width 2D vector
 **/
void minesweeper::_setNumber() {
    // Set values of each block
    for(int i=0; i<getHeight(); i++) {
        for(int j=0; j<getWidth(); j++) {
            if (_getValueBoardAt(j, i) == -1) {
                if (_canSelect(j-1, i-1) && !_isBomb(j-1, i-1))
                    _setValueBoardAt(j-1, i-1, _getValueBoardAt(j-1, i-1) + 1);
                if (_canSelect(j, i-1) && !_isBomb(j, i-1))
                     _setValueBoardAt(j, i-1, _getValueBoardAt(j, i-1) + 1);
                if (_canSelect(j+1, i-1) && !_isBomb(j+1, i-1))
                     _setValueBoardAt(j+1, i-1, _getValueBoardAt(j+1, i-1) + 1);
                if (_canSelect(j-1, i) && !_isBomb(j-1, i))
                    _setValueBoardAt(j-1, i, _getValueBoardAt(j-1, i) + 1);
                if (_canSelect(j+1, i) && !_isBomb(j+1, i))
                    _setValueBoardAt(j+1, i, _getValueBoardAt(j+1, i) + 1);
                if (_canSelect(j-1, i+1) && !_isBomb(j-1, i+1))
                    _setValueBoardAt(j-1, i+1, _getValueBoardAt(j-1, i+1) + 1);
                if (_canSelect(j, i+1) && !_isBomb(j, i+1))
                    _setValueBoardAt(j, i+1, _getValueBoardAt(j, i+1) + 1);
                if (_canSelect(j+1, i+1) && !_isBomb(j+1, i+1))
                    _setValueBoardAt(j+1, i+1, _getValueBoardAt(j+1, i+1) + 1);
            }
        }
    }
}

int minesweeper::getBombsLeft() {
    return _bombsLeft;
}

/**
 * Takes a user input and selects the item.
 **/
void minesweeper::select_item() {
    pair<int, int> coord = _getInput();
    _revealSpace(coord.first, coord.second);
}

void minesweeper::toggle_flag() {
    pair<int, int> coord = _getInput();
    _setShownBoardAt(coord.first, coord.second, 2);
}

/**
 * Reveals a space to the user. If the space is 0 then it revieals surrounding spaces too.
 * @param x the vertical index
 * @param y the horizontal index
 */
void minesweeper::_revealSpace(int x, int y) {
    if (!_canSelect(x, y)) return;
    if (_isBomb(x, y)) return;
    if (_canSee(x, y)) return;
    if (_getValueBoardAt(x, y) != 0) {
        _setShownBoardAt(x, y, true);
        return;
    }
    else if (_getValueBoardAt(x, y) == 0) {
        _setShownBoardAt(x, y, true);
        _revealSpace(x-1, y-1);
        _revealSpace(x, y-1);
        _revealSpace(x+1, y-1);
        _revealSpace(x-1, y);
        _revealSpace(x+1, y);
        _revealSpace(x-1, y+1);
        _revealSpace(x, y+1);
        _revealSpace(x+1, y+1);
    }
}

/**
 *  Checks if the selected space is a bomb or not
 *  @param x the vertival index
 *  @param y the horizontal index
 *  @return false if a the space does not hold a -1 value
 **/
bool minesweeper::_isBomb(int x, int y) {
    return _getValueBoardAt(x, y) == -1;
}

/**
 *  Checks if a selected space exists or not
 *  @param x the vertival index
 *  @param y the horizontal index
 *  @return false if the index is out of bounds
 **/
bool minesweeper::_canSelect(int x, int y) {
    return board::_canSelect(x, y);
}

char minesweeper::_flag_print() {
    return 'F';
}
