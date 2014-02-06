#ifndef FILTER_DEFINED
#define FILTER_DEFINED
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Filter{
  public:
    Filter();
    Filter(Filter& fil);
    virtual ~Filter();
    virtual int getValue(vector<int>& vec ) = 0;
  protected:
    Filter(string filterName);
  private:
    string _filterName;
};

class FilterLinear : public Filter{
  public:
    FilterLinear(double m = 1.0, double b = 0.0);
    virtual int getValue(vector<int>& vec);
  private:
    double _slope;
    double _intercept;
};


class FilterMean : public Filter{
  public:
    FilterMean();
    virtual int getValue(vector<int>& vec);
};


class FilterMedian : public Filter{
  public:
    FilterMedian();
    virtual int getValue(vector<int>& vec);
};

#endif
