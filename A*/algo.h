#ifndef ALGO_H
#define ALGO_H

#include "struct.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
#include <limits.h>

using namespace std;

class Search
{
public:
    Search();
    ~Search();
    bool IsValid(int, int, int, int);
    bool IsObstacle(int, int, int**);
    double Hfunc(Node, Node);
    void Path(Node);
    list<Node> findSuccessors(Node, int**, int, int);
    void Astar(Node, Node, int**, int, int);

    list <Node> open;
    unordered_map <int, Node> close;
    list <Node> track;

    int rows, cols;
    int **p;
    Node start;
    Node fin;

};



#endif // ALGO_H
