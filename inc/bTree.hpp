#ifndef BTREE_HPP
#define BTREE_HPP

#include <string>
#define BT_ORDER 5

using namespace std;

typedef int key_t;

class BTree{
    private:
        typedef struct{
            //indicate if the index is updated regarding to the datafile
            bool updated;
        } Header;

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
        string indexFile;

    public:

        //constructor
        BTree(string url);

        void insertIndex(key_t id, int byteOS);

        //return the byte offset of the searched block in the datafile
        int searchIndex(key_t id);

        void removeIndex(key_t id);

        void updateHeader(bool updated);

        bool isUpdated();
};

#endif /* end of include guard: BTREE_HPP */
