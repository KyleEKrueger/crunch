# crunch.c
 
 Program Name:              crunch
  
  Author:                   Kyle Krueger
  
  Command Line Arguments:   
                            
                            -d <degree>   Number of words from input stream to combine in each crunched output
                            
                            -m <size>     The minimum length of each word used
                            
                            -n <count>    Number of output strings to produce
                            
                            -s            Indicates to insert a space between the output words
  
  Program Input:            stdin
  
  Program Output:           stdout
  
  Allowed Imports:          stdio.h, stdlib.h, time.h
  
Crunch is a program written in C that randomly combines words from the input stream and sends them to the output stream. Some of the challenges of this program were accepting the proper inputs for flags, managing the list of unique words, and adhearing to the specifications given by the requirements:
  1. The words the program selects must meet minimum length criteria, and users may also change this value at program execution to meet their needs.
  2. By default, the program squeezes the words together and omits any spacing between them, but users may override this behavior with a command line argument as well, and the program will produce output with the user specified parameter.
  3. The command line arguments may appear in any order
  4. When unable to construct strings meeting the minimum length from the input stream, the program shall alert the user to an error and suggest corrective action.
  5. There shall be no duplicate words in any single output combination, but the same word may appear twice in the total output when producing more than one string.
  
A make file was included, allowing "make" and "make clean" to be used in order to compile or remove the object file. 
  
