#ifndef BOOK_H
#define BOOK_H

#include <fstream>
#include <string>

struct Book   // имя структуры
{
    std::string name;
    int count = 0;
    std::string avtor;
    int janr = 0;

    void output();
    void input();
    bool operator== ( const Book& b);
    Book operator= ( const Book& b);
};

std::ofstream& operator<<( std::ofstream& ofs, const Book& book );
std::ifstream& operator>>( std::ifstream& ifs, Book& book );

#endif // BOOK_H
