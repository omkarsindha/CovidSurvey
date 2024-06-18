// MyFunctions.c
// Created by Omkarsinh Sindha on 7/6/2024.
//
#include "MyHeader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int getValidInteger(int min, int max, int skipFlag){
    int input;
    int ctr = 0;
    char buff[BUFF_SIZE];
    while(1){
        fgets(buff, sizeof(buff), stdin);   //buff contains the input characters now
        ctr = sscanf(buff, "%d", &input);
        if(ctr!=1){
            printf("Invalid input, enter a number that is %d to %d!! Please try again:\n", min, max );
            continue;
        }
        if(skipFlag){     // if skip flag is 1 it allows input 9
            if(input == 9){
                return input;
            }
        }
        if(input>max || min>input){
            printf("Invalid input, enter a number that is %d to %d!! Please try again:\n", min, max);
            continue;
        }
        break;
    }
    return input;
} //getValidInteger ends

int* sortArrayNKeepIndices(int arr[], int arrSize){
    static int indexArr[SIZE];
    int arr2[arrSize];
    for (int i = 0; i < arrSize; i++) {
        indexArr[i] = 0;
        arr2[i] = arr[i];
    }
    int min = 0, temp = 0;

    for (int i = 0; i < arrSize ; i++)
    {
        min = i;  // record the position of the smallest
        for (int j = i + 1; j < arrSize; j++)
        {
            // update min when finding a smaller element
            if (arr[j] < arr[min])
                min = j;
        }
        // put the smallest element at position i
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    } // array sorting ends here
    int ctr = 0;
    while ( ctr < arrSize) {
        min = 0;  // restart from first element
        for (int j = 0; j < arrSize; j++)
        {
            if (arr2[j] == INT_MAX) continue; // ignore already marked as minimum indices
            // update min when finding a smaller element
            if (arr2[j] < arr2[min])
                min = j;
        }
        indexArr[ctr] = min; // updating indexArr with the index of the next minimum
        arr2[min] = INT_MAX; // marking minimum element to be ignored next time
        ctr++;
    } //keeping track of previous indices of the array elements ends here
    return indexArr;
} // function sortArrayKeepIndices ends

int populateRecordsManually(HouseHold* ptr){
    char buff[BUFF_SIZE];
    int entriesCompleted = 0;
    int input;
    for (int i = 0; i < 3; ++i) {
        printf("\nData entry for household number %d\n", i+1);
        puts("\nRaces:");
        for (int j = 0; j < RACE_LEN; ++j) {
            printf("%s(%d) ", races[j],j);
        }
        puts("\nEnter an integer or 9 to skip: ");

        input = getValidInteger(0,4, 1) ;

        // If input 9 user wants to skip so this breaks out of the for loop
        if(input ==9){
            puts("\nSkipping manual data entry and generating records randomly......\n");
            break;
        }
        strcpy(ptr->race, races[input]);

        puts("\nRegion:");
        for (int j = 0; j < REGIONS_LEN; ++j) {
            printf("%s(%d) ", regions[0][j], j);
        }
        puts("\nEnter an Integer: ");

        int region = getValidInteger(0,2, 0);
        strcpy(ptr->region, regions[0][region]);

        puts("\nTown: ");
        for (int j = 0; j < TOWNS_LEN; ++j) {
            printf("%s(%d) ", regions[j+1][region], j);
        }
        puts("\nEnter an Integer: ");
        int town = getValidInteger(0,1, 0);
        strcpy(ptr->town, regions[town+1][region]);

        puts("\nEnter annual household income:\nNOTE: It will be rounded to nearest 100:");
        int income = getValidInteger(0,INT_MAX, 0);
        ptr->houseHoldIncome =  ((income + 50) / 100) * 100;     //rounding the income before pushing it in database

        puts("\nEnter number of household members, members fully vaccinated, and members tested positive for Covid-19\nrespectively as 3 integers seperated by tabs or space :");
        while(1){    // Code required 3 entries so I used fgets and sscanf instead of using the function
            int ctr =0;
            int members;
            int vaccinated;
            int positive;
            fgets(buff, BUFF_SIZE, stdin);
            ctr = sscanf(buff, "%d%d%d", &members, &vaccinated, &positive);
            if(ctr!=3){
                puts("Enter exactly 3 integers seperated by space!! Please try again: ");
                continue;
            }
            if(members<1){
                puts("Members cannot be less than 1!! Please try again: ");
                continue;
            }
            if(vaccinated > members || positive > members){   // members must be greater than vaccinated and positive members
                puts("Members should be greater than or equal to vaccinated and positive members!! Please try again: ");
                continue;
            }
            ptr->members = members;
            ptr->vaccinated = vaccinated;
            ptr->positive = positive;
            break;
        }
        ptr++;
        entriesCompleted+=1;     // Successful entry so incrementing to keep track of manual entries
    }
    return entriesCompleted;
} // populateRecordsManually ends

