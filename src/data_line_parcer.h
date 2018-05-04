/*
 * data_line_parcer.h
 *
 *  Created on: Feb 24, 2018
 *      Author: vadym
 */

#ifndef DATA_LINE_PARCER_H_
#define DATA_LINE_PARCER_H_

// [{'tradeID': 5994068, 'date': '2018-01-03 15:58:12', 'amount': '100.00000000', 'total': '0.00043000', 'rate': '0.00000430', 'globalTradeID': 314178402, 'type': 'sell'}]
// {'BTC_DGB': {'date': '2018-01-03 15:58:12', 'last': '0.00000430', 'type': 'sell'}}

typedef struct
{
	double last;
	char   type[5];
	char   time_stamp[20];
	int    year;
    int    month;
    int    day;
    int    hour;
    int    minute;
    int    sec;
	char   char_last[];

}MarketData;

void test_funcion(void);

void input_line_parcer(char* in_line, MarketData *output);






#endif /* DATA_LINE_PARCER_H_ */
