#include"COM_Reader_H.h"

ComReader::ComReader(LPCWSTR PortName, int BaudRate, int byteSize) : PortName(PortName), _BaudRate(BaudRate), _byteSize(byteSize)
{
	hSerial = ::CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //Присвайваем значение

	if (hSerial == INVALID_HANDLE_VALUE) //Обработка ошибки значения дескриптора (выпадает из возможныз)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			std::cout << "Serial port doesnt exist. \n";
		}
	}

	//Параметры соединения 
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "Getting state error. \n";
	}
	dcbSerialParams.BaudRate = _BaudRate; //Скорость чтения
	dcbSerialParams.ByteSize = _byteSize; //Размер читаемого контейнера 
	dcbSerialParams.StopBits = ONESTOPBIT; //хз, не лезь
	dcbSerialParams.Parity = NOPARITY; //хз, не лезь
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "Error setting port state. \n\n";
	};

	//Если появляются ошибки  
	if (hSerial == INVALID_HANDLE_VALUE || !GetCommState(hSerial, &dcbSerialParams) || !SetCommState(hSerial, &dcbSerialParams))
	{
		system("cls");
		std::cout << "Failed to connect to the port. \nThe name may have been entered incorrectly or the port may be busy. \nTry again. \n";

	}
	else
	{
		system("cls"); //иначе выкидываем успешный коннект 
		std::cout << "Connecting successfully.\nPress Esc to exit.";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
	}
};

void ComReader::PrintComData()
{
	DWORD iSize = '0';
	char sReceivedChar = '0';
	while (true)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
			std::cout << sReceivedChar;
	}
}


std::vector<char> ComReader::getCharData()
{
	DWORD iSize;
	char sReceivedChar = '0';
	std::vector<char> str = {};
	size_t it = 0;

	while (sReceivedChar != '\n')
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
		{
			str.push_back(sReceivedChar);
			if (sReceivedChar != '\n' && sReceivedChar != '\0')
				it++;
		}
	}
	packSize = it;
	return str;
}


size_t ComReader::getSizeData()
{
	return packSize - 1;
}
