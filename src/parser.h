#ifndef parser_h__
#define parser_h__

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
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
        Stack st;
        string sc = s + eol;
        pos_ = 0;
        res_.clear();
        operations_.clear();
        GetExpression2( s, "$", st );
    }

    /*Stack GetExpression( string s, string prevOp,
         Stack prevStack )
    {
        Stack result;
        string piece = GetPiece( s );
        if( piece == eol )
        {
            if( prevOp == "" )
            {
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
            }
            else
            {
                throw std::exception( "Unexpected bracket" );
            }
        }
        else if( IsPositiveInteger( piece ) )
        {
            result.push_back( piece );
        }
        else if( IsOperation( piece ) )
        {
            if( Priority( piece ) <= Priority( prevOp ) )
            {
                result = GetExpression( s, piece );
                result.push_back( piece );    
            }
            else
            {
                GetExpression( s, piece );

            }
            
        }
             

    }*/

    Stack GetExpression2( string s, string prevOp,
        Stack prevStack )
    {
        StackElement elem;
        Stack prevExpression;
        StackElement prevOpInExpr = "";
        do 
        {
            elem = GetPiece( s );

            /*if( elem == "(" )
            {
                prevExpression = GetExpression2( s, "(", Stack() );
            }*/
            if( IsPositiveInteger( elem ) )
            {
                res_.push_back( elem );
            }
            else if( IsOperation( elem ) )
            {
                while( !operations_.empty() )
                {
                    string lastOp = operations_.back();
                    int prior = Priority( lastOp );
                    if( prior >= Priority( elem ) )
                    {
                        res_.push_back( lastOp );
                        operations_.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
                if( elem == ")" )
                {

                    string lastOp;
                    if( operations_.empty() || ( lastOp = operations_.back()) != "(" )
                    {
                        throw std::exception( "Unexpected ')'" );
                    }
                    operations_.pop_back();
                }
                else
                {
                    operations_.push_back( elem );
                }

                
            }


        } while ( elem != eol );
    
        return prevStack;
    }

    bool IsPositiveInteger(const std::string& s)
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
        else if( s == "(" )
        {
            return 4;
        }
        else if ( s == ")" )
        {
            return 3;
        }
        else if( s == eol )
        {
            return -1;
        }
        else if (IsPositiveInteger( s ))
        {
            return 1;
        }
        else
            return 0;

    }
    bool IsOperation( string s )
    {
        return s == "+" || s == "-" || s == "*" || s == "/" || s == eol || s == "(" || s == ")";
    }
    string GetPiece( const std::string & s )
    {
        string res = "";

        ParserState newState = STATE_START;
        while( pos_ < s.length() && s[pos_] == ' ' ) 
            ++ pos_;

        if( pos_ >= s.length() )
        {
            return eol;
        }
    
        int posFirst= pos_;

        while ( pos_ < s.length() && GetSymbolClass( s[pos_]) == GetSymbolClass( s[posFirst ]) )
        {
            pos_ ++;    
        }

        return s.substr( posFirst, pos_ - posFirst );
       
    }
    typedef enum
    {
        CLASS_ALPHA,
        CLASS_NUM,
        CLASS_OPERATION,
        CLASS_SPACE,
        CLASS_UNKNOWN,
    } SymbolClass;
    SymbolClass GetSymbolClass( char symbol )
    {
        if( isalpha( symbol ) )
            return CLASS_ALPHA;
        if( isdigit( symbol ) )
            return CLASS_NUM;
        if( symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*' )
            return CLASS_OPERATION;
        if( isspace( symbol ) )
            return CLASS_SPACE;

        return CLASS_UNKNOWN;
    }
private:
    ParserState state_;
    int pos_;
    Stack res_;
    Stack operations_;
};

#endif // parser_h__
