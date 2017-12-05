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

bool Library::generateIndex(){
	//Create a filestrem
	fstream dFile;
	//Open the file in read mode
	dFile.open(dataFile.data(), fstream::in);
	//Verify is data file exist
	if (!dFile){
		logFile->noDataFile();
		return false;
	}

	logFile->createIndexLog(tree->getIndexFile(), getDataFile());

	int startRegisty, registrySize, id;
	char pipe;

	//Goes through the file
	while(!dFile.eof()){
		//Receive the registry size and a pipe
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
	}
	//Close the file
	dFile.close();

	return true;
}

//insert the song in the btree and in the datafile
bool Library::insertSong(Song song){

	logFile->insertSongLog(song.id, song.title, song.genre);
	//Verify if a song with song.id already exists
	if (tree->searchIndex(song.id) != -1){
		logFile->insertDuplicated(song.id);
		return false;
	}

	//Creates a filestram
	fstream dFile;
	//Opens the file in append mode
	dFile.open(dataFile.data(), fstream::app);
	dFile.seekg(0, ios_base::end);
	//Calculates the char amount
	int size = integerDigits(song.id) + song.title.length() + song.genre.length() + 3;
	//Writes on file
	dFile << size << '|';
	int byteOS = dFile.tellg();
	dFile << song.id << '|' << song.title << '|' << song.genre << '|';
	//Close the file
	dFile.close();

	tree->insertIndex(song.id, byteOS);
    return true;
}

// search for a song and return it
Song Library::searchSong(key_t id){
	Song song;
	char pipe;

	fstream dFile;

	song.id = -1;

	// verify if index file exists
	dFile.open(tree->getIndexFile().data(), fstream::in);
	if (!dFile){
        logFile->emptyIndex();
        if(!generateIndex()){
            return song;
        }
	}
    dFile.close();

	logFile->searchLog(id);
	//Search byte offset in index
	int byteOS = tree->searchIndex(id);

	//Verify if the song does not exists
	if (byteOS == -1){
		logFile->searchFailLog(id);
		song.id = -1;
		return song;
	}

	//Open the file
	dFile.open(dataFile.data(), fstream::in);
	//Verify if data file exist
	if (!dFile){
		logFile->noDataFile();
		return song;
	}
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

// call btree method to print itself
void Library::showBTree(){
    tree->printTree();
}

// return data file path
string Library::getDataFile(){
	return dataFile;
}

// count how many digits an integer have
int Library::integerDigits(int id){
	int counter = 1;
	while (id >= 10){

		id /= 10;
		counter++;
	}
	return counter;
}
