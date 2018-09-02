#include <cppgenerate/class.h>

int main(int argc, char** argv){
    cppgenerate::Class c( "FooClass" );

    c.setNamespace( "Bar" )
     .addSystemInclude( "string" );
}
