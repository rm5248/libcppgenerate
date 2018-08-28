#include <map>
#include <iostream>
#include <apr_general.h>

#include "testinterface.h"
#include "tests/test_enum.h"

static std::map<std::string, TestMethod > tests;

static void initialize_test_map(){
    tests[ "enum_setName" ] = &TestEnum::test_setName;
    tests[ "enum_setNameWithSpaces" ] = &TestEnum::test_setNameWithSpaces;
    tests[ "enum_setNameBadChars" ] = &TestEnum::test_setNameBadChars;
    tests[ "enum_addSingleValue" ] = &TestEnum::test_addSingleValue;
    tests[ "enum_addMultipleValues" ] = &TestEnum::test_addMultipleValues;
    tests[ "enum_generate1" ] = &TestEnum::test_generate1;
}

int main( int argc, char** argv ){
    //We are going to have a very simple command line parsing here,
    //just enough to tell us which test to run.
    std::string cmakeCommand;
    std::string cmakeGeneratorType;
    std::string cmakeCurrentBinaryDir;
    std::string testToRun;

    if( argc != 5 ){
        std::cerr << "Need at least 5 args to run test" << std::endl;
        return 1;
    }

    //for( int x = 0; x < argc; x++ ){
    //    std::cout << "Arg " << x << ": " << argv[ x ] << std::endl;
    //}

    cmakeCommand = std::string( argv[ 1 ] );
    cmakeGeneratorType = std::string( argv[ 2 ] );
    cmakeCurrentBinaryDir = std::string( argv[ 3 ] );
    testToRun = std::string( argv[ 4 ] );
    setCMakeCommand( cmakeCommand );
    setCMakeGenerator( cmakeGeneratorType );
    setCMakeBinaryDir( cmakeCurrentBinaryDir );

    apr_initialize();
    initialize_test_map();

    TestMethod methodToTest = nullptr;

    std::map<std::string, TestMethod >::iterator it = tests.find( testToRun );
    if( it == tests.end() ){
        std::cerr << "Test with name " << testToRun << " not found" << std::endl;
        return 1;
    }

    methodToTest = (*it).second;

    int ret = !methodToTest();
    apr_terminate();
    return ret;
}
