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
	//Creat a filestrem
	fstream dFile;
	//Open the file in read mode
	dFile.open(dataFile.data(), fstream::in);

	int startRegisty, registrySize, id;
	char pipe;

	//Goes through the file
	while(!dFile.eof()){
		//Recive the registry size and a pipe
		dFile >> registrySize >> pipe;
		//Save the registry byteoffset
		startRegisty = (int)dFile.tellg();
		//Read the id song and a pipe
		dFile >> id >> pipe;
		//Insert id and byte offset in index
		tree->insertIndex(id, startRegisty);
		//Go to the next registry
		dFile.seekg(registrySize, ios_base::beg);
	}
	//Close the file
	dFile.close();
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
