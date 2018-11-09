//
//  board.hpp
//  Minesweeper
//
//  Created by Andrew Rivard on 11/8/18.
//  Copyright © 2018 Andrew Rivard. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <vector>
#include <utility>
#include <iostream>
#include <map>
using namespace std;

class board {
public:
    board(int height=10, int width=10);
    friend const ostream& operator<< (ostream& out, board rhs);
    const void print_hidden_board();
    const void print_shown_board();
    void    select_item();
    int     getHeight();
    int     getWidth();

protected:
    void    _setValueBoardAt(int x, int y, int val);
    int     _getValueBoardAt(int x, int y);
    void    _setShownBoardAt(int x, int y, int val);
    int     _getShownBoardAt(int x, int y);
    bool    _canSelect(int x, int y);
    void    _revealSpace(int x, int y);
    void    _toggleSpace(int x, int y);
    bool    _canSee(int x, int y);
    bool    _pushPrintList(int original, char result);
    bool    _popPrintList(int original);
    void    _clearPrintList();
    bool    _pushPrintActionList(int original, char(*func)());
    bool    _popPrintActionList(int original);
    void    _clearPrintActionList();
    pair<int, int> _getInput();
private:
    int     _height;
    int     _width;
    // When outputing shown data call func when data in data = key.
    map<int, char(*)()> _shown_action;
    // Replaces key with value when printing from _val_board
    map<int, char> _replace;
    //  The completed board
    vector<vector<int>> _val_board;
    //  What blocks are shown to the user
    vector<vector<int>> _shown_board;
};

#endif /* board_hpp */
