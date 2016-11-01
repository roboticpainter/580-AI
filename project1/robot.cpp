/*
 * Author: Colby Bates
 * File: robot.cpp
 */

#include "robot.h"

/*
 * Robot - Constructor. Stores a couple matrix variables.
 */

Robot::Robot(Matrix* trans, Matrix* joint)
{
  m_t = trans;
  m_j = joint;
  m_jointp = m_t->multiply(joint);
}

/*
 * ~Robot - Destructor.
 */

Robot::~Robot()
{
}

/*
 * observationM - This function calculates the observation matrix using
 *                the known tiles, amount of observations and what observation
 *                we are currently on using i. This will fill up an nxn matrix
 *                using the values calculated for each tile.
 */

void Robot::observationM(vector<Tile*> tiles, vector<string> obs, int i)
{
      vector<long double> observ;
      //observ.clear();
      //MAY BE WRONG VALUES, USING HOMEWORK VALUES UNTIL I ASK HOW TO CALC!
      for(int j=0; j < tiles.size();  j++)
      {
        if((tiles[j]->comparePath(obs.at(i)))==4)
        {
          observ.push_back(0.6561);
        }
        else if((tiles[j]->comparePath(obs.at(i)))==3)
        {
          observ.push_back(0.0729);
        }
        else if((tiles[j]->comparePath(obs.at(i)))==2)
        {
          observ.push_back(0.0081);
        }
        else if((tiles[j]->comparePath(obs.at(i)))==1)
        {
          observ.push_back(0.0009);
        }
        else if((tiles[j]->comparePath(obs.at(i)))==0)
        {
          observ.push_back(0.0001);
        }
        else
        {
          cout << "comparePath returned an invalid value.\n";
        }
      }
      m_observation = new Matrix(observ, tiles.size(), 1);
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

/*
 * estimation - This function uses a for loop through the amount of observations
 *              to calculate each set of answer and states using the matricies that
 *              main has been storing in robot all along. It will update the joint
 *              prediction probabilities matrix and observation matricies as it goes
 *              through iterations.
 */

void Robot::estimation(vector<Tile*> tiles, vector<string> obs)
{
  for(int i=0; i < obs.size(); i ++)
  {
    observationM(tiles, obs, i);
   
    //cout << "Observation: \n";    

    //m_observation->print();
    
    //cout << "\n";   

    m_estimation = m_observation->multiply(m_jointp);

    //cout << "Estimation: \n";
 
    //m_estimation->print();

    //cout << "\njoint Probability: \n";
  
    //m_jointp->print();

    //cout << "\n";

    long double sum=0;
    sum = m_estimation->Sum();

    //cout << "Sum: " << sum << "\n";   

    m_answer = m_estimation->estimate(sum);
    m_answer->output();
    m_jointp = m_t->multiply2(m_estimation);
  }
 
}

/*
 * print - Prints out all the transition and joint matrix in a nice format.
 */

void Robot::print()
{
  m_t->print();
  m_j->print();
}