void populateRecordsRandomly(HouseHold* ptr, int entriesCompleted){
    ptr+=entriesCompleted;
    srand(time(NULL));
    for (int i = entriesCompleted; i < SIZE; ++i) {       //i = entries completed so that it does not overwrite the manual entries
        int race = rand()%RACE_LEN;                                    //Generates random number 0 through 4
        int region = rand()%REGIONS_LEN;                                  // Generates random number that is 0,1 or 2
        int town = rand()%(TOWNS_LEN);                                   //Generates random number that is 1 or 2
        unsigned income = (250+ (rand()%(700-250+1)))*100;     //Generates number between 70,000 and 25,000
        int members = rand()%5+1;                               //Generates number 1 through 5  (I made this smaller so that it wont skew poverty data)
        int vaccinated = rand()%members+1;                      //Generates number 1 to number of members
        int positive = rand()%members+1;                        // Same as above
        // Inserting it into structure
        strcpy(ptr->race, races[race]);
        strcpy(ptr->region, regions[0][region]);
        strcpy(ptr->town, regions[town+1][region]);
        ptr->houseHoldIncome = income;
        ptr->members = members;
        ptr->vaccinated = vaccinated;
        ptr->positive = positive;
        ptr++;
    }
    puts("Contents written to file successfully");
} // populateRecordsRandomly() ends

void printRecords(HouseHold* ptr){
    printf("%5s%20s%10s%15s%12s%10s%14s%10s\n","S.no","Race","Region","Town","Income","Members","Vaccinated","Positive");
    int members = 0;         //data members to keep track of total
    int vaccinated = 0;      // "
    int positive = 0;        // "
    for (int i = 0; i < SIZE; ++i) {
        printf("%5d%20s%10s%15s%12u%10d%14d%10d\n",i+1,ptr->race,ptr->region,ptr->town,ptr->houseHoldIncome,ptr->members,ptr->vaccinated,ptr->positive);
        members += ptr->members;
        vaccinated += ptr ->vaccinated;
        positive += ptr-> positive;
        ptr++;
    }
    printf("%5s%20s%10s%15s%12s%10d%14d%10d\n","Total","---------------","------","-----------","------",members,vaccinated,positive);
    puts("\n--------Acknowledgement: above information is obtained from voluntary contributions to survey--------");
} // printRecord() ends

