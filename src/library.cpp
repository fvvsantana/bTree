#include "library.hpp"

//constructor
Library::Library(){
    dataFile = "dados.dad";
    logFile = new Log("log_clima.txt");
    tree = new BTree("arvore.idx", logFile);
}

//destructor
Library::~Library(){
    delete logFile;
    delete tree;
}

void Library::generateIndex(){
	//Creat a filestrem
	fstream dFile;
	//Open the file in read mode
	dFile.open(dataFile.data(), fstream::in);

	logFile->createIndexLog(tree->getIndexFile(), getDataFile());

	int startRegisty, registrySize, id;
	char pipe;

	//Goes through the file
	while((int)dFile.tellg() != -1){
		//Recive the registry size and a pipe
		dFile >> registrySize >> pipe;
		//Save the registry byteoffset
		startRegisty = (int)dFile.tellg();
		//Read the id song and a pipe
		dFile >> id >> pipe;
		//Insert id and byte offset in index
		tree->insertIndex(id, startRegisty);
		//Go to the next registry
		dFile.seekg(registrySize + integerDigits(registrySize), ios_base::beg);
	}
	//Close the file
	dFile.close();
}

//insert the song in the btree and in the datafile
void Library::insertSong(Song song){

	logFile->insertSongLog(song.id, song.title, song.genre);

	//Creates a filestram
	fstream dFile;
	//Opens the file in append mode
	dFile.open(dataFile.data(), fstream::app);
	//Calculates the char amount
	int size = integerDigits(song.id) + song.title.length() + song.genre.length() + 4;
	//Writes on file
	dFile << size << '|' << song.id << '|' << song.title << '|' << song.genre << '|';
	//Close the file
	dFile.close();

}

Song* Library::searchSong(key_t id){

}

void Library::removeSong(key_t id){

}

void Library::showBTree(){
    tree->printTree();
}
string Library::getDataFile(){
	return dataFile;
}

int Library::integerDigits(int id){
	int counter = 1;
	while (id >= 10){
		
		id /= 10;
		counter++;
	}
	return counter;
}
