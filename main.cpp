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

    if (argc < 3) {
        cout << "Usage : ./mazerouter -u <File name>" << endl;
        return 1;
    }
    int caseDirection;
    if (strcmp(argv[1], "-u") == 0) {
        //unidirectional case
        caseDirection = 1;
    } else if (strcmp(argv[1], "-b") == 0) {
        //bidirectional case
        caseDirection = 2;
    } else {
        cout << "wrong argument" << endl;
        return 1;
    }

    char* FILENAME = new char[strlen(argv[2]) + 1];
    strcpy(FILENAME, argv[2]);
    cout << FILENAME << endl;

    //Parse the input files
    int gridSize, tracksPerChannel;
    std::vector<tracks>track;
    std::vector<vector < point>> AllShortRoutes;
    std::vector<vector < wbpoint>> AllShortRoutes_uni;
    vector<int> AllShortWireNums;
    vector<int> AllShortWireNums_uni;
    int numConn = doParse(FILENAME, &gridSize, &tracksPerChannel, &track);
    if (numConn < 1) exit(1);
    cout << "tracks per channel" << tracksPerChannel << endl;
    cout << "File reading complete" << endl;

    InitDataStructure(gridSize, tracksPerChannel);

    cout << "initialization complete" << endl;
    //tracksPerChannel = 14;
    vector<point>* possibleRoute = new vector<point>[tracksPerChannel];
    vector<wbpoint>* possibleRoute_uni = new vector<wbpoint>[tracksPerChannel];
    //initialization of data complete
    int MinSize = INT_MAX;
    int Minsize_wireNumber = -1;
    vector<point> ShortestRoute;
    vector<wbpoint> ShortestRoute_uni;
    int seg_count = 0;
    vector<point> SWB;
    vector<point> TWB;
    vector<int> Spin;
    vector<int> Tpin;
    //now to route
    //for each connection, in the file do:
    for (int i = 0; i < numConn; i++) {
        //1. figure out which wireblock we are connected to

        point SourceWB = getCurrentWireBlock(track[i].From, track[i].pin_From);
        point TargetWB = getCurrentWireBlock(track[i].To, track[i].pin_To);

        wbpoint TargetWB_uni = makeWBPoint(TargetWB.i, TargetWB.j, -1);
        wbpoint SourceWB_uni = makeWBPoint(SourceWB.i, SourceWB.j, -1);


        cout << "Source block : " << SourceWB.i << "::" << SourceWB.j << endl;
        cout << "Target block : " << TargetWB.i << "::" << TargetWB.j << endl;

        //for every track in a wireblock, we shall route
        if (caseDirection == 2) {
            for (int j = 0; j < tracksPerChannel; j++) {
                vector<point> listOfPotentialWireBlocks;
                //vector<wbpoint> listOfPotWB;
                //SourceWB_uni.wirenumber = j;
                listOfPotentialWireBlocks.push_back(SourceWB);
                //listOfPotWB.push_back(SourceWB_uni);


                wb1[SourceWB.i][SourceWB.j].iteration[j] = 0;
                //wb1[SourceWB_uni.i][SourceWB_uni.j].iteration[j] = 0;
                cout << "doing the route thing" << endl;
                cout << j << endl;
                int retval = doPropagate(listOfPotentialWireBlocks, TargetWB, tracksPerChannel, wb1, 1, j);
                //int retval = doPropagate_uni(listOfPotWB, TargetWB_uni, tracksPerChannel, wb1, 1, j);
                if (retval == DEAD_END) {
                    cout << "DEAD_END";
                    continue;
                }


                cout << "going to check match found" << endl;
                if (retval == MATCH_FOUND) {

                    cout << "match found" << endl;
                    //TargetWB_uni.wirenumber = 
                    int Val = doTrace(j, TargetWB, wb1, &possibleRoute[j]);
                    //int Val = doTrace_uni(TargetWB_uni, wb1, &possibleRoute_uni[j]);
                    if (Val != PATH_MADE) {
                        cout << "doTrace didnt work" << endl;
                        continue;
                    }
                    cout << "Wire:" << j << endl;
                    if (MinSize > possibleRoute[j].size()) {
                        MinSize = possibleRoute[j].size();
                        Minsize_wireNumber = j;
                        ShortestRoute = possibleRoute[j];
                    }
                    cout << "pR size:" << possibleRoute[j].size() << endl;
                    for (int x = 0; x < possibleRoute[j].size(); x++) {
                        cout << possibleRoute[j][x].i << "::" << possibleRoute[j][x].j << endl;
                    }

                }


            }
            //       
            cout << "shortestRoute on wire " << Minsize_wireNumber << ":" << endl;
            cout << MinSize << endl;
            if (Minsize_wireNumber < 0) {
                continue;
            }
            for (int a = 0; a < MinSize; a++) {
                wb1[ShortestRoute[a].i][ShortestRoute[a].j].wireTaken[Minsize_wireNumber] = true;
                cout << ShortestRoute[a].i << "::" << ShortestRoute[a].j << endl;
                seg_count = seg_count + 1;
            }

            //refresh the entire wire-grid
            cout << "refreshing" << endl;
            for (int i1 = 0; i1 < wireBlockGridSize; i1++) {
                for (int j1 = 0; j1 < wireBlockGridSize; j1++) {
                    for (int x1 = 0; x1 < tracksPerChannel; x1++) {
                        if (i1 % 2 != j1 % 2) {
                            if (wb1[i1][j1].wireTaken[x1] == false) {
                                wb1[i1][j1].iteration[x1] = -1;
                            }
                        }

                    }

                }
            }
            cout << "refresh done" << endl;
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
            for (int v1 = 0; v1 < tracksPerChannel; v1++) {
                possibleRoute[v1].clear();
            }



        }

    
    
    if(caseDirection == 1){
        for (int j = 0; j < tracksPerChannel; j++) { 
            cout<<"channelNumber"<<j<<endl;
            //for(int n = 0; n<2; n++){
            SourceWB_uni.wirenumber = j;
            vector<wbpoint> listOfPotWB;
            wb1[SourceWB_uni.i][SourceWB_uni.j].iteration[j] = 0;
            listOfPotWB.push_back(SourceWB_uni);
            cout << "doing the route thing" << endl;
            cout << j << endl;
            int* wireIndex;
            int retval = doPropagate_uni(listOfPotWB, TargetWB_uni, tracksPerChannel, wb1, 1, wireIndex,j);
            if (retval == DEAD_END) {
                cout << "DEAD_END";
                continue;
            }
            cout << "going to check match found" << endl;
            if (retval == MATCH_FOUND) {
                cout << "match found" << endl;
                int Val = doTrace_uni(SourceWB_uni, TargetWB_uni, wb1, &possibleRoute_uni[j],*wireIndex);  
                
                if (Val != PATH_MADE) {
                    cout << "doTrace didnt work" << endl;
                    continue;
                }
                   

                if (MinSize >  possibleRoute_uni[j].size()) {
                    MinSize = possibleRoute_uni[j].size();
                    Minsize_wireNumber = j;
                    ShortestRoute_uni = possibleRoute_uni[j]; 
                    
                }
                
                cout << "pR size:" << possibleRoute_uni[j].size() << endl;
                for (int x = 0; x < possibleRoute_uni[j].size(); x++) {
                    cout << possibleRoute_uni[j][x].i << "::" << possibleRoute_uni[j][x].j << endl;
                }


                }
for (int i1 = 0; i1 < wireBlockGridSize; i1++) {
                for (int j1 = 0; j1 < wireBlockGridSize; j1++) {
                    for (int x1 = 0; x1 < tracksPerChannel; x1++) {
                        if (i1 % 2 != j1 % 2) {
                            if (wb1[i1][j1].wireTaken[x1] == false) {
                                wb1[i1][j1].iteration[x1] = -1;
                            }
                        }

                    }

                }
                }
          
        }
            
            //       
            cout << "shortestRoute on wire " << Minsize_wireNumber << ":" << endl;
            cout << MinSize << endl;
            if (Minsize_wireNumber < 0) {
                continue;
            }
        
            for (int a = 0; a < MinSize; a++) {
                wb1[ShortestRoute_uni[a].i][ShortestRoute_uni[a].j].wireTaken[Minsize_wireNumber] = true;
                cout << ShortestRoute_uni[a].i << "::" << ShortestRoute_uni[a].j << endl;
                seg_count = seg_count + 1;
                point A= makePoint(ShortestRoute_uni[a].i ,ShortestRoute_uni[a].j);
                ShortestRoute.push_back(A);
            }
        

            
            
           
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
            ShortestRoute_uni.clear();
            MinSize = INT_MAX;
            for (int v1 = 0; v1 < tracksPerChannel; v1++) {
                possibleRoute_uni[v1].clear();
            }



        }
    }
    

    
    cout << "segments used =" << seg_count;
        //cout << "Num Connection = " << numConn;
	DrawNow(wireBlockGridSize, tracksPerChannel, AllShortWireNums, AllShortRoutes, Spin, Tpin, 0, SWB, TWB);

        return 0;
    }


