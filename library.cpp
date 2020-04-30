#include "library.h"
#include "utils.h"
#include "book.h"
#include "shelf.h"
#include "rack.h"

#include <iostream>
#include <fstream>

void Library::load( std::ifstream& ifs )
{
    ifs >> rack_count;
    if ( rack_count > 0 )
    {
        racks = new Rack[rack_count]; // динамическое выделение памяти на массив указателей
        for ( int i=0; i < rack_count; i++)
        {
            ifs >> racks[i];
        }
    }
}

void Library::save( std::ofstream& ofs )
{
    ofs << rack_count << std::endl;
    for ( int i = 0; i < rack_count; i++)
    {
        ofs << racks[i];
    }
}

void Library::giveOut()
{
    if ( rack_count == 0 )
    {
        std::cout << "\t>> Нет полок и стеллажей\n";
        return;
    }

    std::cout <<"Введите номер стеллажа ( 1.." << rack_count << ")\n";
    int r = checkCorrect( rack_count ) - 1;
    if ( racks[r].getShelfCount() == 0 )
    {
        std::cout << "\t>> Книги на полке отсутствуют\n";
        return;
    }

    const int shelfCount = racks[r].getShelfCount();
    std::cout <<"Введите номер полки ( 1.." << shelfCount << ")\n";
    int s = checkCorrect( shelfCount ) - 1;

    const int bookPlaceCount = racks[r].at(s)->getBookCount();
    std::cout <<"Введите номер места на полке ( 1.." << bookPlaceCount << ") \n";
    int b = checkCorrect( bookPlaceCount ) - 1;
    if ( racks[r].at(s)->getBookCount() == 0)
    {
        std::cout << "\t>> Книги на полке отсутствуют\n";
        return;
    }

    outputByShelfAndRack(r, s, b);
    const int bookCount =  racks[r].at(s)->at(b)->count;
    std::cout << "\t>> Какое число вы хотите выдать ( 1.." << bookCount << ") ?\n";
    int count = checkCorrect(  bookCount );//a=a-b
    racks[r].at(s)->removeBook( b , count );
}

void Library::addShelf()
{
    if ( rack_count == 0 )
    {
        std::cout <<"Стеллажей еще нет.\n";
        return;
    }

    std::cout <<"Введите номер стеллажа ( 1.." << rack_count << ")\n";
    int r = checkCorrect( rack_count ) - 1;
    addShelf( r );
}

void Library::addShelf( int r )
{
    if (( r > -1) && ( r < rack_count ) )
    {
        Shelf shelf;
        racks[r].addShelf( shelf );
    }
}

void Library::addRack()
{
    if ( racks == nullptr )
    {
        racks = new Rack[1];
        rack_count = 1;
    }
    else
    {
        Rack* temp = new Rack[ rack_count + 1];
        for ( int i = 0; i < rack_count; ++i)
        {
            temp[i] = racks[i];
        }
        delete[] racks;
        racks = temp;
        rack_count++;
    }
}

void Library::removeShelf()
{
    if ( rack_count == 0 )
    {
        std::cout << "\t>> Нет стеллажей\n";
        return;
    }

    std::cout << "\t>> С какого стеллажа удалить полку ( 1.." << rack_count << ")?\n";
    int r = checkCorrect( rack_count ) - 1;

    const int shelfCount = racks[r].getShelfCount();
    std::cout << "\t>> Какую удалить полку ( 1.." << shelfCount << ")?\n";
    int s = checkCorrect( shelfCount );

    racks[r].removeShelf( s );

}

void Library::removeRack()
{
    if ( rack_count == 0 )
    {
        std::cout << "\t>> Нет стеллажей\n" ;
        return;
    }

    std::cout <<"\t>> Какой стеллаж удалить ( 1.." << rack_count << ")?\n";
    int pos = checkCorrect( rack_count );

    Rack* temp = new Rack[ rack_count - 1];
    int j = 0;
    for( int k = 0; k < rack_count; k++)
    {
        if ( k != pos )
        {
            temp[j] = racks[k];
            j++;
        }
    }
    delete [] racks;
    racks = temp;
}

void Library::addNewBook()
{
    if ( rack_count == 0)
    {
        std::cout << "\t>> Нет полок и стеллажей\n";
        return;
    }

    std::cout << "\t>> Введите место, куда хотите поместить книги\n";
    std::cout << "\t>> Стеллаж (1.." << rack_count << "): ";
    int r = checkCorrect( rack_count )-1;
    const int shelfCount = racks[r].getShelfCount();
    std::cout << "\t>> Полка (1.." << shelfCount << "): " ;
    int s = checkCorrect( shelfCount ) - 1;

    Book book;
    book.input();
    addBook( r, s, book );

}

void Library::addBook( int r, int s, Book& book )
{
    racks[r].at(s)->addBook( book );
}

void Library::removeBook()
{
    if( rack_count==0 )
    {
        std::cout << "\t>> Нет полок или стеллажей\n" ;
        return;
    }

    std::cout << "\t>> Введите место, откуда хотите убрать книги\n";
    int r = -1;
    int s = -1;
    int b = -1;
    if ( askPosition( &r,&s, &b) )
    {
        const int bookCount = racks[r].at(s)->at(b)->count;
        std::cout << "\t>> Количество книг ( 1.." << bookCount << ") : " ;
        int count = checkCorrect( bookCount );
        racks[r].at(s)->removeBook( b, count );
    }

}

void Library::changeBook(){
    std::cout << "\t>> Сначала удалите, а потом добавьте книгу.\n";
}

