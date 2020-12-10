#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* DELIMITER = ".";

const char* get_week_day(int day){
    // 1 -> Samstag
    // 2 -> Sonntag
    // 3 -> Montag
    switch (day % 7)
    {
        case 1: return "Samstag";
        case 2: return "Sonntag";
        case 3: return "Montag";
        case 4: return "Dienstag";
        case 5: return "Mittwoch";
        case 6: return "Donnerstag";
        case 0: return "Freitag";
        default: return "Häää?";
    }
}

int leap_year(int year){
    // Julian calendar
    if (year < 1700)
    {
        if (year % 4 == 0)
        {
            return 1;
        }else{
            return 0;
        }
    }

    // Gregorian calendar
    if (year % 4 != 0)
    {
        // all years, which are not dividable by 4
        return 0;
    }

    if (year % 100 != 0)
    {
        return 1;
    }

    if (year % 400 == 0)
    {
        return 1;
    }
    
    return 0;
}

int main(void){

    // Format: dd.MM.yyyy
    char date_string[12];
    printf("Date (dd.MM.yyyy):\n");
    fgets(date_string, 11, stdin);

    char* end;
    char* ptr = strtok(date_string, DELIMITER);
    int day = strtol(ptr, &end, 10);
    ptr = strtok(NULL, DELIMITER);
    int month = strtol(ptr, &end, 10);
    ptr = strtok(NULL, DELIMITER);
    int year = strtol(ptr, &end, 10);

    // 1.1.1 Samstag
    unsigned int total_days = 0;

    for (size_t i = 1; i < year; i++){
        if (leap_year(i)){
            total_days += 366;
        }else{
            total_days += 365;
        }
    }

    for (size_t i = 1; i < month; i++)
    {
        switch(i){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                total_days += 31;
                break;
            case 2:
                if (leap_year(year)){
                    total_days += 29;
                }else{
                    total_days += 28;
                }
                break;
            default:
                total_days += 30;
        }
    }

    total_days += day;
    	
    // Fix Julian -> Gregorian!
    // in England
    // 2.9.1752 - 14.9.1752 jump! 11 days

    // in Germany
    // 1.3.1700 (18.2.1700 - 1.3.1700 missing! 10 days)
    if (total_days > 620608 && total_days < 620619) {
        printf("This date does not exist :(!\n");
        return 0;
    }
    
    if (total_days >= 620619){
        total_days -= 10;
    }
    
    printf("Total days since 1.1.1: %d -> %s\n", total_days, get_week_day(total_days));

    return 0;
}