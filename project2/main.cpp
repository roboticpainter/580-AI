/*
 * Author: Colby Bates
 * File: main.cpp
 */

#include <iostream>
#include "ann.h"
#include <fstream>
#include <sstream>

using namespace std;
using std::cout;


int main(int argc, char *argv[])
{
  Ann* ann = new Ann();
  
  for(int i=1; i <= 6; i++)
  {
    long double x = 0;
    string line;
    stringstream ss;
    int rows = 0;
    ifstream f(argv[i]);
    while(getline (f,line))
    {
      ss << line << ' ';
      rows++;
    }
    while(ss >> x)
    {
      ann->add_value(i, x);
    }
    ann->init_rows(rows);
  }
  ann->print_members();
  return 0;
}
