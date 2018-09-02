#include <utility>
#include <ostream>

#include "method.h"

using cppgenerate::Method;

Method::Method() : 
    m_returnType( "void" ){
}

Method::Method( const Method& other ){
    m_name = other.m_name;
    m_returnType = other.m_returnType;
    m_documentation = other.m_documentation;
    m_arguments = other.m_arguments;
}

Method::~Method(){
}

Method& Method::operator=( const Method& other ){
    if( this != &other ){
        m_name = other.m_name;
        m_returnType = other.m_returnType;
        m_documentation = other.m_documentation;
        m_arguments = other.m_arguments;
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

Method& Method::addArgument( std::string argumentType, std::string argumentName ){
    m_arguments.push_back( std::make_pair( argumentType, argumentName ) );
    
    return *this;
}

Method& Method::setDocumentation( std::string documentation ){
    m_documentation = documentation;

    return *this;
}

void Method::printSignature( std::ostream& stream ) const {
    bool addComma = false;

    if( !isValid() ) return;

    if( m_documentation.length() > 1 ){
        stream << "/** " << m_documentation << " */" << std::endl;
    }
    stream << m_returnType << " " << m_name << "(";

    for( std::pair<std::string, std::string> argument : m_arguments ){
        if( addComma ) stream << ", ";
        stream << argument.first << " " << argument.second;
        addComma = true;
    }

    stream << ");" << std::endl;
}

Method Method::create(){
    return Method();
}
