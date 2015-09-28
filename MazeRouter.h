/* 
 * File:   MazeRouter.h
 * Author: parul
 *
 * Created on September 26, 2015, 5:48 PM
 */

#ifndef MAZEROUTER_H
#define	MAZEROUTER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

struct wireBlock {
    bool* wireTaken; //for as many tracks as defined by tracksPerChannel
};

int DrawNow();

#endif	/* MAZEROUTER_H */