void recordsByRaceRegionTowns(HouseHold* ptr){
    puts("\nEnter an integer to see household records of a particular Race(0), Region(1) or Town(2):");
    int choice = getValidInteger(0,2,0);
    if(choice == 0){
        puts("\nRaces:");
        // print races from the array
        for (int i = 0; i < RACE_LEN; ++i) {
            printf("%s(%d) ", races[i],i);
        }
        puts("\nEnter an integer:");
        int race = getValidInteger(0,RACE_LEN-1,0);
        printf("\n%5s%20s%10s%15s%12s%10s%14s%10s\n","S.no","Race","Region","Town","Income","Members","Vaccinated","Positive");
        int counter = 1;
        for (int i = 0; i < SIZE; ++i) {
            // print only if race is same as selected by user
            if(strcmp(ptr->race, races[race]) == 0){
                printf("%5d%20s%10s%15s%12u%10d%14d%10d\n",counter,ptr->race,ptr->region,ptr->town,ptr->houseHoldIncome,ptr->members,ptr->vaccinated,ptr->positive);
                counter += 1;
            }
            ptr++;
        }
    }

    else if(choice == 1){
        puts("Regions:");
        // print regions from the array
        for (int i = 0; i < REGIONS_LEN; ++i) {
            printf("%s(%d) ", regions[0][i],i);
        }
        puts("\nEnter an integer:");
        int region = getValidInteger(0,REGIONS_LEN-1,0);
        printf("\n%5s%20s%10s%15s%12s%10s%14s%10s\n","S.no","Race","Region","Town","Income","Members","Vaccinated","Positive");
        int counter = 1;
        for (int i = 0; i < SIZE; ++i) {
            //print only if the region is same as the one user selected
            if(strcmp(ptr->region, regions[0][region]) == 0){
                printf("%5d%20s%10s%15s%12u%10d%14d%10d\n",counter,ptr->race,ptr->region,ptr->town,ptr->houseHoldIncome,ptr->members,ptr->vaccinated,ptr->positive);
                counter += 1;
            }
            ptr++;
        }
    }

    else if(choice == 2){
        puts("Towns:");
        for (int i = 0; i < REGIONS_LEN; ++i) {
            // Print the towns from the array
            for (int j = 0; j < TOWNS_LEN; ++j) {
                printf("%s(%d) ", regions[j+1][i],i * TOWNS_LEN + j);
            }
        }
        puts("\nEnter an integer:");
        int town = getValidInteger(0,(REGIONS_LEN*TOWNS_LEN)-1,0);
        printf("\n%5s%20s%10s%15s%12s%10s%14s%10s\n","S.no","Race","Region","Town","Income","Members","Vaccinated","Positive");
        int counter = 1;
        for (int i = 0; i < SIZE; ++i) {
            //print only if the region is same as the one user selected
            if(strcmp(ptr->town, regions[(town % TOWNS_LEN) + 1][town/TOWNS_LEN]) == 0){   // You can see how this formula works in the note.txt
                printf("%5d%20s%10s%15s%12u%10d%14d%10d\n",counter,ptr->race,ptr->region,ptr->town,ptr->houseHoldIncome,ptr->members,ptr->vaccinated,ptr->positive);
                counter += 1;
            }
            ptr++;
        }
    }
} // recordsByRaceRegionTowns() ends

void racesRankingByCovid19(HouseHold* ptr){
    puts("\nEnter 0 to see all Covid 19 vaccinated or 1 for tested positive cases or 9 to go to main menu:");
    int choice = getValidInteger(0,1,1);
    if (choice == 9) {
        return;
    }
    // initializing the array as all 0s of length of number of races
    // The Idea is to increment every index if corresponding race is found
    int records[RACE_LEN] = {0};
    if(choice == 0){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < RACE_LEN; ++j) {
                if(strcmp(ptr->race, races[j]) == 0){
                    records[j] += ptr->vaccinated;
                }
            }
            ptr++;
        }
    }
    if(choice == 1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < RACE_LEN; ++j) {
                if(strcmp(ptr->race, races[j]) == 0){
                    records[j] += ptr->positive;
                }
            }
            ptr++;
        }
    }
    puts("\n----------------Races ranking of Covid 19----------------\n");
    printf("%20s%20s\n","Races", choice==0?"Vaccinated":"Tested Positive");
    // Before printing, I sort the array using your function and keep track of old index to keep track of the corresponding race
    int* oldIndices = sortArrayNKeepIndices(records,RACE_LEN);
    for (int i = 0; i < RACE_LEN; ++i) {
        //printing the sorted array and corresponding race using old indices
        printf("%20s%20d\n",races[oldIndices[i]],records[i]);
    }
} // racesRankingByCovid19() ends

void regionsRankingByCovid19(HouseHold* ptr){
    puts("\nEnter 0 to see all Covid 19 vaccinated or 1 for tested positive cases or 9 to go to main menu:");
    int choice = getValidInteger(0,1,1);
    if (choice == 9) {
        return;
    }
    //Array of size of number of regions
    int records[REGIONS_LEN] = {0};
    if(choice == 0){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < REGIONS_LEN; ++j) {
                if(strcmp(ptr->region, regions[0][j]) == 0){
                    records[j] += ptr->vaccinated;
                }
            }
            ptr++;
        }
    }
    if(choice == 1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < REGIONS_LEN; ++j) {
                if(strcmp(ptr->region, regions[0][j]) == 0){
                    records[j] += ptr->positive;
                }
            }
            ptr++;
        }
    }
    puts("\n----------------Regions ranking of Covid 19----------------\n");
    printf("%20s%20s\n","Regions", choice==0?"Vaccinated":"Tested Positive");
    int* oldIndices = sortArrayNKeepIndices(records,REGIONS_LEN);
    for (int i = 0; i < REGIONS_LEN; ++i) {
        //printing the sorted array and corresponding region using old indices
        printf("%20s%20d\n",regions[0][oldIndices[i]],records[i]);
    }
} // regionsRankingByCovid19() ends

