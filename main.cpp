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
#include <string.h>

#include <limits.h>
//#define FILENAME "/home/aliakbareski-2/ECE_CAD_A1/cct1.txt"

using namespace std;

int logicBoxGridSize;
int wireBlockGridSize;

wireBlock **wb1;

/*
 * 
 */

int InitDataStructure(int gridSize, int tracksPerChannel);
int getShortestRoute(vector<point>*, int, vector<point>*);

int main(int argc, char** argv) {
	
	if (argc < 3){
		cout<<"Usage : ./mazerouter -u <File name>"<<endl;
		return 1;
	}
	int caseDirection;
	if (strcmp(argv[1], "-u") == 0){
		//unidirectional case
		caseDirection = 1;
	}
	else if (strcmp(argv[1], "-b") == 0){
		//bidirectional case
		caseDirection = 2;
	}
	else {
		cout<<"wrong argument"<<endl;
		return 1;
	}
	
	char* FILENAME = new char[strlen(argv[2]) + 1];
	strcpy(FILENAME, argv[2]);
	cout<<FILENAME<<endl;
    
    //Parse the input files
    int gridSize, tracksPerChannel;
    std::vector<tracks>track;
    std::vector<vector<point>>  AllShortRoutes;
    vector<int> AllShortWireNums;
    int numConn = doParse(FILENAME, &gridSize, &tracksPerChannel, &track);
    if (numConn < 1) exit(1);
    
    cout <<"File reading complete"<<endl;
    
    InitDataStructure(gridSize, tracksPerChannel);
    
    cout<<"initialization complete"<<endl;
    //tracksPerChannel = 2;
    vector<point>* possibleRoute = new vector<point>[tracksPerChannel];
    
    //initialization of data complete
    int MinSize = INT_MAX;
    int Minsize_wireNumber = -1;
    vector<point> ShortestRoute;
    int seg_count = 0;
    vector<point> SWB;
    vector<point> TWB;
    vector<int> Spin;
    vector<int> Tpin;
    //now to route
    //for each connection, in the file do:
    for (int i = 0; i < 3; i++) {
        //1. figure out which wireblock we are connected to
        
        point SourceWB = getCurrentWireBlock(track[i].From, track[i].pin_From);
        point TargetWB = getCurrentWireBlock(track[i].To, track[i].pin_To);
        
        
        
        cout<<"Source block : "<<SourceWB.i<<"::"<<SourceWB.j<<endl;
        cout<<"Target block : "<<TargetWB.i<<"::"<<TargetWB.j<<endl;
        
		//for every track in a wireblock, we shall route
        
        for (int j = 0; j < tracksPerChannel; j++){
            vector<point> listOfPotentialWireBlocks;
            listOfPotentialWireBlocks.push_back(SourceWB);
            wb1[SourceWB.i][SourceWB.j].iteration[j] = 0;
            cout<<"doing the route thing"<<endl;
            cout<<j<<endl;
            int retval = doPropagate(listOfPotentialWireBlocks, TargetWB, tracksPerChannel, wb1, 1, j);
            if (retval == DEAD_END){cout<<"DEAD_END";continue;}
            /*for(int a = 0;a< listOfPotentialWireBlocks.size();a++){
            	cout<<listOfPotentialWireBlocks[a].i<<listOfPotentialWireBlocks[a].j<<endl;
            }*/
            
            cout<<"going to check match found";
            if(retval == MATCH_FOUND){
                
                cout<<"match found"<<endl;
                int Val = doTrace(j, TargetWB, wb1, &possibleRoute[j]);
                if (Val != PATH_MADE){cout<<"doTrace didnt work"<<endl;continue;}
                cout<<"Wire:"<<j<<endl;
                if(MinSize > possibleRoute[j].size()){
                    MinSize = possibleRoute[j].size();
                    Minsize_wireNumber = j;
                    ShortestRoute = possibleRoute[j];
                }
                cout<<"pR size:"<<possibleRoute[j].size()<<endl;
                for (int x = 0; x < possibleRoute[j].size(); x++){
                    cout << possibleRoute[j][x].i << "::"<<possibleRoute[j][x].j<<endl;
                }
                

            }


        } 
//       
       cout<<"shortestRoute on wire "<<Minsize_wireNumber<<":"<<endl; 
       cout<<MinSize<<endl;
       if (Minsize_wireNumber < 0){continue;}
       for(int a =0;a<MinSize; a++){
           wb1[ShortestRoute[a].i][ShortestRoute[a].j].wireTaken[Minsize_wireNumber] = true;
           cout<<ShortestRoute[a].i<<"::"<<ShortestRoute[a].j<<endl;
           seg_count = seg_count+1;
       }
       
       //refresh the entire wire-grid
       cout<<"refreshing"<<endl;
      for(int i1 = 0; i1< wireBlockGridSize; i1++){
        for(int j1 = 0; j1<wireBlockGridSize; j1++){
            for(int x1= 0;x1<tracksPerChannel;x1++ ){
                if (i1%2 != j1%2){
                    if(wb1[i1][j1].wireTaken[x1] == false){
                        wb1[i1][j1].iteration[x1] = -1;
                    }
                }
                    
            }
            
        }
    }  
    cout<<"refresh done"<<endl;
    #ifdef ROUTING
    //save this route somewhere for future connections to learn from :P
       AllShortRoutes.push_back(ShortestRoute);
       AllShortWireNums.push_back(Minsize_wireNumber);
       SWB.push_back(SourceWB);
		TWB.push_back(TargetWB);
		Spin.push_back(track[i].pin_From);
		Tpin.push_back(track[i].pin_To);
        
    //DrawNow(wireBlockGridSize, tracksPerChannel, Minsize_wireNumber, ShortestRoute);    
    #endif

    //clear up data
    ShortestRoute.clear();
    MinSize = INT_MAX;
    for (int v1 = 0; v1 < tracksPerChannel; v1++){
        possibleRoute[v1].clear();
    }
    
    
    
    }     
    cout<<"segments used ="<<seg_count;
    DrawNow(wireBlockGridSize, tracksPerChannel, AllShortWireNums, AllShortRoutes, Spin, Tpin, 0, SWB, TWB);
    
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


int getShortestRoute(vector<point>* possibleRoutes, int tracksPerChannel, vector<point>* shortestRoute){
	int shortestPin = -1;
	int shortestRouteLength = INT_MAX;
	for (int i = 0; i < tracksPerChannel; i++){
		if (possibleRoutes[i].size() < shortestRouteLength){
			shortestPin = i;
			shortestRouteLength = possibleRoutes[i].size();
			*shortestRoute = possibleRoutes[i];
		}
	}
	
	return shortestPin;	
}
