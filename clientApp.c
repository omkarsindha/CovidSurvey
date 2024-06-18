// clientApp.c
// Created by Omkarsinh Sindha on 7/6/2024.
//
#include <stdio.h>
#include "MyHeader.h"


int main(void) {
    HouseHold database[SIZE];
    HouseHold* ptr = database;
    puts("---------------The Program analyzes and stores information related to Covid-19 cases---------------");
    puts("---------------------and its impact on various races, regions and towns of GTA---------------------");
    puts("------------------------------The program is built by Omkarsinh Sindha-----------------------------\n");
    puts("---------------------------------------Manual data entry module------------------------------------");
    puts("Provide data of up to three household or enter 9 to skip manual data entry to generate records randomly");

    int entriesCompleted = populateRecordsManually(ptr);
    populateRecordsRandomly(ptr, entriesCompleted);
    printRecords(ptr);
    while(1){
        puts("\nMain Menu:");
        puts("\t1. Household records by race, region or town.");
        puts("\t2. Races ranking for Covid 19.");
        puts("\t3. Regions ranking for Covid 19.");
        puts("\t4. Towns ranking for Covid 19.");
        puts("\t5. Races ranking by poverty.");
        puts("\t0. Exit");
        puts("Enter your choice: ");
        int choice = getValidInteger(0,5,1);
        if(choice == 0){
            break;
        }
        switch(choice) {
            case 1:
                recordsByRaceRegionTowns(ptr);
                break;
            case 2:
                racesRankingByCovid19(ptr);
                break;
            case 3:
                regionsRankingByCovid19(ptr);
                break;
            case 4:
                townsRankingByCovid19(ptr);
                break;
            case 5:
                racesRankingByPoverty(ptr);
                break;
            default:
                break;
        }
    }
    return 0;
}
