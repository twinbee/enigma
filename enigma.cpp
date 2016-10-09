#include "enigma.h"

#include <fstream>
#include <iostream>

/*
enigma::~enigma()
{
 delete[] board;
 delete[] rotors;
 delete[] state;
}
*/

enigma::enigma (char * filename)
//returns number of rotors. 0 if error
{
  bool debug   = 1 ;
  bool verbose = 0 ;

  board = new char [26];
  for (int i = 0; i < 26; i++)
  { board[i] = 'A' + i; }
  
  std::ifstream inf;
  
  inf.open(filename);

  inf >> numRot;
  
  char ch;
/*
  char * key = new char[numRot];
  for (int i = 0; i <= 4; i++) inf.get(ch); //"key:"
  for (int i = 0; i < numRot; i++)
  { inf >> key[i];  }
  if (debug && verbose) std::cerr << "Key: " << key << std::endl;
*/
    
  rotors = new char[26*numRot];
  
  //go ahead and set up the rotors
  //we do not deal with the initial key yet
  for (int i = 0; i < numRot; i++)
  {
   if (debug && verbose) std::cerr << "Rotor " << (i < 10 ? "0" : "")
      << (i < 100 ? "0" : "") << i << ":";
   for (int j = 0; j < 26; j++)   
   {
       inf >> rotors[i*26+j];
       if (debug && verbose) std::cerr << rotors[i*26+j];
       inf >> ch;
   }
   if (debug && verbose) std::cerr << std::endl;
  }
  
 if (debug) std::cerr << "Load complete. " << numRot << " rotors in place." << std::endl;  

 state = new int[numRot];

 if (debug && verbose)
 {
  std::cerr << std::endl;
  
  for (int i = 0; i < numRot; i++)
  {
   for (int j = 0; j < 26; j++)   
   {
    int CR = (i*26 + (j + state[i])%26);
    std::cerr << rotors[CR];
   }
   std::cerr << std::endl; 
  }
 }
  
 inf.close(); 
}

void enigma::setkey(char * key)
{
 //this determines the initial position of the rotors
 // only the letters needed are used, read left to right
 
 for (int i = 0; i < numRot; i++)
 {
   for (int j = 0; j < 26; j++)   
   {
    int CR = (i*26 + j);
    if (rotors[CR] == key[i])
    {
     state[i] = j;
     break;             
    }
   }
 }      
}

char enigma::encode(char inchar)
{
 if (inchar > 'Z' || inchar < 'A') return inchar;
  //don't encrypt or change any state for nonAlpha characters


 bool debug = 0;

 char toFind = board[inchar - 'A'];

 //substitution cyphers, one per disk 
 for (int i = 0; i < numRot-1; i++)
 {
  for (int j = 0; j < 26; j++)  
  {
   int CR = (i*26 + (j + state[i])%26);

   if (rotors[CR] == toFind)
   {
    int NR = ((i+1)*26 + (j + state[i+1])%26);
    toFind = rotors[NR];
    break;
   }
  }
 }


 //reflector is constant 'mirror' right now
 //the reflector may be any 26-permutation
 // possibly make it the last disk? 
 toFind = (char) ('Z' - (toFind - 'A'));


 //back through the works again, backwards this time
 // ( (more substitution cyphers, only this time in reverse) )
 for (int i = numRot - 1; i > 0; i--)
 {
  for (int j = 0; j < 26; j++)  
  {
   int CR = (i*26 + (j + state[i])%26);

   if (rotors[CR] == toFind)
   {
    int NR = ((i-1)*26 + (j + state[i-1])%26);
    toFind = rotors[NR];
    break;
   }
  }
 } 

 rotate();

 return board[toFind - 'A'];
}

void enigma::rotate()
{
 bool debug = 0;

 if (debug)
 {
  for (int j = 0; j < numRot; j++) std::cerr << (char) ('A' + state[j]) << " ";
  std::cerr << std::endl;
 }

 rotate(0);    
}

void enigma::rotate(int col)
{
 if (col >= numRot)
 {
  for (int i = numRot; i > 0; i--) state[i] = 0;
  return;
 }
 
 state[col]++;
 
 if (state[col] >= 26) //overflow
 {
  state[col] = 0;
  rotate(col + 1);          
 }

 else return;
}

int enigma::getState(int nth)
{
 if (nth > numRot-1) return-1;  //rotor doesn't exist
 else return state[nth];
}

char* enigma::getRotor(int nth)
{
 if (nth > numRot-1) return 0; 
 
 return &(rotors[nth*26]);     
}

int enigma::getNumRotor() {return numRot;}

bool enigma::plug(char a, char b)
{
 if (a > 'Z' || a < 'A' || b > 'Z' || b < 'A') { return 0;}
 
 else if (board[a - 'A'] == a && board[b - 'A'] == b)
 {
  board[a - 'A'] = b;
  board[b - 'A'] = a;  
  return 1;            
 } 

 else return 0;
}

bool enigma::unplug(char a, char b)
{
 if (a > 'Z' || a < 'A' || b > 'Z' || b < 'A') { return 0;}
 
 else if (board[a - 'A'] == b && board[b - 'A'] == a)
 {
  board[a - 'A'] = a;
  board[b - 'A'] = b;  
  return 1;            
 } 

 else return 0;
}

char * enigma::getPlugboard() { return board; }
