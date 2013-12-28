#include "parser.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std; // убрать из хедера


const string Parser::eol = "$";



double Parser::CalcExpression( Stack st )
{
    StackForCalculations s;
    for( int i = 0; i < st.size(); ++ i )
    {
        if( IsOperation( st[i] ) )
        {
            double res = CalcOperation( st[i], s );
            s.push_back( res );
        }
        else if( IsPositiveInteger( st[i] ) )
        {
            s.push_back( GetNumberFromString( st[i] ) );
        }
    }

    if( s.size() != 1 )
    {
        throw std::exception( "Calculation failed" );
    }
    return s.front();
}

double Parser::CalcOperation( StackElement op, StackForCalculations & s )
{
    double var1, var2;
    if( op == "+" || op == "-" || op == "*" || op == "/" )
    {
        try
        {
            var2 = GetNumberFromStack( s );
            var1 = GetNumberFromStack( s );
        }
        catch( const std::exception & e )
        {
            string message = "Not enough parameters for operation " + op + ". " + e.what();
            throw std::exception( message.c_str() );
        }
    }
    
    double result = 0.0;
    if( op == "+" )
    {
        result = var1 + var2;
    }
    else if( op == "-" )
    {
        result = var1 - var2;
    }
    else if( op == "*" )
    {
        result = var1 * var2;
    }
    else if( op == "/" )
    {
        result = var1 / var2;
    }
    else 
    {
        string message = "Unsupported operation " + op;
        throw std::exception( message.c_str() );
    }
    return result;
}

double Parser::GetNumberFromStack( StackForCalculations & s )
{
    if( s.empty() )
    {
        throw std::exception( "Parameters stack is empty" );
    }
    double value = s.back();
    s.pop_back();
    return value;
}

double Parser::GetNumberFromString( StackElement se )
{
    double value;
    istringstream convert(se);
    if ( !(convert >> value) ) 
    {
        string message = "Unable to parse " + se;
        throw std::exception( message.c_str() );
    }
    return value;
}

Parser::Parser()
{

}

Parser::~Parser()
{

}

double Parser::Parse( const std::string & s )
{
    Stack st;
    string sc = s + eol;
    pos_ = 0;
    stackPostfix_.clear();
    stackOperations_.clear();
    CreateReversePolishNotation( s );
    double res = CalcExpression( stackPostfix_ );
    return res;
}

void Parser::CreateReversePolishNotation( string s )
{
    StackElement elem;
    do 
    {
        elem = GetPiece( s );


        if( IsPositiveInteger( elem ) )
        {
            stackPostfix_.push_back( elem );
        }
        else if( IsOperation( elem ) )
        {
            while( !stackOperations_.empty() )
            {
                string lastOp = stackOperations_.back();
                if( lastOp == "(" )
                    break;

                int prior = Priority( lastOp );

                if( prior < Priority( elem ))
                    break;

                stackPostfix_.push_back( lastOp );
                stackOperations_.pop_back();
            }
            if( elem == ")" )
            {

                string lastOp;
                if( stackOperations_.empty() || ( lastOp = stackOperations_.back()) != "(" )
                {
                    stringstream ss;
                    ss << "Unexpected ')' in position " << pos_;
                    throw std::exception( ss.str().c_str() );
                }
                stackOperations_.pop_back();
            }
            else
            {
                stackOperations_.push_back( elem );
            }


        }


    } while ( elem != eol );
}

bool Parser::IsPositiveInteger( const std::string& s )
{
    return !s.empty() && 
        (std::count_if(s.begin(), s.end(), std::isdigit) == s.size());
}

int Parser::Priority( string s )
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

bool Parser::IsOperation( string s )
{
    return s == "+" || s == "-" || s == "*" || s == "/" || s == eol || s == "(" || s == ")";
}

std::string Parser::GetPiece( const std::string & s )
{
    string res = "";

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

Parser::SymbolClass Parser::GetSymbolClass( char symbol )
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
