#include <cppgenerate/enum.h>
#include <iostream>

#include "test_enum.h"
#include "test_macros.h"
#include "generatorhelper.h"
#include "testinterface.h"

bool TestEnum::test_setName(){
    cppgenerate::Enum e;

    e.setName( "NEWNAME" );

    return TEST_STREQUALS( "NEWNAME", e.getName() );
}

bool TestEnum::test_setNameWithSpaces(){
    cppgenerate::Enum e;

    e.setName( "NEW NAME" );

    return TEST_STREQUALS( "NEW_NAME", e.getName() );
}

bool TestEnum::test_setNameBadChars(){
    cppgenerate::Enum e;

    e.setName( "}FOO{" );

    return TEST_STREQUALS( "_FOO_", e.getName() );
}

bool TestEnum::test_addSingleValue(){
    cppgenerate::Enum e;

    e.addEnumValue( "foobar", 5 );

    std::map<std::string, int> values = e.getEnumNameToValues();

    return TEST_EQUALS( values["foobar"], 5 );
}

bool TestEnum::test_addMultipleValues(){
    cppgenerate::Enum e;

    e.addEnumValue( "what", 6 );
    e.addEnumValue( "stoop" );

    std::map<std::string, int> values = e.getEnumNameToValues();

    return TEST_EQUALS( values["stoop"], 7 );
}

bool TestEnum::test_generate1(){
    GeneratorHelper helper( "generate_enum1", getCMakeBinaryDir(), getCMakeCommand(), getCMakeGenerator() );
    return helper.generateAndBuild();
}
