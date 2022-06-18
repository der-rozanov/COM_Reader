#include "com_reader.h"

int main()
{
    //example 
    ComReader Ard(L"COM3", 9600, 8);
    
    char* str;
    std::vector<char> vct;

    while (1)
    {
        str = Ard.getCharData();
        vct = Ard.getVectorData();

        for (int i = 0; i < Ard.getSizeData(); i++)
            std::cout << str[i];

        for (int i = 0; i < Ard.getSizeData(); i++)
            std::cout << vct[i];
    }
    //example

    return 0;
}