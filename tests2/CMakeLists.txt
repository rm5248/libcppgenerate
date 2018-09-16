# generator-name = generate-class1
# generated-files = generate-class1.h generate-class2.cpp
# test-name = test1
include(./cppgenerate-test-util.cmake)


set(test1_generator_name generate-class1)
set(test1_generated_files generated-class1.h generated-class1.cpp)
set(test1_name test1)

add_cppgenerate_test("${test1_generator_name}" "${test1_generated_files}" "${test1_name}")

