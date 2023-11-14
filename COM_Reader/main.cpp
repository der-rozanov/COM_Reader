#include "com_reader.h"
#include <fstream>

int main()
{
    ComReader Ard(L"COM7", 9600, 8);
    std::fstream write;
    write.open("C:/Users/MAN-MADE/Desktop/Projects/UAV/Skripts/COM_Reader/COM_Reader/FlowData.txt");

    char* str;
    std::vector<char> vct;
    std::string ideal_flow_speed;

    while (1)
    {
        std::cout << "Enter current speed or \"Exit\" to exit ";
        std::cin >> ideal_flow_speed;
        if (ideal_flow_speed == "exit" || ideal_flow_speed == "Exit")
            break;
        
        vct = Ard.getVectorData();
        std::cout << "ideal speed is " << ideal_flow_speed << " sensor measured ";
        write << "ideal speed is " << ideal_flow_speed << " sensor measured ";
        for (size_t i = 0; i < vct.size(); i++)
        {
            std::cout << vct[i];
            write << vct[i];
        }

        std::cout << "\n"; 
    }
    
    write.close();
    return 0;
}