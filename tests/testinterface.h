#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H

#include <string>

/**
 * A simple interface that runs a test and restuns the result
 */
typedef bool (*TestMethod)();

void setCMakeCommand( std::string cmakeCommand );
void setCMakeGenerator( std::string cmakeGenerator );
void setCMakeBinaryDir( std::string cmakeBinaryDir );
std::string getCMakeCommand();
std::string getCMakeGenerator();
std::string getCMakeBinaryDir();

#endif /* TEST_INTERFACE_H */
