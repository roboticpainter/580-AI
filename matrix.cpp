/*
 * Author: Colby Bates
 * File: matrix.cpp
 */

#include "matrix.h"

Matrix::Matrix(vector<long double> m, int row, int col)
{
  m_matrix = m;
  m_row = row;
  m_col = col; 
}

void Matrix::print()
{
  int count = m_col;
  for(int i=0; i < m_matrix.size(); i++)
  {
    cout << m_matrix[i] << " ";
    count--;
    if(count == 0)
    {
      cout << "\n";
      count = m_col;
    }
  }   
}

int Matrix::value_at(int row, int col)
{
  return m_matrix[((((row - 1)*m_col)+col)-1)];
}

int Matrix::size()
{
  return m_row * m_col;
}

int Matrix::rows()
{
  return m_row;
}

int Matrix::cols()
{
  return m_col;
}

Tile::Tile(int value)
{
  m_north=0;
  m_south=0;
  m_west=0;
  m_east=0;
  m_value = value;
  switch(value) {
   case 0:
     break;

   case 1:
     m_east = 1;
     break;
   
   case 2:
     m_west = 1;
     break;
    
   case 3:
     m_west = 1;
     m_east = 1;
     break;
   
   case 4:
     m_south = 1;
     break;

   case 5:
     m_south = 1;
     m_east = 1;
     break;
 
   case 6:
     m_south = 1;
     m_west = 1;
     break;

   case 7:
     m_south = 1;
     m_east = 1;
     m_west = 1;
     break;

   case 8:
     m_north = 1;
     break;

   case 9:
     m_north = 1;
     m_east = 1;
     break;

   case 10:
     m_north = 1;
     m_west = 1;
     break;
  
   case 11:
     m_north = 1;
     m_east = 1;
     m_west = 1;
     break;

   case 12:
     m_north = 1;
     m_south = 1;
     break;

   case 13:
     m_north = 1;
     m_south = 1;
     m_east = 1;
     break;

  case 14:
    m_north = 1;
    m_south = 1;
    m_west = 1;
    break;
  
  case 15:
    m_north = 1;
    m_south = 1;
    m_west = 1;
    m_east = 1;
    break;
  }
}

void Tile::print()
{
  cout << "Value: " << m_value << "\n";
  cout << "North: " << m_north << "\n";
  cout << "South: " << m_south << "\n";
  cout << "West: " << m_west << "\n";
  cout << "east: " << m_east << "\n";
}
