// BIO_Lab3_1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Score(int* s, string* DNA, int l, int t)
{
	int score = 0;
	for (int i = 0; i < l;i++)
	{
		int A = 0, C = 0, G = 0, T = 0;
		for (int j = 0; j < t; j++)
		{
			if (DNA[j][s[j] + i] == 'A')
				A++;
			if (DNA[j][s[j] + i] == 'C')
				C++;
			if (DNA[j][s[j] + i] == 'G')
				G++;
			if (DNA[j][s[j] + i] == 'T')
				T++;
		}
		score += fmax(fmax(A, C), fmax(G, T));
	}
	return score;
}

string* Motifs(int *bestS, string*DNA, int l, int t)
{
	string* motifs = new string[t];
	for (int i = 0; i < t; i++)
	{
		motifs[i] = new char[l];
	}
	for (int i = 0; i < t; i++)
	{
		motifs[i] = DNA[i].substr(bestS[i], l);
	}
	return motifs;
}

void NextLeaf(int* s, int L, int k)
{
	for (int i = L - 1; i >= 0; i--)
	{
		if (s[i] < k)
		{
			s[i] = s[i] + 1;
			return;
		}
		s[i] = 0;
	}
	return;
}

string* BruteForceMotifSearchAgain(string* DNA, int t, int n, int l, int* s, int *bestS, int& bestScore)
{
	int count = 0;
	string* bestM = new string[t];
	int *ss = new int[t];
	for (int i = 0; i < t; i++)
	{
		ss[i] = 0;;
	}
	bestScore = Score(s, DNA, l, t);
	while (true)
	{
		NextLeaf(s, t, n - l);
		if (Score(s, DNA, l, t) >= bestScore)
		{
			bestScore = Score(s, DNA, l, t);
			for (int g = 0; g < t; g++)
			{
				bestS[g] = s[g];
			}
		}
		bool da = true;
		for (int g = 0; g < t; g++)
		{
			if (s[g] != 0)
			{
				da = false;
			}
		}
		if (da == true)
		{
			bestM = Motifs(bestS, DNA, l, t);
			return bestM;
		}
	}
}

void PrintBestMotifs(string* bestM, int t)
{
	for (int i = 0; i < t; i++)
	{
		cout << bestM[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		string lc;
		string tc;
		getline(fin, lc, ' ');
		getline(fin, tc, '\n');
		int l = atoi(lc.c_str());	// размер шаблона
		int t = atoi(tc.c_str());	// число экземпляров ДНК

		cout << l << endl;
		cout << t << endl;
		string* DNA = new string[t];
		int *s = new int[t];
		for (int i = 0; i < t; i++)
		{
			getline(fin, DNA[i]);
			cout << DNA[i] << endl;
			s[i] = 0;
		}
		int n = strlen(DNA[0].c_str());
		fin.close();
		cout << n << endl;

		string* bestM = new string[t];
		int *bestS = new int[t];
		for (int i = 0; i < t; i++)
		{
			bestS[i] = 0;
		}
		int bestScore = 0;
		bestM = BruteForceMotifSearchAgain(DNA, t, n, l, s, bestS, bestScore);
		PrintBestMotifs(bestM, t);
		for (int i = 0; i < t; i++)
		{
			fout << bestM[i] << endl;
		}
		delete[] s;
		delete[] DNA;
		delete[] bestM;
		delete[] bestS;
		cout << "bestScore = " << bestScore << endl;
		fout.close();
	}
	return 0;
}

