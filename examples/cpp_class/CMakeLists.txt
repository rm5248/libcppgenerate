include( ../examples-common.cmake )

link_directories( ${CMAKE_BINARY_DIR} )
add_executable( cpp_class cpp_class.cpp )
target_link_libraries( cpp_class cppgenerate )
target_include_directories( cpp_class PUBLIC ${CMAKE_SOURCE_DIR} )
