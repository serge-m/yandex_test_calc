#ifndef parser_h__
#define parser_h__

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std; // убрать из хедера

class Parser
{
public:

    typedef string StackElement;
    typedef vector<StackElement> Stack;
    typedef vector<double> StackForCalculations;

    static const string eol;
    Parser();
    virtual ~Parser();
    double Parse( const std::string & s );


    void GetExpression2( string s );

    bool IsPositiveInteger(const std::string& s);

    int Priority( string s );
    bool IsOperation( string s );
    string GetPiece( const std::string & s );
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