int InitDataStructure(int gridSize, int tracksPerChannel) {

    logicBoxGridSize = gridSize + 1;
    wireBlockGridSize = gridSize * 2 + 1;

    wb1 = new wireBlock*[wireBlockGridSize];

    for (int i = 0; i < wireBlockGridSize; i++) {
        wb1[i] = new wireBlock[wireBlockGridSize];
    }

    //initialization of wireBlocks
    for (int i = 0; i < wireBlockGridSize; i++) {
        for (int j = 0; j < wireBlockGridSize; j++) {
            if (i % 2 == 0 && j % 2 == 1) { //if i is even,and j is odd 

                wb1[i][j].wireTaken = new bool[tracksPerChannel];
                wb1[i][j].cellMode = WIRE_BLOCK;
                wb1[i][j].iteration = new int[tracksPerChannel];
                for (int k = 0; k < tracksPerChannel; k++) {
                    wb1[i][j].wireTaken[k] = false;
                    wb1[i][j].iteration[k] = -1;

                }
            } else if (i % 2 == 1 && j % 2 == 0) {
                wb1[i][j].wireTaken = new bool[tracksPerChannel];
                wb1[i][j].iteration = new int [tracksPerChannel];
                wb1[i][j].cellMode = WIRE_BLOCK;
                for (int k = 0; k < tracksPerChannel; k++) {
                    wb1[i][j].wireTaken[k] = false;
                    wb1[i][j].iteration[k] = -1; //these blocks are un-initialized

                }
            } else {
                wb1[i][j].cellMode = SWITCH_BOX;
                wb1[i][j].wireTaken = NULL;
            }
        }
    }
}

int getShortestRoute(vector<point>* possibleRoutes, int tracksPerChannel, vector<point>* shortestRoute) {
    int shortestPin = -1;
    int shortestRouteLength = INT_MAX;
    for (int i = 0; i < tracksPerChannel; i++) {
        if (possibleRoutes[i].size() < shortestRouteLength) {
            shortestPin = i;
            shortestRouteLength = possibleRoutes[i].size();
            *shortestRoute = possibleRoutes[i];
        }
    }

    return shortestPin;
}
