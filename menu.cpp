#include "menu.h"
#include "library.h"
#include "utils.h"

#include <iostream>

void Menu::main()
{
    while (1)
    {
        std::cout << std::endl;
        std::cout << "Что Вы хотите сделать?\n";
        std::cout << "1. Взять книгу\n";
        std::cout << "2. Добавить стеллаж,полку,книгу\n";
        std::cout << "3. убрать стеллаж или полку,книгу\n";
        std::cout << "4. скорректировать книгу\n";
        std::cout << "5. вывести информацию\n";
        std::cout << "6. Выйти из программы\n";
        std::cout << "Введите номер соответствующего действия: ";
        int input = checkCorrect(7);
        switch(input){
        case 1:
            if ( _library )
            {
                _library->giveOut();
            }
            break;
        case 2:
            add();
            break;
        case 3:
            rem();
            break;
        case 4:
            if ( _library )
            {
                _library->changeBook();
            }
            break;
        case 5:
            output();
            break;
        case 6:
            return;
        }
    }
}

void Menu::add()
{                                          //добавить что-то
    std::cout << "Что Вы хотите добавить?\n";
    std::cout << "1. Стеллаж\n";
    std::cout << "2. Полку\n";
    std::cout << "3. Книгу\n";
    std::cout << "Введите номер соответствующего действия: ";
    int input=checkCorrect(3);
    switch(input){
    case 1:
        if ( _library )
        {
            _library->addRack();
            std::cout << "Стелажей: " << _library->rackCount() << std::endl;
            std::cout << "Полок: " << _library->shelvesCount() << std::endl;
        }
        break;
    case 2:
        if ( _library )
        {
            _library->addShelf();
            std::cout << "Стелажей: " << _library->rackCount() << std::endl;
            std::cout << "Полок: " << _library->shelvesCount() << std::endl;
        }
        break;
    case 3:
        if ( _library )
        {
            _library->addNewBook();
        }
        break;
    }
}

void Menu::rem()
{                                           //убрать что-то
    int input;
    std::cout << "Что Вы хотите убрать?\n";
    std::cout << "1.Полку\n";
    std::cout << "2.Стеллаж\n";
    std::cout << "3.Книгу\n";
    std::cout << "Введите номер соответствующего действия: ";
    input=checkCorrect(3);
    switch(input){
    case 1:
        if ( _library )
        {
            _library->removeShelf();
        }
        break;
    case 2:
        if ( _library )
        {
            _library->removeRack();
        }
        break;
    case 3:
        if ( _library )
        {
            _library->removeBook();
        }
        break;
    }
}

void Menu::output()
{                        //вывести что-то
    std::cout << "Что вы хотите вывести?\n";
    std::cout << "1.Вывести элемент по номеру полки и стеллажа\n";
    std::cout << "2.Найти элемент по автору\n";
    std::cout << "3.Найти элемент по жанру\n";
    std::cout << "4.Найти элемент по названию\n";
    std::cout << "5.Вывести все\n";
    std::cout << "Введите номер соответствующего действия: ";
    int input = checkCorrect(5);
    switch(input){
    case 1:
        if ( _library )
        {
            _library->findByShelfAndRack();
        }
        break;
    case 2:
        if ( _library )
        {
            _library->findByAvtor();
        }
        break;
    case 3:
        if ( _library )
        {
            _library->findByJanr();
        }
        break;
    case 4:
        if ( _library )
        {
            _library->findByName();
        }
        break;
    case 5:
        if ( _library )
        {
            _library->outputAll();
        }
        break;
    }

}

Library *Menu::library() const
{
    return _library;
}

void Menu::setLibrary(Library *library)
{
    _library = library;
}
