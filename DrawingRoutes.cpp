
#include "graphics.h"
#include "MazeRouter.h"
#include <iostream>
#include <stdlib.h>
#include <cfloat>

using namespace std;

int gridSize = 0;
int tracksPerChannel;
vector<int> pin;
vector<vector<point>> route;
vector<int> sourcePin, targetPin;
int track;
vector<point> SourceWB, TargetWB;
void drawscreen();

point getLBCoords(int i, int j){
	return makePoint((i-1)/2, (j-1)/2);
}

int DrawNow(int _gridSize, int _tracksPerChannel, vector<int> _pin, vector<vector<point>> _route, vector<int> _sourcePin, vector<int> _targetPin, int _track,  vector<point> _sourceWB, vector<point> _targetWB)
{
    cout<<"Hello Graphics\n";
    
    gridSize = _gridSize;
    tracksPerChannel = _tracksPerChannel;
    pin = _pin;
    route = _route; 
    sourcePin = _sourcePin;
    targetPin = _targetPin;
    track = _track;
    SourceWB = _sourceWB;
    TargetWB =_targetWB;
    
//    cout<<"Draw route"<<endl;
//    for (int i=0;i<route.size();i++){
//        cout<<route[i].i<<", "<<route[i].j<<endl;
//    }
    
    init_graphics("MazeRouter", WHITE);
    
    set_visible_world(0, 0, 1000, 1000);
    
    event_loop(NULL, NULL, NULL, drawscreen);  
//    drawscreen();
//    flushinput();
//    cin.get();
    close_graphics();
    cout<<"END"<<endl;
    
    return 0;
    
    
    
}

void drawX(int pin, int track, point WB, float BlockDim, float wireOffset, float rectOffset){
	setfontsize(7);
	float x, y;
	
	if (pin == 1){
		x = rectOffset + BlockDim*WB.i+BlockDim*2/3;
		y = rectOffset+BlockDim*((WB.j))+wireOffset*(track+1);
	}
	else if (pin == 2){
		y = rectOffset + BlockDim*WB.j+BlockDim*1/3;
		x = rectOffset+BlockDim*((WB.i))+wireOffset*(track+1);
	}
	else if (pin == 3){
		x = rectOffset + BlockDim*WB.i+BlockDim*1/3;
		y = rectOffset+BlockDim*((WB.j))+wireOffset*(track+1);
	}
	else if (pin == 4){
		y = rectOffset + BlockDim*WB.j+BlockDim*2/3;
		x = rectOffset+BlockDim*((WB.i))+wireOffset*(track+1);	
	}
	cout<<x<<"--"<<y<<"--"<<pin<<endl;
	drawtext(x, y, "X", FLT_MAX, FLT_MAX);
}

void drawscreen(){
        cout<<"DrawScreen"<<endl;
	//set_draw_mode (DRAW_NORMAL);  // Should set this if your program does any XOR drawing in callbacks.
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
				//setcolor to lightblue for logic boxes
				setcolor (135, 206, 250);
				fillrect(rectOffset+BlockDim*i, rectOffset+BlockDim*j, rectOffset+BlockDim*(i+1), rectOffset+BlockDim*(j+1));	
				setcolor(0, 0, 0);
				point LBCoords = getLBCoords(i, j);
				char buff[100];
				sprintf(buff, "%d, %d", LBCoords.i, LBCoords.j);
				drawtext(rectOffset+BlockDim*i + textOffset, rectOffset+BlockDim*j + textOffset, buff, FLT_MAX, FLT_MAX);
				//draw the pins
				drawline (rectOffset+BlockDim*(i+1), rectOffset+BlockDim*j + BlockDim*2/3, rectOffset+BlockDim*(i+1) +  wireOffset*tracksPerChannel, rectOffset+BlockDim*j + BlockDim*2/3);
				drawline (rectOffset+BlockDim*(i), rectOffset+BlockDim*j + BlockDim*1/3, rectOffset+BlockDim*(i) -  wireOffset*tracksPerChannel, rectOffset+BlockDim*j + BlockDim*1/3);
				drawline (rectOffset+BlockDim*(i) + BlockDim*1/3, rectOffset+BlockDim*(j+1), rectOffset+BlockDim*(i) +  BlockDim*1/3, rectOffset+BlockDim*(j+1) + wireOffset*tracksPerChannel);
				drawline (rectOffset+BlockDim*(i) + BlockDim*2/3, rectOffset+BlockDim*(j), rectOffset+BlockDim*(i) +  BlockDim*2/3, rectOffset+BlockDim*(j) - wireOffset*tracksPerChannel);
				
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
        //a:
        setlinewidth (2);
        for (int s = 0; s < route.size(); s++){
            int r = 25 + rand()%200;
            int g = 25 + rand()%200;
            int b = 25 + rand()%200;
            //if (r == 0 && g == 0 && b == 0){goto a;}
            setcolor (r, g, b);
            for (int r = 0; r < route[s].size(); r++){
                    if (route[s][r].i % 2 == 1 && route[s][r].j % 2 == 0){
                            //horizontal lines
                            drawline(rectOffset+BlockDim*route[s][r].i, rectOffset+BlockDim*route[s][r].j + wireOffset*(pin[s]+1), rectOffset+BlockDim*(route[s][r].i+1), rectOffset + BlockDim*route[s][r].j + wireOffset*(pin[s]+1));
                    }
                    if (route[s][r].i % 2 == 0 && route[s][r].j % 2 == 1){
                            //vertical lines
                            drawline(rectOffset+BlockDim*route[s][r].i + wireOffset*(pin[s]+1), rectOffset+BlockDim*route[s][r].j, rectOffset+BlockDim*route[s][r].i + wireOffset*(pin[s]+1), rectOffset+BlockDim*(route[s][r].j+1));
                    }
            }
            drawX(sourcePin[s], pin[s], SourceWB[s], BlockDim, wireOffset, rectOffset);
	       	drawX(targetPin[s], pin[s], TargetWB[s], BlockDim, wireOffset, rectOffset);
        }
        
        //now draw x's on the source and target pins
        //source
       	
        setlinewidth(1);
#endif
	
}
