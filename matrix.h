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
    int pathChance();
    int checkPath(int t);  
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
    Tile(int value, int rowsize, int row, int col);
    void print();
    int position(int row, int col);
  private: 
    //Tile position in the matrix
    int m_rowsize;
    int m_row;
    int m_col;
    int m_position;
    //If the NSWE path is blocked then these values equal 1
    int m_north;
    int m_south;
    int m_west;
    int m_east;
    //Tiles own value
    int m_value;
    //The tile value to the NSWE 
    int m_tnorth;
    int m_tsouth;
    int m_twest;
    int m_teast; 
};

#endif
