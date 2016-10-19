/*
 * Author: Colby Bates
 * File: main.cpp
 */


#include <iostream>
#include <stdlib.h>
#include "matrix.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using std::cout;


int main(int argc, char *argv[])
{
  Robot* robot;
  Matrix* answer;
  Matrix* estimation;
  Matrix* observation;
  Matrix* result;
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
  long double sum=0;

  vector<string> obs;
  
  vector<long double> v; 
  vector<Tile*> tiles;

  vector<long double> transv;
  vector<long double> jointv;
  vector<long double> observ; 


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

  //cout << "total: " << total << "\n";
  //cout << "cols: " << cols << "\n";
  //cout << "rows: " << rows  << "\n";

  mat = new Matrix(v, rows, cols);

  //mat->print();
  for(int i=0; i < mat->rows(); i++)
  {
    for(int j=0; j < mat->cols(); j++)
    {
      Tile* tmp;
      //cout << "Value going in: " << mat->value_at(i+1,j+1) << "\n";
      tmp = new Tile(mat->value_at(i+1,j+1), mat->cols(), i+1, j+1);
      tiles.push_back(tmp);
    }
  }

  /*for(int i=0; i < tiles.size(); i++)
  {
    cout << "~~~~~~~~~~~~~~~~~~~~\n";
    cout << "TILE[" << i << "]:\n";
    tiles[i]->print();
    if(i == tiles.size()-1)
    {
      cout << "~~~~~~~~~~~~~~~~~~~~\n";
    }
  }*/

  //cout << "Sensory Error: " << sens_err << "\n";
  /*for(int i=0; i<obs.size(); i++)
  {
    cout << "Observations: " << obs.at(i) << "\n";
  }*/

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
 
  //cout << "\nTansitivity Matrix: \n"; 

  //trans->print();


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

  //cout << "\nJoint Matrix: \n";

  //joint->print();

  //cout << "\nResult Matrix: \n";

  robot = new Robot() 
 
  result = trans->multiply(joint);

  //result->print();   

  joint = result; 

  //cout << "\nNew Joint Matrix: \n";

  //joint->print();

  for(int i=0; i < obs.size(); i++)
  {
    observ.clear();
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
    observation = new Matrix(observ, tiles.size(), 1);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
    //cout << "\nObservation Matrix: \n";

    //observation->print(); 

    estimation = observation->multiply(joint);

    //cout << "\nEstimation Matrix: \n";

    //estimation->print(); 

    sum = estimation->Sum(); 

    //cout << "\nSum: " << sum << "\n";

    answer = estimation->estimate(sum);

    //cout << "\nAnswers Matrix: \n";

    //answer->print();

    answer->output();

    result = trans->multiply2(estimation);

    joint = result;
 
    //cout << "\nNew Joint Matrix: \n";

    //joint->print(); 

    //ITERATION 1 DONE
  }
  return 0;
}
