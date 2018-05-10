
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_utilites.h"
#include "data_line_parcer.h"
#include <time.h>

#define _GNU_SOURCE

//gcc -std=c99 data_preprocessing.c

// Input data :
// [{'tradeID': 5994068, 'date': '2018-01-03 15:58:12', 'amount': '100.00000000', 'total': '0.00043000', 'rate': '0.00000430', 'globalTradeID': 314178402, 'type': 'sell'}]
// [{'tradeID': 5994069, 'date': '2018-01-03 15:58:12', 'amount': '4286.92490224', 'total': '0.01834803', 'rate': '0.00000428', 'globalTradeID': 314178403, 'type': 'sell'}]
// [{'tradeID': 5994070, 'date': '2018-01-03 15:58:12', 'amount': '4486.92130000', 'total': '0.01920402', 'rate': '0.00000428', 'globalTradeID': 314178404, 'type': 'sell'}]
// Output data:
// {'BTC_DGB': {'date': '2018-01-03 15:58:12', 'last': '0.00000430', 'type': 'sell'}}
// {'BTC_DGB': {'date': '2018-01-03 15:58:12', 'last': '0.00000428', 'type': 'sell'}}
// {'BTC_BTS': {'date': '2018-01-03 15:58:12', 'last': '0.00005770', 'type': 'buy'}}

#define EXIT_SUCCESS 0
#define EXIT_FAILURE_TO_OPEN_FILE -1

#define MAX_AMOUNT_OF_FILES 50

FILE *fp[MAX_AMOUNT_OF_FILES];
FILE *foutput;




int main(int argc, char **argv) {
	char * line[MAX_AMOUNT_OF_FILES] = {NULL};
	size_t len = 0;
	size_t read;
	unsigned int counter = 0;

	int i;
	int c = 0;
	char **arr = NULL;

	MarketData data_out;
	char path[1035];

	if( argc > MAX_AMOUNT_OF_FILES)
	{
		printf("argc = %d > MAX_AMOUNT_OF_FILE = %d \n", argc, MAX_AMOUNT_OF_FILES);
		exit(1);
	}


	// Print input args:
	for (i = 0; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}


	foutput  = fopen("output.txt", "w");



	c = 0;
	while(c < (argc - 1))
	{

		get_pwd_path(path,sizeof(path));
		make_full_parth(path, argv[c+1]);
		printf("%s \n", path);
		fp[c] = fopen(path, "r");
		c++;
	}

	if (fp[0] == NULL) {
		printf("Error open file.\n");
		exit(EXIT_FAILURE_TO_OPEN_FILE);
	}

	// Print input args:
	for (i = 0; i < (argc - 1); ++i)
	{
		while ((read = getline(&line[i], &len, fp[i])) != -1)
		{
			input_line_parcer(line[i], &data_out);
			printf("Exit line: %s \n", data_out.time_stamp);
			c =  utc_to_unix_time_converter_line_parcer(data_out.time_stamp);
			printf("Unix time is %d , num: %d \n", c, counter);
			counter++;
			if(counter == 4613359)
			{
				printf("Unix time is %d , num: %d \n", c, counter);
			}

			fprintf (foutput,"%s",line[i]);
		}
	}







	c = 0;
	while(c < (argc - 1))
	{
		fclose(fp[c]);
		c++;
	}
	fclose(foutput);

	exit(EXIT_SUCCESS);

}

