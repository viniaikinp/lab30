#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <fstream>

struct Book;
class Shelf;
class Rack;

class Library
{
public:
    Library();
    virtual ~Library();

    void save();
    void load();

    void giveOut();  //  выдача

    void addShelf();//добавить полку
    void addShelf(int r);
    void removeShelf();//убрать полку

    void addRack(); //добавить стеллаж
    void removeRack();//удалить  стеллаж

    void addNewBook();//добавить новый книгу
    void addBook(int r, int s, Book& book);
    void removeBook();//убрать книгу
    void changeBook();//поменять книгу

    void changeBookInSomePlace();//поменять книги местами

    void outputAll();
    void outputByShelfAndRack(int r, int s, int b);//вывод книги по полке и стеллажу
    void findByShelfAndRack();//найти по полке (какая полка) и по стеллажу
    void findByName();//найти по имени
    void findByAvtor(); //найти по автору
    void findByJanr();//найти по жанру

    std::string filePath() const;
    void setFilePath(const std::string &filePath);

    int rackCount() const ;
    int shelvesCount() const;

    Book* getBook( int r, int s, int b);

private:
    void load( std::ifstream& ifs );
    void save( std::ofstream& ofs );
    void init( std::ofstream& ofs );
    bool askPosition(int *r, int *s, int *b);


private:
    std::string _filePath;
    Rack* racks = nullptr;
    int rack_count = 0;
};

#endif
