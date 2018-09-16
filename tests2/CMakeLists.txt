add_custom_command( 
    OUTPUT generated-class1.h generated-class1.cpp
    COMMAND generate-class1
    VERBATIM )

add_custom_target( generator-class1 DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated-class1.h ${CMAKE_CURRENT_BINARY_DIR}/generated-class2.cpp )

link_directories( ${CMAKE_BINARY_DIR} )

add_executable( generate-class1 generate-class1.cpp )
target_link_libraries( generate-class1 cppgenerate )
target_include_directories( generate-class1 PUBLIC ${CMAKE_SOURCE_DIR} )

add_executable( test1 test1.cpp )
target_link_libraries( test1 cppgenerate )
target_include_directories( test1 PUBLIC ${CMAKE_SOURCE_DIR} )
target_include_directories( test1 PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )

add_dependencies( test1 generate-class1 generator-class1 )

add_test( NAME test1 COMMAND 
    test1 )
