#include "data_utilites.h"
#include <stdio.h>
#include <stdlib.h>

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

int split(char *str, char c, char ***arr);

int split(char *str, char c, char ***arr) {
	int count = 1;
	int token_len = 1;
	int i = 0;
	char *p;
	char *t;
	size_t u_size = 0;

	p = str;
	while (*p != '\0') {
		if (*p == c)
			count++;
		p++;
	}


	//*arr = (char**) malloc(sizeof(char*) * count);

	u_size = sizeof(char*) * count;
	*arr = (char**) malloc(u_size);


	if (*arr == NULL)
		exit(1);

	p = str;
	while (*p != '\0') {
		if (*p == c) {
			(*arr)[i] = (char*) malloc(sizeof(char) * token_len);
			if ((*arr)[i] == NULL)
				exit(1);

			token_len = 0;
			i++;
		}
		p++;
		token_len++;
	}
	(*arr)[i] = (char*) malloc(sizeof(char) * token_len);
	if ((*arr)[i] == NULL)
		exit(1);

	i = 0;
	p = str;
	t = ((*arr)[i]);
	while (*p != '\0') {
		if (*p != c && *p != '\0') {
			*t = *p;
			t++;
		} else {
			*t = '\0';
			i++;
			t = ((*arr)[i]);
		}
		p++;
	}

	return count;
}


int make_full_parth(char str[], char* chr_file_name)
{
	int count = 0;
	char *p;

	while (str[count] != '\0')
	{
		if(str[count] == '\n')
		{
			str[count] = '/';
		}
		count++;
	}

	p = chr_file_name;
	while (*p != '\0') {
		str[count] = *p;
		p++;
		count++;
	}
	str[count] = '\0';

	return (1);
}









