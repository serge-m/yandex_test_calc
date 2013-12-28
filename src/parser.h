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
        GetExpression2( s );
    }


    Stack GetExpression2( string s )
    {
        StackElement elem;
        Stack prevExpression;
        StackElement prevOpInExpr = "";
        do 
        {
            elem = GetPiece( s );


            if( IsPositiveInteger( elem ) )
            {
                res_.push_back( elem );
            }
            else if( IsOperation( elem ) )
            {
                while( !operations_.empty() )
                {
                    string lastOp = operations_.back();
                    if( lastOp == "(" )
                        break;

                    int prior = Priority( lastOp );

                    if( prior < Priority( elem ))
                        break;

                    res_.push_back( lastOp );
                    operations_.pop_back();
                }
                if( elem == ")" )
                {

                    string lastOp;
                    if( operations_.empty() || ( lastOp = operations_.back()) != "(" )
                    {
                        stringstream ss;
                        ss << "Unexpected ')' in position " << pos_;
                        throw std::exception( ss.str().c_str() );
                    }
                    operations_.pop_back();
                }
                else
                {
                    operations_.push_back( elem );
                }

                
            }


        } while ( elem != eol );
    
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
            return 1;
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

        string s1 = s.substr( posFirst, 1 );
        if( IsOperation( s1 ) )
        {
            pos_ ++;
            return s1;
        }

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
