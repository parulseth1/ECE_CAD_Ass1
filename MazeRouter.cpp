
#include "MazeRouter.h"
#include <iostream>

point makePoint(int i, int j) {
    point retVal;
    retVal.i = i;
    retVal.j = j;
    return retVal;
}

point getCurrentWireBlock(point Block, int pin) {
    point retVal;
    if (pin == 1) {
        retVal = makePoint((2 * Block.i) + 1 + 1, ((2 * Block.j) + 1));
    }
    if (pin == 2) {
        retVal = makePoint((2 * Block.i) + 1, ((2 * Block.j) + 1 + 1));
    }
    if (pin == 3) {
        retVal = makePoint((2 * Block.i) + 1 - 1, ((2 * Block.j) + 1));
    }
    if (pin == 4) {
        retVal = makePoint((2 * Block.i) + 1, ((2 * Block.j) + 1 - 1));
    }
    return retVal;
}



point getListOfPotentialWireBlocks(point, wireBlock**, int, vector<point>*, int iteration, point Target);

int doPropagate(vector<point> list, point Target, int tracksPerChannel, wireBlock** wb, int iteration, int wireIndex) {

    //this function is recursive!!!!

    int returnStatus = 0;
    vector<point> potentialList;
    //point retVal;

    for (int i = 0; i < list.size(); i++) {
        //for (int j = 0; j < tracksPerChannel; j++){
        //if (wb1[list[i].i][list[i].j].wireTaken[j] == false){
        //means this wire isnt taken, stuff can we be done with it.
        //now to get list of potential wire blocks that we can connect to

        point retVal = getListOfPotentialWireBlocks(list[i], wb1, wireIndex, &potentialList, iteration, Target);
        cout << "propagation #" << i << " done" << endl;
        if (retVal.i == -1 && retVal.j == -1) {
            //we have no match for target, lets move ahead with the new list
            // this is a NO-OP
            cout << "check 1" << endl;
            //retVal = doPropagate(potentialList, Target, tracksPerChannel, wb1, iteration + 1, wireIndex);

        } else if (retVal.i == -2, retVal.j == -2) {
            //this is a dead end, lets quit this wire
            cout << "check 2" << endl;



        } else {
            cout << "check 3" << endl;
            //we have a match for target
            return MATCH_FOUND;
        }
        //}
        //}
    }

    if (potentialList.size() == 0) {
        return DEAD_END;
    }

    //if no match was found, and its not a dead end, we shall now move ahead
    returnStatus = doPropagate(potentialList, Target, tracksPerChannel, wb1, iteration + 1, wireIndex);

    return returnStatus;
}

