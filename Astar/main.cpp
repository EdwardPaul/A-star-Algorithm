#include "struct.h"
#include "astar.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 0;
    }

    Map map1;
    map1.getMap(argv[1]);


    Search search;
    search.Astar(map1);
}
