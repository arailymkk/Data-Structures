
// Lab Exercise 4.

#include "set.h"

bool set::equal( const std::string& s1, const std::string& s2 )
{
    if(s1.size() != s2.size())
        return false;
    
    for(size_t i =0; i<s1.size(); i++)
    {
        char m1 = tolower( s1[i] );
        char m2 = tolower( s2[i] );
        
        if(m1 != m2 )
        {
            return false;
        }
    }
    
    return true;
}
bool set::contains( const std::string& el ) const
{
    for(size_t i = 0; i<data.size(); i++)
    {
        if(equal(data[i],el))
            return true;
    }
    return false;
}
bool set::insert( const std::string& el )
{
    if(contains(el))
        return false;
    
    else
    {
        data.push_back(el);
        return true;
    }
}
size_t set::insert( const set& s )
{
    int count = 0;
    for(auto it = s.begin( ); it != s.end( ); ++it)
    {
        if(insert(*it)){
            count+=1;
        }
    }
    return count;
    
}
bool set::remove( const std::string& el ){
    for(size_t i =0; i<data.size(); i++){
        if(equal(data[i], el)){
            std::swap(data[i], data.back());
            data.pop_back();
            return true;
        }
        
    }
    
    return false;
   
}
size_t set::remove( const set& s ){
    int count = 0;
    for(auto it = s.begin( ); it != s.end( ); ++it)
    {
        if(remove(*it)){
            count+=1;
        }
    }
    return count;
}
std::ostream& operator << ( std::ostream& out, const set& s ){
    out << "{";
    for(auto it = s.begin(); it!=s.end(); ++it){
        if(it!=s.begin()) out << ", ";
        out << *it;
    }
    
    out << " }";
    return out;
}
           

bool subset( const set& s1, const set& s2 )
{
    int count=0;
    for(auto it = s2.begin(); it!=s2.end(); ++it){
        if(s1.contains(*it))
            count++;
    }
    if(count==s2.size())
        return true;
    else
        return false;
}
