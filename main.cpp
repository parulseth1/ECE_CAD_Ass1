/* 
 * File:   main.cpp
 * Author: parul
 *
 * Created on September 26, 2015, 5:40 PM
 */

#include <cstdlib>
#include <iostream>
#include "Parser.h"
#include "MazeRouter.h"
#define FILENAME "/home/parul/NetBeansProjects/MazeRouter/cct1.txt"
using namespace std;

wireBlock **wb1;

/*
 * 
 */
int main(int argc, char** argv) {
    
    //Parse the input files
    int gridSize, tracksPerChannel;
    std::vector<tracks>track;
    int status = doParse(FILENAME, &gridSize, &tracksPerChannel, &track);
    if (status < 1) exit(1);
    int logicBoxGridSize = gridSize + 1;
    int wireBlockGridSize = gridSize*2 + 1;
    
    wb1 = new wireBlock*[wireBlockGridSize];
    
    for (int i = 0; i < wireBlockGridSize; i++){
        wb1[i] = new wireBlock[wireBlockGridSize];
    }
    
    //initialization of wireBlocks
    for (int i = 0; i < wireBlockGridSize; i++){
        for (int j = 0; j < wireBlockGridSize; j++){
            if (i%2 == 0){ //if i is even, 
                if (j%2 == 1){ //then j is odd
                    wb1[i][j].wireTaken = new bool[tracksPerChannel];
                    for (int k = 0; k < tracksPerChannel; k++){
                        wb1[i][j].wireTaken[k] = false;
                    }
                }
            }
        }
    }
    
    
    //initialization of data complete
    
    
    return 0;
}

