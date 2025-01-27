
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iterator>

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
int album::getTotalSeconds()
{
    int total_seconds = 0;
    string minutes = 0;
    string seconds = 0;
    for (int i = 0; i < length; i++)
    {
        istringstream ss(tracks[i].length);
        getline(ss, minutes, ':');
        getline(ss, seconds, ' ');
        // error is due to not being c++11, should be fine
        total_seconds += (stoi(minutes) * 60) + stoi(seconds);
    }
    return total_seconds;
}
struct artist
{
    string name;
    map<string, album> albums;
    void printfile(string filename);
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
    while (ss.good())
    { // used Geeks4Geeks to referesh on stringstreams
        string word = "";
        getline(ss, word, '_');
        // if formatting gets weird, add to a vector and parse that way
        new_string = new_string + word + " ";
    }
    return new_string;
}

map<string, artist> storefile(string filename)
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
    if (fileIn.is_open())
    {
        while (getline(fileIn, line))
        {
            stringstream ss(line);
            ss >> title >> time >> artist_name >> album_name >> genre >> track;
            
            // store artist in map if not found
            if (judah.find(artist_name) == judah.end())
            {
                // make artist, fill variables, and insert
                artist BobMarley;
                BobMarley.name = artist_name;
                judah.insert({artist_name, BobMarley});
            }
            artist BobMarley = judah.at(judah.find(artist_name));
                
           // store album in artist if not found
          if (judah.find(album_name) == .albums.end()){ 
                album Exodus;
                Exodus.title = album_name;
                Exodus.length = 0;
                judah[BobMarley.name].albums.insert({album_name, Exodus});
            }
                song OneLove;
                // fill song variables
                OneLove.tracknum = count;
                OneLove.title = title;
                OneLove.length = time;
                // store song in album
                judah[BobMarley.name].albums[count].tracks.push_back(OneLove);
                count++;
            }
        }
    return judah;
    }


// print file accordngi to the format
void artist::printfile(string filename)
{
    // read the file in and store it, (posibly in vector)
    ifstream fileIn(filename);
    string line = "";
    string title = "";
    string time = "";
    if (fileIn.is_open())
    {
        while (getline(fileIn, line))
        {
            stringstream ss(line);
            ss >> title >> time;
            cout << name << ", " << albums << endl;
            for (int i = 0; i < albums.size(); i++)
            {
                cout << albums[i].title << " " << albums[i].getTotalSeconds() << endl;
                cout << albums[i].tracks.size() << endl;
                cout << albums[i].tracks[0].title << " " << albums[i].tracks[0].length << endl;
                cout << albums[i].tracks[1].title << " " << albums[i].tracks[1].length << endl;
                
            }
            
            // cout << "Track " << track << ": ";
            // cout <<
            cout << title << " " << time << endl;
        }
    }

    return;
}
int main()
{

    return 0;
}
