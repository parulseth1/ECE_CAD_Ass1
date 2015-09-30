/* 
 * File:   Parser.h
 * Author: eski
 *
 * Created on September 25, 2015, 9:04 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include "MazeRouter.h"

#include <fstream>
#include <vector>



int doParse(char* FileName, int* grid, int* tracksPerChannel, std::vector<tracks> *track);

#endif	/* PARSER_H */

