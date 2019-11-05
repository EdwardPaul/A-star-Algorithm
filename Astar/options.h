#ifndef OPTIONS
#define OPTIONS

class Options
{
private:

public:
    Options(){}
    ~Options(){}


    bool allowdiagonal;
    bool cutcorners;
    bool allowsqueeze;
    double hweight;
    int metrictype;
};

#endif // OPTIONS
