# This file is part of libcppgenerate

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( TESTING_SRC
  test_main.cpp
  test_enum.cpp
  generatorhelper.cpp
  testinterface.cpp
)
set( TESTING_HEADERS
  testinterface.h
  test_enum.h
  test_macros.h
  generatorhelper.h
)

#
# Check for APR and APR-UTIL
#
if( UNIX )
	include(FindPkgConfig)

	pkg_check_modules(APR REQUIRED apr-1)
	pkg_check_modules(APR_UTIL REQUIRED apr-util-1)
endif( UNIX )

# On Windows, ask for the path to where APR and APR-util are installed
if(WIN32)
	set(APR_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
	set(APR_LIBRARIES "${CMAKE_INSTALL_PREFIX}/lib/libapr-1.lib")
	set(APR_UTIL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
	set(APR_UTIL_LIBRARIES "${CMAKE_INSTALL_PREFIX}/lib/libaprutil-1.lib")
endif()

add_executable( run_tests ${TESTING_SRC} ${TESTING_HEADERS} )
target_include_directories( run_tests SYSTEM PRIVATE ${CMAKE_SOURCE_DIR} )
include_directories( ${APR_INCLUDEDIR} ${APR_UTIL_INCLUDEDIR} )
target_link_libraries( run_tests cppgenerate ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES} )

# A list of directories that need to be copied for tests to run
set( TEST_DIRS
  generate_enum1
)

# Copy all test directories to build directory
foreach( dir_name ${TEST_DIRS} )
    file( COPY ${dir_name} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
endforeach( dir_name )

# A list of all of the test names that we can run
set( TEST_NAMES
  enum_setName
  enum_setNameWithSpaces
  enum_setNameBadChars
  enum_addSingleValue
  enum_addMultipleValues
#  enum_generate1
)

foreach( test_name ${TEST_NAMES} )
    add_test( NAME ${test_name} COMMAND 
      run_tests 
      "${CMAKE_COMMAND}"
      "${CMAKE_GENERATOR}"
      "${CMAKE_CURRENT_BINARY_DIR}"
      ${test_name}
    )
endforeach( test_name )
