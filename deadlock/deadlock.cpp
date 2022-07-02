#include <iostream>
#include <thread> // библиотека для многопоточности
#include <chrono>
#include <mutex> 
#include "SimpleTimer.h"
using namespace std;

// Взаимная блокировка, или deadlock может возникать, или не возникать в какой то случайно ситуации. Успеет ли поток создаться thread t2 и захватить mtx1 или нет

mutex mtx1;
mutex mtx2;

void Print1()
{
	mtx2.lock();

	this_thread::sleep_for(chrono::milliseconds(1));

	mtx1.lock();


	for (int i = 0; i < 5; ++i)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << '*';
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		cout << endl;
	}

	cout << endl;

	mtx1.unlock();

	mtx2.unlock();
}

void Print2()
{
	mtx1.lock();

	this_thread::sleep_for(chrono::milliseconds(2));

	mtx2.lock();


	for (int i = 0; i < 5; ++i)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << '%';
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		cout << endl;
	}

	cout << endl;

	mtx1.unlock();

	mtx2.unlock();
}




int main()
{
	setlocale(LC_ALL, "rus");

	SimpleTimer Timer; // Таймер для программы.

	thread t1(Print1);

	thread t2(Print2);

	t1.join();
	t2.join();

	return 0;
}


