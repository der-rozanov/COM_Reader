# COM_Reader

This is a class for reading the contents of serial COM ports, for example, reading data coming from Arduino-type boards.

## How to use?
1)Upload files "COM_Reader_F.cpp" and "COM_Reader_H.h" to the root where the project is assembling.

2)add COM_Reader_H.h
    
    #include "COM_Reader_H.h"
    
3)An object of the ComReader class is created for reading.
     
     ComReader Ard(L"COM1", 9600, 8); 
     
Here COM3 is the name of the com port, 9600 is the read speed, 8 is the size of the readable character.
The reading speed parameter can be seen in the port opening settings on your board. For example on Arduino it is set like this:

      Serial.begin(9600);
      
4) A vector of the char type is returned from the com port, which can be processed later.

       std::vector<char> input_vector;
       input_vector = Ard.getCharData();
       
5) You can return the size of the received data packet using the method:

        size_t size = Ard.getSizeData();
        
6) An ordinary output to the console can be done by:

        PrintComData();
