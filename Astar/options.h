#ifndef OPTIONS
#define OPTIONS

class Options
{
private:

public:
    Options();
    Options(bool, bool, bool, double, int);
    ~Options();


    bool allowdiagonal;
    bool cutcorners;
    bool allowsqueeze;
    double hweight;
    int metrictype;
};

#endif // OPTIONS