point getListOfPotentialWireBlocks(point WB, wireBlock** wb1, int track, vector<point>* returnList, int iteration, point Target) {
    point retPoint = makePoint(-1, -1);
    point considerBox;
    if (WB.i % 2 == 1 && WB.j % 2 == 0) { //for all 'horizontal' wire blocks
        //box1
            considerBox = makePoint(WB.i - 1, WB.j + 1); 
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    //check that the iteration of the block we are considering, is -1, i.e. its un-initialized
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }


            //box2
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 1, WB.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box3
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 2, WB.j); 
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }

            }
        }
        //box4
        //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j + 1); 
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }


            //box5
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j - 1); 
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track + 1] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box6
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 2, WB.j); 
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
        

        if (WB.i % 2 == 0 && WB.j % 2 == 1) { //for all 'vertical' wire blocks

            //box1
            considerBox = makePoint(WB.i - 1, WB.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box2
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 1, WB.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box3
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i, WB.j - 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
            //box4
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box5
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box6
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i, WB.j + 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
        }

        //just before returning, we msut check if any of the potential lists match the target if they do we return that instead of -1, -1

        for (int g = 0; g < returnList->size(); g++) {
            if ((*returnList)[g].i == Target.i && (*returnList)[g].j == Target.j) {
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


int doTrace(int track, point Target, wireBlock** wb1, vector<point>* possibleRoute) {

    //    int retVal = 0;

    possibleRoute->push_back(Target);
    point TargetBox = makePoint(Target.i, Target.j);
    point considerBox;
    // to get the boxes it can connect to and at the same time to get if they are the one with the
    // next iteration number.
    for (int a = wb1[Target.i][Target.j].iteration[track]; a > 0; a--) {
        cout << a << endl;
        //        top:
        if (TargetBox.i % 2 == 0 && TargetBox.j % 2 == 1) { //for all 'vertical' wire blocks
            //box1
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box2
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {

                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box3
            considerBox = makePoint(TargetBox.i, TargetBox.j - 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box4
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box5
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box6
            considerBox = makePoint(TargetBox.i, TargetBox.j + 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }

            }

        }


        if (TargetBox.i % 2 == 1 && TargetBox.j % 2 == 0) { //for all 'horizontal' wire blocks
            //box1
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box2
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j - 1);

            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box3
            considerBox = makePoint(TargetBox.i - 2, TargetBox.j);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box4
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box5
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box6
            considerBox = makePoint(TargetBox.i + 2, TargetBox.j);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
        }
    }

}

point getListOfPotentialWireBlocks_uni(point WB, wireBlock** wb1, int track, vector<point>* returnList, int iteration, point Target) {
    point retPoint = makePoint(-1, -1);
    point considerBox;
    if (WB.i % 2 == 1 && WB.j % 2 == 0) { //for all 'horizontal' wire blocks
        //box1
        if (track % 2 == 1) { //// for north side of the wire box which acts as south of the switch box above it
            considerBox = makePoint(WB.i - 1, WB.j + 1); // on east side of the switch box being driven
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track - 1] == false) {
                    //its available
                    //check that the iteration of the block we are considering, is -1, i.e. its un-initialized
                    if (wb1[considerBox.i][considerBox.j].iteration[track - 1] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track - 1] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }


            //box2
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 1, WB.j - 1); // on west side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box3
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 2, WB.j); /// on north side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }

            }
        }
        //box4
        //    considerBox - makePoint();
        if (track % 2 == 0) { /// for south side which acts as the north one for the switch box its connected to. 
            considerBox = makePoint(WB.i + 1, WB.j + 1); // on east side side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }


            //box5
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j - 1); // on west side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track + 1] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track + 1] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track + 1] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box6
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 2, WB.j); //on south side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
        }

        if (WB.i % 2 == 0 && WB.j % 2 == 1) { //for all 'vertical' wire blocks

            //box1
            if(track%2 == 0){ // for the wires on west side, but act as west for the switch box its connected to.
            considerBox = makePoint(WB.i - 1, WB.j + 1);// on the north side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track+1] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track+1] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track+1] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box2
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i + 1, WB.j + 1);// on the south side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box3
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i, WB.j + 2);// on the east side
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
            }
            //box4
            //    considerBox - makePoint();
            if(track%2 ==1){  ///for the wires on west side which act as east for the switch box its connected to.
            considerBox = makePoint(WB.i + 1, WB.j - 1); // for south
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track-1] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track-1] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track-1] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box5
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i - 1, WB.j - 1); // north
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }

            //box6
            //    considerBox - makePoint();
            considerBox = makePoint(WB.i, WB.j - 2); // for west
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                    //its available
                    if (wb1[considerBox.i][considerBox.j].iteration[track] == -1) {
                        wb1[considerBox.i][considerBox.j].iteration[track] = iteration;
                        std::cout << considerBox.i << considerBox.j << endl;
                        returnList->push_back(considerBox);
                    }
                }
            }
        }
        }

        //just before returning, we msut check if any of the potential lists match the target if they do we return that instead of -1, -1

        for (int g = 0; g < returnList->size(); g++) {
            if ((*returnList)[g].i == Target.i && (*returnList)[g].j == Target.j) {
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
}

int doTrace_uni(int track, point Target, wireBlock** wb1, vector<point>* possibleRoute) {

    //    int retVal = 0;

    possibleRoute->push_back(Target);
    point TargetBox = makePoint(Target.i, Target.j);
    point considerBox;
    // to get the boxes it can connect to and at the same time to get if they are the one with the
    // next iteration number.
    for (int a = wb1[Target.i][Target.j].iteration[track]; a > 0; a--) {
        cout << a << endl;
        //        top:
        if (TargetBox.i % 2 == 0 && TargetBox.j % 2 == 1) { //for all 'vertical' wire blocks
            //box1
            if(track%2 == 0){ // for the wires on west side, but act as west for the switch box its connected to.
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track+1] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track+1] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track+1] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box2
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {

                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box3
            considerBox = makePoint(TargetBox.i, TargetBox.j + 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            }
            //box4
            if(track%2 == 1){
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box5
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track-1] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box6
            considerBox = makePoint(TargetBox.i, TargetBox.j - 2);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }

            }

        }
        }


        if (TargetBox.i % 2 == 1 && TargetBox.j % 2 == 0) { //for all 'horizontal' wire blocks
            //box1
            if(track%2 ==1){
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track-1] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box2
            considerBox = makePoint(TargetBox.i - 1, TargetBox.j - 1);

            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }

            //box3
            considerBox = makePoint(TargetBox.i - 2, TargetBox.j);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            }
            //box4
            if(track%2 ==0){
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j - 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track-1] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track-1] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box5
            considerBox = makePoint(TargetBox.i + 1, TargetBox.j + 1);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
            //box6
            considerBox = makePoint(TargetBox.i + 2, TargetBox.j);
            if (considerBox.i >= 0 && considerBox.i < wireBlockGridSize && considerBox.j >= 0 && considerBox.j < wireBlockGridSize) {
                if (wb1[TargetBox.i][TargetBox.j].iteration[track] - 1 == wb1[considerBox.i][considerBox.j].iteration[track]) {
                    if (wb1[considerBox.i][considerBox.j].wireTaken[track] == false) {
                        possibleRoute->push_back(considerBox);
                        TargetBox = makePoint(considerBox.i, considerBox.j);
                        if (wb1[TargetBox.i][TargetBox.j].iteration[track] == 0) {
                            return PATH_MADE;
                        }
                    }
                    continue;
                }
            }
        }
    }

}
}


