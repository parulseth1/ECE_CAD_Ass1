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
#define FILENAME "/home/parul/Downloads/cct1.txt"
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
    
    cout <<"File reading complete"<<endl;
    
    InitDataStructure(gridSize, tracksPerChannel);
    
  	cout<<"initialization complete"<<endl;
    
    //initialization of data complete
    
    //now to route
    //for each connection, in the file do:
    for (int i = 0; i < numConn; i++) {
        //1. figure out which wireblock we are connected to
        
        point SourceWB = getCurrentWireBlock(track[i].From, track[i].pin_From);
        point TargetWB = getCurrentWireBlock(track[i].To, track[i].pin_To);
        
		//for every track in a wireblock, we shall route
        
        for (int j = 0; j < tracksPerChannel; j++){
		    vector<point> listOfPotentialWireBlocks;
		    listOfPotentialWireBlocks.push_back(SourceWB);
		    wb1[SourceWB.i][SourceWB.j].iteration[j] = 0;
                    //cout<<"doing the route thing"<<endl;
                    //cout<<tracksPerChannel<<endl;
		    int retval = doPropagate(listOfPotentialWireBlocks, TargetWB, tracksPerChannel, wb1, 1, j);
                    for(int a = 0;a< listOfPotentialWireBlocks.size();a++){
                    cout<<listOfPotentialWireBlocks[a].i<<listOfPotentialWireBlocks[a].j<<endl;}


                    if(retval == MATCH_FOUND){
                        vector<point>* possibleRoute;
                        cout<<"match found";
                        int Val = doTrace(listOfPotentialWireBlocks, TargetWB, wb1, possibleRoute);
                        
                    }

		    
		    
            if(retval == MATCH_FOUND){
                vector<point>* possibleRoute;
                int Val = doTrace(listOfPotentialWireBlocks, TargetWB, wb1, possibleRoute);
            }


	    }
        
        
        
        
    }
   
    //DrawNow(wireBlockGridSize, tracksPerChannel);
    
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
                wb1[i][j].iteration = new int[tracksPerChannel];
                for (int k = 0; k < tracksPerChannel; k++){
                    wb1[i][j].wireTaken[k] = false;
                    wb1[i][j].iteration[k] = -1;

                }
            }
            else if (i%2==1 && j%2 == 0){
                wb1[i][j].wireTaken = new bool[tracksPerChannel];
                wb1[i][j].iteration = new int [tracksPerChannel];
                wb1[i][j].cellMode = WIRE_BLOCK;
                for (int k = 0; k < tracksPerChannel; k++){
                    wb1[i][j].wireTaken[k] = false;
					 wb1[i][j].iteration[k] = -1; //these blocks are un-initialized
 
                }
            }
            else{
                wb1[i][j].cellMode = SWITCH_BOX;
                wb1[i][j].wireTaken = NULL;
            }
        }
    }
}
