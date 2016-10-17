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
    cout << std::showpoint << std::fixed << setprecision(2) << m_matrix[i] << " ";
    count--;
    if(count == 0)
    {
      cout << "\n";
      count = m_col;
    }
  }   
}

long double Matrix::value_at(int row, int col)
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

Matrix* Matrix::multiply(Matrix* jointm)
{
  long double sum;
  vector<long double> r;

  for(int i=0; i < m_row; i++)
  {
    sum = 0;
    for(int j=0; j < m_col; j++)
    {
      sum+=((m_matrix[i*m_col+j])*(jointm->value_at(i+1,1)));
     // cout << "Sum: " << sum << "\n";
    }
    r.push_back(sum);
  }

  Matrix* R = new Matrix(r, m_row, 1);
  return R;
}

Tile::Tile(int value, int rowsize, int row, int col)
{
  //Tile location
  m_rowsize = rowsize;
  m_row = row;
  m_col = col;
  m_position = position(row,col);
  //Defaults to zero and sets up blocked paths based on input value
  m_north=0;
  m_south=0;
  m_west=0;
  m_east=0;
  m_tnorth = -1;
  m_tsouth = -1;
  m_twest = -1;
  m_teast = -1;
  m_value = value;
  m_obstacle = 0;
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
  //Checks all non-blocked paths and figures out what tile(s)
  //are accessible from itself
  if(m_north == 0)
  {
    m_tnorth = position(m_row-1, col);  
  }
  if(m_south == 0)
  {
    m_tsouth = position(m_row+1, col);
  }
  if(m_west == 0)
  {
    m_twest = position(m_row, col-1);
  }
  if(m_east == 0)
  {
    m_teast = position(m_row, col+1);
  }

  if(m_north == 1 && m_south == 1 && m_west == 1 && m_east == 1)
  {
    m_obstacle = 1;
  }
  
}

void Tile::print()
{
  cout << "Value: " << m_value << "\n";
  cout << "North: " << m_north << "\n";
  cout << "South: " << m_south << "\n";
  cout << "West: " << m_west << "\n";
  cout << "East: " << m_east << "\n";
  cout << "Location: R[" << m_row << "]C[" << m_col << "]\n";
  cout << "Position: " << m_position << "\n";
  cout << "Surrounding Accessible Tiles:" << "\n";
  cout << "-----------------------------" << "\n";
  if(m_tnorth != -1)
  {
    cout << "Tile to the north: " << m_tnorth << "\n";
  }
  if(m_tsouth != -1)
  {
    cout << "Tile to the south: " << m_tsouth << "\n";
  }
  if(m_twest != -1)
  {
    cout << "Tile to the west: " << m_twest << "\n";
  }
  if(m_teast != -1)
  {
    cout << "Tile to the east: " << m_teast << "\n";
  }
  cout << "-----------------------------" << "\n\n";
}
int Tile::position(int row, int col)
{
  return (((row-1)*m_rowsize)+(col-1));
}
long double Tile::pathChance()
{
  long double val = 4-(m_north+m_south+m_west+m_east);
  if(val <= 0)
  {
    return 0;
  }
  return 1/val;
}
int Tile::checkPath(int t)
{
  if(t == m_tnorth || t == m_tsouth || t == m_twest || t == m_teast)
  {
    return 1;
  }
  return 0;
}
int Tile::obstacle()
{
  return m_obstacle;
}
