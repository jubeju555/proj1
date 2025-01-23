
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

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
    string minutes = 0;
    string seconds = 0;
    for(int i=0; i<length; i++)
    {
        istringstream ss(tracks[i].length);
        getline(ss, minutes, ':');
        getline(ss, seconds, ' ');
        total_seconds += (stoi(minutes)*60)+stoi(seconds);
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
    return new_string;
}

map<int, artist> storefile(string filename)
{
    // read the file in and store it, (posibly in vector)
    ifstream fileIn(filename);
    string line = "";
    string title = "";
    string time = "";
    string artist_name = "";
    string name = "";
    string album_name = "";
    string genre = "";
    string track = "";
    int count = 0;
    map<string, artist> judah;
    if(fileIn.is_open()){
        while(getline(fileIn, line)){
            stringstream ss(line);
            ss>>title>>time>>artist_name>>album_name>>genre>>track;
            //make artist and fill variables
            artist BobMarley;
            BobMarley.name = artist_name;
            //store artist in map
            judah.insert({BobMarley.name, BobMarley});
            //make album and fill variables
            for(){

            }
            album Exodus;
            Exodus.title = album_name;
            Exodus.length




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
