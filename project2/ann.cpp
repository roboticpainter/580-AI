/*
 * Author: Colby Bates
 * File: ann.cpp
 */

#include "ann.h"

Node::Node(int id) : a(0), in(0), err(0), idnum(id)
{

}

Node::~Node()
{

}


Ann::Ann(int k) : m_k(k) 
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

void Ann::add_node(Node* n)
{
  network.push_back(n);
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
  cout << "K:" << m_k << "\n";
}

int Ann::size(int selection)
{
  switch(selection)
  {
    case 1:
      return train_input.size();
      break;
    case 2:
      return train_output.size();
      break;
    case 3:
      return test_input.size();
      break;
    case 4:
      return test_output.size();
      break;
    case 5:
      return structure.size();
      break;
    case 6:
      return weights.size();
      break;
    case 0:
      return network.size();
      break;
  }
}

long double Ann::value(int selection, int pos)
{
  switch(selection)
  {
    case 1:
      return train_input.at(pos);
      break;
    case 2:
      return train_output.at(pos);
      break;
    case 3:
      return test_input.at(pos);
      break;
    case 4:
      return test_output.at(pos);
      break;
    case 5:
      return structure.at(pos);
      break;
    case 6:
      return weights.at(pos);
      break;
  } 
}

void Ann::update_next_node(int node, int nex_node)
{
  network.at(node)->next.push_back(network.at(nex_node)); 
}

void Ann::print_struc()
{
  cout << "Structure: \n";
  for(int i = 0; i < network.size(); i++)
  {
    cout << "Node[" << i << "] Links:\n";
    for(int j = 0; j < network.at(i)->next.size(); j++)
    {
      cout << (network.at(i)->next.at(j))->idnum << " ";
    }
    cout << "\n"; 
  }
}
