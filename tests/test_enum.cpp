#include <cppgenerate/enum.h>

#include "test_enum.h"
#include "test_macros.h"

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
