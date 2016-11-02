/*
 * Author: Colby Bates
 * File: ann.cpp
 */

#include "ann.h"

Ann::Ann()
{
  
}

Ann::~Ann()
{

}

void Ann::add_value(int choice, long double value)
{
  switch(choice)
  {
    case 1:
      train_input.push_back(value);
      break;
    case 2:
      train_output.push_back(value);
      break;
    case 3:
      test_input.push_back(value);
      break;
    case 4:
      test_output.push_back(value);
      break;
    case 5:
      structure.push_back(value);
      break;
    case 6:
      weights.push_back(value);
      break;
  }
}

void Ann::init_rows(int value)
{
  io_rows = value;
}

void Ann::print_members()
{
  cout << "Train Input: \n";
  for(int i=0; i < train_input.size(); i++)
  {
    cout << train_input.at(i) << " \n";
  }
  cout << "Train Output: \n";
  for(int i=0; i < train_output.size(); i++)
  {
    cout << train_output.at(i) << " \n";
  }
  cout << "Test Input: \n";
   for(int i=0; i < test_input.size(); i++)
  {
    cout << test_input.at(i) << " \n";
  }
  cout << "Test Output: \n";
   for(int i=0; i < test_output.size(); i++)
  {
    cout << test_output.at(i) << " \n";
  }
  cout << "Structure: \n";
   for(int i=0; i < structure.size(); i++)
  {
    cout << structure.at(i) << " \n";
  }
  cout << "Weights: \n";
   for(int i=0; i < weights.size(); i++)
  {
    cout << weights.at(i) << " \n";
  }
}

Node::Node()
{

}

Node::~Node()
{

}
