#include "algo.h"
#include "struct.h"

int main()
{
    Node start, fin;
    start.i = 8;
    start.j = 0;
    fin.i = 0;
    fin.j = 0;
    int rows = 9, cols = 10;

    int map[rows][cols] = {{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }};

    int *p[rows];
    for (int i = 0; i < rows; i++)
    {
        p[i] = map[i];
    }

    Search search;
    search.Astar(start, fin, p, rows, cols);
}

