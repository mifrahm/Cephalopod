//
// Created by Mifrah Mahroof on 8/4/19.
//

#ifndef ASSIGNMENT1_BOARD_H
#define ASSIGNMENT1_BOARD_H

#include<iostream>
#include <stdlib.h> // for srand
#include <time.h> // for time

#include<list>
#include <unordered_map>
#include <algorithm>
#include "Cell.h"
#include "NeighbourCell.h"


using namespace std;

class Board{
private:
    int row, col;
    int **grid; //1 = black, -1 = white; 0 = empty
    int boardSize;
    vector<Cell> moves;
    int total;



public:
    Board(int r, int c) {
        row = r;
        col = c;
        boardSize = r*c;
        total = 0;
        grid = new int*[row];
        for (int i = 0; i < row; i++)
            grid[i] = new int[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                grid[i][j] = 0;
            }


        srand (time(NULL));
    }

    ~Board(){
        for (int i=0; i <row; i++)
            delete[] grid[i];

        delete[] grid;
    }

    Board(Board& cboard) { //this is to copy board
        row = cboard.row;
        col = cboard.col;

        grid = new int*[row];
        for (int i = 0; i < row; i++)
            grid[i] = new int[col];

        for (int i=0; i < row; i++)
            for (int j = 0; j < col; j++)
                grid[i][j] = cboard.grid[i][j];
    }

    bool addMove(int player, int x, int y); //adds move on board
    void checkNeighbours(int x, int y);
    void checkNeighboursNoText(int x, int y);
//    int noOfNeighbours(int x, int y, vector<Cell>& cells);
    void printBoard();
    void printMoves(); //prints move history at the end of the game
    bool validate(int x, int y);
    int turnPositive(int num);
    int turnNegative(int num);
    bool checkBoardFull();
    int checkWinner();
    void getRandom(int& x, int& y);
    vector<int> getEmptyPositions();
    int getCol();
    int getRow();
};

bool Board::validate(int x, int y) {

    if ((x < 0) || (x >=row) || ( y < 0 ) || (y >= col)){ // check if selection is out of range
      //  cout << "Out of range. Please input your move with a row and column number" << endl;
        return false;
    }

    if (grid[x][y] != 0){ //check to see if move is filled.
    //    cout << "Move is filled. Please input your move with row and column numbers:" << endl;
        return false;
    }

    return true;
}


void Board::checkNeighbours(int x, int y) {

    total = 0;
    unordered_map<int, NeighbourCell> cell;

    //check top cell
    if (x > 0 && grid[x-1][y]!=0){ //check if x is out of bounds and if neighbour is empty
        if (grid[x-1][y] != 0) {
            NeighbourCell n;
            n.first = "Top";
            n.pipCount = grid[x - 1][y];
            cell[((x - 1) * col + y)] = n; // the key is the cell number
        }
    }



    // Check right cell
    if (y+1 < col && grid[x][y]!=0){
        if (grid[x][y+1] != 0) {
            NeighbourCell n;
            n.first = "Right";
            n.pipCount = grid[x][y + 1];
            cell[(x * col + (y + 1))] = n; // the key is the cell number
        }
    }


    // Check bottom cell

    if (x+1< row && grid[x][y]!=0){
        if (grid[x+1][y] != 0) {
            NeighbourCell n;
            n.first = "Bottom";
            n.pipCount = grid[x + 1][y];
            cell[((x + 1) * col + y)] = n; // the key is the cell number
        }
    }


    // Check left cell
    if (y-1 >=0 && grid[x][y]!=0){
        if (grid[x][y-1] != 0) {
            NeighbourCell n;
            n.first = "Left";
            n.pipCount = grid[x][y - 1];
            cell[(x * col + (y - 1))] = n; // the key is the cell number
        }
    }


    // display neighbour information
    for (auto x: cell) {
            cout << x.second.first << " Cell: " << x.second.pipCount << endl;
    }

    cout << endl;

    if ( cell.size() > 1){
        vector<Cell> neighbours; //all I need is a way to add in numbers into an order

        for (auto x: cell) {
           Cell c((x.first/col), (x.first%col), (turnPositive(x.second.pipCount)));
           neighbours.push_back(c);
           total = total + turnPositive(x.second.pipCount);
        }


    // captures

    if (total <= 6){
        for (auto x: cell) {
            grid[x.first/col][x.first%col] = 0;
            cout << x.second.pipCount << " has been captured" << endl;
        }
    } else { // if the total is more than 6, then only some cells can be added

        if (cell.size() > 2){

            total = 0;
            vector<Cell> usedPips;

            for (int i = 0; i < neighbours.size(); i++){
                total = total + neighbours[i].heuristic;
                if (total <= 6){
                    Cell c(neighbours[i].x, neighbours[i].y, neighbours[i].heuristic);
                    usedPips.push_back(c); // add in cell number we will remove
                } else {
                    total = total - neighbours[i].heuristic;
                }
            }

            if (usedPips.size() > 1){
                for (int i = 0; i < usedPips.size(); i++){
                    grid[usedPips[i].x][usedPips[i].y] = 0;
                    cout << usedPips[i].heuristic << " has been captured" << endl;
                }

            }

        }


    }
        cout << endl;
    }



    cout << "The total is: " << total << endl << endl;



}


