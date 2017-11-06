#include <iostream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

namespace global
{
	unsigned int swapped = 0;
}

inline void vertausche(int &a, int &b)
{
	int swap = a;
	a = b;
	b = swap;

	global::swapped++;
}



int spalte_auf(int *a, int n1, int n2)
{
	int tind = (n1 + n2) / 2;
	vertausche(a[tind], a[n1]);
	tind = n1;

	for (int i = n1 + 1; i <= n2; i++)
	{
		if (a[i] <= a[tind])
		{
			vertausche(a[i], a[tind + 1]);
			vertausche(a[tind], a[tind + 1]);
			tind++;
		}

	}
	return tind;
}

int finde_ktes(int *a, int n0, int n, int k)
{
	int n1 = n0, n2 = n;
	int tind;
	while (true)
	{
		tind = spalte_auf(a, n1, n2);
		tind = tind - n1 + 1;

		if (tind < k)
		{
			n1 = n1 + tind;
			k = k - tind;
		}
		else if (tind == k)
			return n1 - 1 + k;
		else
			n2 = n1 + tind - 2;
	}
}


#define in int
void quickSortrek(int *a, int n1, int n2)
{
	in length = (n2 - n1) + 1;
	if (length <= 1) return;

	int p = finde_ktes(a, n1, n1 + length, length / 2);
	quickSortrek(a, n1, p - 1);
	quickSortrek(a, p + 1, n2);
}



int main()
{
	int zahl;
	int length;

	cout << "Filename: ";
	string filename = "test.txt";
	cin >> filename;

	ifstream f(filename);
	f >> length;
	int *a = new int[length + 1];

	unsigned int index = 0;
	while (!f.eof() && index <= length)
	{
		f >> zahl;
		a[index++] = zahl;
	}
	cout << "Eingelesen: " << index << endl;

	int ende, start = clock();
	quickSortrek(a, 0, length - 1);
	ende = ((clock() - start) * 1000) / CLOCKS_PER_SEC;

	ofstream output("output.txt");
	for (size_t i = 0; i < length; i++)
	{
		output << a[i] << endl;
	}
	output.close();

	cout << "Time to finished: " << ende << "ms" << endl;
	cout << "Swapped: " << global::swapped << endl;
	system("pause");
}