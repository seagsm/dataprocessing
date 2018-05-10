
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

FILE *fp[50];

char input_line[1000];



int main(int argc, char **argv) {
	char * line = NULL;
	size_t len = 0;
	size_t read;
	unsigned int counter = 0;

	int i;
	int c = 0;
	char **arr = NULL;

	MarketData data_out;
	char path[1035];


    get_pwd_path(path,sizeof(path));

    // make_full_parth(path, "BTC_BTS.txt");
    make_full_parth(path, argv[1]);
    printf("%s \n", path);


	// Print input args:
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}


	// fp[0] = fopen(argv[1], "r");

	fp[0] = fopen(path, "r");

	//fp[0] = fopen(filename, "r");



	if (fp[0] == NULL) {
		printf("Error open file.\n");
		exit(EXIT_FAILURE_TO_OPEN_FILE);
	}

	while ((read = getline(&line, &len, fp[0])) != -1)
	{
		input_line_parcer(line, &data_out);
		printf("Exit line: %s \n", data_out.time_stamp);
		c =  utc_to_unix_time_converter_line_parcer(data_out.time_stamp);
		printf("Unix time is %d \n", c);
		counter++;
	}

	fclose(fp[0]);
	if (line) {
		free(line);
	}

	exit(EXIT_SUCCESS);

}

