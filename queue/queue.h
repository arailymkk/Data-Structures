#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED  1

#include <iostream>
#include <initializer_list>

struct queue
{
    size_t current_size;
    size_t current_capacity;
    size_t begin;
    size_t end;
    
    double* data;
    
    void ensure_capacity( size_t c );
    // Ensure that queue has capacity of at least c.
    // This function is given, so you don't have to write it.
    
    // Return i+1, but 0 if we reach current_capacity.
    
    size_t next( size_t i ) const
    {
        i = i + 1;
        if( i == current_capacity )
            i = 0;
        return i;
    }
    
    void checkinvariant( ) const;
    // Call this function often during your tests. We will
    // call it during checking!
    
    void printfields( std::ostream& ) const;
    // Print the fields current_size, current_capacity,
    // begin, end. It should be used for debugging.
    
public:
    
    // Constructs empty queue.
    queue()
    {
        current_size = 0;
        current_capacity = 4;
        begin = 0;
        end = 0;
        data = new double[current_capacity];
    }
    
    queue( const queue& q ) //copy constructor
    {
        current_capacity = q.current_capacity;
        current_size =  q.current_size;
        
        data = new double[current_capacity];
        begin = q.begin;
        end = q.end;
        
        {
            for( size_t i = begin; i != end; i = next(i))
                data[i] = q.data[i];
        }
    }
    


    ~queue( )
    {
        delete[] data;
    }
    
    
    const queue& operator = ( const queue& q ) //assigment
    {
        if(current_size != q.current_size)
        {
            ensure_capacity( q.current_capacity);
            current_size = q.current_size;

        }
        begin = q.begin;
        end = q.end;
        
        for( size_t i = begin; i != end; i = next(i))
        {
            data[i] = q.data[i];
        }
        return q;
    }
    
    //constructor
    // So that you can write q = { 1,2,3 };
    // You can use init. size( ) to see the size, and
    // for( double d : init ) to go through all
    // elements in the initializer_list.
    
    queue( std::initializer_list<double> init )
    {
        current_size = 0;
        current_capacity = 4;
        begin=0;
        end=0;
        data = new double[current_capacity];
        {
            for( double d : init )
                push(d);
        }
    }

    
    void push( double d )
    {
        current_size = current_size + 1;
        end = next(end);
        ensure_capacity(current_size);
        if(end==0) data[current_capacity - 1] = d;
        else data[end-1] = d;
    }
    
    void pop( )
    {
        current_size = current_size - 1;
        begin = next(begin);
    }
    
    void clear( ) { current_size = 0; }
    
    double peek( ) const { return data[begin]; }
    
    size_t size( ) const { return current_size; }
    
    bool empty( ) const { return current_size == 0; }
    
    friend std::ostream& operator << ( std::ostream& , const queue& );
}; 

std::ostream& operator << ( std::ostream& , const queue& );

#endif
