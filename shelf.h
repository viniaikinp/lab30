#ifndef SHELF_H
#define SHELF_H

#include <string>

class Book;

class Shelf
{
public:
    Shelf();
    Shelf( const Shelf& s);

    virtual ~Shelf();

    void addBook( Book& book);
    void removeBook( int pos, int count );
    Book* at( int pos );

    int findBookByName( const std::string& name, int startPos = 0 );
    int findBookByAvtor( const std::string& avtor, int startPos = 0 );
    int findBookByJanr( int janr, int startPos = 0 );

    int getBookCount() const;
    void outputAll();

    bool operator==( const Shelf& s);
    Shelf operator= ( const Shelf& s);

private:
    Book* books = nullptr;
    int bookCount = 0;
};

std::ofstream& operator<<( std::ofstream& ofs, Shelf& shelf );
std::ifstream& operator>>( std::ifstream& ifs, Shelf& shelf );


#endif // SHELF_H
