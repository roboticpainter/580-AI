/*
 * Author: Colby Bates
 * File: ann.cpp
 */

#include "ann.h"

Node::Node(int id)
{
  a = 0;
  in = 0;
  err = 0;
  idnum = id;
}

Node::~Node()
{

}


void Node::set_in(long double value)
{
  in = value; 
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

void Ann::add_weights(int iter, long double value)
{
  network.at(iter)->n_weights.push_back(value);
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
  for(unsigned int i=0; i < train_input.size(); i++)
  {
    cout << train_input.at(i) << " \n";
  }
  cout << "Train Output: \n";
  for(unsigned int i=0; i < train_output.size(); i++)
  {
    cout << train_output.at(i) << " \n";
  }
  cout << "Test Input: \n";
   for(unsigned int i=0; i < test_input.size(); i++)
  {
    cout << test_input.at(i) << " \n";
  }
  cout << "Test Output: \n";
   for(unsigned int i=0; i < test_output.size(); i++)
  {
    cout << test_output.at(i) << " \n";
  }
  cout << "Structure: \n";
   for(unsigned int i=0; i < structure.size(); i++)
  {
    cout << structure.at(i) << " \n";
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
  return -1;
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
  return -1; 
}

void Ann::update_next_node(int node, int nex_node)
{
  network.at(node)->next.push_back(network.at(nex_node)); 
}

void Ann::update_prev_nodes()
{
  for(unsigned int i=0; i < (network.size() - structure.back()); i++)
  {
    for(unsigned int j=0; j < network.at(i)->next.size(); j++)
    {
      Node* tmp = network.at(i)->next.at(j);
      network.at(tmp->idnum)->from.push_back(network.at(i));
      long double tmpw = network.at(i)->n_weights.at(j);
      network.at(tmp->idnum)->f_weights.push_back(tmpw);
    }
  }
}

void Ann::print_struc()
{
  cout << "Structure: \n";
  for(unsigned int i = 0; i < network.size(); i++)
  {
    cout << "Node[" << i << "]\n"; 
    cout << "To Links:\n";
    for(unsigned int j = 0; j < network.at(i)->next.size(); j++)
    {
      cout << (network.at(i)->next.at(j))->idnum << " ";
    }
    cout << "\nWeights:\n";
    for(unsigned int j=0; j < network.at(i)->n_weights.size(); j++)
    {
      cout << network.at(i)->n_weights.at(j) << " ";
    }
    cout << "\nFrom Links:\n";
    for(unsigned int j = 0; j < network.at(i)->from.size(); j++)
    {
      cout << (network.at(i)->from.at(j))->idnum << " ";
    }
    cout << "\nFrom Weights:\n";
    for(unsigned int j=0; j < network.at(i)->f_weights.size(); j++)
    {
      cout << network.at(i)->f_weights.at(j) << " ";
    }
    cout << "\n\n";
  }
}

void Ann::eval()
{
  //long double a[network.size()];
  //STEP 1:
  //for loop fills a vector
  /* for(int i=0; i < )
  {

  }*/
  //STEP 2/3:
  for(unsigned int i=structure.at(0); i < (network.size()-1); i++)
  {
    //long double sum=0;
    //Need from values...
    /*
    for(int j=0; j < )
    {
 
    }*/
    //network.at(i)->set_in();
  }
}
