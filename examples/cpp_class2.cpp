#include <cppgenerate/class.h>
#include <cppgenerate/membervariable.h>
#include <iostream>

int main(int argc, char** argv){
    cppgenerate::Class c( "Example2" );

    c.addSystemInclude( "string" )
     .setDocumentation( 
"This example class does nothing useful\n\
except to show how the library can generate\n\
useful code for us with member variables" )
      .addMemberVariable( cppgenerate::MemberVariable::create()
          .setAccessModifier( cppgenerate::MemberVariable::AccessModifier::ACCESS_PROTECTED )
          .setType( "int" )
          .setName( "m_exampleInt" ) )
      .addMemberVariable( cppgenerate::MemberVariable::create()
          .setAccessModifier( cppgenerate::MemberVariable::AccessModifier::ACCESS_PRIVATE )
          .generateGetter( true )
          .generateSetter( true )
          .setType( "double" )
          .setName( "m_exampleDouble" ) );

    //For this simple class, we only print the 
    //generated code to stdout
    c.print( std::cout, std::cout );
}
