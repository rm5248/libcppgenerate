include( ../examples-common.cmake )

add_executable( cpp_class cpp_class.cpp )
target_link_libraries( cpp_class ${cppgenerate_LIBRARIES} )
