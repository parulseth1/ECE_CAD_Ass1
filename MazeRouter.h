/* 
 * File:   MazeRouter.h
 * Author: parul
 *
 * Created on September 26, 2015, 5:48 PM
 */



#ifndef MAZEROUTER_H
#define	MAZEROUTER_H

#include <vector>
using namespace std;

#define DEAD_END -2
#define MATCH_FOUND 123
#define PATH_MADE 1

#define SWITCH_BOX 1
#define WIRE_BLOCK 2

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif
extern int wireBlockGridSize;

struct point {
    int i;
    int j;
};

struct tracks {
    point From;
    int pin_From;
    point To;
    int pin_To;
};


struct wireBlock {
    bool* wireTaken; //for as many tracks as defined by tracksPerChannel
    int cellMode; //switch box or wire block
	int* iteration;
};

extern wireBlock** wb1;

int DrawNow(int, int);
point getCurrentWireBlock(point LB, int pin);
int doPropagate(vector<point> , point, int , wireBlock**, int, int);
int doTrace(vector<point>, point, wireBlock**,vector<point>*);

#endif	/* MAZEROUTER_H */

