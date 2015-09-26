/* 
 * File:   Parser.h
 * Author: eski
 *
 * Created on September 25, 2015, 9:04 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include <fstream>
#include <vector>


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

int doParse(char* FileName, int* grid, int* tracksPerChannel, std::vector<tracks> *track);

#endif	/* PARSER_H */

