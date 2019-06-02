//
// Created by Mifrah Mahroof on 8/4/19.
//

#ifndef ASSIGNMENT1_RANDOMPLAYER_H
#define ASSIGNMENT1_RANDOMPLAYER_H

class RandomPlayer {
public:
    void getMove(Board board, int& x, int& y){
        board.getRandom(x, y);
        return;
    }
};


#endif //ASSIGNMENT1_RANDOMPLAYER_H
