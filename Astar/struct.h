#ifndef STRUCT_H
#define STRUCT_H

#include <list>
#include <time.h>

#include "configuration.h"

struct Node
{
    int i, j;
    double f, g, h;
    Node* parent;

    bool operator ==(const Node &comp) const
    {
        return (i == comp.i && j == comp.j);
    }

};


struct SearchResult
{
    int TotalSteps;
    int NodesNum;
    double length;
    bool FoundPath;
    std::list <AgentConfiguration> track;
    time_t Time;

};

#endif // STRUCT_H
