#include "Filter.h"
#include <algorithm>
#include<debug.h>
//Filtro
Filter::Filter() : _filterName("None"){
}

Filter::Filter(Filter& fil){
  _filterName = fil._filterName;
}
 
Filter::~Filter() {
  DEBOUT(("Filter::~Filter()\n"));
}

Filter::Filter(string filterName) : _filterName(filterName){
}

//Filtro lineare
FilterLinear::FilterLinear(double m, double b): Filter("Linear"), _slope(m), _intercept(b){
  
}

int FilterLinear::getValue(vector<int>& vec){
  return static_cast<int>(_slope*vec[0]+_intercept);
}

//Filtro Media
FilterMean::FilterMean() : Filter("Mean"){
  
}

int
FilterMean::getValue(vector<int>& vec){
  vector<int>::iterator itVec;
  int sum = 0;
  for(itVec=vec.begin();itVec!=vec.end();itVec++){
    sum += *itVec;
  }
  return (sum/vec.size());
  
}

//Filtro Mediano
FilterMedian::FilterMedian() : Filter("Median"){
  
}

int
FilterMedian::getValue(vector<int>& vec){
  int size = vec.size();
  sort(vec.begin(), vec.end());
  if(size%2 == 0) return (vec[size/2]+vec[(size/2)+1])/2;
  else return vec[((size-1)/2)+1];
  
}
