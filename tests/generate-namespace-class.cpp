#include <cppgenerate/class.h>
#include <iostream>
#include <fstream>

#include "generator_util.h"

int main( int argc, char** argv ){
    optional_chdir( argc, argv );

    cppgenerate::Class c( "NamespaceClass" );

    c.setNamespace( "Bar" );
    
    std::ofstream header;
    header.open( "NamespaceClass.h" );

    std::ofstream cpp;
    cpp.open( "NamespaceClass.cpp" );

    c.print( header, cpp );

    header.close();
    cpp.close();
}
