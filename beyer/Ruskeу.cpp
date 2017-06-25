// RuskeyCPP.cpp : Defines the entry point for the console application. 
// 

#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h" 
#include <time.h> 

int i=0,N = 0;
FILE *file, *conf;
long double count1 = 0;
int fl_lst;
int p = N;
int l[30];
int prev[30];
int save[30];


void generateFirstTree(int N) {
	for (i = 0; i < N; i++) {
		l[i] = i;
	}
	if (N < 2) {
		p = i;
	}
	else p = N - 1;
	if (p > 1) {
		for (i = 0; i <= p - 1; i++) {//<= 
			prev[i] = i;
			save[i] = 0;
		}
	}
}
void generateNextTree(int N) {
	l[p] = l[p] - 1;
	if (p < N && (l[p] != 1 || l[p - 1] != 1)) {
		int diff = p - prev[l[p]];
		while (p < N - 1) {
			save[p] = prev[l[p]];
			prev[l[p]] = p;
			p = p + 1;
			l[p] = l[p - diff];
		}
	}
	while (l[p] == 1) {
		p = p - 1;
		prev[l[p]] = save[p];
	}
}

void print(int N) {
	int j = 0;
	if (fl_lst) // вывод файл 
	{
		for (int i = 0; i < N; i++) fprintf(file, "%d", l[i]);
		fprintf(file, "\n");
	}
	else {
		for (int i = 0; i < N; i++) j++;
	}
	count1++;
}
void generateRootedTrees(int N) {
	generateFirstTree(N);
	print(N);
	while (p > 1) {
		generateNextTree(N);
		print(N);
	}
}
void main()
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
	//тут засечь врем€ 
	generateRootedTrees(N);
	//тут остановить врем€ 
	time = clock() - time;

	fprintf(file, "time: %f \n", (double)time / CLOCKS_PER_SEC);
	fprintf(file, " For %d nodes - %f trees ", N, count1);
	fprintf(file, "\n");
	fclose(file);
}