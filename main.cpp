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
#define second_seconds 1 //为节省时间 此项舍弃

#define recin_year cout << "这一年的高考时间已经过了哦，重新输一次吧~" << endl; cin >> year;year -= 1900;

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
	void get_now_t()//获取当前时间
	{
		now_t = time(&now_t);
		n_t = localtime(&now_t);
		//n_t->tm_mon += 1;
	}
	void get_gk_t() //定义高考时间
	{
		g_t = &t;
		g_t->tm_sec = 59;
		g_t->tm_min = 59;
		g_t->tm_hour = 8;
		g_t->tm_mday = 7;
		g_t->tm_mon = 5; //0-11 为 1-12月
		g_t->tm_wday = 1;
		g_t->tm_isdst = 0;
		int year;
		cout << "好哥哥，你得先告诉我你哪一年高考：";
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
		if (is_leap_year(year))  //闰年和平年的高考所在的天数是不同的
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
	void sub_timing() //计算时间差值并分配到结构体timing中
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
	void print_time() //输出高考时间
	{
		system("cls");
		cout << "距离高考还有" << t_timing->days << "日" << t_timing->hours << "时" << t_timing->minutes << "分" << t_timing->seconds << "秒";
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
	int is_leap_year(int year)  //是否是闰年
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