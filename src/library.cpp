#include "library.hpp"

//constructor
Library::Library(){
    tree = new BTree("../library.idx");
    dataFile = "../library.dat";
}

//destructor
Library::~Library(){
    delete tree;
}

void Library::generateIndex(){

}

//insert the song in the btree and in the datafile
void Library::insertSong(Song& song){

	fstream dFile;
	dFile.open(dataFile.data(), fstream::app);

	int size = song.id.length() + song.title.length() + song.genre.length() + 4;

	dFile << size << '|' << song.id << '|' << song.title << '|' << song.genre << '|';

}

Song* Library::searchSong(key_t id){

}

void Library::removeSong(key_t id){

}

void Library::showBTree(){

}
