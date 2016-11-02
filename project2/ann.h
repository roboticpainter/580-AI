/*
 * Author: Colby Bates
 * File: ann.h
 */

#ifndef ANN_H
#define ANN_H

#include<vector>
#include<iostream>
#include<string>

using namespace std;
using std::cout;
using std::string;

class Node
{
  public:
    Node(int id);
    ~Node();
  private:
    int idnum;
    long double a;
    long double in;
    long double err;
    vector<Node*> next;
    vector<long double> weights;

};

class Ann
{
  public:
    Ann(int k);
    ~Ann();
    void add_value(int choice, long double value);
    void add_node(Node* n);
    void init_rows(int value);
    void print_members();
    int  size(int selection);
    long double value(int selection, int pos);
  private:
    vector<long double> train_input;  //1
    vector<long double> train_output; //2
    vector<long double> test_input;   //3
    vector<long double> test_output;  //4
    vector<long double> structure;    //5
    vector<long double> weights;      //6
    int io_rows;
    int m_k;
    vector<Node*> network;

};

#endif
