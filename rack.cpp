#include "rack.h"
#include "shelf.h"

#include <iostream>

Rack::Rack()
{

}

Rack::Rack(const Rack &r)
{
    if ( this != &r )
    {
        shelfCount = r.shelfCount;
        if ( shelfCount > 0 )
        {
            shelvs = new Shelf[r.shelfCount];
            for ( int i = 0; i < shelfCount; ++i)
            {
                shelvs[i] = r.shelvs[i];
            }
        }
    }
}

Rack::~Rack()
{
    if ( shelvs )
    {
        delete [] shelvs;
    }
}

int Rack::getShelfCount() const
{
    return shelfCount;
}

void Rack::addShelf( Shelf& shelf )
{
    if ( shelvs == nullptr )
    {
        shelvs = new Shelf[1];
        shelvs[0] = shelf;
        shelfCount = 1;
    }
    else
    {
        Shelf* temp = new Shelf[ shelfCount + 1 ];
        for ( int i = 0; i < shelfCount; i++ )
        {
            temp[i] = shelvs[i];
        }
        temp[shelfCount] = shelf;
        delete [] shelvs;
        shelvs = temp;
        shelfCount++;
    }
}

void Rack::removeShelf(int pos)
{
    if ( ( pos > -1 ) && ( pos < shelfCount ) )
    {
        Shelf* temp = new Shelf[ shelfCount - 1 ];
        int j = 0;
        for ( int i = 0; i < shelfCount; ++i)
        {
            if ( i != pos )
            {
                temp[j] = shelvs[i];
                j++;
            }
        }
        delete [] shelvs;
        shelvs = temp;
        shelfCount--;
    }
}

Shelf *Rack::at(int pos)
{
    Shelf* result = nullptr;
    if ( ( pos > -1 ) && ( pos < shelfCount ) )
    {
        result = shelvs + pos;
    }
    return result;
}

void Rack::addBook( int shelfNum, Book& book )
{
    if ( ( shelfNum > -1 ) && (shelfNum < shelfCount ) )
    {
        shelvs[ shelfNum ].addBook( book );
    }
}

void Rack::removeBook(int shelfNum, int pos, int count)
{
    if ( ( shelfNum > -1 ) && (shelfNum < shelfCount ) )
    {
        shelvs[ shelfNum ].removeBook( pos, count );
    }
}

int Rack::findBookByName(const std::string &name, int shelfNum, int startPos)
{
    if ( ( shelfNum > -1 ) && (shelfNum < shelfCount ) )
    {
        return shelvs[ shelfNum ].findBookByName( name, startPos );
    }
    return -1;
}

int Rack::findBookByAvtor(const std::string &avtor, int shelfNum, int startPos)
{
    if ( ( shelfNum > -1 ) && (shelfNum < shelfCount ) )
    {
        return shelvs[ shelfNum ].findBookByAvtor( avtor, startPos );
    }
    return -1;
}

int Rack::findBookByJanr( int janr, int shelfNum, int startPos)
{
    if ( ( shelfNum > -1 ) && (shelfNum < shelfCount ) )
    {
        return shelvs[ shelfNum ].findBookByJanr( janr, startPos );
    }
    return -1;
}

void Rack::outputAll()
{
    for ( int s = 0; s < shelfCount; ++s )
    {
        std::cout << "\t>>\tПолка № " << s + 1 << "("  << shelfCount << "):\n";
        shelvs[s].outputAll();
    }
}

bool Rack::operator==(const Rack &r)
{
    bool result = false;
    if ( shelfCount == r.shelfCount )
    {
        result = true;
        if ( shelfCount > 0 )
        {
            for ( int i = 0; i < shelfCount; ++i)
            {
                result &= (shelvs[i] == r.shelvs[i]);
            }
        }
    }
    return result;
}

Rack Rack::operator=(const Rack &r)
{
    if ( this != &r )
    {
        shelfCount = r.shelfCount;
        if ( shelfCount > 0 )
        {
            shelvs = new Shelf[r.shelfCount];
            for ( int i = 0; i < shelfCount; ++i)
            {
                shelvs[i] = r.shelvs[i];
            }
        }
    }
    return *this;
}

std::ofstream &operator<<(std::ofstream &ofs, Rack &rack)
{
    const int count = rack.getShelfCount();
    ofs << count << std::endl;
    for ( int i = 0; i < count; ++i )
    {
        Shelf* ps = rack.at(i);
        ofs << (*ps);
    }

    return ofs;
}

std::ifstream &operator>>(std::ifstream &ifs, Rack &rack)
{
    int count = 0;
    ifs >> count;
    for ( int i = 0; i < count; ++i )
    {
        Shelf shelf;
        ifs >> shelf;
        rack.addShelf( shelf );
    }

    return ifs;
}