void Library::outputAll()
{
    if ( racks == nullptr )
    {
        std::cout << "\t>> Библиотека пуста.\n";
    }
    else
    {
        for ( int r = 0; r < rack_count; ++r)
        {
            std::cout << "\t>> Стеллаж № " << r + 1 << "(" << rack_count << ") :\n";
            racks[r].outputAll();
        }
    }

}

void Library::outputByShelfAndRack(int r, int s, int b)
{
    if ( ( r < 0 ) || ( r >= rack_count ) )
    {
        std::cout << "\t>> Нет стеллажей\n";
        return;
    }

    const int shelvsCount = racks[r].getShelfCount();
    if ( ( s < 0 ) || ( s >= shelvsCount )  )
    {
        std::cout << "\t>> Нет полок\n";
        return;
    }

    const int bookPlaceCount = racks[r].at(s)->getBookCount() ;
    if ( ( b > -1 ) && ( b < bookPlaceCount ) )
    {
        racks[r].at(s)->at(b)->output();
    }
    else
    {
        std::cout << "\t>> Нет книг\n";
        return;
    }

}

void Library::findByShelfAndRack()
{
    if ( rack_count == 0 )
    {
        std::cout << "\t>> Нет полок или стеллажей\n";
        return;
    }

    std::cout << "\t>> Введите место\n";

    int r = -1;
    int s = -1;
    int b = -1;
    if ( askPosition( &r, &s, &b ) )
    {
        outputByShelfAndRack( r, s, b);
    }
}

bool Library::askPosition( int* r, int* s, int* b )
{
    std::cout << "\t>> Стеллаж (1.." << rack_count << "): " ;
    *r = checkCorrect( rack_count )-1;

    const int shelfCount = racks[*r].getShelfCount();
    std::cout << "\t>> Полка (1.." << shelfCount << "): ";
    *s = checkCorrect( shelfCount )-1;

    const int bookPlaceCount = racks[*r].at(*s)->getBookCount();
    std::cout << "\t>> Место на полке (1.." << bookPlaceCount << "): ";
    *b = checkCorrect(  bookPlaceCount )-1;

    return true;
}


void Library::findByName()
{
    std::cout << "\t>> Введите название: ";
    std::string name;
    std::getline( std::cin, name );

    for(int r = 0; r < rack_count; r++)
    {
        for ( int s = 0; s < racks[r].getShelfCount(); ++s )
        {
            int b = racks[r].findBookByName( name, s, 0);
            while ( b > -1 )
            {
                std::cout  << " Стеллаж: " << r << "Полка: " << s << " Место: " << b << std::endl;
                outputByShelfAndRack( r, s, b);
                b = racks[r].findBookByName( name, s, b + 1 );
            }
        }
    }
    std::cout << std::endl;
}

void Library::findByAvtor()
{
    std::cout << "\t>> Введите автора: ";
    std::string avtor;
    std::getline( std::cin, avtor);
    for(int r = 0; r < rack_count; r++)
    {
        for ( int s = 0; s < racks[r].getShelfCount(); ++s )
        {
            int b = racks[r].findBookByAvtor( avtor, s, 0);
            while ( b > -1 )
            {
                std::cout  << " Стеллаж: " << r << "Полка: " << s << " Место: " << b << std::endl;
                outputByShelfAndRack( r, s, b);
                b = racks[r].findBookByAvtor( avtor, s, b + 1 );
            }
        }
    }
    std::cout << std::endl;
}

void Library::findByJanr()
{
    std::cout << "\t>> Выберите жанр:\n";
    std::cout << "\t>> 1. дтектив\n2. классика\n3. финтастика\n4. кулинария\n";
    int janr = checkCorrect(4);
    for(int r = 0; r < rack_count; r++)
    {
        for ( int s = 0; s < racks[r].getShelfCount(); ++s )
        {
            int b = racks[r].findBookByJanr( janr, s, 0);
            while ( b > -1 )
            {
                std::cout  << " Стеллаж: " << r << "Полка: " << s << " Место: " << b << std::endl;
                outputByShelfAndRack( r, s, b);
                b = racks[r].findBookByJanr( janr, s, b + 1 );
            }
        }
    }
    std::cout << std::endl;
}

std::string Library::filePath() const
{
    return _filePath;
}

void Library::setFilePath(const std::string &filePath)
{
    _filePath = filePath;
}

int Library::rackCount() const
{
    return rack_count;
}

int Library::shelvesCount() const
{
    int result = 0;
    for ( int i = 0; i < rack_count; ++i )
    {
        result += racks[i].getShelfCount();
    }
    return result;
}

Book *Library::getBook(int r, int s, int b)
{
    Shelf* shelf = racks[r].at(s);
    return shelf->at(b);
}

Library::Library()
{

}

Library::~Library()
{
    if ( !_filePath.empty() )
    {
        save();
    }
}

void Library::load()
{
    std::ifstream ifs;
    ifs.open( _filePath );
    if ( !ifs.is_open() )
    {
        std::cout << "\t>> Файла не существует. он будет создан\n";
        std::ofstream ofs;
        ofs.open( _filePath );
        init( ofs );
        ofs.close();
    }
    else
    {
        load( ifs );
        ifs.close();
    }
}

void Library::save( )
{
    std::ofstream ofs;
    ofs.open( _filePath );
    save( ofs );
    ofs.close();
}

void Library::init( std::ofstream& ofs )// init-инициализация (создание файла)
{
    int temp = 0;
    ofs << temp << " " << temp << std::endl; // данных нет, будет создан пустой файл
}
