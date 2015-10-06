
#include "graphics.h"
#include "MazeRouter.h"
#include <iostream>
#include <stdlib.h>
#include <cfloat>

using namespace std;

int gridSize = 0;
int tracksPerChannel;
int pin;
vector<point> route;
void drawscreen();

point getLBCoords(int i, int j){
	return makePoint((i-1)/2, (j-1)/2);
}

int DrawNow(int _gridSize, int _tracksPerChannel, int _pin, vector<point> _route)
{
    cout<<"Hello Graphics\n";
    
    gridSize = _gridSize;
    tracksPerChannel = _tracksPerChannel;
    pin = _pin;
    route = _route; //this might not work if no copy contructor;
    
    init_graphics("MazeRouter", WHITE);
    
    set_visible_world(0, 0, 1100, 1100);
    
    event_loop(NULL, NULL, NULL, drawscreen);  
    /*drawscreen();
    flushinput();
    cin.get();*/
    cout<<"END"<<endl;
    
    return 0;
    
    
    
}

void drawscreen(){
	set_draw_mode (DRAW_NORMAL);  // Should set this if your program does any XOR drawing in callbacks.
	clearscreen();  /* Should precede drawing for all drawscreens */
	
	float BlockDim = 1000/(gridSize + 2);
	float wireOffset = BlockDim/(tracksPerChannel + 1);
	float rectOffset = BlockDim;
	float textOffset = BlockDim/2;
	
	/*setcolor (184, 184, 184); //grey
	drawrect(0, 0, 10, 10);
	drawtext(20, 10);
	setcolor (135, 206, 250);//lightblue
	drawrect();
	drawtext();*/
	
	//setcolor(0, 0, 0);
	//drawrect(rectOffset-1, rectOffset-2, rectOffset+BlockDim*(gridSize)+1, rectOffset+BlockDim*(gridSize));
	
	for (int i = 0; i < gridSize; i++){
		for (int j = 0; j  <gridSize; j++){
			if (i%2 == 0 && j%2 == 0){
				//set color to grey
				setcolor(184, 184, 184);
				fillrect(rectOffset+BlockDim*i, rectOffset+BlockDim*j, rectOffset+BlockDim*(i+1), rectOffset+BlockDim*(j+1));
			}
			else if (i%2 == 1 && j%2 == 1){
				//setcolor to lightblue
				setcolor (135, 206, 250);
				fillrect(rectOffset+BlockDim*i, rectOffset+BlockDim*j, rectOffset+BlockDim*(i+1), rectOffset+BlockDim*(j+1));	
				setcolor(0, 0, 0);
				point LBCoords = getLBCoords(i, j);
				char buff[100];
				sprintf(buff, "%d, %d", LBCoords.i, LBCoords.j);
				drawtext(rectOffset+BlockDim*i + textOffset, rectOffset+BlockDim*j + textOffset, buff, FLT_MAX, FLT_MAX);
				
			}
			else if (i%2 == 0 && j%2 == 1) {
				//vertical lines
				setcolor (0, 0, 0);
				for (int v = 0; v < tracksPerChannel; v++){
					drawline(rectOffset+BlockDim*i + wireOffset*(v+1), rectOffset+BlockDim*j, rectOffset+BlockDim*i + wireOffset*(v+1), rectOffset+BlockDim*(j+1));
				}
								
			}
			else if (i%2 == 1 && j%2 == 0){
				//horizontal lines
				setcolor (0, 0, 0);
				for (int h = 0; h < tracksPerChannel; h++){
					drawline(rectOffset+BlockDim*i, rectOffset+BlockDim*j + wireOffset*(h+1), rectOffset+BlockDim*(i+1), rectOffset+ BlockDim*(j) + wireOffset*(h+1));
				}
				
			}

		}
	}

#ifdef ROUTING	
	//now to draw the routes
	//setcolor (rand()%255, rand()%255, rand()%255);
	setcolor (255, 0, 0);
	for (int r = 0; r < route.size(); r++){
		if (route[r].i % 2 == 1 && route[r].j % 2 == 0){
			//horizontal lines
			drawline(rectOffset+BlockDim*route[r].i, rectOffset+BlockDim*route[r].j + wireOffset*(pin+1), rectOffset+BlockDim*(route[r].i+1), rectOffset + BlockDim*route[r].j + wireOffset*(pin+1));
		}
		if (route[r].i % 2 == 0 && route[r].j % 2 == 1){
			//vertical lines
			drawline(rectOffset+BlockDim*route[r].i + wireOffset*(pin+1), rectOffset+BlockDim*route[r].j, rectOffset+BlockDim*route[r].i + wireOffset*(pin+1), rectOffset+BlockDim*(route[r].j+1));
		}
	}
#endif
	
}
