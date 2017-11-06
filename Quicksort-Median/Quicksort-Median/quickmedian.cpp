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
	int n1 = n0, n2 = n + 1;
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



void quickSort(int *a, int n1, int n2)
{
	int k = 0;
	int li = n1; int re = n2;

	int *kli = new int[n2 - n1];
	int *kre = new int[n2 - n1];

	while(( li < re) || (k > 0))
	{
		if (!(li < re))
		{
			li = kli[k];
			re = kre[k];
			k--;
		}
		int length = (re - li) + 1;
		int s = finde_ktes(a, li, li + length - 1, length / 2);
		if ((re - li) >= 2)
		{
			if ((s - li) > (re - 2))
			{
				k = k + 1;
				kli[k] = li;
				kre[k] = s - 1;
				li = s + 1;
			}
			else
			{
				k = k + 1;
				kli[k] = s + 1;
				kre[k] = re;
				re = s - 1;
			}
		}
		else
			li = re;

	}
}



int main()
{
	int zahl;
	unsigned int length;

	cout << "Filename: ";
	string filename = "sample1_no_dups.txt";
	//cin >> filename;

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
	quickSort(a, 0, length - 1);
	ende = ((clock() - start) * 1000) / CLOCKS_PER_SEC;

	ofstream output("output.txt");
	for (size_t i = 0; i < length+1; i++)
	{
		output << a[i] << endl;
	}
	output.close();

	cout << "Time to finished: " << ende << "ms" << endl;
	cout << "Swapped: " << global::swapped << endl;
	system("pause");
}
