#include "astar.h"


Search::Search()
{
}

Search::Search(Map &map)
{
    result.length = 0;
    result.FoundPath = false;
    //XmlLogger();

    start.x = map.start_i;
    start.y = map.start_j;
    goal.x = map.goal_i;
    goal.y = map.goal_j;
}

Search::~Search()
{}

double Search::Hfunc(Node curr, Node fin, Heuristics eur)
{
    switch (eur)
    {
    case EUCLID:
        return sqrt(pow(curr.i-fin.i,2) + pow(curr.j-fin.j,2));
    case MANHATTAN:
        return (abs(curr.i-fin.i) + abs(curr.j - fin.j));
    case DIAGONAL:
        return (abs(abs(curr.i - fin.i) - abs(curr.j - fin.j)) + sqrt(2) * min(abs(curr.i - fin.i), abs(curr.j - fin.j)));
    case CHEBYSHEV:
        return max(abs(curr.i - fin.i), abs(curr.j - fin.j));
    default:
        return 0;
    }
}

void Search::Path(Node curr, Map &map, const char* FileName)
{
    AgentConfiguration path;
    result.length = 0;
    while(curr.parent)
    {
        path.x = curr.i;
        path.y = curr.j;
        result.track.push_front(path);
        curr = *curr.parent;
    }

    list <AgentConfiguration> :: iterator itl = result.track.begin();

    while (itl!=result.track.end())
    {
        if (itl->x - next(itl)->x == 0 || itl->y - next(itl)->y == 0)
        {
            result.length = result.length + 1.0;
        }
        else
        {
            result.length = result.length + 1.4;
        }

        itl++;

    }


    cout << "OpenSize: " << open.size() << endl;
    cout << "Total number of steрs: " << result.TotalSteps << endl;
    cout << "Total number of nodes: " << result.NodesNum << endl;
    cout << "length: " << result.length << endl;
    cout << "Time: " << result.Time << endl;


    config.getConfig(FileName);
    logger = new XmlLogger;
    logger->getLog(FileName, config.LogParams);
    logger->writeToLogSummary(result, map.cellSize);
    logger->writeToLogMap(map, result.track);
    logger->writeToLogPath(result.track);
    logger->saveLog();
}


list<Node> Search::findSuccessors(Node curr, Node fin, Map &map)
{
    Node near;
    list<Node> successors;
    for (int k=-1; k<2; k++)
    {
        for (int l=-1; l<2; l++)
        {
            if (map.IsValid(curr.i + k, curr.j + l) && !map.IsObstacle(curr.i + k, curr.j + l) && (k!=0 || l!=0))
            {
                near.i = curr.i + k;
                near.j = curr.j + l;

                if(k==0 || l==0)
                {
                    near.g = curr.g + 1.0;
                }
                else
                {
                    near.g = curr.g + 1.4;
                }

                near.h = Hfunc(near, fin, EUCLID);
                near.f = near.g + near.h;


                successors.push_front(near);
            }
        }
    }
    return successors;
}

SearchResult Search::Astar(Map &map, const char* FileName)
{
    result.Time = time(NULL);
    Node curr;
    Node fin;
    fin.i = goal.x;
    fin.j = goal.y;
    curr.i = start.x;
    curr.j = start.y;
    curr.g = 0.0;
    curr.h = Hfunc(curr, fin, EUCLID);
    curr.f = curr.g + curr.h;
    curr.parent = nullptr;

    open.insert({curr.i*map.height + curr.j, curr});

    while(!open.empty())
    {
        Node min;
        min.f = LONG_MAX;


        std::map<int, Node>::iterator it = open.begin();
        while (it != open.end())
        {
            if (it->second.f <= min.f)
                min = it->second;
            it++;
        }
        curr = min;
        open.erase(curr.i*map.height + curr.j);

        if (curr.i == fin.i && curr.j == fin.j)
        {
            result.FoundPath = true;
            result.TotalSteps = close.size();
            result.NodesNum = open.size() + close.size();
            result.Time = time(NULL) - result.Time;
            Path(curr, map, FileName);
            break;
        }

        close.insert({curr.i*map.height + curr.j, curr});

        list <Node> successors = findSuccessors(curr, fin, map);
        list <Node> :: iterator it2 = successors.begin();

        while (it2!=successors.end())
        {
            Node temp = *it2;

            if (close.find(temp.i * map.height + temp.j)==close.end())
            {
                std::map<int, Node>::iterator it_open = open.find(temp.i * map.height + temp.j);
                Node o = it_open->second;

                if (open.find(temp.i * map.height + temp.j)!=open.end() && temp.g <= o.g)
                {
                    o.g = temp.g;
                    o.f = o.g + o.h;
                    o.parent = &temp;
                }

                else if (open.find(temp.i * map.height + temp.j)==open.end())
                {
                    temp.parent = &(close.find(curr.i*map.height + curr.j)->second);
                    open.insert({temp.i * map.height + temp.j, temp});
                }
            }

            it2++;
        }


    }

    if(result.FoundPath == false)
    {
        cout<< "Not found" <<endl;
    }


    return result;

}


