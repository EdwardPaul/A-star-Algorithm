#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
//#include <map>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <chrono>

#include "struct.h"
#include "map.h"
#include "configuration.h"
#include "const.h"
#include "config.h"
#include "xmllogger.h"
#include "options.h"

using namespace std;

class Search
{
private:
    unordered_map <int, Node> open;
    unordered_map <int, Node> close;
    SearchResult result;
    AgentConfiguration start;
    AgentConfiguration goal;

    double Hfunc(Node, Node);
    void Path(Node, Map &map);
    list<Node> findSuccessors(Node, Node, Map &map);
    Config                  config;
    XmlLogger logger;
    Options options;

public:
    Search();
    ~Search();
    void get_input(Map&);

    SearchResult Astar(Map &map);

    int count;
};

#endif // ASTAR_H
