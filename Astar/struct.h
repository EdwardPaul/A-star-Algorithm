#ifndef STRUCT_H
#define STRUCT_H

#include <list>

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
    int lenght;
    bool FoundPath;
    std::list <Config> track;

};

#endif // STRUCT_H
