#include "utils.h"

#include <string>
#include <iostream>

int StrToInt( const std::string& str)
{
    int i = 0;
    int flag = 0;
    if ( str.size() > 6 )//длина строки
        return -1; //вернуть -1
    while(str[i]!=0)
    {
        if(str[i]=='1'||str[i]=='2'||str[i]=='3'||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]=='0')
            i++;
        else
        {
            flag=1;
            break;
        }
    }
    if ( flag == 0 )
        return stoi( str );
    else
        return -1;
}

int checkCorrect(int max) //возвращает число, меньшее max  !ЭТО ЗАЩИЩАЕТ ОТ НЕПРАВИЛЬНОГО ИСПОЛЬЗОВАНИЯ!
{
    int input = -1;
    while(1)
    { //бесконечный цикл
        std::string str;
        std::getline( std::cin, str );
        input = StrToInt( str );
        if( ( input != -1 ) && ( input <= max ) && ( input > 0 ))
            break;
        std::cout << "Введено некорректное значение. Повторите попытку: ";
    }
    return input;
}
