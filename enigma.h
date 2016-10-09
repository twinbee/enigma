#include <fstream>

#ifndef _enigma_h_
#define _enigma_h_

class enigma

{
  public:
   enigma(char * filename);
   //~enigma();
   
   char encode (char);

   int   getState(int);
   char* getRotor(int);
   int   getNumRotor();      
   char* getPlugboard();

   void setkey(char *);

   bool plug(char,char);
   bool unplug(char,char);   
    

  private:    
   char * rotors;
   int  * state;      
   char * board;
   int numRot;

   void rotate(int col);
   void rotate();
};

#endif
