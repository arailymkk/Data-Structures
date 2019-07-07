#include <random>
#include <sstream>

#include "set.h"
#include "timetable.h"
#include "timer.h"


std::string addnumber( std::string s, long unsigned int i )
{
    std::ostringstream ind;
    ind << i;
    s += ind. str( );
    return s;
}



int main( int argc, char* argv[ ] )
{
    std::cout << before( "AStanala", "AsTaNal" ) << "\n";
    std::cout << log2(0) << "\n"; // prints 0
    std::cout << log2((size_t)15) << "\n"; // prints 3.
    std::cout << log2(16) << "\n";
    
    set kaz;
    std::cout << kaz << "\n";
    std::cout << "khjklklk" << "\n";
    kaz. insert( "hlmaty" );
    kaz. insert( "aqtobe" );
    kaz. insert( "atyrau" );
    
    std::cout << kaz << "\n";
    
    std::cout << kaz. contains( "Aqtobe" ) << "\n";
    std::cout << kaz. contains( "AqToBe" ) << "\n";
    // Or not to be, that's the question.
    
    kaz. insert( "SHYMKENT" );
    std::cout << kaz. contains( "szymkent" ) << "\n";
    
    kaz. insert( "Almaty" );
    kaz. insert( "Taraz" );
    kaz. insert( "Qaraghandy" );
    kaz. insert( "Qostanay" );
    kaz. insert( "Kokshetau" );
    kaz. insert( "jbhklmrrrf");
    kaz. insert( "afghnmrrfffb" );
    kaz. insert( "tyjcsggggg" );
    kaz. insert( "dfghjgffdd" );
    kaz. insert( "pojhffhhdd" );
    kaz. insert( "vbbjpojhffhhdd" );
    kaz. insert( "ttgbjpojhffhhdd" );
    kaz. insert( "stgbjpojhffhhdd" );
    kaz. insert( "wtgbjpojhffhhdd" );
    kaz. insert( "ztgbjpojhffhhdd" );
    kaz. insert( "zztgbjpojhffhhdd" );




    std::cout << "before removal\n";
    std::cout << kaz << "\n";
    kaz. remove( "Zhezqazghan" );
    kaz. remove( "kokshetau" );
    //kaz. remove( "qaraghandy" );
    //kaz. remove( "Aqtobe" );
    std::cout << "after removal\n";
    std::cout << kaz << "\n";
    
    kaz. checksorted( );
    std::cout << kaz << "\n";
    std::cout << kaz. size( ) << "\n";
    std::cout << "Height is " << kaz. height( );
    std::cout << " should be approximately " << log2( kaz. size( )) << "\n";
    // If the numbers differ much, the tree is badly balanced.
    
    auto kaz2 = kaz; // Copy constructor.
    std::cout << kaz2 << "\n";
    std::cout << kaz2. size( ) << "\n";
    std::cout << kaz2. height( ) << "\n";
    kaz2 = kaz;      // Assignment.
    kaz = kaz;       // Self assignment.
    
    timetable tab( std::string( "set" ));
    
    for( size_t s = 1000; s < 80000; s = 2 * s )
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
        
        if( nr != someset1. size( ))
            throw std::runtime_error( "counting went wrong" );
        
        // Don't use size( )! It is O(n), and will mess up your performance.
        
        while( !someset2. isempty( ))
        {
            nr -= someset2. remove( someset2. top( ));
        }
        
        if( nr != 0 || someset2. size( ) != 0 )
            throw std::runtime_error( "counting went wrong" );
        
        tab. insert( s, tt. time( ));
    }
    
    std::cout << tab << "\n";
    std::cout << "totaltime " << tab. totaltime( ) << "\n";
}



