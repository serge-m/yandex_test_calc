#include "parser.h"

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
