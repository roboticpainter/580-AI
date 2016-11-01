/*
 * Author: Colby Bates
 * File: robot.h
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "matrix.h"
#include <vector>
#include <iostream>

using namespace std;
using std::cout;

class Robot
{
  public:
    Robot(Matrix* trans, Matrix* joint);
    ~Robot();
    void observationM(vector<Tile*> tiles, vector<string> obs, int i);   
    void estimation(vector<Tile*> tiles, vector<string> obs);
    void print();
  private:
    //Transitivity Matrix
    Matrix* m_t;
    //Joint Matrix
    Matrix* m_j;
    //Joint prediction probability Matrix
    Matrix* m_jointp;
    //Observation matrix
    Matrix* m_observation;
    //Estimation matrix
    Matrix* m_estimation;
    // Answer matrix
    Matrix* m_answer;
};

#endif
