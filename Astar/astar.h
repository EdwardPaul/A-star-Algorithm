#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <algorithm>

#include "struct.h"
#include "heuristics.h"
#include "map.h"
#include "configuration.h"
#include "const.h"
#include "config.h"
#include "xmllogger.h"

using namespace std;

class Search
{
private:
    map <int, Node> open;
    unordered_map <int, Node> close;
    SearchResult result;
    AgentConfiguration start;
    AgentConfiguration goal;

    double Hfunc(Node, Node, Heuristics);
    void Path(Node, Map &map, const char*);
    list<Node> findSuccessors(Node, Node, Map &map);
    Config                  config;
    XmlLogger* logger;

public:
    Search();
    Search(Map&);
    ~Search();

    SearchResult Astar(Map &map, const char*);


};

#endif // ASTAR_H
