#include "book.h"
#include "utils.h"

#include <iostream>

std::ofstream &operator<<(std::ofstream &ofs, const Book &book)
{
    ofs << book.name << std::endl;
    ofs << book.count << std::endl;
    ofs << book.avtor << std::endl;
    ofs << book.janr << std::endl;

    return ofs;
}

void skipEOL( std::ifstream& ifs )
{
    char c = ifs.peek();
    while ( c == '\n')
    {
        ifs.get();
        c = ifs.peek();
    }
}

std::ifstream &operator>>(std::ifstream &ifs, Book &book)
{
    skipEOL( ifs );
    std::getline( ifs, book.name );

    ifs >> book.count;

    skipEOL( ifs );
    std::getline( ifs, book.avtor );

    ifs >> book.janr;

    return ifs;
}


void Book::output()
{
    std::cout << "Название: " << name << std::endl;
    std::cout << "Количество: " << count  << std::endl;
    std::cout << "Автор: " << avtor << std::endl;
    switch(janr)
    {
    case 1: std::cout << "жанр: детектив\n" ;
        break;
    case 2: std::cout << "жанр: классика\n" ;
        break;
    case 3: std::cout << "жанр: фантастика\n";
        break;
    case 4: std::cout << "жанр: кулинария\n" ;
        break;
    }
}

void Book::input()
{
    std::cout << "\t>> Новая книга:\n";
    std::cout << "\t>> Введите имя(максимум 100 символов): ";
    std::getline( std::cin, name );
    std::cout << "\t>> Введите количество экземпляров: ";
    count = checkCorrect(1000000);
    std::cout << "\t>> Введите автора(максимум 100 символов): ";
    std::getline( std::cin, avtor );
    std::cout << "\t>> Выберите жанр:\n";
    std::cout << "\t>> 1. детектив\n2. классика\n3. фантастика\n4. кулинария\n";
    janr = checkCorrect(4);
}

bool Book::operator==(const Book &b)
{
    return ( (name == b.name)
             && (count == b.count)
             && (avtor == b.avtor)
             && ( janr == b.janr ));
}

Book Book::operator=(const Book &b)
{
    name = b.name;
    count = b.count;
    avtor = b.avtor;
    janr = b.janr;
    return *this;
}
