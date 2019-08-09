#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <algorithm>

#include "struct.h"
#include "euristics.h"
#include "map.h"

using namespace std;

class Search
{
public:
    Search();
    ~Search();
    //bool IsValid(int, int, int, int);
    //bool IsObstacle(int, int, Map);
    double Hfunc(Node, Node, Euristics);
    void Path(Node, Map &map);
    list<Node> findSuccessors(Node, Map &map);
    void Astar(Map &map);

    list <Node> open;
    unordered_map <int, Node> close;
    list <Node> track;

    SearchResult result;
};

#endif // ASTAR_H
