#include <ostream>

#include "membervariable.h"

using cppgenerate::MemberVariable;

MemberVariable::MemberVariable() :
    m_access( AccessModifier::ACCESS_PUBLIC ),
    m_generateGetter( false ),
    m_generateSetter( false ),
    m_isQProperty( false ){
}

MemberVariable::~MemberVariable(){
}

MemberVariable::MemberVariable( const MemberVariable& other ){
    m_access = other.m_access;
    m_generateGetter = other.m_generateGetter;
    m_generateSetter = other.m_generateSetter;
    m_isQProperty = other.m_isQProperty;
}

MemberVariable& MemberVariable::operator=( const MemberVariable& other ){
    if( this != &other ){
        m_access = other.m_access;
        m_generateGetter = other.m_generateGetter;
        m_generateSetter = other.m_generateSetter;
        m_isQProperty = other.m_isQProperty;
        m_changedSignalName = other.m_changedSignalName;
    }

    return *this;
}

MemberVariable& MemberVariable::setAccessModifier( AccessModifier modifier ){
    m_access = modifier;
    return *this;
}

MemberVariable& MemberVariable::generateSetter( bool generateSetter ){
    m_generateSetter = generateSetter;
    return *this;
}

MemberVariable& MemberVariable::generateGetter( bool generateGetter ){
    m_generateGetter = generateGetter;
    return *this;
}

MemberVariable& MemberVariable::isQProperty( bool isQproperty ){
    m_isQProperty = isQproperty;
    return *this;
}

MemberVariable& MemberVariable::setChangedSignalName( std::string signalName ){
    m_changedSignalName = signalName;
    return *this;
}

void MemberVariable::print( std::ostream& stream ){
    switch( m_access ){
    }
}
