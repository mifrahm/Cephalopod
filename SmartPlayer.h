//
// Created by Mifrah Mahroof on 14/4/19.
//

#ifndef ASSIGNMENT1_SMARTPLAYER_H
#define ASSIGNMENT1_SMARTPLAYER_H

#include "Cell.h"

const int simulation_times = 100;

class SmartPlayer {
    int playerNo;
    int tempPlayerNo;
public:

    SmartPlayer(int a){
        playerNo = a;
        tempPlayerNo = a;
    }
    void getMove(Board& board, int& x, int& y) {

        // starting the Monte Carlo

        vector<int> emptyCells = board.getEmptyPositions();

        if (emptyCells.empty())
            return;

        priority_queue<Cell> moves;

        for (int index: emptyCells) {
            int a = index / board.getCol();
            int b = index % board.getCol();

            Board tempBoard(board);

            tempBoard.addMove(playerNo, a, b);

            if (tempBoard.checkBoardFull()) {
                if (tempBoard.checkWinner() == playerNo) {
                    x = a;
                    y = b;
                    return;
                } else {
                    continue;
                }
            }

            double utility = simulation(tempBoard);

            Cell c(a, b, utility);
            moves.push(c);

        }

        if (moves.size() > 0) {
            x = moves.top().x;
            y = moves.top().y;

            cout << moves.size() << " Monte Carlo Utility = " << moves.top().heuristicvalue << " at (" << x << "," << y << ")"
                 << endl;
        }

        return;
    }

    double simulation (Board& board){

        int winning = 0;

        for (int i = 0; i < simulation_times; i++) {
            Board tempBoard(board);
            winning += expansion(tempBoard);
        }

        return ((double) winning/ (double) simulation_times);
    }

    int expansion(Board& board){

        if (board.checkBoardFull()){
            if (board.checkWinner() == playerNo){
                return 1;
            } else {
                return -1;
            }
        }



        if (tempPlayerNo == 1){
            tempPlayerNo = -1;
        } else {
            tempPlayerNo = 1;
        }

        int j, k;
        board.getRandom(j, k);
        board.addMove(tempPlayerNo, j, k);
        board.checkNeighboursNoText(j, k);

        return expansion(board);
    }
};


#endif //ASSIGNMENT1_SMARTPLAYER_H

