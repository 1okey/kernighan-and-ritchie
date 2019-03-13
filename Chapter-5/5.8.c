static int daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31},
};

int day_of_year(int year, int month, int day)
{
    if(day < 0 || month > 12 || month < 0 || year < 0){
        printf("%d/%d/%d: invalid date\n", day,month,year);
        return day;
    }

    int i, leap;
    leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    for(i = 1; i < month; ++i)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    if(yearday < 0 || year < 0){
        printf("%d / %d: invalid input\n", year, yearday);
    }

    int i, leap;
    leap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    for(i = 1; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
