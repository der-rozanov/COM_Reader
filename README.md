# COM_Reader

This is a class for reading the contents of serial COM ports, for example, reading data coming from Arduino-type boards.

## How to use?
1)Upload files "com_reader.cpp" and "com_reader.h" to the root where the project is assembling.

2)add com_reader.h
    
    #include "com_reader.h"
    
3)An object of the ComReader class is created for reading.
     
     ComReader Ard(L"COM1", 9600, 8); 
     
Here COM3 is the name of the com port, 9600 is the read speed, 8 is the size of the readable character.
The reading speed parameter can be seen in the port opening settings on your board. For example on Arduino it is set like this:

      Serial.begin(9600);
      
4) A vector of the char type is returned from the com port, which can be processed later.

       std::vector<char> input_vector;
       input_vector = Ard.getCharData();
       
5) A C-style string is returned from the com port, which can be processed later.

        char* str;
        str = Ard.getCharData();
       
6) You can return the size of the received data packet using the method:

        size_t size = Ard.getSizeData();
        
7) An ordinary output to the console can be done by:

        PrintComData();
