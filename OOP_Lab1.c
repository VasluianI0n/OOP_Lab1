#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node{
    char value;
    struct node *next, *prev;
}*steps;

//FUNCTIONS
bool isChecked(int num[]);
int location(int num[]);
void grid(int numbers[]);
int* move_up(int num[]);
int* move_left(int num[]);
int* move_down(int num[]);
int* move_right(int num[]);
int* number_generator(int numbers[]);
int* move(char c, int num[]);
int menu();
int* play(int num[]);
int* cont(int num[]);
int* check(int num[]);


//MAIN FUNCTION
void main(){
    
    FILE *saved_data, *numbers; 
    int *num;
    int i, choice;
    num = (int*)calloc(15,sizeof(int));

    for(i = 0; i < 16; i++){
        num[i] = 16;
    }
    choice = menu();
    if(choice  == 1){
        saved_data = fopen("saved_data","w");
        fprintf(saved_data,"");
        fclose(saved_data);
        numbers = fopen("numbers","w");
        num = number_generator(num);
        for(i = 0; i < 16; i++){
            fprintf(numbers,"%d ",num[i]);
        }
        fclose(numbers);
        num = play(num);
    }else if(choice == 2){
        num = cont(num);
        play(num);
    }else if(choice == 3){
        exit(0);
    }
}





//STRUCTURE BEHIND FUNCTIONS

bool isChecked(int num[]){
    int i;
    bool ascending = true;
    for(int i = 0; i < 15; i++){
        if(num[i]!=(i+1)){
            ascending = false;
        }
    }
    return ascending;
}

int location(int num[]){
    int i;
    for(i = 0; i < 16; i++){
        if(num[i] == 0){
            return i;
        }
    }
}

