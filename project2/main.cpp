/*
 * Author: Colby Bates
 * File: main.cpp
 */

#include <stdlib.h>
#include <iostream>
#include "ann.h"
#include <fstream>
#include <sstream>

using namespace std;
using std::cout;


int main(int argc, char *argv[])
{
  Ann* ann = new Ann(atoi(argv[7]));
  int tmp = 0; 
  int tmp2 = 0;
  int tmp3 = 0; 

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
  tmp2 = ann->size(5);
  for(int i=0; i < tmp2; i++)
  {
    tmp3 = ann->value(5,i);
    for(int j=0; j < tmp3; j++)
    {
      ann->add_node(new Node(tmp));  
      tmp++;
    }    
  }

  return 0;
}
