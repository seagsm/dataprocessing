

#include <stdlib.h>
#include <string.h>

#include "data_utilites.h"
#include "data_line_parcer.h"
#include <time.h>
#include <stdio.h>

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
	char pair_name[MAX_AMOUNT_OF_FILES][100] = {NULL,NULL};
	int int_unix_time[MAX_AMOUNT_OF_FILES];
	size_t st_read[MAX_AMOUNT_OF_FILES];
	char * output_line;

	int int_index_of_minimal_value = 0;
	int int_minimal_value = 0;

	size_t len = 0;
	size_t read;
	unsigned int counter = 0;

	int i;
	int c = 0;
	char **arr = NULL;

	MarketData data_out;
	char path[1035];

	char **currency_name = NULL;

	if( argc > MAX_AMOUNT_OF_FILES)
	{
		printf("argc = %d > MAX_AMOUNT_OF_FILE = %d \n", argc, MAX_AMOUNT_OF_FILES);
		exit(1);
	}


	// Print input args:
	printf("argv[%d]: %s\n", 0, argv[0]);
	// Here we add name of pairs to char array:
	for (i = 1; i < argc; ++i)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		c = split(argv[i], '.', &currency_name);
		sprintf(&pair_name[i-1],"%s",currency_name[0]);
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

	// First read lines from all opened input files:
	for (i = 0; i < (argc - 1); ++i)
	{
		// read lines:
		st_read[i] = getline(&line[i], &len, fp[i]);
		// extract time stamp:
		input_line_parcer(line[i], &data_out);
		// convert in to unix time:
		int_unix_time[i] =  utc_to_unix_time_converter_line_parcer(data_out.time_stamp);
	}

	int_index_of_minimal_value = 0;
	int_minimal_value = int_unix_time[int_index_of_minimal_value];

	while(1)
	{
		for (i = 1; i < (argc - 1); ++i)
		{
			if((int_minimal_value > int_unix_time[i]) && (int_unix_time[i] != -1) )
			{
				int_index_of_minimal_value = i;
				int_minimal_value = int_unix_time[i];
			}
			if(int_minimal_value == -1)
			{
				int_index_of_minimal_value = i;
				int_minimal_value = int_unix_time[i];
			}
		}

		if(int_minimal_value == -1)
		{
			break;
		}


		//---Build output string----------------------------------------
		// Remove last ']'
		output_line = strtok(line[int_index_of_minimal_value], "]");

		           // [{'trad................... 'globalTradeID': 314178404, 'type': 'sell'}]
         //{'BTC_STR': {'date': '2018-05-13 09:14:13', 'last': '0.00004204', 'type': 'sell'}}
         // line[int_index_of_minimal_value] + 1  -> + 1 is for remove first '['

		fprintf (foutput,"{'%s': %s}\n",pair_name[int_index_of_minimal_value], line[int_index_of_minimal_value] + 1);



		//currency_name[0] is currency name.
		//--------------------------------------------------------------
		//fprintf (foutput,"%s",line[int_index_of_minimal_value]);
		if(counter % 100000 == 0)
		{
			input_line_parcer(line[int_index_of_minimal_value], &data_out);
			printf("UTC time is %s , num: %d \n", data_out.time_stamp, counter);
		}
		counter++;


		/** Read new line: */
		st_read[int_index_of_minimal_value] = getline(&line[int_index_of_minimal_value], &len, fp[int_index_of_minimal_value]);
		if(st_read[int_index_of_minimal_value] != -1)
		{
			input_line_parcer(line[int_index_of_minimal_value], &data_out);
			int_unix_time[int_index_of_minimal_value] =  utc_to_unix_time_converter_line_parcer(data_out.time_stamp);
		}
		else
		{
			int_unix_time[int_index_of_minimal_value] = -1;
		}
		int_index_of_minimal_value = 0;
		int_minimal_value = int_unix_time[int_index_of_minimal_value];
	}

//	for (i = 0; i < (argc - 1); ++i)
//	{
//		while ((read = getline(&line[i], &len, fp[i])) != -1)
//		{
//			input_line_parcer(line[i], &data_out);
//			printf("Exit line: %s \n", data_out.time_stamp);
//			c =  utc_to_unix_time_converter_line_parcer(data_out.time_stamp);
//			printf("Unix time is %d , num: %d \n", c, counter);
//			counter++;
//			if(counter == 4613359)
//			{
//				printf("Unix time is %d , num: %d \n", c, counter);
//			}
//
//			fprintf (foutput,"%s",line[i]);
//		}
//	}








	c = 0;
	while(c < (argc - 1))
	{
		fclose(fp[c]);
		c++;
	}
	fclose(foutput);

	exit(EXIT_SUCCESS);

}

