#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <time.h>

FILE *file, *conf;
long double count1 = 0;
int fl_lst, N;

void Gen(int p, int s, int cL, int* par){
	if (p > N || par[p - 1] == 1 && par[p - 2] == 1) {
		int j = 0;
		if (fl_lst) // вывод файл
		{
			for (int i = 1; i < N+1; i++) fprintf(file, "%d", par[i]);
			fprintf(file, "\n");
		} 
		else {
			for (int i = 1; i < N + 1; i++) j+=1; // для замедления работы без вывода
		}
		count1+=1;
	}
	else
	{
		if (cL == 0) par[p] = p - 1;
		else if (par[p - cL] < s) par[p] = par[s];
		else par[p] = cL + par[p - cL];
		Gen(p + 1, s, cL, par);
		while (par[p] > 1) {
			s = par[p];
			par[p] = par[s];
			Gen(p + 1, s, p - s, par);
		}
	}
}
/*********************************************************/
void main()
{
	int num[30];
	char el[80];
	conf = fopen("config", "r");
	fgets(el, 99, conf);
	fscanf(conf, "%d\n", &N);
	fgets(el, 99, conf);
	fscanf(conf, "%d\n", &fl_lst);
	fclose(conf);
	file = fopen("out_syn", "w+");
	fprintf(file, "\n");
	fprintf(file,"The syntesis algorithm by means of initial vertices vectors:\n");
	fprintf(file,"\n");

	clock_t time;
	time = clock();
	//тут засечь время
	Gen(1, 0, 0, num);
	//тут остановить время
	time = clock() - time;

	fprintf(file, "воемя в с: %f \n", (double)time / CLOCKS_PER_SEC);
	fprintf(file, "%d вершин - %f деревьев", N , count1);
	fprintf(file, "\n");
	fclose(file);
}