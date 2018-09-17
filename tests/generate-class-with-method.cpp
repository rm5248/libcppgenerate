#include <cppgenerate/class.h>
#include <iostream>
#include <fstream>

int main(){
    cppgenerate::Class c( "FooClass" );

    c.addMethod( cppgenerate::Method::create()
        .setName( "exampleMethod" )
        .setAccessModifier( cppgenerate::AccessModifier::PUBLIC ) );
    
    std::ofstream header;
    header.open( "c-with-method.h" );

    std::ofstream cpp;
    cpp.open( "c-with-method.cpp" );

    c.print( header, cpp );

    header.close();
    cpp.close();
}
