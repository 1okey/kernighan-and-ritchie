static int daytab[2][12]= {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31},
};

int day_of_year(int year, int month, int day)
{
    int leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);

    if(day < 0 || (day > 365 && !leap) || (day > 366 && leap)
       || month > 12 || month < 0 || year < 0){
        printf("%d/%d/%d: invalid date\n", day,month,year);
        return day;
    }

    while(month >= 1)
        day += *(*(daytab + leap) + month--);
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    if(yearday < 0 || year < 0){
        printf("%d / %d: invalid input\n", year, yearday);
    }

    int i, leap;
    leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    for(i = 1; yearday > *(*(daytab + leap) + i); ++i)
        yearday -= *(*(daytab + leap) + i);
    *pmonth = i;
    *pday = yearday;
}

