/*
 * Author: Colby Bates
 * File: main.cpp
 */


#include <iostream>
#include <stdlib.h>
#include "matrix.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using std::cout;


int main(int argc, char *argv[])
{
  Matrix* mat;
  Matrix* mat2;
  Matrix* mat3;
  string line;
  stringstream ss;
  int rows=0;
  int total=0;
  int cols=0;
  int x=0;
  double sens_err=0;
 
  vector<string> obs;
  
  vector<long double> v; 
  vector<Tile*> tiles;
 
  ifstream f(argv[1]);
  while(getline (f, line))
  {
    ss << line << ' ';
    rows++;
  }

  while(ss >> x)
  {
    v.push_back(x);
    total++;
  }
 
  sens_err = atof(argv[2]);

  for(int i=3; i<argc; i++)
  {
    obs.push_back(argv[i]);
  }

  cols = total/rows;

  cout << "total: " << total << "\n";
  cout << "cols: " << cols << "\n";
  cout << "rows: " << rows  << "\n";

  mat = new Matrix(v, rows, cols);

  mat->print();
  for(int i=0; i < mat->rows(); i++)
  {
    for(int j=0; j < mat->cols(); j++)
    {
      Tile* tmp;
      cout << "Value going in: " << mat->value_at(i+1,j+1) << "\n";
      tmp = new Tile(mat->value_at(i+1,j+1));
      tiles.push_back(tmp);
    }
  }

  for(int i=0; i < tiles.size(); i++)
  {
    cout << "~~~~~~~~~~~~~~~~~~~~\n";
    cout << "TILE[" << i << "]:\n";
    tiles[i]->print();
    if(i == tiles.size()-1)
    {
      cout << "~~~~~~~~~~~~~~~~~~~~\n";
    }
  }

  cout << "Sensory Error: " << sens_err << "\n";
  for(int i=0; i<obs.size(); i++)
  {
    cout << "Observations: " << obs.at(i) << "\n";
  }

  return 0;
}
