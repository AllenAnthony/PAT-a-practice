/*!
 * \file 1033. To Fill or Not to Fill.cpp
 *
 * \author Lu Yudi
 * \date ���� 2017
 * https://www.patest.cn/contests/pat-a-practise/1033
 * 
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
#define MAX 510
// definition
int Cmax, D, Davg, N;

struct GasStation
{
	double price;
	int dist;
}station[MAX];

bool cmp(GasStation gs1, GasStation gs2)
{
	return gs1.dist < gs2.dist;
}

int main(int argc, const char *argv[])
{
#ifdef ONLINE_JUDGE
#else
	ifstream ifs("input.txt");
	streambuf *cinbackup = cin.rdbuf(ifs.rdbuf());
#endif
	// ����
	cin >> Cmax >> D >> Davg >> N;
	for (int i = 0; i < N; i++)
		cin >> station[i].price >> station[i].dist;
	station[N].dist = D;
	station[N].price = 0.0;
	// �㷨
	sort(&station[0], &station[N + 1], cmp);
	double GasToFill[MAX];	// Gas to fill in gas station
	deque<int> GasIndex;	// Gas station index that can be filled; sorted by price from low to high
	double TotalPrice = 0.0;	// min money paid for the travel
	double TotalDistance = 0.0;
	deque<int>::iterator it;
	double lastdist = 0.0;
	bool reach = true;
	double tempGas = 0.0;
	// ̰���㷨
	if (station[0].dist != 0.0)
	{
		printf("The maximum travel distance = %.2lf", TotalDistance);
		return 0;
	}
	int i = 0;
	while (TotalDistance < D)
	{
		lastdist = station[i].dist;
		double distance = station[i + 1].dist;
		// ����ӵ�ǰstation ��������һ��station
		if (distance - lastdist > Cmax * Davg)
		{
			TotalDistance += Cmax * Davg;
			TotalPrice += (Cmax - tempGas) * station[i].price;
			reach = false;
			break;
		}
		else
		{
			int min_station = i;
			// �ڵ�ǰ�͵ķ�Χ��ҵ��ȵ�ǰstation�ʷ�����˵ĳ�վ
			for (int j = i; j <= N && station[j].dist - lastdist <= tempGas*Davg; j++)
			{
				if (station[j].price < station[min_station].price)
					min_station = j;
			}
			// ���û�ҵ�
			if (min_station == i)
			{
				// �����������ķ�Χ�� �ҵ��ȵ�ǰstation�ʷ������
				for (int j = i; j <= N && station[j].dist - lastdist <= Cmax*Davg; j++)
				{
					if (station[j].price < station[min_station].price)
					{
						min_station = j;
						break;
					}
				}
				// ���û�ҵ�
				if (min_station == i)
				{
					min_station = i + 1;
					// �����ͺ󵽿ɼ���Χ�ڵ�����˵ĳ�վ
					for (int j = i + 1; j <= N && station[j].dist - lastdist <= Cmax*Davg; j++)
					{
						if (station[j].price < station[min_station].price)
						{
							min_station = j;
						}
					}
					TotalDistance += station[min_station].dist - lastdist;
					TotalPrice += (Cmax - tempGas) * station[i].price;
					tempGas = Cmax - (station[min_station].dist - lastdist) / Davg;
					i = min_station;
				}
				// �ҵ��������������ķ�Χ�ڱȵ�ǰstation�ʷѱ��˵ĵ�һ����վ
				else
				{
					TotalDistance += station[min_station].dist - lastdist;
					TotalPrice += ((station[min_station].dist - lastdist) / Davg - tempGas) * station[i].price;
					tempGas = 0.0;
					i = min_station;
				}
			}
			// �ҵ����ڵ�ǰ�͵ķ�Χ��ȵ�ǰstation�ʷ�����˵ĳ�վ
			else
			{
				TotalDistance += station[min_station].dist - lastdist;
				tempGas -= (station[min_station].dist - lastdist) / Davg;
				i = min_station;
			}
		}
	}
	if (!reach)
		printf("The maximum travel distance = %.2lf", TotalDistance);
	else
		printf("%.2lf", TotalPrice);

	return 0;
}
