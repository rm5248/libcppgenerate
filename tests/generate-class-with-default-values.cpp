#include <cppgenerate/class.h>
#include <iostream>
#include <fstream>

#include "generator_util.h"

int main( int argc, char** argv ){
    optional_chdir( argc, argv );

    cppgenerate::Class c( "ClassWithDefaultValues" );

    c.addConstructor( cppgenerate::Constructor::create()
        .addArgument( cppgenerate::Argument::create()
            .setType( "std::string" )
            .setName( "fooArg" )
            .setDefaultValue( "\"foo\"" )
        )
    );

    c.addMethod( cppgenerate::Method::create()
        .setName( "foomethod" )
        .addArgument( cppgenerate::Argument::create()
            .setType( "std::string" )
            .setName( "fooArg" )
            .setDefaultValue( "\"foo\"" )
        )
    );

    c.addSystemInclude( "string" );

    std::ofstream header;
    header.open( "ClassWithDefaultValues.h" );

    std::ofstream cpp;
    cpp.open( "ClassWithDefaultValues.cpp" );

    c.print( header, cpp );

    header.close();
    cpp.close();
}
