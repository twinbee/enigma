# enigma
A simulation of enigma machine rotors in OpenGL

![](https://github.com/twinbee/enigma/blob/master/manual.htm_files/21177c80-fd3b-11db-931b-ff870ff8d999.png?raw=true)

    Visual, Digital Enigma
    Matthew Bennett
    CSC 592 / Special Topics: Cryptography

This project presents an object oriented implementation of the enigma cryptographic device used by the Axis powers in World War Two. Additionally, a windows-only visual representation of the machine's state is provided. The enigma class may be used with or without the 3d graphics visual component.

# History

The enigma is a mechanical device consisting of a keyboard, a series of cypher disks, a special disk known as a reflector, a printer, and a plugboard. The disks each represent a full non-idempotent permutation of the alphabet. Each disks performs a permutation cypher, and the entire machine represents a multi-stage permutation cypher. The stream is entered one character at a time via the keypad. The initial state of the machine is determined by a secret key the same length as the number of disks.  Each disk begins rotated into place of that character. After a character is encoded, the disks advance in some deterministic fashion so that the permutation cypher of the machine changes. 

# Usage

To compile, be sure to include the header file. The class is designed to be used as a "black box". No information is provided in the interface about the internal workings of the machine. 


	#include "enigma.h"
	//place the header files in your include directory

	enigma MyEnigma("rotor_file_name.txt");

    MyEnigma.setkey("drowssap");
    
    char [10] cyphertext = MyEnigma.encode("Secret Message");
    
    The result can be checked by creating another machine with identical state and passing the ciphertext in. This is because the enigma cypher is symmetric. 
    
    enigma YourEnigma("rotor_file_name.txt");
    
    YourEnigma.setkey("drowssap");
    
    char [10] plaintext = YourEnigma.encode(cyphertext);
    

The plugboard is provided as part of the enigma reference implementation. This swaps any set of letter-pairs as the characters enter and exit the machine. Once a plug is completed, pairing either of them with another letter has no effect.
    
    MyEnigma.plug('A','E');
    MyEnigma.unplug('A','E');

# Rotor Files

A rotor file is a text file consisting of the following: Line 1 is an integer representing the number of disks (N), followed by N lines of  permutations of the Roman alphabet, as comma separated capital letters. A program is provided to produce such a file. It can be found in rotorgen.cpp or as a windows console executable rotors.exe.






# Visualization



An OpenGL / SDL graphical front end is provided, implemented in main.cpp. This compiles in windows under Dev-C++ 4.9.9.2, but may be easily ported to other environments such as linux. A windows executable is provided as-is (enigma.exe). The primary function of this is a proof of concept and could be used as an educational tool.
