// MergeSortAsm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
using namespace std;

const int arraylen = 1000;

int L[arraylen], R[arraylen], Arr[arraylen];

void merge(int arr[], int l, int m, int r)
{
	//i is a pointer to arr[l....m]
	//j is a pointer to arr[m+1..r]	
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	for (i = 0; i < n1; i++)
		L[i] = Arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = Arr[m + 1 + j];

	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	
	__asm 
	{
		
		while1 :

			mov eax, i
			mov ebx, n1
			cmp eax, ebx
			jge outwhile1
			mov eax, j
			mov ebx, n2
			cmp eax, ebx
			jge outwhile1

			; L[i] to ebx
			mov eax, i
			mov ecx, 4
			mul ecx
			mov edx, OFFSET L
			add edx, eax
			mov ebx, [edx]

			; R[j] to ecx
			mov eax, j
			mov ecx, 4
			mul ecx
			mov edx, OFFSET R
			add edx, eax
			mov ecx, [edx]

			cmp ebx, ecx
			jg elsepart

			mov eax, k
			mov ecx, 4
			mul ecx
			mov ebx, OFFSET Arr
			add ebx, eax
								;;;;;;;;; ebx = arr[k]
			mov eax, i
			mov ecx, 4
			mul ecx
			mov edx, OFFSET L
			add edx, eax
								;;;;;;;;; edx = L[i]
			mov eax, [edx]
			mov [ebx], eax
			mov eax, i
			inc eax
			mov i, eax
			
			jmp outif

		elsepart :	
			mov eax, k
			mov ecx, 4
			mul ecx
			mov ebx, OFFSET Arr
			add ebx, eax
								;;;;;;;;; ebx = arr[k]
			mov eax, j
			mov ecx, 4
			mul ecx
			mov edx, OFFSET R
			add edx, eax
								;;;;;;;;; edx = R[j]
			mov eax, [edx]
			mov [ebx], eax
			mov eax, j
			inc eax
			mov j, eax
		outif:
			mov eax, k
			inc eax
			mov k, eax

			jmp while1

		outwhile1:	
		while2 :
			mov eax, i
			mov ebx, n1
			cmp eax, ebx
			jge outwhile2

			mov eax, k
			mov ecx, 4
			mul ecx
			mov ebx, OFFSET Arr
			add ebx,eax
								;;;;;;;;; ebx = arr[k]
			mov eax, i
			mov ecx, 4
			mul ecx
			mov edx, OFFSET L
			add edx, eax
								;;;;;;;;; edx = L[i]
			mov eax, [edx]
			mov [ebx], eax
			mov eax, i
			inc eax
			mov i, eax
			mov eax, k
			inc eax
			mov k, eax
			jmp while2
		outwhile2:

		while3:
			mov eax, i
			mov ebx, n2
			cmp eax, ebx
			jge outwhile3

			mov eax, k
			mov ecx, 4
			mul ecx
			mov ebx, OFFSET Arr
			add ebx, eax
								;;;;;;;;; ebx = arr[k]
			mov eax, j
			mov ecx, 4
			mul ecx
			mov edx, OFFSET R
			add edx, eax
								;;;;;;;;; edx = R[j]
			mov eax, [edx]
			mov[ebx], eax
			mov eax, j
			inc eax
			mov j, eax
			mov eax, k
			inc eax
			mov k, eax
			jmp while3
		outwhile3:
	}
	/*
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}*/
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int main()
{
	int n;//array length
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> Arr[i];

	mergeSort(Arr, 0, n-1);

	for (int i = 0; i < n; i++)
		cout << Arr[i] << " ";
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
//
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
