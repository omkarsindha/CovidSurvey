// MyHeader.h
// Created by Omkarsinh Sindha on 7/6/2024.
//

#ifndef OMKARSINHSINDHAASSIGN2_MYHEADER_H
#define OMKARSINHSINDHAASSIGN2_MYHEADER_H

#define SIZE 100
#define BUFF_SIZE 100
#define LEN 20

typedef struct _try{
    char race[LEN];
    char region[LEN];
    char town[LEN];
    unsigned int houseHoldIncome;
    int members;
    int vaccinated;
    int positive;
}HouseHold;


/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * @return It returns the number of entries input manually
 * This function lets the user input data into the database manually or gives option to skip
 */
int populateRecordsManually(HouseHold* ptr);

/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * @param entriesCompleted is number of records already inserted
 * This function inserts randomly generated structures into database up till 100
 */
void populateRecordsRandomly(HouseHold* ptr, int entriesCompleted);

/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This function displays full database in a readable table on the console
 */
void printRecords(HouseHold* ptr);


/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This method gives the user option to display only the records of region, town or race of their liking
 */
void recordsByRaceRegionTowns(HouseHold* ptr);

/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This function ranks all the races by calculating total positive or vaccinated members for each race
 */
void racesRankingByCovid19(HouseHold* ptr);


/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This function ranks all the regions by calculating total positive or vaccinated members for each race
 */
void regionsRankingByCovid19(HouseHold* ptr);


/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This function ranks all the towns by calculating total positive or vaccinated members for each race
 */
void townsRankingByCovid19(HouseHold* ptr);



/**
 *
 * @param ptr is an HouseHold* type pointer that points to the records database
 * This function ranks all the races by calculating poverty in reach household for that race
 */
void racesRankingByPoverty(HouseHold* ptr);


/**
 *
 * @param min is the smallest allowed integer
 * @param max is the largest allowed integer
 * @param skipFlag if set to 1 it allows user to input '9' outside of allowed range
 * @return is the integer that user has given as input
 * This function is used to get a single integer between a certain range from the user
 */
int getValidInteger(int min, int max, int skipFlag);

/**
 *
 * @param arr
 * @param arrSize
 * @return Indices of old array
 * This is your method I just copy pasted it
 */
int* sortArrayNKeepIndices(int arr[], int arrSize);

#define RACE_LEN 5
static char* races[] = {"Indigenous", "Caucasian", "African American", "Asian", "Others"};

#define REGIONS_LEN 3
#define TOWNS_LEN 2
static char* regions[REGIONS_LEN][TOWNS_LEN+1] = {{"Durham", "Peel", "York"},
                      {"Whitby", "Brampton", "Maple"},
                      {"Oshawa", "Mississauga", "Vaughan"} };

#endif //OMKARSINHSINDHAASSIGN2_MYHEADER_H
