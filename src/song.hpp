#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <iostream>

using namespace std;

typedef int key_t;

class Song{
	private:
		key_t id;
		string title;
		string genre;

	public:
		//Contructor
		Song(key_t id, string& title, string& genre);

		key_t getId();

		string getTitle();

		string getGenre();

		//Counts number of digits in an integer
		int integerDigits(int id);

};

#endif
