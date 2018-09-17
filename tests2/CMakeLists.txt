include(./cppgenerate-test-util.cmake)

#add_cppgenerate_test("${test1_generator_name}" "${test1_generated_files}" "${test1_name}")
add_cppgenerate_test( generate-class1 "generated-class1.h generated-class1.cpp" test1)

#
# Enum tests
#
add_cppgenerate_test_simple( enum_name )
add_cppgenerate_test_simple( enum_with_space )
add_cppgenerate_test_simple( enum_single_value )
add_cppgenerate_test_simple( enum_multiple_value )
add_cppgenerate_test_simple( enum_name_bad_chars )
