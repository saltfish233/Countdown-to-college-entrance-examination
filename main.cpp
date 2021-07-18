#include<iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<thread>

using namespace std;

#define ordinary_year 31536000
#define month_seconds 2592000
#define day_seconds 86400
#define hour_seconds 3600
#define minute_seconds 60
#define second_seconds 1 //Ϊ��ʡʱ�� ��������

#define recin_year cout << "��һ��ĸ߿�ʱ���Ѿ�����Ŷ��������һ�ΰ�~" << endl; cin >> year;year -= 1900;

struct timing {
	int years;
	int months;
	int days;
	int hours;
	int minutes;
	int seconds;
};
class TIME {
public:
	TIME()
	{
		t_init();
	}
	void get_now_t()//��ȡ��ǰʱ��
	{
		now_t = time(&now_t);
		n_t = localtime(&now_t);
		//n_t->tm_mon += 1;
	}
	void get_gk_t() //����߿�ʱ��
	{
		g_t = &t;
		g_t->tm_sec = 59;
		g_t->tm_min = 59;
		g_t->tm_hour = 8;
		g_t->tm_mday = 7;
		g_t->tm_mon = 5; //0-11 Ϊ 1-12��
		g_t->tm_wday = 1;
		g_t->tm_isdst = 0;
		int year;
		cout << "�ø�磬����ȸ���������һ��߿���";
		cin >> year;
		year -= 1900;
		while (year <= n_t->tm_year)
		{
			if (year < n_t->tm_year)
			{
				recin_year
			}
			else
			{
				if (g_t->tm_mon < n_t->tm_mon)
				{
					recin_year
				}
			}
		}
		if (is_leap_year(year))  //�����ƽ��ĸ߿����ڵ������ǲ�ͬ��
		{
			g_t->tm_yday = 158;
		}
		else
		{
			g_t->tm_yday = 157;
		}
		g_t->tm_year = year;
		gk_t = mktime(g_t);
	}
	void sub_timing() //����ʱ���ֵ�����䵽�ṹ��timing��
	{
		double sub_seconds = difftime(gk_t, now_t);
		for (int i = 0; i < 6; i++)
		{
			*general_timing[i] = 0;
		}
		for (int i = 2; i < 5; i++)
		{
			while (sub_seconds >= general_seconds[i])
			{
				sub_seconds -= general_seconds[i];
				*general_timing[i] += 1;
			}
		}
		*general_timing[5] += sub_seconds;
	}
	void print_time() //����߿�ʱ��
	{
		system("cls");
		cout << "����߿�����" << t_timing->days << "��" << t_timing->hours << "ʱ" << t_timing->minutes << "��" << t_timing->seconds << "��";
	}
	void t_init()
	{
		get_now_t();
		get_gk_t();
		sub_timing();
		print_time();
	}
	void t_main()
	{
		while (1) {
			Sleep(1000);
			get_now_t();
			sub_timing();
			print_time();
		}
	}
	int is_leap_year(int year)  //�Ƿ�������
	{
		if (year % 4 == 0 || year % 400 == 0 && year % 100 != 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	~TIME() {
		delete[] general_timing;
		delete[] general_seconds;
	}
private:
	time_t now_t;
	time_t gk_t;
	tm *n_t;
	tm *g_t;
	tm t;
	struct timing timing;
	struct timing *t_timing = &timing;
	int *general_seconds = new int[6]{ ordinary_year,month_seconds,day_seconds,hour_seconds,minute_seconds,second_seconds };
	int **general_timing = new int*[6]{ &t_timing->years,&t_timing->months,&t_timing->days,&t_timing->hours,&t_timing->minutes,&t_timing->seconds };
};
void get_input()
{
	char input = getch();
	switch (input) {
	case 'q':
		exit(0);
	}
}
int main()
{
	TIME t;
	thread get_q(get_input);
	get_q.detach();
	t.t_main();
	return 0;
}