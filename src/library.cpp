#include "library.hpp"

//constructor
Library::Library(){
    tree = new BTree("arvore.idx");
    dataFile = "dados.dad";
}

//destructor
Library::~Library(){
    delete tree;
}

void Library::generateIndex(){

}

//insert the song in the btree and in the datafile
void Library::insertSong(Song song){
	//Creates a filestram
	fstream dFile;
	//Opens the file in append mode
	dFile.open(dataFile.data(), fstream::app);
	//Calculates the char amount
	int size = song.integerDigits(song.getId()) + song.getTitle().length() + song.getGenre().length() + 4;
	//Writes on file
	dFile << size << '|' << song.getId() << '|' << song.getTitle() << '|' << song.getGenre() << '|';
	//Close the file
	dFile.close();

}

Song* Library::searchSong(key_t id){

}

void Library::removeSong(key_t id){

}

void Library::showBTree(){

}
