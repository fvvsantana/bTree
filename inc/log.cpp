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
		if (!lFile){
			cerr << "Nao foi possivel criar o arquivo de log.\n";
			return;
		}
		writeLog("Arquivo de log criado.");
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
		  << setfill('0') << setw(2) << now->tm_sec << "   "
		  << text.data() << "\n";
	//Close the file
	lFile.close();
}

void Log::createIndexLog(string index, string data){
	ostringstream ss;

	ss << "Execucao da criacao do arquivo de indice " << index << " com base no arquivo de dados " << data << '.';

	writeLog(ss.str().c_str());
}

void Log::insertSongLog(int id, string title, string genre){
	ostringstream ss;

	ss << "Execucao de operacao de INSERCAO de no arquivo de dados de " << id << ", " << title << ", " << genre << '.';

	writeLog(ss.str().c_str());
}

void Log::nodeDivisionLog(int rrn){
	ostringstream ss;

	ss << "Divisao de no - " << rrn << " pagina.";

	writeLog(ss.str().c_str());	
}

void Log::promotionLog(int id){
	ostringstream ss;

	ss << "Chave " << id << " promovida.";

	writeLog(ss.str().c_str());	
}

void Log::insertSuccesLog(int id){
	ostringstream ss;

	ss << "Chave " << id << " inserida com sucesso.";

	writeLog(ss.str().c_str());
}

void Log::insertDuplicated(int id){
	ostringstream ss;

	ss << "Chave " << id << " duplicada.";

	writeLog(ss.str().c_str());

}

void Log::searchLog(int id){
	ostringstream ss;

	ss << "Execucao de operacao de PESQUISA de " << id << '.';

	writeLog(ss.str().c_str());
}

void Log::searchSuccesLog(int id, int byteOS, string title, string genre){
	ostringstream ss;

	ss << "Chave " << id << " encontrada, offset " << byteOS << ", Título: " 
	   << title << ", Genero: " << genre << '.';

	writeLog(ss.str().c_str());
}

void Log::searchFailLog(int id){
	ostringstream ss;

	ss << "Chave " << id << " nao encontrada.";

	writeLog(ss.str().c_str());
}

void Log::createFileErrorLog(){
	ostringstream ss;

	ss << "Nao foi possivel criar o arquivo de indice";

	writeLog(ss.str().c_str());
}

void Log::emptyIndex(){
	ostringstream ss;

	ss << "O arquivo de indice não existe.";

	writeLog(ss.str().c_str());	
}

void Log::noDataFile(){
	ostringstream ss;

	ss << "O arquivo de dados não existe.";

	writeLog(ss.str().c_str());	
}
void Log::insertIndex(int id){
	ostringstream ss;

	ss << "Execucao de operacao de INSERCAO no arquivos de indice de " << id << '.';

	writeLog(ss.str().c_str());
}