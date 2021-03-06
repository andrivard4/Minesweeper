//
//  board.cpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/8/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#include "board.hpp"

/**
 *  Constructor
 *  Creates a 10 x 10 board when nothing passed
 *  @param height a positive integer height of the board
 **/
board::board(int height, int width){
    // Sets default size of board
    _height = height;
    _width = width;
    _numb_shown = 0;
    // Places the bombs on the board
    for(int i=0; i<_height; i++) {
        // Declares 2 vectors to be rows of board / fill them
        vector<int> vect;
        vector<int> shown;
        for(int j=0; j<_width; j++) {
            shown.push_back(0);
            vect.push_back(0);
        }
        // Add each row to board
        _val_board.push_back(vect);
        _shown_board.push_back(shown);
    }
}
/**
 *  Prints the current state of the value board showing a completed board
 **/
const void board::print_hidden_board() {
    for(int i=0; i<_height; i++) {
        for(int j=0; j<_width; j++) {
            if (_replace.count(_getValueBoardAt(j, i)))
                cout << _replace.at(_getValueBoardAt(j, i));
            else
                cout << _val_board.at(i).at(j);
            cout << "\t";
        }
        cout << endl;
    }
}

/**
 *  Prints the comleted board checking _shown_board to see if the user can see it
 **/
const void board::print_shown_board() {
    for(int i=0; i<_height; i++) {
        for(int j=0; j<_width; j++) {
            if (_shown_action.count(_shown_board.at(i).at(j)))
                cout << (_shown_action.at(_shown_board.at(i).at(j)))() << "\t";
            else if (_shown_board.at(i).at(j) == 1) {
                if (_replace.count(_getValueBoardAt(j, i)))
                    cout << _replace.at(_getValueBoardAt(j, i));
                else
                    cout << _val_board.at(i).at(j);
                cout << "\t";
            }
            else
                cout << "█\t";
        }
        cout << endl;
    }
    cout << _numb_shown << endl;
}

/**
 *  Gets the width of the board
 *  @return int width
 **/
int board::getWidth() {
    return _width;
}

/**
 *  Gets the height of the board
 *  @return int height
 **/
int board::getHeight() {
    return _height;
}

/**
 *  Gets the number of spaces shown to the user
 *  @return int spaces shown
 **/
int board::_getNumbShown() {
    return _numb_shown;
}

/**
 *  Overload of ostream << via friend function
 *  @param out a refrence to the stream to output to
 *  @param rhs the board to output
 *  @return a refrence to the ostream to output to
 **/
const ostream& operator<< (ostream& out, board rhs) {
    rhs.print_shown_board();
    return out;
}

/**
 * Takes a user input and selects the item.
 **/
void board::select_item() {
    pair<int, int> coord = _getInput();
    _revealSpace(coord.first, coord.second);
}

/**
 *  Checks if a selected space exists or not
 *  @param x the vertival index
 *  @param y the horizontal index
 *  @return false if the index is out of bounds
 **/
bool board::_canSelect(int x, int y) {
    if ((x < 0 || x >= _width) || (y < 0 || y >= _height))
        return false;
    return true;
}

/**
 * Reveals a space to the user if the space isnt already revieled.
 * @param x the vertical index
 * @param y the horizontal index
 */
void board::_revealSpace(int x, int y, int val) {
    if (!_canSelect(x, y)) return;
    if (_canSee(x, y)) return;
    if (val==0) return;
    _shown_board.at(y).at(x) = val;
    _numb_shown++;
}

/**
 * Toggles the visibility of a space.
 * @param x the vertical index
 * @param y the horizontal index
 * @param val the value to set _shown_board to if it is toggled on (default to 1)
 */
void board::_toggleSpace(int x, int y, int val) {
    if (!_canSelect(x, y)) return;
    if (_shown_board.at(y).at(x)) {
        _shown_board.at(y).at(x) = false;
        _numb_shown--;
    } else {
        _shown_board.at(y).at(x) = val;
        _numb_shown ++;
    }
}

/**
 * Checks if the user can or cannot see a space
 * @return false if hidden to the user
 **/
bool board::_canSee(int x, int y) {
    return _shown_board.at(y).at(x);
}

/**
 *  Gets the coordinates from the user. The user inputs the value of the spot and then it gets converted to an index
 *  @return a pair of index values, the first item being the vertical and seccond horizontal
 **/
pair<int, int> board::_getInput() {
    cout << "Enter a coordanate: ";
    pair<int, int> coord;
    do {
        cin >> coord.first;
        cin >> coord.second;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }while (!_canSelect(--coord.first, --coord.second) && (cout << "Enter a valid input: "));
    return coord;
}

/**
 * Sets the value of an element in the _val_board at a location.
 * @param x the horizontal coord
 * @param y the vertical coord
 * @param val the value to set
 **/
void board::_setValueBoardAt(int x, int y, int val) {
    _val_board.at(y).at(x) = val;
}

/**
 * Gets the value in _val_board at a location.
 * @param x the horizontal coord
 * @param y the vertical coord
 * @return the value at the location
 **/
int board::_getValueBoardAt(int x, int y) {
    return _val_board.at(y).at(x);
}

/**
 * Sets the value of an element in the _shown_board at a location.
 * @param x the horizontal coord
 * @param y the vertical coord
 * @param val the value to set
 * Note: Removed so that board class handles all changing of the _shown_board and _numb_shown is accurate
 **/
//void board::_setShownBoardAt(int x, int y, int val) {
//    _shown_board.at(y).at(x) = val;
//}

/**
 * Gets the value in _shown_board at a location.
 * @param x the horizontal coord
 * @param y the vertical coord
 * @return the value at the location
 **/
int board::_getShownBoardAt(int x, int y) {
    return _shown_board.at(y).at(x);
}

/**
 * Adds a character replacement value to the map to replace a number with a character on print.
 * @param original the number to replace
 * @param result the character to replace the number with
 * @return false if the item was not added to the map
 **/
bool board::_pushPrintList(int original, char result) {
    if (!_replace.count(original)) {
        _replace.emplace(original, result);
        return true;
    }
    return false;
}

/**
 * Removes an entry in the map of replacemnt items
 * @param original the original number being replaced
 * @return false if failed to remove or entry does not exist
 **/
bool board::_popPrintList(int original) {
    if (_replace.count(original)) {
        _replace.erase(original);
        return true;
    }
    return false;
}

/**
 * Clears the entire map of replacement values.
 **/
void board::_clearPrintList() {
    _replace.clear();
}

/**
 * When shown is being printed call a function if a specified value is encountered.
 * @param original the value in the shown board
 * @param func a function that returns a character that will be printed
 * @return false if the action wasnt added to the map
 **/
bool board::_pushPrintActionList(int original, char(*func)()) {
    if (!_shown_action.count(original)) {
        _shown_action.emplace(original, func);
        return true;
    }
    return false;

}

/**
 * Removes item from the map of actions
 * @param original the key to remove
 * @return false if failure to remove
 **/
bool board::_popPrintActionList(int original) {
    if (_shown_action.count(original)) {
        _shown_action.erase(original);
        return true;
    }
    return false;
}

/**
 * Clears the current map of actions
 **/
void board::_clearPrintActionList() {
    _shown_action.clear();
}
