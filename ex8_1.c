#include <stdio.h>
#include <string.h>

#define SIZE 128
#define BUF_SIZE 255

unsigned int hash(char *str);

typedef struct person_st{
    char name[30];
    int gender;
    int age;
} person_t;

person_t data;
person_t table[SIZE];
const person_t init = {"", 0, 0};

int main(void){
    for(int i=0;i<SIZE;i++){
        table[i] = init;
    }
    char input[30];
    int n = 0;
    int hashed = 0;
    FILE *fp;
    char buff[BUF_SIZE];

    fp = fopen("personal_data.txt", "r");

    while(fgets(buff, sizeof(buff), fp) != NULL){
        n = sscanf(buff, "%s %d %d", data.name, &data.gender, &data.age);
        if(n != 3){
            printf("Input Error!\n");
            return 1;
        }

        hashed = hash(data.name);

        if(strcmp(table[hashed].name, init.name) == 0){
            table[hashed] = data;
        } else {
            printf("collision\n");
            return 1;
        }
    }
    
    fclose(fp);

    while(1){
        printf("Name? >");
        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = '\0';

        if(strcmp(input, "exit") == 0){
            printf("Bye!");
            break;
        } else {
            data = table[hash(input)];
            if(strcmp(data.name, init.name) == 0){
                printf("No data\n");
            } else {
                if(data.gender == 1){
                    printf("(%s male %d)\n", data.name, data.age);
                }
                else if(data.gender == 2){
                    printf("(%s female %d)\n", data.name, data.age);
                } else {
                    printf("(%s other %d)\n", data.name, data.age);
                }
            }
        }
    }

    return 0;
}

unsigned int hash(char *str){
    int hashval = 0;
    while(*str != '\0'){
        hashval = hashval + *str;
        str++;
    }
    return hashval%SIZE;
}