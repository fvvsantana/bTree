#include "bTree.hpp"

BTree::BTree(string url){
    indexFile = url;
}

void BTree::insertIndex(key_t id, int byteOS){

	Header header;

	Index indexRecived;
	indexRecived.key = id;
	indexRecived.byteOS = byteOS;

	switch(createFile()){
		case -1:
			//Error log
			break;

		case 0:
			//Change update bit and initialize root to rrn 0
			updateHeader(false, 0);

			Node page;
			//Initialize a page as leaf
			createLeaf(page);
			//Write the index recived on page
			page.index[0] = indexRecived;
			//Increases number of elements
			page.nIndexes++;
			//Write page file on 0 position
			writePage(page, 0);

			updateHeader(true);

			break;

		case 1:
			//Update header
			updateHeader(false);

			fstream bTree;
			//Open the file
			bTree.open(indexFile.data(), fstream::in| fstream::binary);
			//Read the header
			bTree.read((char*)&header, sizeof(header));
			bTree.close();
			//return variable
			Index promoIndex;
			int promoChild;
			//Insert an index at the tree
			if (insert(header.rrnRoot, indexRecived, promoIndex, promoChild) == 1){
				Node newRoot;
				//If a promotion occurred, a new root is created
				createLeaf(newRoot);
				//Change isLeaf to false
				newRoot.isLeaf = false;
				//Store the index and the rrn of children
				newRoot.index[0] = promoIndex;
				newRoot.children[0] = header.rrnRoot;
				newRoot.children[1] = promoChild;
				//Increase the number of elements
				newRoot.nIndexes++;
				//Write the file and update the header with tthe new root
				updateHeader(true, writePage(newRoot));
			}
			break;
	};

}

//return the byte offset of the searched block in the datafile
int BTree::searchIndex(key_t id){

}

void BTree::removeIndex(key_t id){

}

//Change the update state and root  rrn
void BTree::updateHeader(bool updated, int root){
	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::out|fstream::binary);

	Header header;

	header.updated = updated;
	header.rrnRoot = root;

	bTree.write((char*)&header, sizeof(Header));

	bTree.close();
}

//Change the update state
void BTree::updateHeader(bool updated){
	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::out|fstream::binary);

	Header header;

	bTree.read((char*)&header, sizeof(Header));

	bTree.seekg(0, ios_base::beg);

	header.updated = updated;

	bTree.write((char*)&header, sizeof(Header));

	bTree.close();
}

//Change the color of the root
void BTree::updateHeader(int root){
	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::out|fstream::binary);

	Header header;

	bTree.read((char*)&header, sizeof(Header));

	bTree.seekg(0, ios_base::beg);

	header.rrnRoot = root;

	bTree.write((char*)&header, sizeof(Header));

	bTree.close();
}

bool BTree::isUpdated(){

}

//Read a page in the file with the specified rrn
BTree::Node BTree::readPage(int rrn){
	fstream bTree;

	Node page;

	bTree.open(indexFile.data(), fstream::in|fstream::binary);

	bTree.seekg(sizeof(Header) + rrn * sizeof(Node), ios_base::beg);

	bTree.read((char*)&page, sizeof(Node));

	bTree.close();

	return page;
}

//Write the page in the specified rrn
void BTree::writePage(Node page, int rrn){
	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::out|fstream::binary);

	bTree.seekg(sizeof(Header) + rrn * sizeof(Node), ios_base::beg);

	bTree.write((char*)&page ,sizeof(Node));

	bTree.close();
}

//Write the page at the end of the file
//Return the rrn where it the pages was written
int BTree::writePage(Node page){
	long int rrn;

	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::out|fstream::binary);

	bTree.seekg(0, ios_base::end);

	rrn = ((long int)bTree.tellg() - sizeof(Header))/sizeof(Node);

	bTree.write((char*)&page ,sizeof(Node));

	bTree.close();

	return rrn;
}

//Initializate the page variables
void BTree::createLeaf(Node &page){

	page.nIndexes = 0;

	for (int i = 0; i < BT_ORDER; i++)
		page.children[i] = NIL;

	page.isLeaf = 1;
}

