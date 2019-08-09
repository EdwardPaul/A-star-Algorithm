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


struct SearchResult
{
    int TotalSteps;
    int OpenSize;
    int CloseSize;
    int lenght;
    bool FoundPath;

};

#endif // STRUCT_H
