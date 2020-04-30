#include "shelf.h"
#include "book.h"

#include <iostream>

Shelf::Shelf()
{

}

Shelf::Shelf(const Shelf &s)
{
    if ( this != &s )
    {
        bookCount = s.bookCount;
        if ( bookCount > 0 )
        {
            books = new Book[s.bookCount];
            for ( int i = 0; i < bookCount; ++i)
            {
                books[i] = s.books[i];
            }
        }
    }
}

Shelf::~Shelf()
{
    if ( books )
    {
        delete [] books;
    }
}

void Shelf::addBook(Book &book)
{
    if ( books == nullptr )
    {
        books = new Book[1];
        books[0].name = book.name;
        books[0].count = book.count;
        books[0].avtor = book.avtor;
        books[0].janr = book.janr;
        bookCount = 1;
    }
    else
    {
        Book* temp = new Book[ bookCount + 1 ];
        for ( int i = 0; i < bookCount; ++i )
        {
            temp[i].name = books[i].name;
            temp[i].count = books[i].count;
            temp[i].avtor = books[i].avtor;
            temp[i].janr = books[i].janr;
        }
        temp[bookCount].name = book.name;
        temp[bookCount].count = book.count;
        temp[bookCount].avtor = book.avtor;
        temp[bookCount].janr = book.janr;
        delete [] books;
        books = temp;
        bookCount++;
    }
}

void Shelf::removeBook(int pos, int count)
{
    if ( ( pos < 0 ) || ( pos >= bookCount ) )
    {
        return;
    }

    const int diff = books[pos].count - count;
    books[pos].count = ( diff < 0 ) ? 0 : diff;

    if ( books[pos].count == 0 )
    {
        if ( bookCount == 1 )
        {
            delete [] books;
             books = nullptr;
             bookCount = 0;
        }
        else
        {
            Book* temp = new Book[ bookCount - 1 ];
            int j = 0;
            for ( int i = 0; i < bookCount ; ++i )
            {
                if ( i != pos)
                {
                    temp[j].name = books[i].name;
                    temp[j].count = books[i].count;
                    temp[j].avtor = books[i].avtor;
                    temp[j].janr = books[i].janr;
                    j++;
                }
            }
            delete [] books;
            books = temp;
            bookCount--;
        }
    }
}

Book *Shelf::at(int pos)
{
    Book* result = nullptr;
    if ( ( pos > -1) && ( pos < bookCount) )
    {
        result = books + pos;
    }
    return result;
}

int Shelf::findBookByName(const std::string &name, int startPos)
{
    int result = -1;
    for ( int i = startPos; i < bookCount; ++i )
    {
        if ( books[i].name == name )
        {
            result = i;
            break;
        }
    }
    return result;
}

int Shelf::findBookByAvtor(const std::string &avtor, int startPos)
{
    int result = -1;
    for ( int i = startPos; i < bookCount; ++i )
    {
        if ( books[i].avtor == avtor )
        {
            result = i;
            break;
        }
    }
    return result;
}

int Shelf::findBookByJanr(int janr, int startPos)
{
    int result = -1;
    for ( int i = startPos; i < bookCount; ++i )
    {
        if ( books[i].janr == janr )
        {
            result = i;
            break;
        }
    }
    return result;
}

int Shelf::getBookCount() const
{
    return bookCount;
}

void Shelf::outputAll()
{
    for ( int b = 0; b < bookCount ; ++b )
    {
        std::cout << "\t>>\tМесто № " << b + 1 << "("  << bookCount << "):\n";
        books[b].output();
    }

}

bool Shelf::operator==(const Shelf &s)
{
    bool result = false;
    if ( bookCount == s.bookCount )
    {
        result = true;
        for (int i = 0; i < bookCount; ++i)
        {
            result &= ( books[i] == s.books[i] );
        }
    }
    return result;
}

Shelf Shelf::operator=(const Shelf &s)
{
    if ( this != &s )
    {
        bookCount = s.bookCount;
        if ( bookCount > 0 )
        {
            books = new Book[s.bookCount];
            for ( int i = 0; i < bookCount; ++i)
            {
                books[i] = s.books[i];
            }
        }
    }
    return *this;
}

std::ofstream &operator<<(std::ofstream &ofs, Shelf &shelf)
{
    const int bookCount = shelf.getBookCount();
    ofs << bookCount << std::endl;
    for ( int i = 0; i < bookCount; ++i)
    {
        Book* pb = shelf.at(i);
        ofs << *pb;
    }
    return ofs;
}

std::ifstream &operator>>(std::ifstream &ifs, Shelf &shelf)
{
    int bookCount = 0;
    ifs >> bookCount;
    for ( int i = 0; i < bookCount; ++i)
    {
        Book book;
        ifs >> book;
        shelf.addBook( book );
    }
    return ifs;
}
