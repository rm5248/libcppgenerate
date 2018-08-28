#include "testinterface.h"

static std::string m_cmakeCommand;
static std::string m_cmakeGenerator;
static std::string m_cmakeBinaryDir;

void setCMakeCommand( std::string cmakeCommand ){
    m_cmakeCommand = cmakeCommand;
}

void setCMakeGenerator( std::string cmakeGenerator ){
    m_cmakeGenerator = cmakeGenerator;
}

void setCMakeBinaryDir( std::string cmakeBinaryDir ){
    m_cmakeBinaryDir = cmakeBinaryDir;
}

std::string getCMakeCommand(){
    return m_cmakeCommand;
}

std::string getCMakeGenerator(){
    return m_cmakeGenerator;
}

std::string getCMakeBinaryDir(){
    return m_cmakeBinaryDir;
}
