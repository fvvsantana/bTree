#include "log.hpp"


Log::Log(string directory){
	logFile = directory;
}


void Log::writeLog(string text){
	//Create a files stream
	fstream lFile;
	//Opens the file in read mode
	lFile.open(logFile.data(), fstream::in);
	//Ferify if file exist
	if(!lFile){
		lFile.open(logFile.data(), fstream::app);
		writeLog("Log file created.");
	}
	else{
		lFile.close();
		lFile.open(logFile.data(), fstream::app);
	}
	//Saves ter current GMT date and time
	time_t tme = time(0);
	struct tm* now = localtime(&tme);
	//Prints on log the date, time and text recived
	lFile << setfill('0') << setw(2) << now->tm_mday << '-'
		  << setfill('0') << setw(2) << now->tm_mon + 1 << '-' << now->tm_year + 1900 << "   "
		  << setfill('0') << setw(2) << now->tm_hour << ':' 
		  << setfill('0') << setw(2) << now->tm_min << ':'
		  << setfill('0') << setw(2) << now->tm_sec << "(GMT)" << "   "
		  << text.data() << "\n";
	//Close the file
	lFile.close();
}
