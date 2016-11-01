/*
 * Author: Colby Bates
 * File: main.cpp
 */


#include <iostream>
#include <stdlib.h>
#include "matrix.h"
#include "robot.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using std::cout;


int main(int argc, char *argv[])
{
  Robot* robot;
  Matrix* trans;
  Matrix* joint;
  Matrix* mat;
  string line;
  stringstream ss;
  int rows=0;
  int total=0;
  int cols=0;
  int x=0;
  long double tmp=0;
  double sens_err=0;

  vector<string> obs;
  
  vector<long double> v; 
  vector<Tile*> tiles;

  vector<long double> transv;
  vector<long double> jointv;

  //Takes in command line arguments and parses them into variables.
  ifstream f(argv[1]);
  while(getline (f, line))
  {
    ss << line << ' ';
    rows++;
  }

  while(ss >> x)
  {
    v.push_back(x);
    total++;
  }
 
  sens_err = atof(argv[2]);

  for(int i=3; i<argc; i++)
  {
    obs.push_back(argv[i]);
  }

  cols = total/rows;

  //creates the initial matrix using the parsed input

  mat = new Matrix(v, rows, cols);


  //Makes a tile object for each value passed in
  for(int i=0; i < mat->rows(); i++)
  {
    for(int j=0; j < mat->cols(); j++)
    {
      Tile* tmp;
      tmp = new Tile(mat->value_at(i+1,j+1), mat->cols(), i+1, j+1);
      tiles.push_back(tmp);
    }
  }

  //Calculates the Transitivity Matrix 
  for(int i=0; i < tiles.size(); i++)
  {
    for(int j=0; j < tiles.size(); j++)
    {
      if(tiles[j]->checkPath(i) == 1)
      {
        transv.push_back(tiles[j]->pathChance());
      }
      else
      {
        transv.push_back(0);
      } 
    }
  }
  
  trans = new Matrix(transv, tiles.size(), tiles.size());
 
  //Checks for obstacles and creates a joint matrix
  for(int i=0; i < tiles.size(); i++)
  {
    if(tiles[i]->obstacle() == 0)
    { 
      tmp++;
    }
  }

  long double obsv = 1/tmp; 
  
  for(int i=0; i < tiles.size(); i++)
  {
    if(tiles[i]->obstacle() == 0)
    {
      jointv.push_back(obsv);
    }
    else
    {
      jointv.push_back(0);
    }
  }

  joint = new Matrix(jointv, tiles.size(), 1);

  //Creates a robot object that will take transitivity and joint matricies for calculations 
  robot = new Robot(trans, joint);

  //Call robot estimation to preform all the calculations left in order to get the 
  //estimation probabilities and states
  robot->estimation(tiles, obs);

  //Clean up loose memory allocated earlier.
  delete trans;
  delete joint;
  delete mat;
  delete robot; 
    
  for(int i=0; i < tiles.size(); i++)
  {
    delete tiles[i];
  } 
  return 0;
}
