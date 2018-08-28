#include "class.h"
#include "cppgenerateutils.h"

#include <algorithm>

using cppgenerate::Class;

Class::Class() :
    m_isQobject( false ){
}

Class::Class( std::string name ) :
    m_className( name ),
    m_isQobject( false )
{}

Class::Class( const Class& other ) :
    m_className( other.m_className ),
    m_namespace( other.m_namespace ),
    m_systemIncludes( other.m_systemIncludes ),
    m_localIncludes( other.m_localIncludes ),
    m_methods( other.m_methods ),
    m_memberVariables( other.m_memberVariables ),
    m_documentation( other.m_documentation ),
    m_isQobject( other.m_isQobject )
{}

Class& Class::operator=( const Class& other ){
    if( this != &other ){
        m_className = other.m_className;
        m_namespace = other.m_namespace;
        m_systemIncludes.clear();
        m_systemIncludes = other.m_systemIncludes;
        m_localIncludes.clear();
        m_localIncludes = other.m_localIncludes;
        m_methods.clear();
        m_methods = other.m_methods;
        m_memberVariables.clear();
        m_documentation = other.m_documentation;
        m_isQobject = other.m_isQobject;
    }

    return *this;
}

bool Class::isValid() const {
    return m_className.size() > 1;
}

std::string Class::getFullyQualifiedName() const{
    std::string ret;

    if( m_namespace.size() > 1 ){
        ret += m_namespace;
        ret += "::";
    }
    ret += m_className;

    return ret;
}

std::string Class::getName() const{
    return m_className;
}

Class& Class::setNamespace( std::string namespaceName ){
    m_namespace = namespaceName;

    return *this;
}

Class& Class::addSystemInclude( std::string includeFile ){
    m_systemIncludes.insert( includeFile );

    return *this;
}

Class& Class::addSystemIncludes( std::vector<std::string> includeFiles ){
    for( std::string str : includeFiles ){
        m_systemIncludes.insert( str );
    }
        
    return *this;
}

Class& Class::addLocalInclude( std::string includeFile ){
    m_localIncludes.insert( includeFile );

    return *this;
}

Class& Class::addLocalIncludes( std::vector<std::string> includeFiles ){
    for( std::string str : includeFiles ){
        m_localIncludes.insert( str );
    }
        
    return *this;
}

Class& Class::addMethod( const Method& func ){
    m_methods.push_back( func );

    return *this;
}

Class& Class::addMemberVariable( const MemberVariable& var ){
    m_memberVariables.push_back( var );

    return *this;
}

Class& Class::setDocumentation( const std::string documentation ){
    m_documentation = documentation;

    return *this;
}

Class& Class::setIsQObject( const bool isQObject ){
    if( isQObject ){
        addSystemInclude( "QObject" );
    }

    m_isQobject = isQObject;

    return *this;
}
