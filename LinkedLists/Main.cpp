#include <iostream>
#include "List.h"

template <typename T>
T add(T lhs, T rhs)
{
	return lhs + rhs;
}

//Create a function that will sort an array of integers using bubble sort
//Print the array before and after it's sorted

void bubbleSort(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = length - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

//void print(int array[], int length) 
//{
//	//Iterate through the array
//	for (int i = 0; i < length; i++) 
//	{
//		//Sending the indexed number to the console
//		std::cout << array[i];
//
//		if (i < length - 1) 
//		{
//			//Comma for clarity
//			std::cout << ", ";
//		}
//	}
//	//End the line
//	std::cout << std::endl;
//	system("pause");
//}

int main()
{
	List<int>* testList = new List<int>();

	testList->initialize();

	testList->pushFront(2);
	testList->pushFront(4);
	testList->pushFront(6);
	testList->pushFront(8);
	testList->pushBack(10);

	testList->print();
	testList->sort();
	testList->print();

	system("pause");
}