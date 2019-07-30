#include "map.h"

Map::Map()
{
    rows = 0;
    cols = 0;
    p = nullptr;
}


Map::Map(int row, int col, Node start, Node fin)
{
    rows = row;
    cols = col;

    int map[rows][cols] = {{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                           { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                           { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                           { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                           { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                           { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                           { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }};

    p = new int*[rows];
    for (int i=0; i<rows; i++)
    {
        p[i] = new int[cols];
        for (int j=0; j<cols; j++)
        {
            p[i][j]=map[i][j];
        }
    }

    start.i = 8;
    start.j = 0;
    fin.i = 0;
    fin.j = 0;

}

bool Map::IsValid(int i, int j)
{
    return (i<rows) && (i>=0) && (j<cols) && (j>=0);
}

bool Map::IsObstacle(int i, int j)
{
    return p[i][j] == 0;
}

Map::~Map()
{

    for (int i=0; i<rows; i++)
    {
        delete []p[i];
    }
    delete []p;
}
