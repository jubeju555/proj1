
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
    int time_length = 0;
    int num_songs = 0;
    int num_tracks = 0;
    map<string, song> tracks;

    int getTotalSeconds();
};
// Calculate and return the total number of
// seconds of all of the tracks in an album

// int album::getTotalSeconds()
// {
//     int total_seconds = 0;
//     string minutes = 0;
//     string seconds = 0;
//     map<string, song>::iterator song_it;
//
//     for (song_it = tracks.begin(); song_it!=tracks.end(); song_it++)
//     {
//         istringstream ss(song_it->first);
//         getline(ss, minutes, ':');
//         getline(ss, seconds, ' ');
//         // error is due to not being c++11, should be fine
//         total_seconds += (stoi(minutes) * 60) + stoi(seconds);
//     }
//     return total_seconds;
// }
struct artist
{
    string name;
    int num_songs = 0;
    string total_time = 0;
    map<string, album> albums;
    void printfile(string filename);
};

string removeSpaces(string s)
{
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

int toSeconds(string sec){
    stringstream ss(sec);
    string time_string;
    int seconds = 0;
    getline(ss, time_string, ':');
    seconds += stoi(time_string)*60;
    getline(ss, time_string);
    seconds += stoi(time_string);
    return seconds;
}

map<string, artist> storefile(string filename)
{
    // read the file in and store it, (posibly in vector)
    ifstream fileIn(filename);
    string line = "";
    string song_title = "";
    string time = "";
    string artist_name = "";
    string name = "";
    string album_name = "";
    string genre = "";
    int track = 0;
    int count = 0;
    map<string, artist> judah;
    while (getline(fileIn, line))
    {
        stringstream ss(line);
        ss >> song_title >> time >> artist_name >> album_name >> genre >> track;
            
        // store artist in map if not found
        map<string, artist>::iterator artist_it = judah.find(artist_name);
        if (artist_it == judah.end())
        {
            // make artist, fill variables, and insert
            artist BobMarley;
            BobMarley.name = artist_name;
            artist_it = judah.insert({artist_name, BobMarley}).first;
        }

        map<string, album>::iterator album_it = artist_it->second.albums.find(album_name);
        if (album_it == artist_it->second.albums.end()){ 
            //make album, fill variables, insert
            album Exodus;
            Exodus.title = album_name;
            Exodus.time_length += toSeconds(time);
            album_it=artist_it->second.albums.insert({album_name, Exodus}).first;
        }

        map<string, song>::iterator song_it = album_it->second.tracks.find(song_title);
        if(song_it == album_it->second.tracks.end()){
            artist_it->second.num_songs++;
            song OneLove;
            OneLove.tracknum = track;
            OneLove.title = song_title;
            OneLove.length = time;
            album_it->second.tracks.insert({song_title, OneLove});
            // store song in album

            count++;
        }
    }
    return judah;
}


// print file accordngi to the format
/* 
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
                cout << albums[i].title << albums[i].tracks.size() <<albums[i].getTotalSeconds() << endl;
                cout << artist_name[i].title << " " << albums[i].tracks.size() << " " << albums[i].getTotalSeconds() << endl;
                printf("%s %d %d\n", albums[i].title, albums[i].tracks.size(), albums[i].getTotalSeconds());
                for (int j = 0; j < albums[i].tracks.size(); j++)
                {
                    cout << albums[i].tracks[j].title << " " << albums[i].tracks[j].length << endl;
                }

                // cout << albums[i].tracks[0].title << " " << albums[i].tracks[0].length << endl;
                // cout << albums[i].tracks[1].title << " " << albums[i].tracks[1].length << endl;
                
            }
            cout << title << " " << time << endl;
        }
    }

    return;
}
*/
void printfile(string filename){
    // read the file in and store it, (posibly in vector)
    map<string, artist> judah = storefile(filename);
    for(map<string,artist>::iterator it = judah.begin(); it!=judah.end(); it++){
        cout<<it->second.name<<": "<<it->second.num_songs<<", "<<it->second.total_time<<endl;
        for(map<string,album>::iterator jt = it->second.albums.begin(); jt!=it->second.albums.end(); jt++){
            cout<<"        "<<jt->second.title<<": "<<jt->second.num_tracks<<", "<<jt->second.time_length<<endl;
            for(map<string,song>::iterator nt = jt->second.tracks.begin(); nt!=jt->second.tracks.end(); nt++){
                cout<<nt->second.tracknum<<". "<<nt->second.title<<": "<<nt->second.length;
            }
        }
    }
}
int main(int argc, char* argv[]){
    if(argc<1) cerr<<"No file input";
    printfile(argv[1]);
}
