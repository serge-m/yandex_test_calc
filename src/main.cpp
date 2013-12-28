#include "parser.h"

#include <string>
#include <iostream>
using namespace std;


void RunParser( string expression, bool check = false, bool isCorrect = true, double reference = 0.0)
{
    Parser parser;
    bool testPassed = false;
    try
    {
        double res = parser.Parse( expression );
        cout << expression << "=" << res;
        if( check && isCorrect && reference == res )
        {
            testPassed = true;
        }
    }
    catch( const std::exception & e )
    {
        cout << e.what();
        if( check && !isCorrect )
        {
            testPassed = true;
        }
    }

    if( check )
    {
        if( testPassed )
        {
            cout << " OK";
        }
        else
        {
            cout << " FAIL";
        }
    }

    cout << endl;
}

int main()
{
    RunParser( "8+9*(7+8)-13", true, true, 130 );
    RunParser( "1+1+1+1", true, true, 4 );
    RunParser( "1*1+1+1))", true, false );

    
    RunParser( "1*(1+1+1)" );
    RunParser( "1(*(((1+1+1)" );


    return 0;


}