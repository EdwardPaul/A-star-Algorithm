#include "options.h"

Options::Options(){}

Options::Options(bool AD, bool CC, bool AS, double HW, int MT)
{
    allowdiagonal = AD;
    cutcorners = CC;
    allowsqueeze = AS;
    hweight = HW;
    metrictype = MT;
}

Options::~Options()
{
}
