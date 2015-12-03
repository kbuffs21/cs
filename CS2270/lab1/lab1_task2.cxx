//Kevin Macias
//CSCI 2270
//01/13/14

#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS
using namespace std;


double underflow_double( );

float underflow_float( );

int main( )
{
    cout << underflow_float() << endl;
    cout << underflow_double() << endl;
    return EXIT_SUCCESS;
}

double underflow_double( )
{
    double n1  = 1, n2;
    while (n1 > 0)
    {
		n2 = n1 * 2;
		n1 = n1 / 2;
	}
	return (n2);	// more is needed here
}

float underflow_float( )
{
    float n1 = 1 , n2;
    while (n1 > 0)
    {
		n2 = n1 * 2;
		n1 = n1 / 2;
	}
	return (n2);	// more is needed here
}

