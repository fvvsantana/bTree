#include "song.hpp"

Song::Song(key_t id, string& title, string& genre){
	this->id = id;
	this->title = title;
	this->genre = genre;
}

key_t Song::getId(){
	return id;
}

string Song::getTitle(){
	return title;
}

string Song::getGenre(){
	return genre;		
}

//Counts number of digits in an integer
int Song::integerDigits(int id){
	int counter = 1;
	while (id >= 10){
		
		id /= 10;
		counter++;
	}
	return counter;
}
