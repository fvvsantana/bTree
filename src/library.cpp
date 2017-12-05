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
	while(!dFile.eof()){
		//Recive the registry size and a pipe
		dFile >> registrySize >> pipe;
		//Save the registry byteoffset
		startRegisty = (int)dFile.tellg();
		//If outside the file limits, break
		if (startRegisty == -1)
			break;
		//Read the id song and a pipe
		dFile >> id >> pipe;
		//Insert id and byte offset in index
		tree->insertIndex(id, startRegisty);
		//Go to the next registry
		dFile.seekg(registrySize - dFile.tellg() + startRegisty , ios_base::cur);

		cout << (int)dFile.tellg() << '\n';
	}
	//Close the file
	dFile.close();
}

//insert the song in the btree and in the datafile
void Library::insertSong(Song song){

	logFile->insertSongLog(song.id, song.title, song.genre);

	if (tree->searchIndex(song.id) == -1){
		logFile->insertDuplicated(song.id);
		return;
	}

	//Creates a filestram
	fstream dFile;
	//Opens the file in append mode
	dFile.open(dataFile.data(), fstream::app);
	//Calculates the char amount
	int size = integerDigits(song.id) + song.title.length() + song.genre.length() + 3;
	//Writes on file
	dFile << size << '|';
	int byteOS = dFile.tellg();
	dFile << song.id << '|' << song.title << '|' << song.genre << '|';
	//Close the file
	dFile.close();

	tree->insertIndex(song.id, byteOS);

}


Song Library::searchSong(key_t id){
	Song song;
	char pipe;

	logFile->searchLog(id);
	//Search byte offset in index
	int byteOS = tree->searchIndex(id);

	if (byteOS == -1){
		logFile->searchFailLog(id);
		song.id = -1;
		return song;
	}

	fstream dFile;
	//Opens the file in append mode
	dFile.open(dataFile.data(), fstream::in);
	//Go to the specified byte offset
	dFile.seekg(byteOS, ios_base::beg);
	//Read the song information
	dFile >> song.id >> pipe ;
	getline(dFile, song.title, '|');
	getline(dFile, song.genre, '|');

	dFile.close();

	logFile->searchSuccesLog(song.id, byteOS, song.title, song.genre);

	return song;

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
