#include "cppgenerateutils.h"

static char sanitizeChar( char c ){
    if( c >= 'A' && c <= 'z' ){
        return c;
    }else if( c >= '0' && c <= '9' ){
        return c;
    }else{
        return '_';
    }
}

std::string cppgenerate::sanitizeString( std::string input ){
    std::string newString;

    //Make sure that we only have valid chars.  A-Z, a-z, 0-9, _
    std::string::const_iterator it = input.begin();
    while( it != input.end() ){
        char c = *it;
        newString.push_back( sanitizeChar( c ) );
        it++;
    }

    return newString;
}
