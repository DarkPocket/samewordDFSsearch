
#include "stdafx.h"
#include "Timing_function.h"

Timing_function::Timing_function()
{
	//ctor
}

Timing_function::~Timing_function()
{
	//dtor
}

clock_t   Timing_function::Timing_start() //struct timing * timeSTR
{
	cout << "Timing_start \n";
	Timing_init();
	start = clock();
	return start;
}

void Timing_function::Timing_init()
{
	start = 0;
	finish = 0;
	duration = 0;
}



clock_t Timing_function::Timing_finish()
{
	cout << "Timing_finish  \n";
	finish = clock();

	duration = 0;
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	Timing_show();
	return 0;
}




void Timing_function::Timing_show()
{
	char unit[][10] = { {"ms"} , { "s"}, {"min"}, {"hour"}, {"day"}, {"years"} };
	int j = 0;

	int s, min, hour, day;
	int temp;
	double ms;

	temp = duration;
	ms = (duration - temp) * 1000;

	s = temp % 60;

	temp = temp / 60;
	min = temp % 60;

	temp = temp / 60;
	hour = temp % 24;

	temp = temp / 24;
	day = temp % 24;

	//  min = min % 60;
	j = 4;

	if (day > 0)
	{
		//  printf(" %d %s", day, unit [ j]);
		cout << " " << day << " day ";

	}
	j--;
	if (hour > 0)
	{
		//                printf(" %d %s", hour, unit [ j]);
		cout << " " << hour << " hour ";
	}
	j--;
	if (min > 0)
	{
		//   printf(" %d %s",  min, unit [ j]);
		cout << " " << min << " min ";
	}
	j--;
	if (s >= 0)
	{
		//                printf(" %d %s",  s, unit [ j]);
		cout << " " << s << " s ";
	}
	j--;
	if (ms >= 0)
	{
		//                printf(" %0.4lf %s",  ms, unit [ j]);
		cout << " " << ms << " ms ";
	}


	//printf(" \n");
	cout << endl;
	//     timeSTR->duration ;

}

