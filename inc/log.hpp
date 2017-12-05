#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>


using namespace std;

//maybe we can print the time every message printed
class Log{
    private:
		string logFile;
    
    public:
    	//Constructor
    	Log(string directory);

    	//Write a text in the log 
    	void writeLog(string text);

    	void createIndexLog(string index, string data);

		void insertSongLog(int id, string title, string genre);

		void nodeDivisionLog(int rrn);

		void promotionLog(int id);

		void insertSuccesLog(int id);

		void insertDuplicated(int id);

		void searchLog(int id);

		void searchSuccesLog(int id, int byteOS, string title, string genre);

		void searchFailLog(int id);

		void createFileErrorLog();
};


#endif /* end of include guard: LOG_HPP */
