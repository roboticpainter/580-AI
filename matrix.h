/*
 * Author: Colby Bates
 * File: matrix.h
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;
using std::cout;

class Matrix
{
  public:
    Matrix(vector<long double> m, int row, int col);
    void print();
    int value_at(int row, int col);
    int size();
    int rows();
    int cols();

  private:
    vector<long double> m_matrix;
    int m_row;
    int m_col;
};

class Tile
{
  public:
    Tile(int value);
    void print();
  private: 
    int m_north;
    int m_south;
    int m_west;
    int m_east;
    int m_value;  
};

#endif
