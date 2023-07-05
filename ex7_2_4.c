#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF_SIZE	255
#define ZIPCHAR_SIZE	8
#define PREF_SIZE	20
#define CITY_SIZE	50
#define ADDR_SIZE	100
#define FULL_ADDR_SIZE	170

typedef struct _zipnode{
    int zip;
    char fulladdr[FULL_ADDR_SIZE];
    struct _zipnode *next;
} zipnode_t;

int skip_delim(char instr[], char delim, int choffset);
int csv_dq_read(char instr[], char outstr[], int quote_ch, int choffset);
int read_from_csv(zipnode_t **head, FILE *infp);
int add_node(zipnode_t **head, int zip, char *fulladdr);
int print_n_node(zipnode_t *head, int n);
zipnode_t *search_node(zipnode_t *head, char *fulladdr);

int main(void){
    zipnode_t *head = NULL;
    zipnode_t *result;
    zipnode_t *node;
    FILE *infp;
    int n = 0;
    char input_addr[FULL_ADDR_SIZE];

	if ( ( infp = fopen("tokyo_all_dat.txt", "r")) == NULL) {
		fprintf(stderr, "File not found\n");
		exit(EXIT_FAILURE);
	}

    n = read_from_csv(&head, infp);

    fclose(infp);

    print_n_node(head, 5);

    while(1){
        printf("full address ? >");
        fgets(input_addr, sizeof(input_addr), stdin);
        input_addr[strlen(input_addr)-1] = '\0';

        if(strcmp(input_addr, "exit") == 0){
            printf("Bye!");
            break;
        }

        result = search_node(head, input_addr);
        if(result == NULL) printf("no data\n");
        else printf("zipcode = %d\n", (*result).zip);
    }

    while(head != NULL){
        node = (*head).next;
        free(head);
        head = node;
    }

    return 0;
}

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

int read_from_csv(zipnode_t **head, FILE *infp){
	int chofs, zip, n=0;
	char instr[BUF_SIZE];
	char zip_char[ZIPCHAR_SIZE];
	char pref[PREF_SIZE];
	char city[CITY_SIZE];
	char addr[ADDR_SIZE];

    char fulladdr[FULL_ADDR_SIZE];


	while (fgets(instr, BUF_SIZE, infp) != NULL) {
		chofs = 0;
		chofs = csv_dq_read(instr, zip_char, '"', chofs);
		zip = atoi(zip_char);
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, pref, '"', chofs);
        strcpy(fulladdr, pref);
        strcat(fulladdr, " ");
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, city, '"', chofs);
		strcat(fulladdr, city);
        strcat(fulladdr, " ");
		chofs = skip_delim(instr, ',', chofs);
		chofs = csv_dq_read(instr, addr, '"', chofs);
		strcat(fulladdr, addr);
        add_node(head, zip, fulladdr);
		n++;
	}
	return n;
}

int add_node(zipnode_t **head, int zip, char *fulladdr){
    zipnode_t *newnode = (zipnode_t *)malloc(sizeof(zipnode_t));
    (*newnode).zip = zip;
    strcpy((*newnode).fulladdr, fulladdr);
    (*newnode).next = *head;
    if(newnode == NULL){
        return 1;
    }
    *head = newnode;
    return 0;
}

int print_n_node(zipnode_t *head, int n){
    zipnode_t *node = head;
    int print_size = 0;
    int flag=0;
    for(int i=0;i<n;i++){
        if(node == NULL){
            print_size = i+1;
            flag = 1;
            break;
        }
        printf("%d : %s\n", (*node).zip, (*node).fulladdr);
        node = (*node).next;
    }
    if(flag == 0){
        return n;
    }
    else if(flag == 1){
        return print_size;
    }
}

zipnode_t *search_node(zipnode_t *head, char *fulladdr){
    zipnode_t *node = head;
    while(node != NULL){
        if(strcmp((*node).fulladdr, fulladdr) == 0){
            return node;
        }
        node = (*node).next;
    }
    return NULL;
}