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

class Ann
{
  public:
    Ann();
    ~Ann();
    void add_value(int choice, long double value);
    void init_rows(int value);
    void print_members();
  private:
    vector<long double> train_input;
    vector<long double> train_output;
    vector<long double> test_input;
    vector<long double> test_output;
    vector<long double> structure;
    vector<long double> weights;
    int io_rows;
    

};

class Node
{
  public:
    Node();
    ~Node();
  private:
    long double a;
    long double in;
    long double err;

};

#endif
