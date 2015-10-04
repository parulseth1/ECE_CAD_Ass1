#include "graphics.h"
#include <iostream>

using namespace std;


int DrawNow()
{
    cout<<"Hello Graphkdksnfics\n";
    init_graphics("MazeRouter", WHITE);
    int a;
    std::cin>>a;
    set_visible_world(0, 1000, 1000, 0);
    update_message ( " MAZE ROUTER" ) ;
    
    
    close_graphics () ;
    cout<<"END"<<endl;
    return 0;
}

