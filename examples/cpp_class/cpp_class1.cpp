#include <cppgenerate/class.h>
#include <iostream>

int main(int argc, char** argv){
    cppgenerate::Class c( "FooClass" );

    c.setNamespace( "Bar" )
     .addSystemInclude( "string" );

    c.print( std::cout, std::cout );
}
