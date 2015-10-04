
#include "graphics.h"
#include <iostream>

using namespace std;

int gridSize = 0;
int tracksPerChannel;

void drawscreen();

int DrawNow(int _gridSize, int _tracksPerChannel)
{
    cout<<"Hello Graphics\n";
    
    gridSize = _gridSize;
    tracksPerChannel = _tracksPerChannel;
    
    init_graphics("MazeRouter", WHITE);
    
    set_visible_world(0, 1000, 1000, 0);
    
    event_loop(NULL, NULL, NULL, drawscreen);  
    
    cout<<"END"<<endl;
    return 0;
    
    
    
}

void drawscreen(){
	set_draw_mode (DRAW_NORMAL);  // Should set this if your program does any XOR drawing in callbacks.
	clearscreen();  /* Should precede drawing for all drawscreens */
	
	int BlockDim = 1000/(gridSize + 2);
	int wireOffset = BlockDim/(tracksPerChannel + 1);
	int rectOffset = BlockDim;
	
	setcolor(0, 0, 0);
	drawrect(rectOffset-1, rectOffset-2, rectOffset+BlockDim*(gridSize)+1, rectOffset+BlockDim*(gridSize));
	
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
			}
			else if (i%2 == 1 && j%2 == 0) {
				//vertical lines
				setcolor (0, 0, 0);
				for (int v = 0; v < tracksPerChannel; v++){
					drawline(rectOffset+BlockDim*i + wireOffset*(v+1), rectOffset+BlockDim*j, rectOffset+BlockDim*i + wireOffset*(v+1), rectOffset+BlockDim*(j+1));
				}
								
			}
			else if (i%2 == 0 && j%2 == 1){
				setcolor (0, 0, 0);
				for (int h = 0; h < tracksPerChannel; h++){
					drawline(rectOffset+BlockDim*i, rectOffset+BlockDim*j + wireOffset*(h+1), rectOffset+BlockDim*(i+1), rectOffset+ BlockDim*(j) + wireOffset*(h+1));
				}
				
			}

		}
	}
}
