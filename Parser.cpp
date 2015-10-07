#include "Parser.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

int doParse(char* FileName, int* grid, int* tracksPerChannel, vector<tracks> *track) {
    /*
     * The doParse function takes in the filename, and a pointer to gridSize, tracksPerChannel 
     * and a vector of the connection structure tracks to store the connection information in
     * this function returns the total no of connections made, or -1 if the file could not be opened
     * if the file is not formatted correctly, undefined behavior will occur
     */
    cout<<FileName<<endl;
    ifstream fin;
    tracks temp;
    fin.open(FileName); //why wont you open?
    if (!fin.is_open()){
        cout<<"File could not be opened"<<endl;
        return -1;
    }
    
    //once file is opened, we should read the file and parse it
    string line;
    //the first line has the grid size
    std::getline(fin, line);
    *grid = atoi(line.c_str());
    //the second line has the no. of tracks per channel
    std::getline (fin, line);
    *tracksPerChannel = atoi(line.c_str());
    
    bool quit = false;
    
    
    //now the consecutive lines will have the data of the connections
    while (!quit) {
        std::getline (fin, line);
        istringstream StringStream(line);
        string ConnData;
        
        /*The Connection data is ordered as follows : 
         * LB1 i, j pin LB2 i, j, pin
         */
        
        StringStream >> ConnData;
        temp.From.i = atoi(ConnData.c_str());
        StringStream >> ConnData;
        temp.From.j = atoi(ConnData.c_str());
        StringStream >> ConnData;
        temp.pin_From = atoi(ConnData.c_str());
        StringStream >> ConnData;
        temp.To.i = atoi(ConnData.c_str());
        StringStream >> ConnData;
        temp.To.j = atoi(ConnData.c_str());
        StringStream >> ConnData;
        temp.pin_To = atoi(ConnData.c_str());
        
        if (temp.From.i == -1 &&
            temp.From.j == -1 &&
            temp.pin_From == -1 &&
            temp.To.i == -1 &&
            temp.To.j == -1 &&
            temp.pin_To == -1){
            quit = true;
        }
        else{
            track->push_back(temp);
        }
    }
    
    fin.close();
    return track->size();
    
}
