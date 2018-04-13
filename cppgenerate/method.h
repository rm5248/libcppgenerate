/*
 *
 */

#ifndef CPPGENERATE_METHOD_H
#define CPPGENERATE_METHOD_H

#include <string>

namespace cppgenerate{

/**
 * Represents a single method, generally on a class
 */
class Method{
  public:
    Method();

    /**
     * Create a method with the specified name.
    */
    Method( std::string name );

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
};

}

#endif /* CPPGENERATE_METHOD_H */
