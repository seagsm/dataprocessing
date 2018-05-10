/*
 * data_line_parcer.c
 *
 *  Created on: Feb 24, 2018
 *      Author: vadym
 */

#include "data_line_parcer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data_utilites.h"

// [{'tradeID': 5994068, 'date': '2018-01-03 15:58:12', 'amount': '100.00000000', 'total': '0.00043000', 'rate': '0.00000430', 'globalTradeID': 314178402, 'type': 'sell'}]
// [{'tradeID': 5994069, 'date': '2018-01-03 15:58:12', 'amount': '4286.92490224', 'total': '0.01834803', 'rate': '0.00000428', 'globalTradeID': 314178403, 'type': 'sell'}]
// [{'tradeID': 5994070, 'date': '2018-01-03 15:58:12', 'amount': '4486.92130000', 'total': '0.01920402', 'rate': '0.00000428', 'globalTradeID': 314178404, 'type': 'sell'}]
// Output data:
// {'BTC_DGB': {'date': '2018-01-03 15:58:12', 'last': '0.00000430', 'type': 'sell'}}
// {'BTC_DGB': {'date': '2018-01-03 15:58:12', 'last': '0.00000428', 'type': 'sell'}}
// {'BTC_BTS': {'date': '2018-01-03 15:58:12', 'last': '0.00005770', 'type': 'buy'}}


char *in_line = "[{'tradeID': 5994068, 'date': '2018-01-03 15:58:12', 'amount': '100.00000000', 'total': '0.00043000', 'rate': '0.00000430', 'globalTradeID': 314178402, 'type': 'sell'}]";

char *date 	= "date";
char *rate = "rate";
char *type 	= "type";
char *sell 	= "sell";
char *buy 	= "buy";


char tmp[1000];

void input_line_parcer(char* in_line, MarketData *output)
{
	char *current_line;
	char *end_line;
    int size_of_line;

	//printf("Input line: %s", in_line);


	//search first char char *strchr(const char *str, int c)
	//search last char   char *strrchr(const char *str, int c)

	size_of_line = strlen(in_line);

	/** Get date.  */
	// get size of input line:

	// copy input line to temporary buffer:
	strncpy(tmp, &in_line[1], size_of_line);
    // get pointer to start of date:
	current_line = strstr(tmp, date);

	memcpy(output->time_stamp, &current_line[8], 19);
	output->time_stamp[19] = '\0';
	output->sec = atoi(&current_line[25]);
	current_line[24] = '\0';
	output->minute = atoi(&current_line[22]);
	current_line[21] = '\0';
	output->hour = atoi(&current_line[19]);
	current_line[18] = '\0';
	output->day = atoi(&current_line[16]);
	current_line[15] = '\0';
	output->month = atoi(&current_line[13]);
	current_line[12] = '\0';
	output->year = atoi(&current_line[8]);

	/** Get rate.  */
	// copy input line to temporary buffer:
	strncpy(tmp, &in_line[1], size_of_line);
    // get pointer to start of date:
	current_line = strstr(tmp, rate);
	current_line[18] = '\0';
	output->last = atof(&current_line[8]);

}


int utc_to_unix_time_converter_line_parcer(char* utc_in_time)
{
	int int_time;
    struct tm future;       /* as in future date */
    time_t t;

    int i = 0;
	int c = 0;
	char **arr_date = NULL;
	char **arr_days = NULL;
	char **arr_time = NULL;

	c = split(utc_in_time, ' ', &arr_date);
	c = split(arr_date[0], '-', &arr_days);
	c = split(arr_date[1], ':', &arr_time);

	future.tm_sec   = 	atoi(arr_time[2]);
	future.tm_min   = 	atoi(arr_time[1]);
	future.tm_hour  = 	atoi(arr_time[0]);
	future.tm_mday  = 	atoi(arr_days[2]);
	future.tm_mon   = 	atoi(arr_days[1]) - 1; 		/* Month, 0 - Jan   */
	future.tm_year  = 	atoi(arr_days[0]) - 1900; 	/* years since 1900 */
	future.tm_isdst = 0;          					/* Daylight Saving not in affect (UTC) */
	#ifdef _BSD_SOURCE
	        future.tm_zone = "UTC";
	#endif

    free(arr_time[2]);
	free(arr_time[1]);
	free(arr_time[0]);
	free(arr_days[2]);
	free(arr_days[1]);
	free(arr_days[0]);




	t = mktime( &future );
	if ( -1 == t )
	{
	                printf("Error converting UTC time to time_t time since Epoch\n");
	                //return EXIT_FAILURE;
	}
	return(t);
}









