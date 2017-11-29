#include "bTree.hpp"

// BTree constructor, receives file url
BTree::BTree(const char* url){

    indexFile = url;

    // try to open the file
    fstream fs;
    fs.open(url, fstream::in);

    // verify if the file was opened successfully
    if (fs.is_open()) {

    	cout << "Arquivo " << url << " aberto com sucesso";

    	// read root rrn
    	fs >> root;
    	cout << root;
    }
    else {
    	// an error occurred, maybe the file does not exist
    	cout << " Erro ao abrir o arquivo " << url << ", tentando criar um novo..." << endl;

    	// create a new file
    	fs.open(url, fstream::out);

    	// verify again
    	if (fs.is_open()) {

    		cout << " Arquivo criado com sucesso." << endl;

    		// set root as 0 and save to file
    		root = 0;
    		fs << root << endl;
    	}
    	else {
    		cout << " Erro ao criar o arquivo, possivelmente erro de permissao." << endl;
    	}
    }

    fs.close();
}

void BTree::insertIndex(key_t id, int byteOS){

}

//return the byte offset of the searched block in the datafile
int BTree::searchIndex(key_t id){

}

void BTree::removeIndex(key_t id){

}

void BTree::updateHeader(bool updated){

}

bool BTree::isUpdated(){

}

