#include "global_variable.h";
#include "pch.h";

int globalVariable = 0;
std::mutex globalVariableMutex;

std::string currentIniPath;
std::mutex currentIniPathMutex;

void writeGlobalVariable(int value)
{
	std::lock_guard<std::mutex> lock(globalVariableMutex);
	globalVariable = value;
}

int readGlobalVariable()
{
	std::lock_guard<std::mutex> lock(globalVariableMutex);
	return globalVariable;	
}

void writeIniPath(std::string path)
{
	std::lock_guard<std::mutex> lock(currentIniPathMutex);
	currentIniPath = path;
}

std::string readIniPath()
{
	std::lock_guard<std::mutex> lock(currentIniPathMutex);
	return currentIniPath;

}