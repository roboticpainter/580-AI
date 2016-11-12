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
  int cur_node = 0;
  long double val =0;
  string l;
  stringstream stream;
  

  for(int i=1; i <= 5; i++)
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
    if(i==1)
    {
      ann->init_rows(rows);
    }
    if(i==2)
    {
      ann->init_test_rows(rows);
    }
  }

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

  for(int i=0; i < (ann->size(5) - 1); i++)
  {
    tmp = ann->value(5,i);
    tmp2 = ann->value(5, i+1);
    for(int j=0; j < tmp; j++)
    {
      for(int k=0; k < tmp2; k++)
      {
        ann->update_next_node(j+cur_node, cur_node+tmp+k);
      }
    }
    cur_node += tmp;
  } 


  ifstream f6(argv[6]); 
  int count = 0;
  while(getline(f6, l))
  {
    istringstream ist(l);
    while(ist >> val)
    {
      ann->add_weights(count, val);
    }
    count++;
  }

  ann->update_prev_nodes();
  ann->set_y();

  //ann->print_members();
  //ann->print_struc();

  int k = ann->get_k();  
  for(int i=0; i < k; i++)
  {
    ann->eval();
    
  }
  
  ann->e_dist();
 
  ann->print_weights();

  return 0;
}
