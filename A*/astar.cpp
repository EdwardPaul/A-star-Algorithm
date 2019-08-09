#include "astar.h"


Search::Search()
{
    result.OpenSize = 0;
    result.CloseSize = 0;
    result.lenght = 0;
    result.FoundPath = false;
}

Search::~Search()
{}

double Search::Hfunc(Node curr, Node fin, Euristics eur)
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

void Search::Path(Node curr, Map &map)
{
    while(curr.parent)
    {
        track.push_front(curr);
        curr = *curr.parent;
    }

    track.push_front(curr);
    cout<<"Trajectory: ";
    while(!track.empty())
    {
        Node temp = *track.begin();
        track.pop_front();
        //map.p[temp.i][temp.j] = 8;
        cout << "->(" << temp.i << ", " << temp.j << ")";
        result.lenght++;
    }
    cout<<endl;
//    for (int i=0; i<map.rows; i++)
//    {
//        for (int k=0; k<map.cols; k++)
//        {
//            cout << map.p[i][k];
//        }
//        cout << endl;
//    }
    cout << "OpenSize: " << result.OpenSize << endl;
    cout << "CloseSize: " << result.CloseSize << endl;
    cout << "Total number of steрs: " << result.TotalSteps << endl;
    cout << "Lenght: " << result.lenght << endl;
    return;
}


list<Node> Search::findSuccessors(Node curr, Map &map)
{
    Node near;
    list<Node> successors;
    for (int k=-1; k<2; k++)
    {
        for (int l=-1; l<2; l++)
        {
            if (map.IsValid(curr.i + k, curr.j + l) && !map.IsObstacle(curr.i + k, curr.j + l) && (k!=0 || l!=0) && close.find((curr.i+k)*5 + curr.j+l)==close.end())
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

                list<Node>::iterator f = find(open.begin(), open.end(), near);
                Node b = *f;

                if (find(open.begin(), open.end(), near)==open.end() || b.g <=near.g)
                {
                    successors.push_front(near);
                }
            }
        }
    }
    return successors;
}

void Search::Astar(Map &map)
{
    Node curr;
    curr.i = map.start.i;
    curr.j = map.start.j;
    curr.g = 0.0;
    curr.h = Hfunc(curr, map.fin, EUCLID);
    curr.f = curr.g + curr.h;
    curr.parent = nullptr;

    open.push_back(curr);
    result.OpenSize++;

    while(!open.empty())
    {
        Node min;
        min.f = LONG_MAX;


        list<Node>::iterator it = open.begin();
        while (it != open.end())
        {
            if (it->f <= min.f)
                min = *it;
            it++;
        }
        curr = min;
        open.remove(curr);
        result.OpenSize--;

        if (curr.i == map.fin.i && curr.j == map.fin.j)
        {
            result.FoundPath = true;
            result.TotalSteps = result.CloseSize + result.OpenSize;
            Path(curr, map);
        }

        close.insert({curr.i*5 + curr.j, curr});

        list <Node> successors = findSuccessors(curr, map);
        list <Node> :: iterator it2 = successors.begin();

        while (it2!=successors.end())
        {
            it2->parent = &(close.find(curr.i*5 + curr.j)->second);
            it2->h = Hfunc(*it2, map.fin, EUCLID);
            it2->f = it2->g + it2->h;
            open.push_back(*it2);
            result.OpenSize++;
            it2++;

            result.CloseSize = close.size() + 1;

        }

    }

    if(result.FoundPath == false)
    {
        cout<< "Meh" <<endl;
    }

}
