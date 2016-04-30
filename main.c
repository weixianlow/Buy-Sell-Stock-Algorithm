/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: weixianlow
 * Course:
 * Title:
 *
 * Created on April 17, 2016, 1:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "vector.h"

typedef struct set
{
    int toBuyHere;
    int toSellHere;
}buySellSet;

void parsing(int*, char*, int);
void stockBuySell(int* prices, int number_days, int r);
void stockBuySell2(int* prices, int);
void findGlobalParent(int* globalDirection[], int* localDirection[], int[], int[], int counter, int i, int j, int* code );
void findLocalParent(int* globalDirection[], int* localDirection[], int[], int[], int counter, int i, int j, int* code);


/*
 * 
 */
int main(int argc, char** argv) {

    if(argc != 4)
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    
    
    
    int i;
    
    int numberOfDays = atoi(argv[1]);
    int r = atoi(argv[2]);
    
    int prices[numberOfDays];
    parsing(prices, argv[3], numberOfDays);
    
    
    
    
    
//    for (i=0;i<numberOfDays;i++)
//    {
//        printf("\nReading value at index %d: %d", i, prices[i]);
//    }
    
    
    stockBuySell(prices, numberOfDays, r);
    
    
    return (EXIT_SUCCESS);
}

void parsing(int* prices, char* fileInput, int numberOfDays){
    
    FILE* fp = fopen(fileInput, "r");
    char c;
    int input;
    int count=0;
   
//    struct vector_value value;
    
    if(!fp ){
        exit(FILE_FAILED_TO_OPEN);
    }
    
    
    

    
    while(!feof(fp)){
        //count++;
        
        
    if(!fscanf(fp, "%d\n", &input)){
        fclose(fp);
        
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }
    else{
        prices[count] = input;
        count++;
    }
    
    
    
    }
    if(count != numberOfDays){
        fclose(fp);
        exit(INCORRECT_NUMBER_OF_DAYS_INPUTTED);
    }
    
    
//    if(count == 0){
//        fclose(fp);
//        free_vector(v);
//        exit(PARSING_ERROR_EMPTY_FILE);
//    }
}

void stockBuySell(int* array, int number_days, int r)
{
    
    if(number_days < 2){
        return;
    }
    
    int days = number_days;
    if(r >= days){
        return stockBuySell2(array, number_days);
    }
    int i=0, j=0;
    int local[days][r+1];
    int global[days][r+1];
    int* localDirection[days];
    int* globalDirection[days];
    int code =1;
    int buy[r];
    int sell[r];
    
    
    
//    buySellSet setofBuySell[r];
    int counter = r-1;
    
    
    for(i=0;i<r;i++){
       buy[i] = -1;
       sell[i] = -1;
    }
    
    for(i=0;i<days;i++){
        localDirection[i] = malloc(sizeof(int)*(r+1));
        globalDirection[i] = malloc(sizeof(int)*(r+1));
    }
    
    for(i=0;i<days;i++){
        for(j=0;j<r+1;j++){
            localDirection[i][j] = 0;
            globalDirection[i][j] = 0;
        }
    }
    
    
    for(i=0;i<days;i++){
        for(j=0;j<r+1;j++){
            local[i][j] = 0;
            
            global[i][j] = 0;
            
            
            
                    
        }
    }
    for( i=1;i<days;i++){
        int difference = array[i] - array[i-1];
        
        for( j=1;j<=r;j++){
            if(global[i-1][j-1] >= local[i-1][j]+ difference){
                local[i][j] = global[i-1][j-1];
                localDirection[i][j] = 2;
            }else{
                local[i][j] = local[i-1][j]+ difference;
                localDirection[i][j] = 1;
                
            }
            
            if(global[i - 1][j] >= local[i][j]){
                global[i][j] = global[i - 1][j];
                globalDirection[i][j] = 3;
            }else{
                global[i][j] = local[i][j];
                globalDirection[i][j] = 4;
                
            }
        }
    }
//    printf("Local Direction\n");
//    for(i=0;i<r+1;i++){
//        printf("%d %d %d %d %d %d\n", localDirection[0][i], localDirection[1][i], localDirection[2][i], localDirection[3][i], localDirection[4][i], localDirection[5][i]);
//    }
//    printf("Global Direction\n");
//    for(i=0;i<r+1;i++){
//        printf("%d ", globalDirection[0][i]);
//        printf("%d ", globalDirection[1][i]);
//        printf("%d ", globalDirection[2][i]);
//        printf("%d ", globalDirection[3][i]);
//        printf("%d ", globalDirection[4][i]);
//        printf("%d ", globalDirection[5][i]);
//        printf("\n");
//    }
    findGlobalParent(globalDirection, localDirection, buy, sell, counter, days-1, r, &code);
    
    for(i=0;i<r;i++){
        if(buy[i] == -1){
            
        }else{
            printf("%d\n", buy[i]+1);
        }
        if(sell[i] == -1){
            
        }else{
            printf("%d\n", sell[i]+1);
        }
    }
    
    //printf("\nProfit is %d", global[days-1][r]);
    
    
}

void stockBuySell2 (int array[], int numberOfDays){
    int maxProfit =0;
    
    for(int i=1;i<numberOfDays;i++){
        if(array[i] > array[i-1]){
            maxProfit += array[i] - array[i-1];
        }
    }
    
    printf("Maximum profit from stockBuySell2 : %d", maxProfit);
}

void findGlobalParent(int* globalDirection[], int* localDirection[], int buy[], int sell[], int counter, int i, int j, int* code){
    
    
    while(*code){
        if ((globalDirection[i][j]) == 0){
            *code = 0;
            break;
        }else{
            if((globalDirection[i][j]) == 4){
                sell[counter] = i;
                findLocalParent(globalDirection, localDirection, buy, sell, counter, i, j, code);
            }else
            
            if((globalDirection[i][j]) == 3){
                i--;
            }
        }
    }
}

void findLocalParent(int* globalDirection[], int* localDirection[], int buy[], int sell[], int counter, int i, int j, int* code){
    
    while(*code){
        if(localDirection[i][j] == 0){
            buy[counter] = i;
            *code = 0;
            break;
        }else{
            if(localDirection[i][j] == 2){
                buy[counter--] = i;
                findGlobalParent(globalDirection, localDirection, buy, sell, counter, i-1, j, code);
            }else if(localDirection[i][j] == 1){
                i--;
            }
        }
    }
}