void townsRankingByCovid19(HouseHold* ptr){
    puts("\nEnter 0 to see all Covid 19 vaccinated or 1 for tested positive cases or 9 to go to main menu:");
    int choice = getValidInteger(0,1,1);
    if (choice == 9) {
        return;
    }
    // array of size of number of towns
    int records[TOWNS_LEN*REGIONS_LEN] = {0};
    if(choice == 0){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < REGIONS_LEN; ++j) {
                for (int k = 0; k < TOWNS_LEN; ++k) {
                    //incrementing the respective index if town is same
                    if (strcmp(ptr->town, regions[k+1][j]) == 0) {
                        records[j * TOWNS_LEN + k] += ptr->vaccinated;
                    }
                }
            }
            ptr++;
        }
    }
    if(choice == 1){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < REGIONS_LEN; ++j) {
                for (int k = 0; k < TOWNS_LEN; ++k) {
                    if (strcmp(ptr->town, regions[k+1][j]) == 0) {
                        records[j * TOWNS_LEN + k] += ptr->positive;
                    }
                }
            }
            ptr++;
        }
    }
    puts("\n----------------Towns ranking of Covid 19----------------\n");
    printf("%20s%20s\n","Towns", choice==0?"Vaccinated":"Tested Positive");
    int* oldIndices = sortArrayNKeepIndices(records,REGIONS_LEN*TOWNS_LEN);
    for (int i = 0; i < REGIONS_LEN*TOWNS_LEN; ++i) {
        //printing the sorted array and corresponding town using old indices
        printf("%20s%20d\n",regions[ (oldIndices[i]%TOWNS_LEN)+1 ][(oldIndices[i]/TOWNS_LEN)],records[i]);
    }
}  // townsRankingByCovid19() ends

void racesRankingByPoverty(HouseHold* ptr){
    int belowPoverty[RACE_LEN] = {0};
    int abovePoverty[RACE_LEN] = {0};
    int povertyPercentage[RACE_LEN] = {0};
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < RACE_LEN; ++j) {
            if(strcmp(ptr->race, races[j]) == 0){
                if(ptr->members == 1 && ptr->houseHoldIncome<30000){
                    belowPoverty[j] += 1;
                }else if(ptr->members == 2 && ptr->houseHoldIncome<35000){
                    belowPoverty[j] += 1;
                }else if(ptr->members == 3 && ptr->houseHoldIncome<40000){
                    belowPoverty[j] += 1;
                }else if(ptr->members == 4 && ptr->houseHoldIncome<45000){
                    belowPoverty[j] += 1;
                }else if(ptr->members > 4 && ptr->houseHoldIncome<50000){
                    belowPoverty[j] += 1;
                }
                else{
                    abovePoverty[j] += 1;
                }
            }
        }
        ptr++;
    }
    puts("\n----------------Races ranking of Poverty----------------\n");
    printf("%20s%20s\n","Races", "Poverty percentage");
    for (int i = 0; i < RACE_LEN; ++i) {
        int total = belowPoverty[i] + abovePoverty[i];
        if (total > 0) {        // Checking this to avoid division by 0 (Really rare but possible)
            povertyPercentage[i] = ((float)belowPoverty[i] / total) * 100;   // used float so that I do not lose data
        } else {
            povertyPercentage[i] = 0;
        }
    }
    int* oldIndices = sortArrayNKeepIndices(povertyPercentage,RACE_LEN);
    for (int i = 0; i < RACE_LEN; ++i) {
        printf("%20s%19d%%\n",races[oldIndices[i]],povertyPercentage[i]);
    }
}  // racesRankingByPoverty() ends


