#include <cppgenerate/class.h>

int main(int argc, char** argv){
    Class c( "FooClass" );

    c.setNamespace( "Bar" )
     .addSystemInclude( "string" );
}
