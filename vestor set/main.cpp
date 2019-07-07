
#include <random>
#include <sstream>

#include "set.h"
#include "timetable.h"
#include "timer.h"

// Append a number to string.

std::string addnumber( std::string s, long unsigned int i )
{
    std::ostringstream ind;
    ind << i;
    s += ind. str( );
    return s;
}


int main( int argc, char* argv[ ] )
{
    
    set kaz;
    
    std::cout << set::equal( "aStana", "AsTaNa" ) << "\n";
    // true
    std::cout << set::equal( "astana", "Almaty" ) << "\n";
    // false.
    std::cout << set::equal( "astana", "astana" ) << "\n";
    // true.
    
    kaz. insert( "aqtobe" );
    std::cout << kaz. contains( "Aqtobe" ) << "\n";
    std::cout << kaz. contains( "Aqtau" ) << "\n";
    
    kaz. insert( "SZYMKENT" );
    std::cout << kaz. contains( "szymkent" ) << "\n";
    
    std::cout << kaz << "\n";
    kaz. remove( "Szymkent" );
    std::cout << kaz << "\n";
    kaz. remove( "Aqtobe" );
    std::cout << kaz << "\n";
    set s1;
    s1. insert( "arailym" );
    s1. insert( "arai" );
    s1. insert( "loo" );
    set s2;
    s2. insert( "arai" );
    s2. insert( "loo" );
    std::cout << subset(s1, s2) << "\n";
    
    
    timetable tab( std::string( "set" ));
    for( size_t s = 1000; s < 20000; s = 2 * s )
    {
        set someset1;
        
        timer tt;
        size_t nr = 0;
        for( size_t k = 0; k != s; ++ k )
        {
            nr += someset1. insert( addnumber( "aa", rand( )));
            nr += someset1. insert( addnumber( "bb", rand( )));
        }
        
        auto someset2 = someset1;
        
        if( nr != someset1. size( )) throw std::runtime_error( "counting went wrong" );
        
        for( const auto& el : someset2 )
        {
            nr -= someset1. remove( el );
        }
        
        if( nr != 0 || someset1. size( ) != 0 )
            throw std::runtime_error( "counting went wrong" );
        
        tab. insert( s, tt. time( ));
    }
    
    std::cout << tab << "\n";
    std::cout << "totaltime " << tab. totaltime( ) << "\n";
    
}
