
#include "MazeRouter.h"
#include <iostream>

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

point getListOfPotentialWireBlocks(point, wireBlock**, int, vector<point>*, int iteration, point Target);

int doPropagate(vector<point> list, point Target, int tracksPerChannel, wireBlock** wb, int iteration, int wireIndex){
    
    //this function is recursive!!!!
    
    int retVal = 0;
    vector<point> potentialList;
    
    for (int i = 0; i < list.size(); i++){
        //for (int j = 0; j < tracksPerChannel; j++){
            //if (wb1[list[i].i][list[i].j].wireTaken[j] == false){
            //means this wire isnt taken, stuff can we be done with it.
            //now to get list of potential wire blocks that we can connect to
            point retVal = getListOfPotentialWireBlocks(list[i], wb1, wireIndex, &potentialList, iteration, Target);
            if (retVal.i == -1 && retVal.j == -1){
            	//we have no match for target, lets move ahead with the new list
            	// this is a NO-OP
            }
            else if (retVal.i == -2, retVal.j == -2){
            	//this is a dead end, lets quit this wire
            	return DEAD_END;
            }
            else{
            	//we have a match for target
            	return MATCH_FOUND;
            }
            //}
        //}
    }
    
    //if no match was found, and its not a dead end, we shall now move ahead
    retVal = doPropagate(potentialList, Target, tracksPerChannel, wb1, iteration + 1, wireIndex);
    
    return retVal;
}


point getListOfPotentialWireBlocks(point WB, wireBlock** wb1, int track, vector<point>* returnList, int iteration, point Target){
	point retPoint = makePoint(-1, -1);
    point considerBox;
    if(WB.i%2 == 1 && WB.j%2 == 0){ //for all 'horizontal' wire blocks
		//box1
		considerBox = makePoint(WB.i-1, WB.j+1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
				//check that the iteration of the block we are considering, is -1, i.e. its un-initialized
				if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		
		//box2
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i-1, WB.j-1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		
		//box3
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i-2, WB.j);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		//box4
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i+1, WB.j+1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		} 
	}   

        //box5
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+1, WB.j-1);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
				wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                std::cout<<considerBox.i<<considerBox.j;
            	returnList->push_back(considerBox);
            }
        }
    }
    
    //box6
//    considerBox - makePoint();
    considerBox = makePoint(WB.i+2, WB.j);
    if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
        if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
            //its available
            if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
				wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                std::cout<<considerBox.i<<considerBox.j;
            	returnList->push_back(considerBox);
            }
        }
    }

    if(WB.i%2 == 0 && WB.j%2 == 1){ //for all 'vertical' wire blocks
        
		//box1
		considerBox = makePoint(WB.i-1, WB.j+1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		
		//box2
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i-1, WB.j-1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		
		//box3
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i, WB.j-2);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		//box4
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i+1, WB.j+1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}    

		    //box5
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i+1, WB.j-1);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
		
		//box6
	//    considerBox - makePoint();
		considerBox = makePoint(WB.i, WB.j+2);
		if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize){
		    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false){
		        //its available
		        if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
					wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                                        std::cout<<considerBox.i<<considerBox.j;
		        	returnList->push_back(considerBox);
		        }
		    }
		}
	}
	
	//just before returning, we msut check if any of the potential lists match the target if they do we return that instead of -1, -1

	for (int g = 0; g < returnList->size(); g++){
		if ((*returnList)[g].i == Target.i && (*returnList)[g].j == Target.j){
			//one of the potential blocks is actually matching the target.
			retPoint = makePoint(Target.i, Target.j);
		}
	}
	
	if (returnList->size() == 0) {
		// no match was found, this is a dead end
		retPoint = makePoint(-2, -2);
	}
	
	
    return retPoint;
}   

int doTrace(vector<point> PotentialList, point Target, wireBlock** wb1, vector<point>* possibleRoute){
    point TargetBox = Target;
    point considerBox;
    // to get the boxes it can connect to and at the same time to get if they are the one with the
    // next iteration number.
    for(int a = PotentialList.size(); a>0; a++){
        top:
        if(TargetBox.i%2 == 0 && TargetBox.j%2 == 1){ //for all 'vertical' wire blocks
            //box1
            considerBox = makePoint(TargetBox.i-1, TargetBox.j+1);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute->push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }
        
            //box2
            considerBox = makePoint(TargetBox.i-1, TargetBox.j-1);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute-> push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }  
             //box3
            considerBox = makePoint(TargetBox.i, TargetBox.j-2);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute-> push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }  
            //box4
            considerBox = makePoint(TargetBox.i+1, TargetBox.j-1);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute-> push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }  
            //box5
            considerBox = makePoint(TargetBox.i+1, TargetBox.j+1);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute-> push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }   
            //box2
            considerBox = makePoint(TargetBox.i, TargetBox.j+2);
            if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                possibleRoute-> push_back(considerBox);
                TargetBox = considerBox;
                if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                    return PATH_MADE;
                }
                goto top;
            }  
        }
        
        
        if(TargetBox.i%2 == 0 && TargetBox.j%2 == 1){ //for all 'horizontal' wire blocks
                //box1
                considerBox = makePoint(TargetBox.i-1, TargetBox.j+1);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute-> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }

                //box2
                considerBox = makePoint(TargetBox.i-1, TargetBox.j-1);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute-> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }  
                 //box3
                considerBox = makePoint(TargetBox.i-2, TargetBox.j);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute-> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }  
                //box4
                considerBox = makePoint(TargetBox.i+1, TargetBox.j-1);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute-> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }   
                //box5
                considerBox = makePoint(TargetBox.i+1, TargetBox.j+1);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute-> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }   
                //box2
                considerBox = makePoint(TargetBox.i+2, TargetBox.j);
                if (wb1[TargetBox.i][TargetBox.j].iteration -1 == wb1[considerBox.i][considerBox.j].iteration){
                    possibleRoute -> push_back(considerBox);
                    TargetBox = considerBox;
                    if(wb1[TargetBox.i][TargetBox.j].iteration == 0){
                        return PATH_MADE;
                    }
                    goto top;
                }  
        }
    }   
    
    
}


