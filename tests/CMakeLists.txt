# This file is part of libcppgenerate

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( TESTING_SRC
  test_main.cpp
  test_enum.cpp
)
set( TESTING_HEADERS
  testinterface.h
  test_enum.h
  test_macros.h
)

add_executable( run_tests ${TESTING_SRC} ${TESTING_HEADERS} )
target_include_directories( run_tests SYSTEM PRIVATE ${CMAKE_SOURCE_DIR} )
target_link_libraries( run_tests cppgenerate )

# A list of all of the test names that we can run
set( TEST_NAMES
  enum_setName
  enum_setNameWithSpaces
  enum_setNameBadChars
)

foreach( test_name ${TEST_NAMES} )
    add_test( NAME ${test_name} COMMAND 
      run_tests 
      "${CMAKE_COMMAND}"
      "${CMAKE_GENERATOR}"
      ${test_name}
    )
endforeach( test_name )
