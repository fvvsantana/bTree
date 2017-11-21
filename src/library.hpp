#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "../inc/bTree.hpp"

typedef string key_t;

typedef struct{
    string id;
    string title;
    string genre;
} Song;

class Library{
    private:
        BTree* tree;
        string dataFile;

    public:
        //constructor
        Library();

        //destructor
        ~Library();

        void generateIndex();

        //insert the song in the btree and in the datafile
        void insertSong(Song& song);

        Song* searchSong(key_t id);

        void removeSong(key_t id);

        void showBTree();
};

#endif /* end of include guard: LIBRARY_HPP */
