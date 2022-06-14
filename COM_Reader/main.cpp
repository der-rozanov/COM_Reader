#include "COM_Reader_H.h"

int main()
{
    //example 
    ComReader Ard(L"COM3", 9600, 8);
    std::vector<char> inp_str;

    while (1)
    {
        inp_str = Ard.getCharData();
            for (int i = 0; i < Ard.getSizeData(); i++)
            {
                std::cout << inp_str[i];
            }
            std::cout << std::endl;
    }
    //example

    return 0;
}