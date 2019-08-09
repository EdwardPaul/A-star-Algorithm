#include "map.h"

Map::Map()
{
    rows = 512;
    cols = 512;
    ifstream file;
    file.open("random512-20-0.map");

    p = new char *[rows];
    for (int i=0; i<rows; ++i)
    {
        p[i] = new char [cols];
    }
    if (file.is_open())
    {
        for (int i=0; i<rows; i++)
        {
            int j = 0;
            char n=0;
            n = file.get();
            while (n!='\n' && n !=EOF)
            {
                p[i][j] = n;
                j++;
                n = file.get();
            }
        }
    }
    else
    {
        cout << "Can't open the file";
    }

    file.close();
}

Map::~Map()
{
    for (int i=0; i<rows; ++i)
    {
        delete[] p[i];
    }
    delete[] p;
}


bool Map::IsObstacle(int row, int col)
{
    return p[row][col] == '1';
}


bool Map::IsValid(int row, int col)
{
    return (row>=0) && (row<rows) && (col<cols);
}
