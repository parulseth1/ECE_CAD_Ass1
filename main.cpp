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
#include "graphics.h"
#define FILENAME "/home/parul/NetBeansProjects/MazeRouter/cct1.txt"
using namespace std;

int logicBoxGridSize;
int wireBlockGridSize;

wireBlock **wb1;

/*
 * 
 */

int InitDataStructure(int gridSize, int tracksPerChannel);

int main(int argc, char** argv) {
    
    //Parse the input files
    int gridSize, tracksPerChannel;
    std::vector<tracks>track;
    int numConn = doParse(FILENAME, &gridSize, &tracksPerChannel, &track);
    if (numConn < 1) exit(1);
    
    InitDataStructure(gridSize, tracksPerChannel);
    
    //initialization of data complete
    
    //now to route
    //for each connection, in the file do:
    for (int i = 0; i < numConn; i++) {
        //1. figure out which wireblock we are connected to
        
        point SourceWB = getCurrentWireBlock(track[i].From, track[i].pin_From);
        point TargetWB = getCurrentWireBlock(track[i].To, track[i].pin_To);
        
//        //for every track in a wire block, do:
//        for (int j = 0; j < tracksPerChannel; j++){
//            if (wb1[SourceWB.i][SourceWB.j].wireTaken[j] == false){
//                int ret = propagate();
//            }
//        }
        
        vector<point> listOfPotentialWireBlocks;
        listOfPotentialWireBlocks.push_back(SourceWB);
        
        int retval = doPropagate(listOfPotentialWireBlocks, TargetWB, tracksPerChannel, wb1);
        
        
        
        
    }
   
    DrawNow();
    
    return 0;
}

int InitDataStructure(int gridSize, int tracksPerChannel)
{
    
    logicBoxGridSize = gridSize + 1;
    wireBlockGridSize = gridSize*2 + 1;
    
    wb1 = new wireBlock*[wireBlockGridSize];
    
    for (int i = 0; i < wireBlockGridSize; i++){
        wb1[i] = new wireBlock[wireBlockGridSize];
    }
    
    //initialization of wireBlocks
    for (int i = 0; i < wireBlockGridSize; i++){
        for (int j = 0; j < wireBlockGridSize; j++){
            if (i%2 == 0 && j%2 == 1){ //if i is even,and j is odd 

                wb1[i][j].wireTaken = new bool[tracksPerChannel];
                wb1[i][j].cellMode =WIRE_BLOCK;
                for (int k = 0; k < tracksPerChannel; k++){
                    wb1[i][j].wireTaken[k] = false;

                }
            }
            else if (i%2==1 && j%2 == 0){
                wb1[i][j].wireTaken = new bool[tracksPerChannel];
                wb1[i][j].cellMode =WIRE_BLOCK;
                for (int k = 0; k < tracksPerChannel; k++){
                    wb1[i][j].wireTaken[k] = false;

                }
            }
            else{
                wb1[i][j].cellMode = SWITCH_BOX;
                wb1[i][j].wireTaken = NULL;
            }
        }
    }
}