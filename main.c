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

void parsing(struct vector* v, char*);
void stockBuySell(struct vector* v, int number_days, int r);

typedef struct set
{
    int toBuy;
    int toSell;
}buySellSet;
/*
 * 
 */
int main(int argc, char** argv) {

    if(argc != 4)
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    
    struct vector v;
    parsing(&v, argv[3]);
    
    int i;
    
    int numberOfDays = atoi(argv[1]);
    int r = atoi(argv[2]);
    
    if(v.size != numberOfDays){
        exit(INCORRECT_NUMBER_OF_DAYS_INPUTTED);
    }
    
//    for (i=0;i<v.size;i++)
//    {
//        printf("\nReading value at index %d: %d", i, v.data[i]-48);
//    }
    
    stockBuySell(&v, numberOfDays, r);
    free_vector(&v);
    
    return (EXIT_SUCCESS);
}

void parsing(struct vector* v, char* fileInput){
    
    FILE* fp = fopen(fileInput, "r");
    char c;
    int input;
    int count;
   
//    struct vector_value value;
    
    if(!fp ){
        exit(FILE_FAILED_TO_OPEN);
    }
    
    init_vector(v);
    
//    while( (c=getc(fp))!= EOF){
//        if(c == '\n'){
//            input = get_value_and_clear_vector(&value);
//            insert_element_vector(v, input);
//            printf("Added: %c\n", input);
//            
//            continue;
//        }
//        if(isdigit(c)){
//            insert_element_vector_value(&value, c);
//        }else{
//            free_vector(v);
//            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
//        }
//        
//    }
    
//    if(feof(fp)){
//       fclose(fp);
//        free_vector(v);
//        exit(PARSING_ERROR_EMPTY_FILE);
//    }
    
    while(!feof(fp)){
        //count++;
        
        
    if(!fscanf(fp, "%d\n", &input)){
        fclose(fp);
        free_vector(v);
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }
    else{
        insert_element_vector(v, input);
        //printf("Added: %d\n", input);
    }
    
    
    }
    
    if((*v).size == 0){
        fclose(fp);
        free_vector(v);
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    
//    if(count == 0){
//        fclose(fp);
//        free_vector(v);
//        exit(PARSING_ERROR_EMPTY_FILE);
//    }
}

void stockBuySell(struct vector* v, int number_days, int r)
{
    // Prices must be given for at least two days
    if (number_days == 1)
        return;

    if(r == 1){
        
        int maximum = access_element_vector(v, 0);
        int minimum = access_element_vector(v, 0);
        
        int i;
        
        for(i=0;i<number_days;i++)
        {
            if(access_element_vector(v, i) < minimum)
            {
                minimum = access_element_vector(v, i);
            }
            
            if(access_element_vector(v, i) > maximum)
            {
                maximum = access_element_vector(v, i);
            }
        }
        
        printf("%d\n", minimum);
        printf("%d\n", maximum);
        
        return;
        
    }else{
        
    int count = 0; // count of solution pairs

    // solution vector
    buySellSet sol[number_days/2 + 1];

    // Traverse through given price array
    int i = 0;
    while (i < number_days-1)
    {
        // Find Local Minima. Note that the limit is (n-2) as we are
        // comparing present element to the next element. 
        while ((i < number_days-1) && (access_element_vector(v, i+1) <= access_element_vector(v, i))){
            i++;
        }

        // If we reached the end, break as no further solution possible
        if (i == number_days-1)
        {
            break;
        }
        // Store the index of minima
        sol[count].toBuy = i++;

        // Find Local Maxima.  Note that the limit is (n-1) as we are
        // comparing to previous element
        while ((i < number_days) && (access_element_vector(v, i) >= access_element_vector(v, i-1))){
           i++; 
        }
            

        // Store the index of maxima
        sol[count].toSell = i-1;

        // Increment count of buy/sell pairs
        count++;
    }

    // print solution
    if (count == 0){
        return;
    }
    else
    {
        //printf("\n");
       for (int i = 0; i < count; i++){
          printf("%d\n", sol[i].toBuy+1);
          printf("%d\n", sol[i].toSell+1);
       }
    }

    return;
    }
}