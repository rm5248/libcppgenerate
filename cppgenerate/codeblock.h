#ifndef CPPGENERATE_CODEBLOCK_H
#define CPPGENERATE_CODEBLOCK_H

#include <string>
#include <sstream>

namespace cppgenerate{

class CodeBlock{
public:
    CodeBlock();

    CodeBlock( const CodeBlock& other );

    CodeBlock& operator=( const CodeBlock& other );

    CodeBlock& indent();

    CodeBlock& unindent();

    CodeBlock& setIndent( int indent );

    /**
     * Add a line of code to this block
     */
    CodeBlock& addLine( std::string line );

    void print( std::ostream& writer ) const;

    /**
     * Get the internal buffer for this code block
     */
    std::ostringstream& buffer();

private:
    std::ostringstream m_text;
    int m_indent;
};

}

#endif /* CPPGENERATE_CODEBLOCK_H */
