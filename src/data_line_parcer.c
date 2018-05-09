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

void test_funcion(void)
{
	MarketData data_out;


	input_line_parcer(in_line, &data_out);

}


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



	//printf("\n Exit line: %s \n", output->time_stamp);

}








