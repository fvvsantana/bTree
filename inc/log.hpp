#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>


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
};


#endif /* end of include guard: LOG_HPP */
