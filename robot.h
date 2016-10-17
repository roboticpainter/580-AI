/*
 * Author: Colby Bates
 * File: robot.h
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;
using std::cout;

class Robot
{
  public:
  Robot();
  private:
  //Transitivity Matrix
  Matrix* m_t;
  //Joint Matrix
  Matrix* m_j;
  //Observation Matrix
  Matrix* m_o;
};

#endif
