/***************************************************************************************
* Akhror Rakhmatov,1794798 arakhmat@ucsc.edu, PA5 
*  Shuffle.c
*  Uses functions in List.cpp to find and shuffle a list
****************************************************************************************/
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<vector>
#include"Dictionary.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf( stderr, "Incorrect number of command line arguments, please include a file in and file out only\n" );
        exit(1);
    }
    std::ifstream in;
    std::ofstream out;
    in.open(argv[1]);
    if( !in.is_open() ){
      std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
      std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      return(EXIT_FAILURE);
    }
    Dictionary A;
    std::string key;
    long i = 0;
    while(std::getline(in, key)) {
        ++i;
        A.setValue(key, i);
    }
    out << A << std::endl;
    out << A.pre_string() << std::endl;
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}