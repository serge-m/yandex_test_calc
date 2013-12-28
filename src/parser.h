#ifndef parser_h__
#define parser_h__

#include <string>

using namespace std; // убрать из хедера

class Parser
{
public:

    typedef enum 
    {
        STATE_START = 0,
        STATE_OPERATION,
        STATE_NUMBER,
        STATE_BRACKET,
    } ParserState;

    typedef string StackElement;
    typedef vector<StackElement> Stack;

    static const string eol;
    Parser()
    {
        state_ = STATE_START;
    }
    virtual ~Parser()
    {

    }
    void Parse( const std::string & s )
    {
       
        string sc = s + eol;
        int i = 0;
        GetExpression( s );
    }

    Stack GetExpression( string s, string prevOp )
    {
        Stack result;
        string piece = GetPiece( s );
        if( piece == eol )
        {
            if( prevOp == "" )
            {
                return result;
            }
        }
        else if( piece == "(" )
        {
            Stack newExp = GetExpression( s, "(" );
            result.insert( result.end(), newExp.begin(), newExp.end() );
        }
        else if( piece == ")" )
        {
            if( prevOp == "(" )
            {
                return result; // ok
            }
            else
            {
                throw std::exception( "Unexpected bracket" );
            }
        }
        else if( isPositiveInteger( piece ) )
        {
            //GetExpression( s, "num" );
            if( prevOp == "" || prevOp == "(" )
            {
                Push( piece );
            }
            else 
            {
                
            }
            return; // ok
        }
        else if( IsOperation( piece ) )
        {
            if( Priority( piece ) <= Priority( prevOp ) )
            {
                GetExpression( s, piece );
                Push( piece );    
            }
            else
            {
                GetExpression( s, piece );

            }
            
        }
             

    }

    bool isPositiveInteger(const std::string& s)
    {
        return !s.empty() && 
            (std::count_if(s.begin(), s.end(), std::isdigit) == s.size());
    }

    int Priority( string s )
    {
        if( s == "+" || s == "-" )
        {
            return 1;

        }
        else if( s == "*" || s == "/" )
        {
            return 2;
        }
        else
            throw std::exception( "Unknown operation " + s );

    }
    bool IsOperation( string s )
    {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
    string GetPiece( int & i, const std::string & s )
    {
        string res = "";
        ParserState newState = STATE_START;
        while( i < s.length() && s[i] == ' ' ) 
            ++ i;

        if( i >= s.length() )
        {
        
        }
        while ( i < s.length() )
        {
            if( s[i] == ' ' )
            {
                break;
            }
            else if( isalpha( s[i] ) )
            {

            }

        }
    }
private:
    ParserState state_;
};

#endif // parser_h__
