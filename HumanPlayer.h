//
// Created by Mifrah Mahroof on 8/4/19.
//

#ifndef ASSIGNMENT1_HUMANPLAYER_H
#define ASSIGNMENT1_HUMANPLAYER_H

class HumanPlayer {
public:
    void getMove(Board board, int& x, int& y){
        cout << "Input your move with row and column numbers:" << endl;
        cin >> x >> y;
        x--;
        y--;

        return;
    }
};



#endif //ASSIGNMENT1_HUMANPLAYER_H
