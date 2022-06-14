#pragma once

#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>

/// <summary>
/// Класс ComReader создает объекты для чтения данных из последовательных UART портов.
/// </summary>
struct ComReader
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="PortName">Название порта как LPCWSTR</param>
	/// <param name="BaudRate">Скорость работы, по умолчанию 9600</param>
	/// <param name="byteSize">Размер принимаемых пакетов, по умолчанию 8</param>
	ComReader(LPCWSTR PortName, int BaudRate = 9600, int byteSize = 8);
	
	
	/// <summary>
	/// Выводит в консоль всю информацию, получаемую с COM порта.
	/// </summary>
	void PrintComData();

	/// <summary>
	/// Возвращает вектор-строку принятую из COM порта
	/// </summary>
	std::vector<char> getCharData();

	/// <summary>
	/// Возвращает размер принятого пакета.
	/// </summary>
	/// <returns></returns>
	size_t getSizeData();

private:
	HANDLE hSerial;
	LPCWSTR PortName;
	int _BaudRate;
	int _byteSize;
	size_t packSize;

};
