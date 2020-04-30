#ifndef MENU_H //если не объявлено MENU_H
#define MENU_H//объявить MENU_H

class Library;

class Menu
{
public:
    void main();

    void add();  //добавить что-то
    void rem();  //убрать что-то
    void output();  //вывести что-то

    Library *library() const;
    void setLibrary(Library *library);

private:
    Library* _library = nullptr;
};

#endif//конец если