void Board::checkNeighboursNoText(int x, int y) {

    total = 0;
    unordered_map<int, NeighbourCell> cell;

    //check top cell
    if (x > 0){ //check if x is out of bounds and if neighbour is empty
        if (grid[x-1][y] != 0) {
            NeighbourCell n;
            n.first = "Top";
            n.pipCount = grid[x - 1][y];
            n.x = x-1;
            n.y = y;
            cell[1] = n; // the key is the cell number
        }
    }



    // Check right cell
    if (y+1 < col){
        if (grid[x][y+1] != 0) {
            NeighbourCell n;
            n.first = "Right";
            n.pipCount = grid[x][y + 1];
            n.x = x;
            n.y = y+1;
            cell[2] = n; // the key is the cell number
        }
    }


    // Check bottom cell

    if (x+1< row){
        if (grid[x+1][y] != 0) {
            NeighbourCell n;
            n.first = "Bottom";
            n.pipCount = grid[x + 1][y];
            n.x = x+1;
            n.y = y;
            cell[3] = n; // the key is the cell number
        }
    }


    // Check left cell
    if (y-1 >=0){
        if (grid[x][y-1] != 0) {
            NeighbourCell n;
            n.first = "Left";
            n.x = x;
            n.y = y-1;
            n.pipCount = grid[x][y - 1];
            cell[4] = n; // the key is the cell number
        }
    }


    if ( cell.size() > 1){
        vector<Cell> neighbours; //all I need is a way to add in numbers into an order

        for (auto x: cell) {
            Cell c((x.second.x), (x.second.y), (turnPositive(x.second.pipCount)));
            neighbours.push_back(c);
            total = total + turnPositive(x.second.pipCount);
        }


        // captures

        if (total <= 6){
            for (auto x: cell) {
                grid[x.second.x][x.second.y] = 0;
            }
        } else { // if the total is more than 6, then only some cells can be added

            if (cell.size() > 2){

                total = 0;
                vector<Cell> usedPips;

                for (int i = 0; i < neighbours.size(); i++){
                        total = total + neighbours[i].heuristic;
                        if (total <= 6){
                            Cell c(neighbours[i].x, neighbours[i].y, neighbours[i].heuristic);
                            usedPips.push_back(c); // add in cell number we will remove
                         //   grid[neighbours[i].x][neighbours[i].y] = 0;
                        } else {
                            total = total - neighbours[i].heuristic;
                        }
                }

                if (usedPips.size() > 1){
                    for (int i = 0; i < usedPips.size(); i++){
                        grid[usedPips[i].x][usedPips[i].y] = 0;
                    }

                }

            }
        }
    }


}






int Board::checkWinner(){

    int countW = 0; // Player white 1
    int countB = 0; // Player black -1

    for (int i=0; i <row; i++)
        for (int j = 0; j < col; j++){
            if(grid[i][j] > 0)
              countW++;
            else if (grid[i][j]< 0)
                countB++;
        }

    if (countW > countB)
        return 1;
    else
        return -1;

}

int Board::turnPositive(int num){

    if (num < 0){
        num = num * -1;
    }

    return num;
}

int Board::turnNegative(int num){

    if (num > 0){
        num = num * -1;
    }

    return num;
}

bool Board::addMove(int player, int x, int y) {

    // dice added into board position

    grid[x][y] = rand()%6+1;


    if (total == 0){
        grid[x][y] = 1;
    } else if (total > 0 && total <= 6){
        grid[x][y] = total;
    }

//    else {
//        grid[x][y] = 1;
//    }

    // turning black player to negative
    if (player == -1){
        grid[x][y] = turnNegative(grid[x][y]);
    }

    //adding in the moves into cell object
    Cell cell(x, y, grid[x][y]);
    moves.push_back(cell);

}

void Board::printMoves() {

    cout << "Game Finished. Moves history:" << endl;

    for (int i=0; i < moves.size(); i ++){
        cout << "Move " << i+1 << ": " << "(" << moves[i].x+1 << "," << moves[i].y+1 << ")" << endl;
    }
}


bool  Board::checkBoardFull(){

    bool boardStatus = true; //by default, the board is full

    for (int i=0; i < row; i++) { // a check needs to be made, to prove it is empty
        for (int j = 0; j < col; j++){
            if(grid[i][j] == 0) {
            boardStatus = false;
            break; // if one cell is found to empty then loop will break and return true.
            }
        }
    }

    return boardStatus;

}

void Board::printBoard() {
    cout << "    ";
    for (int j = 0; j < col; j++) {
        cout << j + 1 << "   ";
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        cout << "  ";
        for (int j = 0; j < col; j++) {
            cout << " ---";
        }
        cout << endl;

        cout << (i + 1) << " |";

        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0) {
                cout << "   |";
            } else if (grid[i][j] > 0) {
                cout << " " << grid[i][j] << " |";
            } else if (grid[i][j] < 0) {
                cout << "" << grid[i][j] << " |";
            }
        }
        cout << endl;
    }
    cout << "  ";

    for (int j = 0; j < col; j++) {
        cout << " ---";
    }
    cout << endl << endl;

}

void Board::getRandom(int &x, int &y) {

    // the random function is inbuilt with validation function

        vector<int> emptyCell = getEmptyPositions();

        int index = rand() % emptyCell.size();
        x = (emptyCell[index]/col);
        y = (emptyCell[index]%col);

   if(!(validate(x,y)))
       cout <<" Problem here" << endl;


}


vector<int> Board::getEmptyPositions(){
    vector<int> emptyCells;
    for (int i=0; i <row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0)
                emptyCells.push_back(i * col + j);
        }
    }

    return emptyCells;

}

int Board::getCol(){
    return col;
}

int Board::getRow(){
    return row;
}

#endif //ASSIGNMENT1_BOARD_H
