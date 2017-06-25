// Nakan.cpp: определяет точку входа для консольного приложения.
//
//#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"
//#include <iostream>
#include <time.h>

using namespace std;


FILE *file, *conf;
int fl_lst;
int N=0;
long double count1 = 0;
	
void print(int N, int *list) {
	int j = 0;
	if (fl_lst) // вывод файл 
	{
		for (int i = 0; i < N; i++) fprintf(file, "%d", list[i]);
		fprintf(file, "\n");
	}
	else {
		for (int i = 0; i < N; i++) j++; // это нужно для замедления программы 
	}

	count1++;
}

void findChild(int *list, int len, int cd)
{
	if (len == N)
	{
		print(len, list);
		return;
	}
	//get subtree lengths
	int rsize = 1;
	int ssize = 1;
	while (list[len - rsize] > cd + 1 && rsize < len)
		rsize++;
	while (list[len - rsize - ssize] > cd + 1 && rsize + ssize < len)
		ssize++;
	if (rsize == ssize && list[len - 1] != len - 1)
	{
		//Case 2
		for (int i = 0; i <= cd; i++)
		{
			list[len] = i + 1;
			findChild(list, len + 1, i);
		}
	}
	else
	{
		//Case 3
		int d;
		if (list[len - 1] == len - 1)
			d = len;
		else
			d = list[len - ssize];
		for (int i = 0; i < d - 1; i++)
		{
			list[len] = i + 1;
			findChild(list, len + 1, i);
		}
		list[len] = d;
		findChild(list, len + 1, cd);
	}
}

void findTree(int n)
{
	N = n;
	int list[30];
	list[0] = 0;
	list[1] = 1;
	findChild(list, 2, 0);
}


int main()
{
	
	char el[80];
	conf = fopen("config", "r");
	fgets(el, 99, conf);
	fscanf(conf, "%d\n", &N);
	fgets(el, 99, conf);
	fscanf(conf, "%d\n", &fl_lst);
	fclose(conf);
	file = fopen("out_syn", "w+");
	fprintf(file, "\n");
	fprintf(file, "The syntesis algorithm by means of initial vertices vectors:\n");
	fprintf(file, "\n");

	clock_t time;
	time = clock();
	//тут засечь время 
	findTree(N);
	//тут остановить время 
	time = clock() - time;

	fprintf(file, "time: %f \n", (double)time / CLOCKS_PER_SEC);
	fprintf(file, " For %d nodes - %.0f trees ", N, count1);
	fprintf(file, "\n");
	fclose(file);
	
	
	return 0;
}