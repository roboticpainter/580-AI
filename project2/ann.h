/*
 * Author: Colby Bates
 * File: ann.h
 */

#ifndef ANN_H
#define ANN_H

#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<math.h>

using namespace std;
using std::cout;
using std::string;
using std::map;

class Node
{
 
  friend class Ann; 

  public:
    Node(int id);
    ~Node();
    void set_in(long double value);
    void set_a(long double value);
    void set_err(long double value);
  private:
    int idnum;
    long double a;
    long double in;
    long double err;
    //map<Node*, long double> nextmap;
    //map<Node*, long double> frommap;
    vector<Node*> next;
    vector<long double> n_weights;
    vector<Node*> from;
    vector<long double> f_weights;

};

class Ann
{
  public:
    Ann(int k);
    ~Ann();
    void add_value(int choice, long double value);
    void set_y();
    void add_weights(int iter, long double value);
    void add_node(Node* n);
    void init_rows(int value);
    void print_members();
    int  size(int selection);
    long double value(int selection, int pos);
    void update_next_node(int node, int nex_node);
    void update_prev_nodes();
    void print_struc();
    void eval();
  private:
    vector<long double> train_input;  //1
    vector<long double> train_output; //2
    vector<long double> test_input;   //3
    vector<long double> test_output;  //4
    vector<long double> structure;    //5
    vector<long double> weights;      //6
    int io_rows;
    int m_k;
    vector<Node*> network;            //0
    vector< vector<long double> > y;

};

#endif
