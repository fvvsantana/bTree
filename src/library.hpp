#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "../inc/bTree.hpp"
#include "../inc/log.hpp"

typedef int key_t;


typedef struct{
    key_t id;
    string title;
    string genre;
}Song;

class Library{
    private:
        BTree* tree;
        Log* logFile;
        string dataFile;

    public:
        //constructor
        Library();

        //destructor
        ~Library();

        bool generateIndex();

        //insert the song in the btree and in the datafile
        void insertSong(Song song);

        Song searchSong(key_t id);

        void showBTree();

        string getDataFile();

        int integerDigits(int id);
};

#endif /* end of include guard: LIBRARY_HPP */
