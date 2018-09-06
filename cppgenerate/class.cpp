#include "class.h"
#include "cppgenerateutils.h"
#include "codeblock.h"

#include <algorithm>
#include <ostream>
#include <iostream>

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
    m_constructors( other.m_constructors ),
    m_parents( other.m_parents ),
    m_documentation( other.m_documentation ),
    m_isQobject( other.m_isQobject )
{}

Class::~Class(){
}

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
        m_constructors.clear();
        m_constructors = other.m_constructors;
        m_parents.clear();
        m_parents = other.m_parents;
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

Class& Class::setName( std::string name ){
    m_className = name;

    return *this;
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

Class& Class::addMemberVariable( const Variable& var ){
    const MemberVariable* memVar = dynamic_cast<const MemberVariable*>( &var );
    if( memVar ){
        m_memberVariables.push_back( *memVar );
    }

    return *this;
}

Class& Class::setDocumentation( const std::string documentation ){
    m_documentation = documentation;

    return *this;
}

Class& Class::setIsQObject( const bool isQObject ){
    if( isQObject ){
        addSystemInclude( "QObject" );
        addParentClass( "QObject", cppgenerate::AccessModifier::PUBLIC );
    }

    m_isQobject = isQObject;

    return *this;
}

Class Class::create(){
    return Class();
}

void Class::print( std::ostream& header, std::ostream& implementation ) const {
    printHeader( header );
    printImplementation( implementation );
}

void Class::printHeader( std::ostream& output ) const{
    cppgenerate::CodeBlock block;

    for( std::string include : m_systemIncludes ){
        output << "#include <" << include << ">" << std::endl;
    }

    for( std::string include : m_localIncludes ){
        output << "#include \"" << include << "\"" << std::endl;
    }

    if( m_namespace.size() > 1 ){
        output << m_namespace << " {" << std::endl;
    }

    if( m_documentation.size() > 0 ){
        block.addLine( "/*" )
            .addLine( m_documentation )
            .addLine( "*/" );
    }
    block.addLine( "class " + m_className );

    if( m_parents.size() > 0 ){
        bool comma = false;
        block.buffer() << " : ";
        for( Parent parent : m_parents ){
            if( comma ) block.buffer() << ", ";
            switch( parent.inheritanceType ){
            case cppgenerate::AccessModifier::PUBLIC:
                block.buffer() << "public ";
                break;
            case cppgenerate::AccessModifier::PROTECTED:
                block.buffer() << "protected ";
                break;
            default:
                break;
            }
            block.buffer() << parent.parentName << " ";
            comma = true;
        }
    }

    block.buffer() << "{" << std::endl;

    if( m_isQobject ){
        block.indent()
            .addLine( "Q_OBJECT" )
            .unindent();
    }

    for( cppgenerate::Constructor constructor : m_constructors ){
        constructor.printSignature( this, block.buffer() );
    }

    for( cppgenerate::Method method :  m_methods ){
        method.printSignature( block.buffer() );
    }

    for( cppgenerate::MemberVariable variable : m_memberVariables ){
        variable.print( block );
    }

    block.addLine( "};" );

    block.print( output );

    if( m_namespace.size() > 1 ){
        output << "} /* namespace " << m_namespace << " */" << std::endl;
    }
}

void Class::printImplementation( std::ostream& implementation ) const{
    for( cppgenerate::Constructor constructor : m_constructors ){
        constructor.printImplementation( this, implementation );
    }

    for( cppgenerate::Method method :  m_methods ){
        method.printImplementation( this, implementation );
    }
}

Class& Class::addConstructor( const Constructor& constructor ){
    m_constructors.push_back( constructor );

    return *this;
}

Class& Class::addParentClass( std::string parentName, cppgenerate::AccessModifier inheritanceType, std::string initializer ){
    Parent p;
    p.parentName = parentName;
    p.inheritanceType = inheritanceType;
    p.initializer = initializer;
    m_parents.push_back( p );

    return *this;

}

void Class::print( std::ostream& output ) const{
}
