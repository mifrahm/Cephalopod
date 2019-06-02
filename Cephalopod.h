//
// Created by Mifrah Mahroof on 8/4/19.
//

#ifndef ASSIGNMENT1_CEPHALOPOD_H
#define ASSIGNMENT1_CEPHALOPOD_H


#include "Board.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include "SmartPlayer.h"

class Cephalopod {

public:

    void play(){

        cout <<"Select from the follow: " << endl;
        cout <<"1) Human Player (White Player) vs Smart Player (Black Player)" << endl;
        cout << "2) Random Player (White Player) vs Smart Player (Black Player) " << endl;

        int selection;
        cin >> selection;

        if (selection == 1){
            HumanVsSmartPlayer();
        } else if (selection ==2 ){
            RandomPlayerVsSmartPlayer();
        } else {
            cout << "Incorrect, please select another option" << endl;
        }


    }

    void HumanVsSmartPlayer(){

        cout <<"Input the size of board, say (3 3), (3 5) or (5 5): " << endl;

        int row, col;
        cin >> row >> col;

        Board board(row,col);



        HumanPlayer human;
        SmartPlayer smartPlayer(-1);

        int x, y;
        int turn = 0;
        int player; // 1 (for white player) or -1 (for black player)

        do {
            cout << "Game board:" << endl;
            board.printBoard();

            do {
                if (turn%2 == 0){
                    human.getMove(board, x, y);
                    player = 1;
                }
                else {

                    smartPlayer.getMove(board, x, y);
                    player = -1;
                }

            } while (!(board.validate(x,y)));

            cout << " --------------------- " << endl;
            if (player==1){
                cout << "Human Move: (";
            } else if (player==-1){
                cout << "Computer Move: (";
            }

            cout << x << "," << y <<")" << endl;

            board.addMove(player, x, y);
            //checking the neighbours
            board.checkNeighbours(x, y);
            turn++;

        } while ( !board.checkBoardFull() );

        board.printBoard();


        if (board.checkWinner() > 0){
            cout << "The winner is Human Player. Congratulations!" << endl << endl;
        } else {
            cout << "The winner is Computer Move. Congratulations!" << endl << endl;
        }

        board.printMoves();
    }


    void RandomPlayerVsSmartPlayer(){

        cout <<"Input the size of board, say (3 3), (3 5) or (5 5): " << endl;

        int row, col;
        cin >> row >> col;

        Board board(row,col);


        RandomPlayer random;
        SmartPlayer smartplayer(-1);

        int x, y;
        int turn = 0;
        int player; // 1 (for white player) or -1 (for black player)

        do {
            cout << "Game board:" << endl;
            board.printBoard();


                if (turn%2 == 0){
                    random.getMove(board, x, y);
                    player = 1;
                }
                else {
                    smartplayer.getMove(board, x, y);
                    player = -1;
                }


             cout << " --------------------- " << endl;
            if (player==1){
                cout << "Random Player Move: (";
            } else if (player==-1){
                cout << "Smart Player Move: (";
            }

            cout << x << "," << y <<")" << endl;

            board.addMove(player, x, y);

            //checking the neighbours
            board.checkNeighbours(x, y);

            turn++;

        } while ( !board.checkBoardFull() );

        board.printBoard();

        if (board.checkWinner() > 0){
            cout << "The winner is Random Player. Congratulations!" << endl << endl;
        } else {
            cout << "The winner is Smart Player. Congratulations!" << endl << endl;
        }

        board.printMoves();
    }

};

#endif //ASSIGNMENT1_CEPHALOPOD_H
