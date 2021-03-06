/*****************************************************************************\

NEWTON                |
                      |
Multiphysics          | CLASS
coupling              | CLIENT
maste code            |
                      |

-------------------------------------------------------------------------------

In this class user can programm specific routines to read output and write
inputs for a particular client code.

Date: 24 June 2017

-------------------------------------------------------------------------------

Copyright (C) 2017 Federico A. Caccia

This file is part of Newton.

Newton is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Newton is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Newton.  If not, see <http://www.gnu.org/licenses/>.

\*****************************************************************************/

#include "Client.h"

using namespace::std;

/* Client::prepareNeutronicKP2crInput
 
In this function user can programm all necessary to write an input
for an specific client code.
Values in prepare(...)input are in the same order than the corresponding
mapper has saved them. If there are not mapper, values are in the same order 
that has been set in GUESSES in "newton.config".

input: code name, amount of values to send, vector with values to send 
and inputs file string (to write, and to read as model)
output: error: NEWTON_ERROR or NEWTON_SUCCESS

*/
int Client::prepareNeutronicKP2crInput(string codeName, int nValues, double* values, string input, string inputModel)
{ 
  // number of fermi code
  // Input file  
  inputFile.open(input.c_str());
  inputFile.precision(numeric_limits<double>::digits10 + 1);
  
  if (inputFile.is_open()){
    for(int i=0; i<nValues; i++){
      inputFile << values[i]<<endl;
    }
  }
  else{
    cout<<"Error writing input file for code: "<<codeName<<" - Client::prepareNeutronicKP2crInput"<<endl;
    error = NEWTON_ERROR;
  }
  inputFile.close();

  debug.log("values sended to "+codeName+":\n",0,0);

  for(int i=0; i<nValues; i++){
    debug.log(dou2str(values[i]));
  }
  debug.log("\n");

  return error;
}

/* Client::readNeutronicCr2kPOutput
 
In this function user can programm all necessary to read an output
for an specific client code.
Values in read(...)output has to be saved in the same order than the 
corresponding mapper uses them. If there are not mapper, values has to be saved
in the same order that has been set in CALCS in "newton.config".

input: code name, amount of values to read, vector with values to read 
and output file string
output: error: NEWTON_ERROR or NEWTON_SUCCESS

*/
int Client::readNeutronicKP2crOutput(string codeName, int nValues, double* values, string output)
{ 
  // Output file
  outputFile.open(output.c_str());
  if (outputFile.is_open()){
    for(int i=0; i<nValues; i++){
      outputFile >> values[i];
    }
  }
  else{
    cout<<"Error reading output file from code: "<<codeName<<" - Client::readNeutronicKP2crOutput"<<endl;
    error = NEWTON_ERROR;
  }
  outputFile.close();

  // If values received has been deltas
/*    for(int i=0; i<nValues; i++){
      values[i] += fermi[0].cr[i].pos;
    }*/
 
 return error; 
}
