//
//  Minesweeper.cpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/8/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#include "Minesweeper.hpp"
minesweeper::minesweeper(int height, int width, int bomb_frequency):board(height, width){
    _pushPrintList(0, '-');
    _pushPrintList(-1, '*');
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

/**
 *  Gets the number of bombs on the board
 *  @return int bombs
 **/
int minesweeper::getBombsLeft() {
    return _bombsLeft;
}

/**
 *  Gets the number of spaces flagged
 *  @return int spaces flagged
 **/
int minesweeper::getFlaggedSpaces() {
    return _flaggedSpaces;
}

/**
 * Takes a user input and selects the item.
 **/
void minesweeper::select_item() {
    pair<int, int> coord = _getInput();
    _revealSpace(coord.first, coord.second);
}

/**
 * Takes a user input and flags the item as a bomb.
 **/
void minesweeper::toggle_flag() {
    pair<int, int> coord = _getInput();
    if (_getShownBoardAt(coord.first, coord.second) == 0) {
    board::_toggleSpace(coord.first, coord.second, 2);
        _flaggedSpaces++;
    }
    else if (_getShownBoardAt(coord.first, coord.second) == 2) {
        board::_toggleSpace(coord.first, coord.second);
        _flaggedSpaces--;
    }
    else
        cout << "That space can\'t be selected!" << endl;
}

/**
 * Reveals a space to the user. If the space is 0 then it revieals surrounding spaces too.
 * @param x the vertical index
 * @param y the horizontal index
 */
void minesweeper::_revealSpace(int x, int y) {
    if (!_canSelect(x, y)) return;
    if (_isBomb(x, y))  return;
    if (_canSee(x, y)) return;
    if (_getValueBoardAt(x, y) != 0) {
        board::_revealSpace(x, y);
        return;
    }
    else if (_getValueBoardAt(x, y) == 0) {
        board::_revealSpace(x, y);
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
