#include <iostream>
#include <chrono>
#include <time.h>
#include <algorithm>
#include <Windows.h>
#include <fstream>
using namespace std;
using namespace std::chrono;
void quickSort(int *ourArray, int p, int r);
int qsPartition(int *ourArray, int p, int r);
void InsertionSort(int *ourArray, int length);
void mergeSort(int *ourArray, int length);
void ourMerge(int *ourArray, int p, int q, int r);

void mergeSort(int *ourArray, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(ourArray, p, q);
		mergeSort(ourArray, q + 1, r);
		ourMerge(ourArray, p, q, r);
	}
}
void ourMerge(int *ourArray, int p, int q, int r)
{
	int* left = NULL;
	int* right = NULL;
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	left = new int[n1];
	right = new int[n2];
	for (i = 0; i < n1; i++)
		left[i] = ourArray[p + i];
	for (j = 0; j < n2; j++)
		right[j] = ourArray[q + 1 + j];

	i = 0;
	j = 0;
	k = p;

	for (k; k <= r; k++)
	{
		if (left[i] <= right[j])
		{
			ourArray[k] = left[i];
			i++;
		}
		else
		{
			ourArray[k] = right[j];
			j++;
		}
	}

	delete[] left;
	delete[] right;
}

void quickSort(int *ourArray, int p, int r)
{
	if (p < r)
	{
		int q = qsPartition(ourArray, p, r);
		quickSort(ourArray, p, q - 1);
		quickSort(ourArray, q + 1, r);
	}
}
int qsPartition(int *ourArray, int p, int r)
{
	int x = ourArray[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (ourArray[j] <= x)
		{
			i = i + 1;
			swap(ourArray[i], ourArray[j]);
		}
	}
	swap(ourArray[i + 1], ourArray[r]);
	return i + 1;
}
void InsertionSort(int *ourArray, int length)
{
	//int i, j, key, numLength = length;
	int j;
	int key;
	int i;

	for (j = 1; j <= length; j++)    // Start with 1 (not 0)
	{
		key = ourArray[j];
		i = j - 1;
		while (i > -1 && ourArray[i] > key)
		{
			ourArray[i + 1] = ourArray[i];
			i = i - 1;
		}
		//for (i = j - 1; (i >= 0) && (ourArray[i] < key); i--)   // Smaller values move up
		//{
		//	ourArray[i + 1] = ourArray[i];
		//}
		ourArray[i + 1] = key;    //Put key into its proper location
	}

	return;
}
int main()
{
	float average;
	ofstream myfile;
	myfile.open("data.txt");

	int a[5][1000];
	//int b[1000];
	//int temp[1000];
	LARGE_INTEGER start, end, freq;;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 999; j++)
		{
			a[i][j] = rand();
		}
	}

	myfile << "Insertion sort" << endl;
	for (int n = 99; n <= 999; n = n + 100)
	{
		myfile << n + 1 << " elements" << endl;
		average = 0;
		for (int i = 0; i <= 4; i++)
		{
			int* b = NULL;
			b = new int[n + 1];
			for (int k = 0; k <= n; k++)
			{
				b[k] = a[i][k];
			}

			//auto start_time = std::chrono::high_resolution_clock::now();

			//SOURCE: http://www.cplusplus.com/forum/general/80867/
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&start);
			InsertionSort(b, n);
			QueryPerformanceCounter(&end);
			//auto end_time = std::chrono::high_resolution_clock::now();
			//auto time = end_time - start_time;

			//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
			myfile << i + 1 << ":" << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			average += (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
			cout << "Insertion sort of " << (n + 1);
			cout << " elements session " << (i + 1);
			cout << " took: ";
			//long long ms = chrono::duration_cast<std::chrono::microseconds>(time).count();
			//cout << ms << endl;
			//std::cout << "The resolution of this timer is: " << freq.QuadPart << " Hz." << std::endl;
			cout << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			delete[] b;
		}
		myfile << "Average: " << average / 5 << endl;
		cout << "Average: " << average / 5 << endl;
		myfile << endl;
	}
	myfile << endl;

	myfile << "Quick sort" << endl;
	for (int n = 99; n <= 999; n = n + 100)
	{
		myfile << n + 1 << " elements" << endl;
		average = 0;
		//cout << n << endl;
		for (int i = 0; i <= 4; i++)
		{
			int* b = NULL;
			b = new int[n + 1];
			for (int k = 0; k <= n; k++)
			{
				b[k] = a[i][k];
			}

			//auto start = std::chrono::high_resolution_clock::now();

			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&start);
			quickSort(b, 0, n);
			QueryPerformanceCounter(&end);
			//auto end = std::chrono::high_resolution_clock::now();
			//a/uto elapsed = end - start;
			//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

			cout << "QuickSort sort of " << (n + 1);
			cout << " elements session " << (i + 1);
			cout << " took: ";
			cout << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			average += (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
			myfile << i + 1 << ":" << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			//float end = (float)End / CLOCKS_PER_SEC;
			//cout << microseconds << endl;
			//cout << clock() - Start << endl;
			delete[] b;
		}
		myfile << "Average: " << average / 5 << endl;
		cout << "Average: " << average / 5 << endl;
		myfile << endl;
	}

	myfile << "Merge sort" << endl;
	for (int n = 99; n <= 999; n = n + 100)
	{
		myfile << n + 1 << " elements" << endl;
		average = 0;
		//cout << n << endl;

		for (int i = 0; i <= 4; i++)
		{
			int* b = NULL;
			b = new int[n + 1];
			for (int k = 0; k <= n; k++)
			{
				b[k] = a[i][k];
			}

			//auto start = std::chrono::high_resolution_clock::now();
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&start);
			mergeSort(b, 0, n);
			QueryPerformanceCounter(&end);
			//auto end = std::chrono::high_resolution_clock::now();
			//a/uto elapsed = end - start;
			//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

			cout << "MergeSort sort of " << (n + 1);
			cout << " elements session " << (i + 1);
			cout << " took: ";
			cout << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			average += (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
			myfile << i + 1 << ":" << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart
				<< " microSeconds" << std::endl;
			//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			//float end = (float)End / CLOCKS_PER_SEC;
			//cout << microseconds << endl;
			//cout << clock() - Start << endl;
			delete[] b;
		}
		myfile << "Average: " << average / 5 << endl;
		cout << "Average: " << average / 5 << endl;
		myfile << endl;
	}
	myfile << endl;
	myfile.close();
	
}