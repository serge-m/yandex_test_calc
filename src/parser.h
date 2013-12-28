#ifndef parser_h__
#define parser_h__

#include <string>
#include <vector>

class Parser
{
public:
    Parser();
    virtual ~Parser();
    double Parse( const std::string & s );

private:
    typedef std::string StackElement;
    typedef std::vector<StackElement> Stack;
    typedef std::vector<double> StackForCalculations;

    static const std::string eol;
    

    void GetExpression2( std::string s );

    bool IsPositiveInteger(const std::string& s);

    int Priority( std::string s );
    bool IsOperation( std::string s );
    StackElement GetPiece( const std::string & s );
    typedef enum
    {
        CLASS_ALPHA,
        CLASS_NUM,
        CLASS_OPERATION,
        CLASS_SPACE,
        CLASS_UNKNOWN,
    } SymbolClass;
    SymbolClass GetSymbolClass( char symbol );
   
    double CalcExpression( Stack st );
   
    double CalcOperation( StackElement op, StackForCalculations & s );
   
    double GetNumberFromStack( StackForCalculations & s );
    double GetNumberFromString( StackElement se );
private:
    int pos_;
    Stack res_;
    Stack operations_;
};

#endif // parser_h__
