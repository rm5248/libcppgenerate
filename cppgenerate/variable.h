#ifndef CPPGENERATE_VARIABLE_H
#define CPPGENERATE_VARIABLE_H

#include <string>

namespace cppgenerate{

/**
 * Represents a variable in the generated code.
 */
class Variable{
  public:
    Variable();

    virtual ~Variable();

    Variable& operator=( const Variable& other );

    Variable& setInitializer( std::string initializer );

    Variable& setType( std::string type );

    Variable& setName( std::string name );

};

}

#endif /* CPPGENERATE_VARIABLE_H */
