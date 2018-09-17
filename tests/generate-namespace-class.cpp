#include <cppgenerate/class.h>
#include <iostream>
#include <fstream>

int main(){
    cppgenerate::Class c( "FooClass" );

    c.setNamespace( "Bar" );
    
    std::ofstream header;
    header.open( "namespace-class.h" );

    std::ofstream cpp;
    cpp.open( "namespace-class.cpp" );

    c.print( header, cpp );

    header.close();
    cpp.close();
}
