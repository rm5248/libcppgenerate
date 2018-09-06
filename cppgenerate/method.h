#ifndef CPPGENERATE_METHOD_H
#define CPPGENERATE_METHOD_H

#include <string>
#include <list>

#include "codeblock.h"
#include "argument.h"

namespace cppgenerate{

class Class;

/**
 * Represents a single method, generally on a class
 */
class Method{
  public:

    Method();

    Method( const Method& other );

    ~Method();

    Method& operator=( const Method& other );

    /**
     * Checks to see if this method is valid.  A method is valid if it
     * has a name.
     */
    bool isValid() const;

    /**
     * Set the name of this method
     */
    Method& setName( std::string name );

    Method& setReturnType( std::string returnType );

    /**
     * Add an argument to the method
     */
    Method& addArgument( const Argument& arg );

    /**
     * Set the documentation for the method
     */
    Method& setDocumentation( std::string documentation );

    /**
     * Add a block of code.  Appends to the currently existing code.
     */
    Method& addCode( const CodeBlock& block );

    /**
     * Set the code for this method
     */
    Method& setCode( const CodeBlock& block );

    /**
     * Print the method signature to the specified stream
     */
    void printSignature( std::ostream& stream ) const;

    /**
     * Print the method implementation to the specified stream
     */
    void printImplementation( const Class* parent, std::ostream& stream ) const;

    static Method create();

  private:
    void printMethodSignature( std::ostream& stream, std::string className ) const;

  private:
    std::string m_name;
    std::string m_returnType;
    std::string m_documentation;
    std::list<Argument> m_arguments;
    CodeBlock m_code;
};

}

#endif /* CPPGENERATE_METHOD_H */
