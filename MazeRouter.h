/* 
 * File:   MazeRouter.h
 * Author: parul
 *
 * Created on September 26, 2015, 5:48 PM
 */

#ifndef MAZEROUTER_H
#define	MAZEROUTER_H

#define SWITCH_BOX 1
#define WIRE_BLOCK 2

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

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
};

int DrawNow();
int getCurrentWireBlock(point LB, int pin);

#endif	/* MAZEROUTER_H */

