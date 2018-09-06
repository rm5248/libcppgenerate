/*
 *
 */

#include <string>
#include <vector>
#include <set>

#include "method.h"
#include "membervariable.h"

#ifndef CPPGENERATE_CLASS_H
#define CPPGENERATE_CLASS_H

namespace cppgenerate{

/**
 * A cppgenerate::Class contains information about the
 * class that is to be created. 
 */
class Class{
  public:
    Class();

    /**
     * Create a Class with the specified name.
     */
    Class( const std::string name );

    /**
     * Copy constructor
     */
    Class( const Class& other );

    ~Class();

    Class& operator=( const Class& other );

    /**
     * Checks to see if this class is valid.  A valid class
     * has at least a name.
     */
    bool isValid() const;

    /**
     * Get the fully qualified name of the class, including the namespaces.
     */
    std::string getFullyQualifiedName() const;

    /**
     * Get the name of this class
     */
    std::string getName() const;

    /**
     * Set the namespace for this class.
     */
    Class& setNamespace( std::string namespaceName );

    /**
     * Add an include file to this class.
     * Will generate an #include <includeFile> directive
     */
    Class& addSystemInclude( std::string includeFile );

    /**
     * Add multiple includes to the class
     * Will generate an #include <includeFile> directive
     */
    Class& addSystemIncludes( std::vector<std::string> includeFiles );

    /**
     * Add an include file to this class.
     * Will generate an #include "includeFile" directive
     */
    Class& addLocalInclude( std::string includeFile );

    /**
     * Add an include file to this class.
     * Will generate an #include "includeFile" directive
     */
    Class& addLocalIncludes( std::vector<std::string> includeFiles );

    /**
     * Add a method to the class
     */
    Class& addMethod( const Method& func );

    /**
     * Add a member variable to this class
     */
    Class& addMemberVariable( const MemberVariable& var );

    /**
     * Attempts to add a variable as a member variable.
     * This method does a dynamic_cast of the Varaible, and thus may fail
     * at runtime.
     */
    Class& addMemberVariable( const Variable& var );

    /**
     * Set the documentation for this class
     */
    Class& setDocumentation( const std::string documentation );

    /**
     * Set if this class is a QObject at all.  If it is,
     * the QObject header is implicitly added to the system includes,
     * and the Q_OBJECT macro will be output to ensure that moc
     * runs properly.
     */
    Class& setIsQObject( const bool isQObject );

    /**
     * Print this class to the output stream specified.  The header
     * is always printed before the class functions, so that they can
     * be in the same file.
     *
     * @param header The output stream to write the header to
     * @param implementation The output stream to write the
     * implementation to
     */
    void print( std::ostream& header, std::ostream& implementation ) const;

    static Class create();

private:
    void printHeader( std::ostream& header ) const;
    void printImplementation( std::ostream& implementation ) const;

private:
    std::string m_className;
    std::string m_namespace;
    std::set<std::string> m_systemIncludes;
    std::set<std::string> m_localIncludes;
    std::vector<Method> m_methods;
    std::vector<MemberVariable> m_memberVariables;
    std::string m_documentation;
    bool m_isQobject;
};

}

#endif /* CPPGENERATE_CLASS_H */
