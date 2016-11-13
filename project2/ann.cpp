/*
 * Author: Colby Bates
 * File: ann.cpp
 */

#include "ann.h"
//Constructor
Node::Node(int id)
{
  a = 0.0;
  in = 0.0;
  err = 0.0;
  dummy = 0.01;
  idnum = id;
}
//Destructor
Node::~Node()
{

}

//Setter for in value
void Node::set_in(long double value)
{
  in = value; 
}
//Set value for a in a node using the in value
void Node::set_a(long double value)
{
  long double tmp = 0.0;
  //cout << "In: " << value << "\n";
  tmp = 1.0/(1.0+exp(-value));
  a = tmp;
  //cout << "A value: " << a << "\n";
}
//Set error value for a node
void Node::set_err(long double value)
{
  err = value;
}
//Ann constuctor
Ann::Ann(int k) : m_k(k) 
{
    
}
//Ann destructor
Ann::~Ann()
{

}
//Function to take values from input and add them to vectors in the Ann
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
//Set up the Y vectors based on how many nodes are in the output layer
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
      ys.push_back(y0);
      ys.push_back(y1);
      ys.push_back(y2);
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
      ys.push_back(y0);
      ys.push_back(y1);
      ys.push_back(y2);
      ys.push_back(y3);
      break;
        break;
    default:
      y0.push_back(0);
      ys.push_back(y0);
      break; 
  }
}
//Function to add weights from input files
void Ann::add_weights(int iter, long double value)
{
  network.at(iter)->n_weights.push_back(value);
}
//Function to create empty nodes for the Ann
void Ann::add_node(Node* n)
{
  network.push_back(n);
}
//Function to pass row values for layer calculations into the Ann
void Ann::init_rows(int value)
{
  io_rows = value;
}
//Function to pass row values for layer calculations into the Ann
void Ann::init_test_rows(int value)
{
  test_rows = value;
}
//Function to print Ann vectors to make sure values were geting passed in correct.
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
//A single function to return the size of a chosen vector to main
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
//A function to return the value of a given vector to main
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
//A function to add a Node pointer to a given nodes next vector
void Ann::update_next_node(int node, int nex_node)
{
  network.at(node)->next.push_back(network.at(nex_node)); 
}
//A function to create all the from weights and pointers using the next weights
// and pointers
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
//A function to update the from weights after the next weights are updated
void Ann::update_from_weights()
{
  int iter=0;
  int iter2=0;
  for(unsigned int i=0; i < (network.size() - structure.back()); i++)
  {
    if(iter == structure.at(iter2))
    {
      iter=0;
      iter2++;
    }
    for(unsigned int j=0; j < network.at(i)->next.size(); j++)
    {
      Node* tmp = network.at(i)->next.at(j);
      long double tmpw = network.at(i)->n_weights.at(j);
      network.at(tmp->idnum)->f_weights.at(iter) = tmpw;
    }
    iter++;
  }
}
//A function to print a nodes structure variables
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
      cout << showpoint << fixed << setprecision(12) << network.at(i)->f_weights.at(j) << " ";
    }
    cout << "\n\n";
  }
}
//A function to print out the weights and format the output as the professor instructed for 
// testing
void Ann::print_weights()
{
  //cout << "train_input rows: " << io_rows << "\n";
  int amt = structure.at(1);
  for(int i=0; i < amt; i++)
  {
    cout << showpoint << fixed << setprecision(12) << network.at(0)->n_weights.at(i) << " ";
  }
  cout << "\n";
  for(unsigned int i=0; i < guesses.size(); i++)
  {
    cout << guesses.at(i) << "\n";
  }
  cout << accuracy << "\n";
}
//A function to preform all the algorithms neccessary to train weights
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
      //cout << "Initial A: " << network.at(i)->a << "\n";
    }
    //STEP 2/3:Calculate a values and in values for each node outside of the input layer
    for(unsigned int i=input_layer_size; i < network.size(); i++)
    {
      long double sum=0.0; 
      for(unsigned int j=0; j < network.at(i)->from.size(); j++)
      {
        sum += ((network.at(i)->from.at(j)->a) * (network.at(i)->f_weights.at(j)));
        //cout << "Sum[" << k << "]" << "= " << network.at(i)->from.at(j)->a  << " * " << network.at(i)->f_weights.at(j) << "\n"; 
      }
      //cout << "Sum: " << sum << "\n";
      //cout << "Dummy: " << network.at(i)->dummy << "\n";
      sum += network.at(i)->dummy;
      network.at(i)->set_in(sum);
      //cout << "Sum: " << sum << "\n";
      network.at(i)->set_a(sum);
    }
    //STEP 4:Calculate the error in the output layer.
    int iter=0;
    for(unsigned int i = output_layer_first_node; i < network.size(); i++)
    {
      long double product = 0.0;
      product = ((network.at(i)->a) * (1-(network.at(i)->a)) * ((ys.at(train_output.at(k)).at(iter))-(network.at(i)->a)));
      network.at(i)->set_err(product);
      iter++;
    }
    //STEP 5/6:Calculate error for each previous node using back propagation.
    for(unsigned int i = (output_layer_first_node - 1); i > 0; i--)
    {
      long double tmp = 0.0;
      long double product = 0.0;
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
        long double tmp = 0.0;
        tmp = ((0.01)*(network.at(i)->a)*(network.at(i)->next.at(j)->err));
        network.at(i)->n_weights.at(j) = (network.at(i)->n_weights.at(j) + tmp);
      }
      long double product = 0.0;
      product = ((0.01)*(network.at(i)->err));
      network.at(i)->dummy = (network.at(i)->dummy + product); 
    }
    update_from_weights();
    //print_struc();
  }
}
//Return the K value in the Ann for main
int Ann::get_k()
{
  return m_k;
}
//A function to calculated the Euclidean distance for each row of input using
//testing values.
void Ann::e_dist()
{
  unsigned int input_layer_size = structure.at(0);
  unsigned int test_cols = test_input.size()/test_rows;
  unsigned int output_layer_size = structure.back();
  unsigned int output_layer_first_node = (network.size() - output_layer_size);
  //Steps 1-3, identical to the eval function but using the trained weights
  for(int i=0; i < test_rows; i++)
  {
    for(unsigned int j=0; j < input_layer_size; j++)
    {
      network.at(j)->a = test_input.at((i*test_cols)+j);
    }
    for(unsigned int j=input_layer_size; j < network.size(); j++)
    {
      long double sum=0.0;
      for(unsigned int k=0; k < network.at(j)->from.size(); k++)
      {
        sum += ((network.at(j)->from.at(k)->a) * (network.at(j)->f_weights.at(k)));
      }
      sum += network.at(j)->dummy;
      network.at(j)->set_in(sum);
      network.at(j)->set_a(sum);
    }
    //Calculate ED using the A values from above, then make a guess based on the 
    //minimum ED
    long double ed = 0.0;
    long double tmp = 0.0;
    int guess = -1;
    for(unsigned int j=0; j < structure.back(); j++)
    {
      long double sum = 0.0;
      int iter = 0;
      for(unsigned int k=output_layer_first_node; k < network.size(); k++)
      {
        sum += pow((ys.at(j).at(iter) - network.at(k)->a), 2.0);
        iter++;
      }
      if(j==0)
      {
        ed = sqrt(sum);
        guess = j;
      }
      else
      {
        tmp = sqrt(sum);
        if(tmp < ed)
        {
          ed = tmp;
          guess = j;
        }
      }
    }
    guesses.push_back(guess);
  }
  long double count = 0.0; 
  for(unsigned int j=0; j < guesses.size(); j++)
  {
    if(guesses.at(j) == test_output.at(j))
    {
      count++;
    }
  }
  //cout << "guesses: " << static_cast<long double>(guesses.size()) << "\n";
  //cout << "count: " << count << "\n";
  accuracy = (count/(static_cast<long double>(guesses.size())));
}
