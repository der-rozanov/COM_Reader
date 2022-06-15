#pragma once

#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>

/// <summary>
/// The ComReader class creates objects for reading data from serial UART ports.
/// </summary>
struct ComReader
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="PortName">Port name LPCWSTR</param>
	/// <param name="BaudRate">Operating speed, default 9600 </param>
	/// <param name="byteSize">The size of the received packets, by default 8</param>
	ComReader(LPCWSTR PortName, int BaudRate = 9600, int byteSize = 8);
	
	
	/// <summary>
	/// Outputs all the information received from the COM port to the console.
	/// </summary>
	void PrintComData();

	/// <summary>
	/// Returns a vector-string received from the COM port
	/// </summary>
	std::vector<char> getCharData();

	/// <summary>
	/// Returns the size of the received packet.
	/// </summary>
	/// <returns></returns>   
	size_t getSizeData();

private:
	HANDLE hSerial;
	LPCWSTR PortName;
	int baud_rate;
	int byte_size;
	size_t pack_size;
};
