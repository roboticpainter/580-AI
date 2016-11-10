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
  dummy = 0.01;
  idnum = id;
}

Node::~Node()
{

}


void Node::set_in(long double value)
{
  in = value; 
}

void Node::set_a(long double value)
{
  long double tmp = 0;
  tmp = (1/(1+(exp((-1)*(value)))));
  a = tmp;
}

void Node::set_err(long double value)
{
  err = value;
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

void Ann::set_y()
{
  //Only setup for current tests with 3 types of digits
  int tmp = structure.back();
  switch(tmp)
  {
    case 3:
      y0.push_back(0.1);
      y0.push_back(0.9);
      y0.push_back(0.9);
      y1.push_back(0.9);
      y1.push_back(0.1);
      y1.push_back(0.9);
      y2.push_back(0.9);
      y2.push_back(0.9);
      y2.push_back(0.1);
    break;
    case 4:
      y0.push_back(0.1);
      y0.push_back(0.9);
      y0.push_back(0.9);
      y0.push_back(0.9);
      y1.push_back(0.9);
      y1.push_back(0.1);
      y1.push_back(0.9);
      y1.push_back(0.9);
      y2.push_back(0.9);
      y2.push_back(0.9);
      y2.push_back(0.1);
      y2.push_back(0.9);
      y3.push_back(0.9);
      y3.push_back(0.9);
      y3.push_back(0.9);
      y3.push_back(0.1);
    break;
    default:
      y0.push_back(0);
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

void Ann::init_test_rows(int value)
{
  test_rows = value;
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

void Ann::print_weights()
{
  //cout << "train_input rows: " << io_rows << "\n";
  int amt = structure.at(1);
  for(int i=0; i < amt; i++)
  {
    cout << showpoint << fixed << setprecision(12) << network.at(0)->n_weights.at(i) << " ";
  }
  cout << "\n";
}

void Ann::eval()
{
  unsigned int input_layer_size = structure.at(0);
  unsigned int output_layer_size = structure.back();
  unsigned int output_layer_first_node = (network.size() - output_layer_size);
  unsigned int train_cols = train_input.size()/io_rows;
  //cout << "Train_input size: " << train_input.size() << "\n";
  //cout << "Train_input cols: " << train_cols << "\n";
  //cout << "Train_input rows: " << io_rows << "\n";
  for(int k=0; k < io_rows; k++)
  {
    //X values are: train_input values
    //STEP 1:
    //for loop fills a value of first layer
    for(unsigned int i=0; i < input_layer_size; i++)
    {
      network.at(i)->a = train_input.at(i+(k*train_cols));
    }
    //STEP 2/3:Calculate a values and in values for each node outside of the input layer
    for(unsigned int i=input_layer_size; i < network.size(); i++)
    {
      long double sum=0; 
      for(unsigned int j=0; j < network.at(i)->from.size(); j++)
      {
        sum += ((network.at(i)->from.at(j)->a) * (network.at(i)->f_weights.at(j))); 
      }
      sum += network.at(i)->dummy;
      network.at(i)->set_in(sum);
      network.at(i)->set_a(sum);
    }
    //STEP 4:Calculate the error in the output layer. NEEDS MODIFICATION OF Y VALUES
    int iter=0;
    for(unsigned int i = output_layer_first_node; i < network.size(); i++)
    {
      long double product = 0;
      product = ((network.at(i)->a) * (1-(network.at(i)->a)) * ((y0.at(iter))-(network.at(i)->a)));
      network.at(i)->set_err(product);
      iter++;
    }
    //STEP 5/6:Calculate error for each previous node using back propagation.
    for(unsigned int i = (output_layer_first_node - 1); i > 0; i--)
    {
      long double tmp = 0;
      long double product = 0;
      product = ((network.at(i)->a)*((1-(network.at(i)->a))));
      for(unsigned int j = 0; j < network.at(i)->next.size(); j++)
      {
        tmp += ((network.at(i)->next.at(j)->err) * network.at(i)->n_weights.at(j));
      }
      tmp = tmp*product;
      network.at(i)->set_err(tmp);
    }
    //STEP 7:Update weights!
    for(unsigned int i=0; i < network.size(); i++)
    {
      for(unsigned int j=0; j < network.at(i)->n_weights.size(); j++)
      {
        long double tmp = 0;
        tmp = ((0.01)*(network.at(i)->a)*(network.at(i)->next.at(j)->err));
        network.at(i)->n_weights.at(j) = (network.at(i)->n_weights.at(j) + tmp);
      }
      long double product = 0;
      product = ((0.01)*(network.at(i)->err));
      network.at(i)->dummy = (network.at(i)->dummy + product); 
    }
  }
}

int Ann::get_k()
{
  return m_k;
}

void Ann::e_dist()
{
  unsigned int input_layer_size = structure.at(0);
  unsigned int test_cols = test_input.size()/test_rows;
  for(unsigned int i=0; i < test_rows; i++)
  {
    for(unsigned int j=0; j < input_layer_size; j++)
    {
      network.at(i)->a = test_input.at((i*test_cols)+j);
    }
  }
}






//REMOVE after work, remove empty lines ^
                                     // |
