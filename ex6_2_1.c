#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

/* ---------------------------------- */

int skip_delim(char instr[], char delim, int choffset) {
	// printf("skip_delim : offset %d, str %s\n", choffset, &instr[choffset]);
	if (instr[choffset]==delim) {
		choffset++;
	} else {
		fprintf(stderr, "Error at csv_read. Delim Char not found.\n");
	   	exit(-1);
	}
	return (choffset);
}

int csv_dq_read(char instr[], char outstr[], int quote_ch, int choffset) {
	int instr_pos, outstr_pos;

	instr_pos = choffset;
	outstr_pos = 0;
	// printf("csv_dq_read : offset %d, str %s\n", choffset, &instr[choffset]);
    if (instr[instr_pos] == quote_ch) {
    	instr_pos++;
    } else {
    	fprintf(stderr, "Error at csv_read. Quote Char not found.\n");
	   	exit(-1);
    }
	while (instr[instr_pos]!=quote_ch) {
 		if (!isprint(instr[instr_pos])) {
			fprintf(stderr, "Error at csv_read. Wrong char.\n");
		   	exit(-1);
		} else {
			outstr[outstr_pos]=instr[instr_pos];
			outstr_pos++;
		}
		instr_pos++;
	}
	outstr[outstr_pos]=0; // outstr_pos++;
	if (instr[instr_pos]==quote_ch)	/* skip quote char */
		instr_pos++;
	return (instr_pos);
}

/* ---------------------------------- */

#define BUF_SIZE	255
#define ZIPCHAR_SIZE	8
#define PREF_SIZE	20
#define CITY_SIZE	50
#define ADDR_SIZE	100
#define ADDR_ALL_SIZE	255

#define ZIPTABLE_MAX 4000

typedef struct _ziptable {
	int zip;
	char pref[PREF_SIZE];
	char city[CITY_SIZE];
	char addr[ADDR_SIZE];
} ziptable_t;

int read_from_csv(ziptable_t **ziptable, FILE *infp){
    int n = 0;
    int chofs = 0;
    int zip = 0;
	char instr[BUF_SIZE];
	char zip_char[ZIPCHAR_SIZE];
	char pref[PREF_SIZE];
	char city[CITY_SIZE];
	char addr[ADDR_SIZE];

	while (fgets(instr, BUF_SIZE, infp) != NULL) {
        ziptable[n] = (ziptable_t *)malloc(sizeof(ziptable_t));
        if(ziptable[n]==NULL){
            printf("Cannot allocate memory.\n");
            break;
        }
		chofs = 0;
		chofs = csv_dq_read(instr, zip_char, '"', chofs);
		zip = atoi(zip_char);
		(*ziptable[n]).zip = zip;
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, pref, '"', chofs);
		strcpy((*ziptable[n]).pref, pref);
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, city, '"', chofs);
		strcpy((*ziptable[n]).city, city);
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, addr, '"', chofs);
		strcpy((*ziptable[n]).addr, addr);
		n++;
	}
	return n;
}

int main(void) {
	ziptable_t *ziptable[ZIPTABLE_MAX];
    int input = 0;
    int flag = 0;
    int ans = 0;
	FILE *infp;

	if ( ( infp = fopen("tokyo_all_dat.txt", "r")) == NULL) {
		fprintf(stderr, "File not found\n");
		exit(EXIT_FAILURE);
	}

	int n = read_from_csv(ziptable,infp);
	printf("number of data = %d\n", n);
	fclose(infp);
	
    printf("zipcode?  : ");
    scanf("%d", &input);

    for(int i=0;i<n;i++){
        if((*ziptable[i]).zip==input){
            flag = 1;
            ans = i;
        }
    }

    if(flag == 1){
        printf("address : %s %s %s\n", (*ziptable[ans]).pref, (*ziptable[ans]).city, (*ziptable[ans]).addr);
    }
    else if(flag == 0){
        printf("No data");
    }

    for(int i=0;i<n;i++){
        free(ziptable[i]);
    }

    return 0;
}
