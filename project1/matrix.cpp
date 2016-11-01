/*
 * Author: Colby Bates
 * File: matrix.cpp
 */

#include "matrix.h"

/*
 * Matrix - Constructor.
 */

Matrix::Matrix(vector<long double> m, int row, int col)
{
  m_matrix = m;
  m_row = row;
  m_col = col; 
}

/*
 * ~Matrix - Destructor.
 */

Matrix::~Matrix()
{
}
/*
 * Print - Prints out the matrix in a nice format.
 */
void Matrix::print()
{
  int count = m_col;
  for(int i=0; i < m_matrix.size(); i++)
  {
    cout << std::showpoint << std::fixed << setprecision(12) << m_matrix[i] << " ";
    count--;
    if(count == 0)
    {
      cout << "\n";
      count = m_col;
    }
  }   
}

/*
 * Output - Prints the answers in a output that elena wants for grading.
 *          Ex. <estimation probability><space><state><space><state><space><endl>
 */
void Matrix::output()
{
  vector<int> states;
  long double max=0;
  for(int i=0; i < m_row; i++)
  {
    for(int j=0; j < m_col; j++)
    {
      if(m_matrix[i*m_col+j] > max)
      {
        max=m_matrix[i*m_col+j];
        states.clear();
        states.push_back(i*m_col+j);
      }
      else if(m_matrix[i*m_col+j] == max)
      {
        states.push_back(i*m_col+j);
      }
    }
  }
  cout << std::showpoint << std::fixed << setprecision(12) << max;
  for(int i=0; i < states.size(); i++)
  {
    cout << " " << states.at(i);
  }
  cout << " \n";
}

/*
 * value_at - Returns the value at a given index(row, column).
 */

long double Matrix::value_at(int row, int col)
{
  return m_matrix[((((row - 1)*m_col)+col)-1)];
}

/*
 * size - Returns the total size of the matrix.
 */

int Matrix::size()
{
  return m_row * m_col;
}

/*
 * rows - Returns the amount of rows in the matrix.
 */

int Matrix::rows()
{
  return m_row;
}

/*
 * col - Returns the amount of columns in the matrix.
 */

int Matrix::cols()
{
  return m_col;
}

/*
 * multiply - Multiplys the current matrix by the matrix being passed in
 *            and returns a pointer to a new matrix containing the results.
 */

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
      //cout << "Sum: " << sum << "\n";
    }
    r.push_back(sum);
  }

  return new Matrix(r, m_row, 1);
}

/*
 * Multiply2 - Multiplys the current matrix by the new matrix being passed in
 *             and returns a pointer to a new matrix containing the results.
 *             This version uses a diffrent algorithm and is only called when
 *             updating the joint prediction probability matrix after an iteration.
 */

Matrix* Matrix::multiply2(Matrix* jointm)
{
  long double sum;
  vector<long double> r;

  for(int i=0; i < m_row; i++)
  {
    sum = 0;
    for(int j=0; j < m_col; j++)
    {
      sum+=((m_matrix[i*m_col+j])*(jointm->value_at(j+1, 1)));
    }
    r.push_back(sum);
  }
  
  Matrix* R = new Matrix(r, m_row, 1);
  return R;
}

/*
 * Sum - Returns the sum of all values in a matrix.
 */

long double Matrix::Sum()
{
  long double sum=0;
  for(int i=0; i < m_row; i++)
  {
    for(int j=0; j < m_col; j++)
    {
      sum+=m_matrix[i*m_col+j];
    }
  }
  return sum;
}

/*
 * estimate - This function returns a matrix holding the estimation probabilities
 *            that are calculated by dividing the matrix by the sum passed in.
 */

Matrix* Matrix::estimate(long double sum)
{
  vector<long double> r;

  for(int i=0; i < m_row; i++)
  {
    for(int j=0; j < m_col; j++)
    {
      r.push_back(((m_matrix[i*m_col+j])/sum));
    }
  }
  Matrix* R = new Matrix(r, m_row, 1);
  return R;
}

/*
 * Tile - Constructor.
 */

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

/*
 * ~Tile - Destructor.
 */

Tile::~Tile()
{
}

/*
 * Print - Prints out the tile information in a nice format.
 */

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

/*
 * position - This funtion returns what tile is at a given row and column.
 */

int Tile::position(int row, int col)
{
  return (((row-1)*m_rowsize)+(col-1));
}

/*
 * pathChance - This function uses the amount of blocked paths to calculate
 *              the the likelyhood of a robot moving each direction from this
 *              tile.
 */

long double Tile::pathChance()
{
  long double val = 4-(m_north+m_south+m_west+m_east);
  if(val <= 0)
  {
    return 0;
  }
  return 1/val;
}

/*
 * checkPath - This function checks if the given input t is one of the 
 *             tiles surrounding this tile.
 */

int Tile::checkPath(int t)
{
  if(t == m_tnorth || t == m_tsouth || t == m_twest || t == m_teast)
  {
    return 1;
  }
  return 0;
}

/*
 * obstacle - returns if the tile is an obstacle.
 */

int Tile::obstacle()
{
  return m_obstacle;
}

/*
 * comparePath - This function uses the string observation and checks
 *                how many bits differ in the observed path and the tile.
 */

int Tile::comparePath(string obs)
{
  int sum = 0;
  if(obs.find('N') != string::npos)
  {
    if(m_north == 1)
    {
      sum++;
    } 
  }
  else
  {
    if(m_north == 0)
    {
      sum++;
    }
  }
  if(obs.find('S') != string::npos)
  {
    if(m_south == 1)
    {
      sum++;
    } 
  }
  else
  {
    if(m_south == 0)
    {
      sum++;
    }
  }
  if(obs.find('W') != string::npos)
  {
    if(m_west == 1)
    {
      sum++;
    } 
  }
  else
  {
    if(m_west == 0)
    {
      sum++;
    }
  }
  if(obs.find('E') != string::npos)
  {
    if(m_east == 1)
    {
      sum++;
    } 
  }
  else
  {
    if(m_east == 0)
    {
      sum++;
    }
  }
  return sum;
}
