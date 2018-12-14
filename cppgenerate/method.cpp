#include <utility>
#include <ostream>

#include <iostream>

#include "method.h"
#include "class.h"
#include "cppgenerateutils.h"

using cppgenerate::Method;

Method::Method() : 
    m_returnType( "void" ),
    m_access( cppgenerate::AccessModifier::PRIVATE ){
    m_code.setIndent( 4 );
}

Method::Method( const Method& other ){
    m_name = other.m_name;
    m_returnType = other.m_returnType;
    m_documentation = other.m_documentation;
    m_arguments = other.m_arguments;
    m_code = other.m_code;
    m_access = other.m_access;
}

Method::~Method(){
}

Method& Method::operator=( const Method& other ){
    if( this != &other ){
        m_name = other.m_name;
        m_returnType = other.m_returnType;
        m_documentation = other.m_documentation;
        m_arguments = other.m_arguments;
        m_code = other.m_code;
        m_access = other.m_access;
    }

    return *this;
}

bool Method::isValid() const {
    return m_name.size() > 1 && m_returnType.size() > 1;
}

Method& Method::setName( std::string name ){
    m_name = name;

    return *this;
}

Method& Method::setReturnType( std::string returnType ){
    m_returnType = returnType;

    return *this;
}

Method& Method::addArgument( const Argument& arg ){
    m_arguments.push_back( arg );
    
    return *this;
}

Method& Method::setDocumentation( std::string documentation ){
    m_documentation = documentation;

    return *this;
}

Method& Method::addCode( const CodeBlock& block ){
    m_code << block;

    return *this;
}

Method& Method::setCode( const CodeBlock& block ){
    m_code = block;

    return *this;
}

void Method::printSignature( std::ostream& stream, int indent, bool withAccessModifier ) const {
    if( !isValid() ) return;

    if( withAccessModifier ){
        switch( m_access ){
        case cppgenerate::AccessModifier::PRIVATE: stream << "private:" << std::endl; break;
        case cppgenerate::AccessModifier::PUBLIC: stream << "public:" << std::endl; break;
        case cppgenerate::AccessModifier::PROTECTED: stream << "protected:" << std::endl; break;
        }
    }

    if( m_documentation.length() > 1 ){
        cppgenerate::insertSpaces( stream, indent );
        stream << "/** " << m_documentation << " */" << std::endl;
    }

    cppgenerate::insertSpaces( stream, indent );
    printMethodSignature( stream, "" );

    stream << ";" << std::endl;
}

void Method::printImplementation( const cppgenerate::Class* parent, std::ostream& stream ) const{
    if( !isValid() ) return;

    printMethodSignature( stream, parent->getName() );

    stream << "{" << std::endl;

    stream << m_code << std::endl;
    stream << "}" << std::endl;
}

Method Method::create(){
    return Method();
}

void Method::printMethodSignature( std::ostream& stream, std::string className ) const {
    bool addComma = false;

    stream << m_returnType << " ";

    if( className.size() > 0 ){
        stream << className << "::";
    }

    stream << m_name << "(";

    for( Argument argument : m_arguments ){
        if( addComma ) stream << ", ";
        stream << argument;
        addComma = true;
    }

    stream << " )";
}

std::vector<cppgenerate::Argument> Method::arguments() const {
    return m_arguments;
}

std::string Method::name() const{
    return m_name;
}

std::string Method::returnType() const {
    return m_returnType;
}

Method& Method::setAccessModifier( AccessModifier modifier ){
    m_access = modifier;

    return *this;
}

cppgenerate::AccessModifier Method::accessModifier() const{
    return m_access;
}
