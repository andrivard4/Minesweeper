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
    void select_item();
    int getHeight();
    int getWidth();
    bool pushPrintList(int original, char result);
    bool popPrintList(int original);
    void clearPrintList();
    void setPrintList(map<int, char>);
protected:
    void _setValueBoardAt(int x, int y, int val);
    int _getValueBoardAt(int x, int y);
    void _setShownBoardAt(int x, int y, bool val);
    bool _getShownBoardAt(int x, int y);
    bool _canSelect(int x, int y);
    void _revealSpace(int x, int y);
    void _toggleSpace(int x, int y);
    bool _canSee(int x, int y);
    pair<int, int> _getInput();
private:
    int _height;
    int _width;
    map<int, char> _replace;
    //  The completed board
    vector<vector<int>> _val_board;
    //  What blocks are shown to the user
    vector<vector<bool>> _shown_board;
};

#endif /* board_hpp */