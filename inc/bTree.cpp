#include "bTree.hpp"

// BTree constructor, receives file url
BTree::BTree(const char* url, Log* logFile){
    indexFile = url;
    this->logFile = logFile;
}

void BTree::insertIndex(key_t id, int byteOS){

	Index indexRecived;
	indexRecived.key = id;
	indexRecived.byteOS = byteOS;

	logFile->insertIndex(id);

	switch(createFile()){
		case -1:
			logFile->createFileErrorLog();
			return;

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

			//Read the header
			Header header = readHeader();

			//return variable
			Index promoIndex;
			int promoChild;
			//Insert an index at the tree
			int insertReturn = insert(header.rrnRoot, indexRecived, promoIndex, promoChild);
			if (insertReturn == 1){
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
			else if(insertReturn == -1){
				logFile->insertDuplicated(id);
				return;
			}
			break;
	};

	logFile->insertSuccesLog(id);
}

//return the byte offset of the searched block in the datafile
int BTree::searchIndex(key_t id){
    // read the header
    Header header = readHeader();

    // get root node rrn
    int rrn = header.rrnRoot;

    // search until is a leaf
    while (rrn != NIL) {

        Node node = readPage(rrn);

        // use binary search on the current page
        int pos;
        bool found = binarySearch(node, id, pos);

        if (found)
            return node.index[pos].byteOS;
        else
            rrn = node.children[pos];
    }

    return -1;
}

//Change the update state and root  rrn
void BTree::updateHeader(bool updated, int root){
	fstream bTree;

	bTree.open(indexFile, fstream::in|fstream::out|fstream::binary);

	Header header;

	header.updated = updated;
	header.rrnRoot = root;

	bTree.write((char*)&header, sizeof(Header));

	bTree.close();
}

//Change the update state
void BTree::updateHeader(bool updated){
	fstream bTree;

	bTree.open(indexFile, fstream::in|fstream::out|fstream::binary);

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

	bTree.open(indexFile, fstream::in|fstream::out|fstream::binary);

	Header header;

	bTree.read((char*)&header, sizeof(Header));

	bTree.seekg(0, ios_base::beg);

	header.rrnRoot = root;

	bTree.write((char*)&header, sizeof(Header));

	bTree.close();
}

//Read a page in the file with the specified rrn
BTree::Node BTree::readPage(int rrn){
	fstream bTree;

	Node page;

	bTree.open(indexFile, fstream::in|fstream::binary);
	//Verify is index file exist
	if (!bTree){
		page.nIndexes = -1;
		return page;
	}

	bTree.seekg(sizeof(Header) + rrn * sizeof(Node), ios_base::beg);

	bTree.read((char*)&page, sizeof(Node));

	bTree.close();

	return page;
}

//Write the page in the specified rrn
void BTree::writePage(Node page, int rrn){
	fstream bTree;

	bTree.open(indexFile, fstream::in|fstream::out|fstream::binary);

	bTree.seekg(sizeof(Header) + rrn * sizeof(Node), ios_base::beg);

	bTree.write((char*)&page ,sizeof(Node));

	bTree.close();
}

//Write the page at the end of the file
//Return the rrn where it the pages was written
int BTree::writePage(Node page){
	long int rrn;

	fstream bTree;

	bTree.open(indexFile, fstream::in|fstream::out|fstream::binary);

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

	bTree.open(indexFile, fstream::in|fstream::binary);

	if (!bTree){
		bTree.open(indexFile, fstream::out|fstream::binary);

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
		//If an index with the requested key already exists, returns erro
		if (binarySearch(page, toAdd.key, pos))
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
			logFile->nodeDivisionLog(rrn);
			//A split happens
			split(promoBottomIndex, promoBottomChild, page, promoIndex, promoChild, newPage);
			//Write in the file
			writePage(page, rrn);
			logFile->promotionLog(promoIndex.key);
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

//Realize a binary search on a page.
//Return true if the key already exists and false if it doesn't
//The pos argument gets the position where the key is or where it should be
bool BTree::binarySearch(Node page, int key, int &pos){
	int left = 0;
	int right = page.nIndexes - 1;
	int middle;

	while(right - left > 1){
		middle = (left + right)/2;

		if(page.index[middle].key == key){
			pos = middle;
			return true;
		}
		else if (page.index[middle].key > key)
			right = middle - 1;

		else
			left = middle + 1;
	}
	pos = left;
	while (pos <= right && page.index[pos].key <= key) {
        if (page.index[pos].key == key)
            return true;
        pos++;
	}
	return false;
}

BTree::Header BTree::readHeader() {
    // open the file
    fstream bTree;
    bTree.open(indexFile, fstream::in| fstream::binary);

    // read the header
    Header header;
	bTree.read((char*)&header, sizeof(header));
    //Verify is index fil exist
	if (!bTree){
    	header.rrnRoot = -1;
    	return header;
    }

    bTree.close();

    return header;
}

void BTree::printTree() {
    // read the header
    Header header = readHeader();
    //Verify is index fil exist
    if(header.rrnRoot == -1){
    	logFile->emptyIndex();
    	return;
    }

    // print initial phrase
    cout << "Execucao de operacao para mostrar a arvore-B gerada:" << endl;

    // create a queue of nodes to print
    Queue queue;

    // add the root node
    queue.push(header.rrnRoot, 0);

    // print elements until queue is empty
    while (!queue.isEmpty()) {

        // get first queue element
        int rrn, level;
        queue.pop(rrn, level);

        // read the node
        Node node = readPage(rrn);

        // print page level
        cout << level << ' ';

        // print number of elements
        cout << node.nIndexes << ' ';

        // print each element
        for (int i = 0; i < node.nIndexes; i++)
            cout << '<' << node.index[i].key << '/' << node.index[i].byteOS << "> ";
        cout << endl;

        // add the children to the queue
        for (int i = 0; i <= node.nIndexes; i++) {
            if (node.children[i] != NIL)
                queue.push(node.children[i], level+1);
        }
    }
}

string BTree::getIndexFile(){
	string url(indexFile);
	return url;
}
