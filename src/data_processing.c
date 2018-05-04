
#include <stdio.h>
#include <stdlib.h>

#include "data_utilites.h"
#include "data_line_parcer.h"

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
	char *s = "Hello, this is a test module for the string splitting.";
	int c = 0;
	char **arr = NULL;



	test_funcion();


	// Print input args:
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	fp[0] = fopen(argv[1], "r");
	if (fp[0] == NULL) {
		exit(EXIT_FAILURE_TO_OPEN_FILE);
	}

	//while ((read = getline(&line, &len, fp)) != -1)
	//{
	//    printf("Retrieved line of length %zu :\n", read);
	//    printf("%d  %s",counter, line);
	//    counter++;
	//}
	read = getline(&line, &len, fp[0]);
	printf("Retrieved line of length %zu :\n", read);
	printf("%d  %s", counter, line);



	//Line processing:
	{
		for(int i = 0; i < len; i++ )
		{
			input_line[i] = line[i];

		}
		printf("%d  %s", len, input_line);




	}














	//strlen(contents)

	//*s = *line;

	printf("TEST:: %s ", s);
	printf("TEST:: %s ", line);

	c = split(line, ':', &arr);

	printf("found %d tokens.\n", c);

	for (i = 0; i < c; i++) {
		printf("string #%d: %s\n", i, arr[i]);
	}

	fclose(fp[0]);
	if (line) {
		free(line);
	}

	c = split(argv[1], '.', &arr);

	printf("found %d tokens.\n", c);

	for (i = 0; i < c; i++) {
		printf("string #%d: %s\n", i, arr[i]);
	}

	exit(EXIT_SUCCESS);

}