void grid(int numbers[]){
    int i;
    printf("\033[1;35m|-----------------------|\n");
    for(i = 0; i < 4; i++){
        if(numbers[i]==0){
            printf("|     ");
        }else if(numbers[i]>9){
            printf("|\033[0m \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }else{
            printf("|\033[0m  \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }
    }
    printf("|\n");
    printf("|-----------------------|\n");
    for(i = 4; i < 8; i++){
        if(numbers[i]==0){
            printf("|     ");
        }else if(numbers[i]>9){
            printf("|\033[0m \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }else{
            printf("|\033[0m  \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }
    }
    printf("|\n");
    printf("|-----------------------|\n");
    for(i = 8; i < 12; i++){
        if(numbers[i]==0){
            printf("|     ");
        }else if(numbers[i]>9){
            printf("|\033[0m \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }else{
            printf("|\033[0m  \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }
    }
    printf("|\n");
    printf("|-----------------------|\n");
    for(i = 12; i < 16; i++){
        if(numbers[i]==0){
            printf("|     ");
        }else if(numbers[i]>9){
            printf("|\033[0m \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }else{
            printf("|\033[0m  \033[1;33m%d  \033[0m\033[1;35m",numbers[i]);
        }
    }
    printf("|\n");
    printf("|-----------------------|\n\033[0m");
}

int* move_up(int num[]){
    int aux,pos;
    if(location(num)> 11){

        }else{
            pos = location(num);
            aux = num[pos+4];
            num[pos+4] = num[pos];
            num[pos] = aux;
        }    
    return num;
}

int* move_left(int num[]){
    int aux,pos;
    if(location(num)==3||location(num)==7||location(num)==11||location(num)==15){
            
        }else{
            pos = location(num);
            aux = num[pos+1];
            num[pos+1] = num[pos];
            num[pos] = aux;
        }
        return num;
}

int* move_down(int num[]){
    int aux,pos;
    if(location(num)<4){

        }else{
            pos = location(num);
            aux = num[pos-4];
            num[pos-4] = 0;
            num[pos] = aux;
        }
        return num;
}

int* move_right(int num[]){
    int aux,pos;
    if(location(num)==0||location(num)==4||location(num)==8||location(num)==12){
            
        }else{
            pos = location(num);
            aux = num[pos-1];
            num[pos-1] = num[pos];
            num[pos] = aux;
        }
        return num;
}

int* number_generator(int numbers[]){
    int i,j,single;
    //variable for random
    time_t t;

    srand((unsigned) time(&t));

    for(i = 0; i < 16; i++){
        single = 1;
        while(single != 0){
            numbers[i] = rand()%16;
            for(j = 0; j < 16; j++){
                if(numbers[i] == numbers[j]){
                    single++;
                }
            }
            if(single == 2){
                single = 0;
            }else{
                single = 1;
            }
        }
    }
    return numbers;
}

int* move(char c, int num[]){
    FILE *saved_data, *numbers;
    int aux,pos,i;
    char t;
    

    if(tolower(c) == 'w'){
        saved_data = fopen("saved_data","a");
        if(location(num)<10){
            fprintf(saved_data,"%c",c);
            
        }
        num = move_up(num);
        fclose(saved_data);
    }else if(tolower(c) == 'a'){
        saved_data = fopen("saved_data","a");
        if(location(num)!=3&&location(num)!=7&&location(num)!=11&&location(num)!=15){
            fprintf(saved_data,"%c",c);    
        }
        num =move_left(num);
        fclose(saved_data);
    }else if(tolower(c) == 's'){
        saved_data = fopen("saved_data","a");
        if(location(num)>3){
            fprintf(saved_data,"%c",c);
        }
        num = move_down(num);
        fclose(saved_data);
    }else if(tolower(c) == 'd'){
        saved_data = fopen("saved_data","a");
        if(location(num)!=0&&location(num)!=4&&location(num)!=8&&location(num)!=12){
            fprintf(saved_data,"%c",c);
        }
        num = move_right(num);
        fclose(saved_data);
    }else if(tolower(c) == 'u'){
        saved_data = fopen("saved_data","r");
        char aux = getc(saved_data);
        fseek(saved_data, 0L, SEEK_END);
        int sz  = ftell(saved_data);
        fseek(saved_data, 0L, SEEK_SET);
        char str[sz+1], str1[sz-1];
        fgets(str, sz+1, saved_data);
        for(i = 0; i < sz-1; i++){
            str1[i] = str[i];
        }
        str1[sz-1]='\0';
        if(sz == 1){
            t=aux;
        }else{
            t = str[sz-1];    
        }
        fclose(saved_data);
        if(t == 'w'){
                num = move_down(num);
                saved_data = fopen("saved_data","w");
                fprintf(saved_data,"");
                fputs(str1,saved_data);
                fclose(saved_data);
        }else if(t == 'a'){
                num = move_right(num);
                saved_data = fopen("saved_data","w");
                fputs(str1,saved_data);
                fclose(saved_data);
        }else if(t == 's'){
                num = move_up(num);
                saved_data = fopen("saved_data","w");
                fputs(str1,saved_data);
                fclose(saved_data);
        }else if(t == 'd'){
                num = move_left(num);
                saved_data = fopen("saved_data","w");
                fputs(str1,saved_data);
                fclose(saved_data);
        }
    }else if(tolower(c) == 'q'){
        exit(0);
    }else if(tolower(c)=='r'){
        for(i = 0; i < 16; i++){
            num[i] = 16;
        }
        num = number_generator(num);
        saved_data = fopen("saved_data","w");
        fprintf(saved_data,"");
        fclose(saved_data);
    }
    numbers = fopen("numbers","w");
        for(i = 0; i < 16; i++){
            fprintf(numbers,"%d ",num[i]);
        }
        fclose(numbers);
    return num;
}

int menu(){
    int choice;
    printf("\033[1;31m\t15 Puzzle\n\033[0m"); ;
    printf("\033[1;32m>1.New Game \n>2.Resume \n>3.Quit\n\033[0m\033[0;34m>\033[0m");
    scanf("%d", &choice);
    while((choice != 1) && (choice != 2) && (choice != 3)){
        printf("Choose one of the options above: >");
        scanf("%d", &choice);
    }
    return choice;
}  

int* play(int num[]){
    char option;
    while(isChecked(num)==false){
        grid(num);
        printf("\033[1;31m>Move a square in the free square with WASD; \n>Press U for Undo; \n>Press R for Restart\n>Press Q to Quit \n\033[0m\033[0;34m>\033[0m");
        scanf(" %c",&option);
        
        num = move(option,num);
    }
    grid(num);
    printf("\033[0;37m\tGOOD JOB!!\n\033[0m");

    return num;
}

int* cont(int num[]){
    FILE *numbers;
    int i = 0,j = 0;
    numbers = fopen("numbers","r");
    fscanf(numbers,"%d",&i);
    while(!feof(numbers)){
        num[j]=i;
        j++;
        fscanf(numbers,"%d",&i);
    }
    printf("\n");
    fclose(numbers);
    return num;
}

int* check(int num[]){
    int i;
    for(i = 0; i < 14; i++){
            num[i] = i+1;
        }
        num[14] = 0;
        num[15]= 15;
    return num;
}