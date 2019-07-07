
#include "set.h"

void print( std::ostream& out, const treenode* n, size_t indent )
{
    
    for( size_t i = 0; i != indent; ++ i )
        out << "|  ";
    if(n)
    {
        out << ( n -> val ) << "\n";
        print( out, n -> left, indent + 1 );
        print( out, n -> right, indent + 1 );
    }
    else
        out << "#\n";
}


void checksorted(
                 treenode* n,
                 const std::string* lowerbound,
                 const std::string* upperbound )
{
    while(n)
    {
        if( lowerbound && !before( *lowerbound, n -> val ))
        {
            std::cout << "value " << ( n -> val );
            std::cout << " is not above lower bound " << *lowerbound << "\n";
            std::abort( );
        }
        
        if( upperbound && !before( n -> val, *upperbound ))
        {
            std::cout << "value " << ( n -> val );
            std::cout << " is not below upperbound " << *upperbound << "\n";
            std::abort( );
        }
        
        checksorted( n -> left, lowerbound, &( n -> val ));
        lowerbound = & ( n -> val );
        n = n -> right;
    }
}


// Used by copy constructor and assignment:

void writecopy( treenode** to, treenode* from )
{
    while( from )
    {
        *to = new treenode{ from -> val };
        
        writecopy( & (*to) -> left, from -> left );
        to = & (*to) -> right;
        from = from -> right;
    }
}

// Used by destructor:

void deallocate( treenode* n )
{
    while(n)
    {
        deallocate( n -> left );
        treenode* bye = n;
        n = n -> right;
        delete bye;
    }
}



size_t log2( size_t s ){
    if(s==1) return 1;
    else if(s==0) return 0;
    else
    {
        size_t count = 0;
        for(size_t i = s; i>1; i=i/2){
            count++;
        }
        return count;
    }
    
}

// From previous task:

bool equal( const std::string& s1, const std::string& s2 )
{
    if(s1.size() != s2.size()) return false;
    
    for(size_t i =0; i<s1.size(); i++)
    {
        char m1 = tolower( s1[i] );
        char m2 = tolower( s2[i] );
        if(m1 != m2 ) return false;
    }
    return true;
}
    

// Must be written for task 5(part 2) :


bool before( const std::string& s1, const std::string& s2 )
{
    size_t n;
    if(s1.size() > s2.size()) n = s2.size();
    else n = s1.size();
    
    size_t i = 0;
    while(i < n)
    {
        char m1 = tolower( s1[i] );
        char m2 = tolower( s2[i] );
        if (m1 < m2) return true;
        else if(m1 == m2) i++;
        else return false;
    }
    if(s1.size()<s2.size()) return true;
    else return false;
}


const treenode* find( const treenode* n, const std::string& el )
{
    if(n == nullptr) return nullptr;
    else if(equal(n->val, el)) return n;
    else if(before(el, n->val)) return find(n->left, el);
    else return find(n->right, el);
}
// Write this one first.

treenode** find( treenode** n, const std::string& el ){
    if(*n == nullptr) return n;
    else if(equal((*n)->val, el)) return &(*n);
    else if(before(el, (*n)->val)) return find(&((*n)->left), el);
    else return find(&((*n)->right), el);
}

// Modify the other find into this one, also have a look at
// stackscan4.pdf


// Insert n at the right most position in into:

void rightinsert( treenode** into, treenode* n ){
    if(*into == nullptr) *into = n;
    else rightinsert(&((*into)->right), n);
}


size_t size( const treenode* n ) {
    if(n==nullptr) return 0;
    else return(size(n->left) + 1 + size(n->right));
}

size_t height( const treenode* n ){
    if(n==nullptr) return -1;
    else
    {
        size_t height_left = height(n->left) + 1;
        size_t height_right = height(n->right) + 1;
        if (height_left > height_right) return height_left;
        else return height_right;
    }
}


bool set::insert( const std::string& el ){
    treenode** z = find(&tr, el);
    if(*z==nullptr){
        treenode* f = new treenode(el);
        *z = f;
        return true;
    }
    else return false;
}

bool set::contains( const std::string& el ) const
{
    return find( tr, el ) != nullptr;
}


bool set::remove( const std::string& el )
{
    treenode** z = find(&tr, el);
    if(*z==nullptr) return false;
    else{
        if((*z)->left==nullptr){
            treenode* temp = *z;
            *z=(*z)->right;
            delete temp;
        }
        else{
            treenode* temp = *z;
            rightinsert(&((*z)->left), (*z)->right);
            *z=(*z)->left;
            delete temp;
        }
        return true;
    }
}


void set::checksorted( ) const
{
    ::checksorted( tr, nullptr, nullptr );
    // :: are needed because the other checksorted is not in the class.
}


std::ostream& set::print( size_t indent, std::ostream& out ) const
{
    ::print( out, tr, indent );
    return out;
}


