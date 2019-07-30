#ifndef STRUCT_H
#define STRUCT_H

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


#endif // STRUCT_H
