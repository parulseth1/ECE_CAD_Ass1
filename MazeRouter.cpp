
#include "MazeRouter.h"

point makePoint(int i, int j){
    point retVal;
    retVal.i = i;
    retVal.j = j;
    return retVal;
}

point getCurrentWireBlock (point Block, int pin){
    point retVal;
    if (pin == 1){
        retVal = makePoint((2*Block.i)+1+1, ((2*Block.j)+1));
    }
     if (pin == 2){
        retVal = makePoint((2*Block.i)+1, ((2*Block.j)+1+1));
    } 
    if (pin == 3){
        retVal = makePoint((2*Block.i)+1-1, ((2*Block.j)+1));
    } 
    if (pin == 4){
        retVal = makePoint((2*Block.i)+1, ((2*Block.j)+1-1));
    }
    return retVal;    
  }

int getListOfPotentialWireBlocks(point, wireBlock**, int, vector<point>*);

int doPropagate(vector<point> list, point Target, int tracksPerChannel, wireBlock** wb){
    
    /*
     * for every element in the list, 
     * for every track per element
     * check for availability 
     */
    
    vector<point> potentialList;
    
    for (int i = 0; i < list.size(); i++){
        for (int j = 0; j < tracksPerChannel; j++){
            if (wb1[list[i].i][list[i].j].wireTaken[j] == false){
                //means this wire isnt taken, stuff can we be done with it.
                //now to get list of potential wire blocks that we can connect to
                int retVal = getListOfPotentialWireBlocks(list[i], wb1, j, &potentialList);
            }
        }
    }
    
    return 0;
}

int getListOfPotentialWireBlocks(point WB, wireBlock** wb1, int track, vector<point>* returnList){
    point considerBox;
    if(WB.i%2 == 1 && WB.j%2 == 0){
    //box1
    considerBox = makePoint(WB.i-1, WB.j+1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box2
//    considerBox - makePoint();
    considerBox = makePoint(WB.i-1, WB.j-1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box3
//    considerBox - makePoint();
    considerBox = makePoint(WB.i-2, WB.j);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    //box4
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+1, WB.j+1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }    

        //box5
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+1, WB.j-1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box6
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+2, WB.j);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
}
    if(WB.i%2 == 0 && WB.j%2 == 1){
        
    //box1
    considerBox = makePoint(WB.i-1, WB.j+1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box2
//    considerBox - makePoint();
    considerBox = makePoint(WB.i-1, WB.j-1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box3
//    considerBox - makePoint();
    considerBox = makePoint(WB.i, WB.j-2);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    //box4
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+1, WB.j+1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }    

        //box5
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+1, WB.j-1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    
    //box6
//    considerBox - makePoint();
    considerBox = makePoint(WB.i, WB.j+2);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            returnList->push_back(considerBox);
        }
    }
    }
    return 0;
}   


