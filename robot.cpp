/*
 * Author: Colby Bates
 * File: robot.cpp
 */

#include "robot.h"

Robot::Robot(Matrix* trans, Matrix* joint, Matrix* obser)
{
  m_t = trans;
  m_j = joint;
  m_o = obser;
}
