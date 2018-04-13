#include "enum.h"
#include "cppgenerateutils.h"

using cppgenerate::Enum;

Enum::Enum() :
    m_isEnumClass( false )
{}

Enum::Enum( const Enum& other ){
}

Enum::~Enum(){
}

Enum& Enum::setName( std::string name ){
    m_name = cppgenerate::sanitizeString( name );
    return *this;
}

std::string Enum::getName(){
    return m_name;
}

Enum& Enum::setIsEnumClass( bool isClass ){
    m_isEnumClass = isClass;
    return *this;
}

Enum& Enum::addEnumValue( std::string name, int value ){
    m_enumNameToValue[ name ] = value;
    return *this;
}

Enum& Enum::addEnumValue( std::string name ){
    int maxValue = 0;
    std::map<std::string,int>::const_iterator it = m_enumNameToValue.begin();

    while( it != m_enumNameToValue.end() ){
        int currentValue = (*it).second;
        if( currentValue > maxValue ){
            maxValue = currentValue;
        }
        it++;
    }

    return addEnumValue( name, maxValue + 1 );
}
