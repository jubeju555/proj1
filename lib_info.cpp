
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iomanip>
#include <iterator>

using namespace std;
struct song
{
    int tracknum;
    string title;
    string length;
    song(){
        tracknum = 0;
        title = "";
        length = "";
    }
};
struct album
{
    string title;
    int time_length;
    int num_tracks;
    map<int, song> tracks;
    album(){
        title = "";
        time_length = 0;
        num_tracks = 0;
    }
    int getTotalSeconds();
};
struct artist
{
    string name;
    int num_songs;
    int total_time;
    map<string, album> albums;
    artist(){
        name = "";
        num_songs = 0;
        total_time = 0;
    }
    void printfile(string filename);
};

string removeSpaces(string s)
{
    string new_string = "";
    stringstream ss(s);
    string word = "";
    while (getline(ss, word, '_'))
    { // used Geeks4Geeks to referesh on stringstreams
        // if formatting gets weird, add to a vector and parse that way
        new_string = new_string + word + " ";
    }
    new_string.pop_back();
    return new_string;
}
void removeUnderscores(string &s){
    for(int i=0; i<s.length(); i++){
        if(s[i]=='_') s[i]=' ';
    }
}

int toSeconds(string sec){
    stringstream ss(sec);
    string time_string = "";
    int seconds = 0;
    getline(ss, time_string, ':');
    // cout<<endl<<time_string<<endl<<endl;
    seconds += stoi(time_string)*60;
    getline(ss, time_string);
    // cout<<endl<<time_string<<endl<<endl;
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
        removeUnderscores(song_title);
        removeUnderscores(artist_name);
        removeUnderscores(album_name);
        removeUnderscores(genre);
        
        // store artist in map if not found
        map<string, artist>::iterator artist_it = judah.find(artist_name);
        if (artist_it == judah.end())
        {
            // make artist, fill variables, and insert
            struct artist BobMarley;
            BobMarley.name = artist_name;
            artist_it = judah.insert({artist_name, BobMarley}).first;
        }

        map<string, album>::iterator album_it = artist_it->second.albums.find(album_name);
        if (album_it == artist_it->second.albums.end()){ 
            //make album, fill variables, insert
            album Exodus;
            Exodus.title = album_name;
            album_it=artist_it->second.albums.insert({album_name, Exodus}).first;
        }

        map<int, song>::iterator song_it = album_it->second.tracks.find(track);
        if(song_it == album_it->second.tracks.end()){
            artist_it->second.num_songs++;
            album_it->second.num_tracks++;
            album_it->second.time_length+=toSeconds(time);
            artist_it->second.total_time += toSeconds(time);
            song OneLove;
            OneLove.tracknum = track;
            OneLove.title = song_title;
            OneLove.length = time;
            album_it->second.tracks.insert({track, OneLove});
            // store song in album

            count++;
        }
    }
    return judah;
}
string secondsToString(int sec){
    string time = "";
    time += to_string(sec/60);
    time += ":";
    if(sec%60<10) time+= "0";
    time += to_string(sec%60);
    return time;
}
void printfile(string filename){
    // read the file in and store it, (posibly in vector)
    map<string, artist> judah = storefile(filename);
    for(map<string,artist>::iterator it = judah.begin(); it!=judah.end(); it++){
        cout<<it->second.name<<": "<<it->second.num_songs<<", "<<secondsToString(it->second.total_time)<<endl;
        for(map<string,album>::iterator jt = it->second.albums.begin(); jt!=it->second.albums.end(); jt++){
            cout<<setw(8)<<right<<""<<jt->second.title<<": "<<jt->second.num_tracks<<", "<<secondsToString(jt->second.time_length)<<endl;
            for(map<int,song>::iterator nt = jt->second.tracks.begin(); nt!=jt->second.tracks.end(); nt++){
                cout<<right<<setw(16)<<""<<nt->second.tracknum<<". "<<nt->second.title<<": "<<nt->second.length;
                cout<<endl;
            }
        }
    }
}
int main(int argc, char* argv[]){
    printfile(argv[1]);
}
