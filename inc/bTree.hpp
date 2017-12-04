#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <string>
#include <fstream>
#define BT_ORDER 5
#define NIL -1

using namespace std;

typedef int key_t;

class BTree{
    private:

        typedef struct{
            //key
            key_t key;
            //byte offset in the data file
            int byteOS;
        } Index;

        typedef struct{
            //number of indexes
            int nIndexes;
            //pairs of key and byte offset
            Index index[BT_ORDER-1];
            //rrn from the children
            int children[BT_ORDER];
            //is true if the Node is a leaf
            bool isLeaf;
        } Node;

        //index file url
        const char* indexFile;
        
        //rrn of tree root node
        int root;

    public:

        //constructor
        BTree(const char* url);

        void insertIndex(key_t id, int byteOS);

        //return the byte offset of the searched block in the datafile
        int searchIndex(key_t id);

        void removeIndex(key_t id);

        void updateHeader(bool updated, int root);

        void updateHeader(bool updated);

        void updateHeader(int root);

        bool isUpdated();

        BTree::Node readPage(int rrn);

        void writePage(Node node, int rrn);

        int writePage(Node page);

        void createLeaf(Node &page);

        int createFile();

        void addIndexPage(Node &page, Index &toAdd);

        void indexExtended(Index *reciver, Index &toAdd);

        int insert(int rrn, Index &toAdd, Index &promoIndex, int &promoChild);

        void split(Index &key, int &rrn, Node &page, Index &promoIndex, int &promoChild, Node &newPage);

        bool binarySearch(Node page, int key, int &pos);
};

#endif /* end of include guard: BTREE_HPP */
