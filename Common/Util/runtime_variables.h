#pragma once

#include <mutex>

// Global variables
extern int globalVariable;
extern std::mutex globalVariableMutex;

extern int globalVariable;
extern std::mutex globalVariableMutex;

extern std::string currentIniPath;
extern std::mutex currentIniPathMutex;

// Function declarations
void writeGlobalVariable(int value);
int readGlobalVariable();

void writeIniPath(std::string value);
std::string readIniPath();

