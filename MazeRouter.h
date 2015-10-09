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
#define PATH_MADE 234

#define SWITCH_BOX 1
#define WIRE_BLOCK 2

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

#define ROUTING

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

struct wbpoint{
    int i;
    int j;
    int wirenumber;
};


extern wireBlock** wb1;

int DrawNow(int, int, vector<int>, vector<vector<point>>);
point getCurrentWireBlock(point LB, int pin);
int doPropagate(vector<point> , point, int , wireBlock**, int, int);
int doTrace(int, point, wireBlock**,vector<point>*);
point makePoint(int i, int j);
int doTrace_uni(wbpoint, wbpoint, wireBlock**, vector<wbpoint>*, int);
int doPropagate_uni(vector<wbpoint>, wbpoint, int, wireBlock** , int, int*, int);
wbpoint makeWBPoint(int, int, int);

#endif	/* MAZEROUTER_H */

