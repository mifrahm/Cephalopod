//
// Created by Mifrah Mahroof on 8/4/19.
//

#ifndef ASSIGNMENT1_CELL_H
#define ASSIGNMENT1_CELL_H

struct Cell {
    int x;
    int y;
    int heuristic;
    double heuristicvalue;
    Cell(){}
    Cell(int xx, int yy, int hh):x(xx), y(yy), heuristic(hh) {}
    Cell(int xx, int yy, double hh):x(xx), y(yy), heuristic(0), heuristicvalue(hh) {}
    bool operator<(const Cell& c) const {
        return heuristic < c.heuristic;
    }
};

#endif //ASSIGNMENT1_CELL_H
