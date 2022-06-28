#include"com_reader.h"

ComReader::ComReader(LPCWSTR PortName, int BaudRate, int byteSize) 
	: PortName(PortName), baud_rate(BaudRate), byte_size(byteSize)
{
	pack_size = 8;

	hSerial = ::CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); 

	if (hSerial == INVALID_HANDLE_VALUE) //Handle value error (falls out of the possible)
	{
		std::cout << "Handle value error:\n";
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			std::cout << "\tSerial port doesnt exist. \n";
		}
		else
		{
			std::cout << "\tUnknown handle value error:\n";
		}
	}

	//Connection Parameters
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "Getting state error. \n";
	}
	dcbSerialParams.BaudRate = baud_rate; //Reading speed
	dcbSerialParams.ByteSize = byte_size; //The size of the readable container
	dcbSerialParams.StopBits = ONESTOPBIT; //dont touch me there
	dcbSerialParams.Parity = NOPARITY; //dont touch me there
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "Error setting port state. \n\n";
	};

	//If errors appear
	if (hSerial == INVALID_HANDLE_VALUE || !GetCommState(hSerial, &dcbSerialParams) || !SetCommState(hSerial, &dcbSerialParams))
	{
		system("cls");
		std::cout << "Failed to connect to the port. \nThe name may have been entered incorrectly or the port may be busy. \nTry again. \n";

	}

	else
	{
		system("cls"); //else, we throw out a successful connection
		std::cout << "Connecting successfully.\nPress Esc to exit.";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
	}
};

void ComReader::PrintComData()
{
	DWORD recived_size = '0';
	char received_char = '0';
	while (true)
	{
		ReadFile(hSerial, &received_char, 1, &recived_size, 0);
		if (recived_size > 0)
			std::cout << received_char;
		else
			std::cout << "No char received";
	}
}


std::vector<char> ComReader::getVectorData()
{
	DWORD recived_size;
	char received_char = '0';
	std::vector<char> str = {};
	size_t it = 0;

	while (received_char != '\n')
	{
		ReadFile(hSerial, &received_char, 1, &recived_size, 0);
		if (recived_size > 0)
		{
			str.push_back(received_char);
			if (received_char != '\n' && received_char != '\0')
				it++;
		}
	}
	pack_size = it;
	return str;
}

char* ComReader::getCharData()
{
	int size = pack_size;
	int t = 0;
	DWORD recived_size;
	char received_char = '0';

	char* str = (char*)calloc(size, sizeof(char));
	while (received_char != '\n')
	{
		ReadFile(hSerial, &received_char, 1, &recived_size, 0);
		if (recived_size > 0)
		{
			str[t] = received_char;
			t++;
			if (t >= size)
			{
				str = (char*)realloc(str, (size + 1) * sizeof(char));
				size += 1;
			}
		}
	}
	pack_size = size - 2; // size without '\0' and '\n'

	return str;
}


size_t ComReader::getSizeData()
{
	return pack_size - 1;
}
