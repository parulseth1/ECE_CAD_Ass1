#include "graphics.h"
#include <iostream>

using namespace std;


int DrawNow()
{
    cout<<"Hello Graphics\n";
    init_graphics("Drawing1", WHITE);
    int a;
    std::cin>>a;
    set_visible_world(0, 0, 1000, 1000);
    update_message ( " Interactive graphics example . " ) ;
    
    
    close_graphics () ;
    cout<<"END"<<endl;
    return 0;
}
