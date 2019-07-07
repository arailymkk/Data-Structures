/*
 * set.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: benja
 */

#include "set.h"

// From previous task:

bool equal( const std::string& s1, const std::string& s2 ){
    if(s1.size() != s2.size()) return false;
    
    for(size_t i =0; i<s1.size(); i++)
    {
        char m1 = tolower( s1[i] );
        char m2 = tolower( s2[i] );
        if(m1 != m2 ) return false;
    }
    return true;
}

// Must be new written:
// It is important that equal and hash agree. That means:
//    If equal(s1,s2) then hash(s1) == hash(s2).

size_t hash( const std::string& st ){
    int pow = 19;
    size_t total = tolower(st[st.size()-1]);
    for(size_t i = st.size() - 2; i > 0; i--){
        pow *= 19;
        total += pow * tolower(st[i]);
    }
    return total+19*pow*tolower(st[0]);
}

bool set::contains( const std::string& s ) const{
    size_t hashval = hash(s) % buckets.size();
    for( auto it = buckets[hashval].begin(); it != buckets[hashval].end(); ++it){
        if( equal(*it, s)) return true;
    }
    return false;
}

bool set::simp_insert( const std::string& s ){
    if(contains(s)) return false;
    else{
        size_t hashval = hash(s) % buckets.size();
        buckets[hashval].push_back(s);
        set_size++;
        return true;
    }
}

bool set::insert( const std::string& s ){
    bool d = simp_insert(s);
    if(!d) return false;
    else{
        if((double)set_size/buckets.size() > max_load_factor){
            rehash(buckets.size());
        }
        return true;
    }
}


void set::rehash( size_t newbucketsize ){
    if( newbucketsize < 4 ){newbucketsize = 4;}
    else {newbucketsize = 2 * newbucketsize;}
    std::vector< std::list< std::string >> newbuckets = std::vector< std::list< std::string >> ( newbucketsize );
    for( size_t i = 0; i < buckets.size(); ++i )
    {
        for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
            size_t new_hashval = hash(*it) % newbucketsize;
            newbuckets[new_hashval].push_back(*it);
        }
    }
    buckets = newbuckets;
    //buckets = std::move(newbuckets);
}



bool set::remove( const std::string& s ){
    if(contains(s)){
        size_t hashval = hash(s) % buckets.size();
        buckets[hashval].remove(s);
        set_size--;
        return true;
    }
    return false;
}

void set::clear( ){
    for( size_t i = 0; i < buckets.size(); i++ ){
        buckets[i].clear();
    }
}

std::ostream& set::print( std::ostream& out ) const{
    
    for(size_t i = 0; i < buckets.size(); ++ i ){
        out << "[" << i << "]";
        for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
            out << " -> "<< *it;
        }
        out<<"\n";
    }
    return out;
}



std::ostream& set::printstatistics( std::ostream& out ) const
{
    std::cout << "set size =            " << size( ) << "\n";
    std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
    std::cout << "standard deviation =  " << standarddev( ) << "\n";
    return out;
}



