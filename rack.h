#ifndef RACK_H
#define RACK_H

#include <string>
#include <fstream>

class Shelf;
struct Book;

class Rack
{
public:
    Rack();
    Rack( const Rack& r);
    virtual ~Rack();

    int getShelfCount() const;

    void addShelf( Shelf& shelf );
    void removeShelf( int pos );
    Shelf* at( int pos );

    void addBook( int shelfNum, Book& book);
    void removeBook( int shelfNum, int pos, int count );

    int findBookByName( const std::string& name, int shelfNum = 0, int startPos = 0 );
    int findBookByAvtor( const std::string& avtor, int shelfNum = 0, int startPos = 0 );
    int findBookByJanr(int janr, int shelfNum, int startPos = 0);

    void outputAll();

    bool operator==( const Rack& r);
    Rack operator=( const Rack& r);

private:
    Shelf* shelvs = nullptr;
    int shelfCount = 0;
};


std::ofstream& operator<<( std::ofstream& ofs, Rack& rack );
std::ifstream& operator>>( std::ifstream& ifs, Rack& rack );


#endif // RACK_H
