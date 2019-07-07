#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <iostream>
#include <initializer_list>

class stack
{
    size_t current_size;
    size_t current_capacity;
    
    double* data;
    // INVARIANТ: has been allocated with size current_capacity.
    // 0 <= current_size <= current_capacity.
    
    void ensure_capacity( size_t c );
    // Ensure that stack has capacity of at least c.
    // This function is given, so you don't have to write it.
    
public:
    
    
    stack()
    {
        current_size = 0;
        current_capacity = 10;
        data = new double[current_capacity];
    }
    
    stack( const stack& s )
    {
        current_capacity = s.current_capacity;
        current_size =  s.current_size;
        
        data = new double[current_capacity];
        
        
        for( size_t i = 0; i != current_size; ++ i )
        {
            data[i] = s.data[i];
        }
    }
    
    ~stack( )
    {
        delete[] data;
    }
    
    
    
    const stack& operator = ( const stack& s )
    {
        if(current_size!=s.current_size)
        {
            ensure_capacity( s.current_size );
            current_size = s.current_size;
        }
        for( size_t i = 0; i != s.current_size; ++ i)
        {
            data[i] = s.data[i];
        }
        return s;
    }
    
    stack( std::initializer_list<double> init )
    {
        current_size = 0;
        current_capacity = 10;
        data = new double[current_capacity];
        {
            for( double d : init )
                push(d);
        }
    }
    
    void push( double d )
    {
        current_size = current_size + 1;
        ensure_capacity(current_size);
        
        
        data[current_size-1] = d;
        //current_size = current_size + 1;
        
    }
    
    
    void pop( )
    {
        current_size = current_size - 1;
    }
    
    
    void clear( )
    {
        current_size = 0;
    }
    
    void reset( size_t s )
    {
        current_size = s;
    }
    
    double peek( ) const
    {
        return data[current_size-1];
    }
    
    size_t size( ) const
    {
        return current_size;
    }
    
    bool empty( ) const
    {
        return current_size==0;
    }
    
    friend std::ostream& operator << ( std::ostream& , const stack& );
};



#endif
