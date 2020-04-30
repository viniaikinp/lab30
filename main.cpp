#include <iostream>

#include "menu.h"// для использования  menu;
#include "library.h"

int main( int argc, char** argv)
{
    Library library;
    switch(argc){                      //для проверки значений argc, проверяем передано ли что-то
        case 1:
            std::cout << "не передано название файла\nбудет использовано имя по умолчанию-file.txt" << std::endl;
            library.setFilePath( "file.txt" );
            break;
        case 2:
            library.setFilePath( argv[1] );
            break;
        default:
            std::cout << "ошибка!!! лишние аргументы при вызове" << std::endl;
            return 0;
    }

    library.load();

    Menu menu;
    menu.setLibrary( &library );
    menu.main();

    return 0;
}
