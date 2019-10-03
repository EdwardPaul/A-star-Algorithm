#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <algorithm>

#include "struct.h"
#include "heuristics.h"
#include "map.h"
#include "configuration.h"
#include "const.h"

using namespace std;

class Search
{
private:
    list <Node> open;
    unordered_map <int, Node> close;
    SearchResult result;
    Config start;
    Config goal;

    double Hfunc(Node, Node, Heuristics);
    void Path(Node, Map &map);
    list<Node> findSuccessors(Node, Map &map);
public:
    Search(int, int, int, int);
    ~Search();

    SearchResult Astar(Map &map);


};

#endif // ASTAR_H
