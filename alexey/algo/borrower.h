#pragma once
#include <cassert>

template<class Container>
class Borrower {
public:
    Borrower( Container& container, typename Container::iterator iter ) : container_( &container )
    {
        value_ = *iter;
        container_->erase( iter );
    }

    Borrower( const Borrower<Container>& other ) = delete;
    const Borrower& operator=( const Borrower<Container>& other ) = delete;

    Borrower( Borrower<Container>&& other ) {
        container_ = other.container_;
        other.container_ = nullptr;
        value_ = other.value_;
    }

    const Borrower& operator=( Borrower<Container>&& other )  {
        ~Borrower();
        container_ = other.container_;
        other.container_ = nullptr;
        value_ = other.value_;
        return *this;
    }

    ~Borrower()    {
        if (container_) container_->insert( value_ );
        container_ = nullptr;
    }

private:
    Container* container_ = nullptr;
    typename Container::value_type value_;
};

template<class Container>
Borrower<Container> make_borrower( Container& container, typename Container::iterator iter ) {
    return Borrower<Container>(container, iter); 
}

template<class Container>
Borrower<Container> make_borrower( Container& container, typename Container::value_type value )
{
    auto iter = container.find( value );
    assert( iter != end( container ) );
    return make_borrower( container, iter );
}