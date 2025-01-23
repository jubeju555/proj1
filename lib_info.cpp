// aasdkfjl judah
// checking if pushed

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
struct song
{
    int tracknum;
    string title;
    string length;
};
struct album
{
    string title;
    double length;
    vector<song> tracks;

    int getTotalSeconds();
};
// Calculate and return the total number of 
// seconds of all of the tracks in an album
int album::getTotalSeconds(){
    int total_seconds = 0;
    int minutes = 0;
    int seconds = 0;
    for(int i=0; i<tracks.length(); i++)
    {
        stringstream ss(tracks[i].length);
        getline(ss, minutes, ':');
        getline(ss, seconds);
        total_seconds += (minutes*60)+seconds;
    }
    return total_seconds;
}
struct artist
{
    string name;
    vector<album> albums;
};

string removeSpaces(string s)
{
    // for(int i=0; i< s.length(); i++){
    //     if(s[i] == '_'){
    //         s[i] = ' ';
    //     }
    // }

    string new_string = "";
    stringstream ss(s);
    while (ss.good()){ //used Geeks4Geeks to referesh on stringstreams
        string word = "";
        getline(ss, word, '_');
        //if formatting gets weird, add to a vector and parse that way
        new_string = new_string + word + " ";
    }
}

void storefile(string filename)
{
    // read the file in and store it, (posibly in vector)
    ifstream fileIn(filename);
    string line = "";
    if(fileIn.is_open()){
        while(getline(fileIn, line)){
        }
    }
    return;
}

void organizefile(string filename)
{
    
    // organize the file in a specific format
    return;
}
// print file accordngi to the format
void printfile(string filename)
{
    return;
}
int main()
{
    return 0;
}