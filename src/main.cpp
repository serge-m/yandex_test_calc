#include "parser.h"

#include <string>
#include <iostream>
using namespace std;


int main()
{
    string s = "8+9*(7+8))-13";

    cout << s << endl;

    Parser parser;
    try
    {
        parser.Parse( s );
    }
    catch( const std::exception & e )
    {
        cout << e.what();
    }


    return 0;


}