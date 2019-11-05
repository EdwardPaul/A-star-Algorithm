#include "astar.h"


Search::Search()
{
    result.FoundPath = false;
    count = 0;
}

Search::~Search()
{
}

void Search::get_input(Map &map)
{
    start.x = map.start_i;
    start.y = map.start_j;
    goal.x = map.goal_i;
    goal.y = map.goal_j;

    config.getConfig(map.filename);
    options.allowdiagonal = config.SearchParams[CN_SP_AD];
    options.cutcorners = config.SearchParams[CN_SP_CC];
    options.allowsqueeze = config.SearchParams[CN_SP_AS];
    options.hweight = config.SearchParams[CN_SP_HW];
    options.metrictype = config.SearchParams[CN_SP_MT];
}


double Search::Hfunc(Node curr, Node fin)
{
    switch (options.metrictype)
    {
    case 0:
        return (abs(abs(curr.i - fin.i) - abs(curr.j - fin.j)) + sqrt(2) * min(abs(curr.i - fin.i), abs(curr.j - fin.j)));
    case 1:
        return (abs(curr.i-fin.i) + abs(curr.j - fin.j));
    case 2:
        return sqrt(pow(curr.i-fin.i,2) + pow(curr.j-fin.j,2));
    case 3:
        return max(abs(curr.i - fin.i), abs(curr.j - fin.j));
    default:
        return 0;
    }
}


void Search::Path(Node curr, Map &map)
{
    AgentConfiguration path;
    while(curr.parent)
    {
        path.x = curr.i;
        path.y = curr.j;
        result.track.push_front(path);
        curr = *curr.parent;
    }

    result.track.push_front(start);


    cout << "OpenSize: " << open.size() << endl;
    cout << "Total number of steрs: " << result.TotalSteps << endl;
    cout << "Total number of nodes: " << result.NodesNum << endl;
    cout << "length: " << result.length << endl;
    cout << count << endl;

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
                if (k!=0 && l!=0)
                {
                    if (!options.allowdiagonal)
                    {
                        continue;
                    }

                    else if (!options.cutcorners)
                    {
                        if (map.IsObstacle(curr.i, curr.j + l) || map.IsObstacle(curr.i + k, curr.j))
                        {
                            continue;
                        }
                    }

                    else if (!options.allowsqueeze)
                    {
                        if (map.IsObstacle(curr.i, curr.j + l) && map.IsObstacle(curr.i + k, curr.j))
                        {
                            continue;
                        }
                    }
                }

                near.i = curr.i + k;
                near.j = curr.j + l;


                if(k==0 || l==0)
                {
                    near.g = curr.g + 1.0;
                }
                else
                {
                    near.g = curr.g + CN_SQRT_TWO;
                }

                near.h = Hfunc(near, fin);
                near.f = near.g + near.h;

                successors.push_front(near);

            }
        }
    }
    return successors;
}

SearchResult Search::Astar(Map &map)
{

    get_input(map);

    std::chrono::time_point<std::chrono::system_clock> start_sec, end_sec;
    start_sec = std::chrono::system_clock::now();
    Node curr;
    Node fin;
    fin.i = goal.x;
    fin.j = goal.y;
    curr.i = start.x;
    curr.j = start.y;
    curr.g = 0.0;
    curr.h = Hfunc(curr, fin);
    curr.f = curr.g + options.hweight * curr.h;
    curr.parent = nullptr;

    open.insert({curr.i*map.height + curr.j, curr});

    while(!open.empty())
    {
        Node min;
        min.f = LONG_MAX;


        std::unordered_map<int, Node>::iterator it = open.begin();
        for (;it != open.end(); it++)
        {
            if (it->second.f > min.f)
            {
                continue;
            }
            if (it->second.f == min.f)
            {
                if (it->second.g >= min.g)
                {
                    continue;
                }

                min = it->second;
            }
            else
            {
                min = it->second;
            }
        }
        curr = min;
        close.insert({curr.i*map.height + curr.j, curr});
        open.erase(curr.i*map.height + curr.j);

        if (curr.i == fin.i && curr.j == fin.j)
        {
            result.FoundPath = true;
            result.TotalSteps = close.size();
            result.NodesNum = open.size() + close.size();
            result.length = curr.g;
            Path(curr, map);
            break;
        }


        list <Node> successors = findSuccessors(curr, fin, map);
        list <Node> :: iterator it2 = successors.begin();

        for (;it2 != successors.end();++it2)
        {
            Node temp = *it2;

            unordered_map<int, Node>::iterator it_open = open.find(temp.i * map.height + temp.j);
            Node* o = &(it_open->second);

            if (close.find(temp.i * map.height + temp.j)!=close.end())
            {
                continue;
            }

            if (it_open==open.end())
            {

                temp.parent = &(close.find(curr.i*map.height + curr.j)->second);
                open.insert({temp.i * map.height + temp.j, temp});
            }

            else
            {
                if (temp.g >= o->g)
                {
                    continue;
                }

                open.erase(temp.i * map.height + temp.j);
                o->g = temp.g;
                o->f = o->g + options.hweight * o->h;
                o->parent = &(close.find(curr.i*map.height + curr.j)->second);
                open.insert({temp.i * map.height + temp.j, *o});
                count++;
            }
        }

    }

    if(result.FoundPath == false)
    {
        cout<< "Not found" <<endl;
    }

    end_sec = std::chrono::system_clock::now();
    result.Time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end_sec - start_sec).count()) / 1000000000;

    logger.getLog(map.filename, config.LogParams);
    logger.writeToLogSummary(result, map.cellSize);
    logger.writeToLogMap(map, result.track);
    logger.writeToLogPath(result.track);
    logger.saveLog();

    return result;
    return result;

}