//Verify that the file exists
//If negative, creates. If it fails, return an error
//Else return 1
int BTree::createFile(){
	fstream bTree;

	bTree.open(indexFile.data(), fstream::in|fstream::binary);

	if (!bTree){
		bTree.open(indexFile.data(), fstream::out|fstream::binary);
		
		if (!bTree)
			return -1;
		
		bTree.close();
		return 0;
	}

	bTree.close();
	return 1;
}

//Insert an index on the page.
//Return error(-1), no promotion(0) or promotion(1)
int BTree::insert(int rrn, Index &toAdd, Index &promoIndex, int &promoChild){
	//Base case
	if (rrn == NIL){
		promoIndex = toAdd;
		promoChild = NIL;
		return 1;
	}
	else{
		Node page;
		Node newPage;
		Index promoBottomIndex;
		int promoBottomChild;
		int returnValue;
		int pos = 0;

		page = readPage(rrn);
		//Search for the position of the new index
		while (pos < page.nIndexes && page.index[pos].key < toAdd.key)
			pos++;
		//If an index with the requested key already exists, returns erro
		if (page.index[pos].key == toAdd.key)
			return -1;
		//Recursion to the next page
		returnValue = insert(page.children[pos], toAdd, promoBottomIndex, promoBottomChild);

		if (returnValue == -1 || returnValue == 0){
			return returnValue;
		}
		//If the page is not full, add the index
		else if (page.nIndexes < BT_ORDER - 1){
			int i = page.nIndexes;
			//Shift the elemtents to right until the index position is empty
			while(i > 0 && page.index[i - 1].key > toAdd.key){
				page.index[i] = page.index[i - 1];
				page.children[i + 1] = page.children[i];
				i--;
			}
			//Adds the index and the child on page
			page.index[i] = promoBottomIndex;
			page.children[i + 1] = promoBottomChild;
			//Increase the number of elements
			page.nIndexes++;
			//write on file
			writePage(page, rrn);
			//retunr no promotion
			return 0;
		}
		//If promotion occurred
		else{
			//A split happens
			split(promoBottomIndex, promoBottomChild, page, promoIndex, promoChild, newPage);
			//Write in the file
			writePage(page, rrn);
			return 1;
		}
	}
}

void BTree::split(Index &index, int &rrn, Node &page, Index &promoIndex, int &promoChild, Node &newPage){
	//Temporary arrays
	Index extraIndex[BT_ORDER];
	int extraChildren[BT_ORDER + 1];
	int i;
	//Copie the data os page to temporary arrays
	for (i = 0; i < page.nIndexes; i++){
		extraIndex[i] = page.index[i];
		extraChildren[i] = page.children[i];
	}
	extraChildren[i] = page.children[i];

	i = BT_ORDER - 1;
	//Search for the position of the new index
	while (i > 0 && extraIndex[i - 1].key > index.key){
		extraIndex[i] = extraIndex[i - 1];
		extraChildren[i + 1] = extraChildren[i];
		i--; 
	}
	//Add the new index in its position
	extraIndex[i] = index;
	extraChildren[i + 1] = rrn;
	//Create the new page
	createLeaf(newPage);

	newPage.isLeaf = page.isLeaf;
	//Choose the index to be promoted
	promoIndex = extraIndex[BT_ORDER/2];
	//Copy the index en children to the page
	for (i = 0; i < BT_ORDER/2; i++){
		page.index[i] = extraIndex[i];
		page.children[i] = extraChildren[i];
	}
	page.children[i] = extraChildren[i];
	//Update number of elements
	page.nIndexes = BT_ORDER/2;

	for (i = BT_ORDER/2 + 1; i < BT_ORDER; i++){
		newPage.index[i - BT_ORDER/2 - 1] = extraIndex[i];
		newPage.children[i - BT_ORDER/2 - 1] = extraChildren[i];
		newPage.nIndexes++;
	}
	newPage.children[i - BT_ORDER/2 - 1] = extraChildren[i];
	//Return the rrn where the page was written
	promoChild = writePage(newPage);
}