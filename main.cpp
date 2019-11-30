#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h>
#include "airport.h"
#include <stdlib.h>

extern pRunwayNode pAirport;
int main() {
	char inputLine[MAX_LINE_SIZE];
	char delimiters[4] = " \t\n";
	char* command;
	char* arg1;
	char* arg2;
	char* arg3;
	char* arg4;
	while (fgets(inputLine, MAX_LINE_SIZE, stdin)) {
		//printf("%s\n", inputLine);
		command = strtok(inputLine, delimiters);
		arg1 = strtok(NULL, delimiters);
		arg2 = strtok(NULL, delimiters);
		arg3 = strtok(NULL, delimiters);
		arg4 = strtok(NULL, delimiters);


		if (strcmp(command, "Insert") == 0) {

			if (arg1 == NULL || arg2 == NULL) {
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}

			int runwayNumber = atoi(arg1);
			if (runwayNumber == 0 || (strcmp(arg2, "D") != 0 && strcmp(arg2, "I") != 0)) {
				fprintf(stderr, "Insert execution failed.\n");
				//printf("%d", runwayNumber);
				continue;
			}

			FlightType runwayType = (strcmp(arg2, "D") == 0) ? DOMESTIC : INTERNATIONAL;
			if (addRunway(runwayNumber, runwayType) == FAILURE) {
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}


		}
		else if (strcmp(command, "Remove") == 0) {

			if (arg1 == NULL) {
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}

			int runwayNumber = atoi(arg1);
			if (runwayNumber == 0) {
				fprintf(stderr, "Remove execution failed.\n");
				continue;

			}

			if (removeRunway(runwayNumber) == FAILURE) {
				fprintf(stderr, "Remove execution failed.\n");
				continue;

			}



		}
		////////////////////////////////////////////////////////////////////////////////////////////
		else if (strcmp(command, "Add") == 0) {
			if (arg1 == NULL || arg2 == NULL || arg3 == NULL || arg4 == NULL) {
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}

			int flightNumber = atoi(arg1);
			if (flightNumber == 0 || (strcmp(arg2, "D") != 0 && strcmp(arg2, "I") != 0) || (strcmp(arg4, "E") != 0 && strcmp(arg4, "R") != 0)) {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}


			FlightType type = (strcmp(arg2, "D") == 0) ? DOMESTIC : INTERNATIONAL;
			BOOL isEmergency = (strcmp(arg4, "E") == 0) ? TRUE : FALSE;


			if (addFlightToAirport(flightNumber, type, arg3, isEmergency) == FAILURE) {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}
		else if (strcmp(command, "Depart") == 0) {
			if (depart() == FAILURE)
				fprintf(stderr, "Depart execution failed.\n");

		}


		else if (strcmp(command, "Change") == 0) {


			if (arg1 == NULL || arg2 == NULL) {
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}

			if (changeDest(arg1, arg2) == FAILURE)
				fprintf(stderr, "Change execution failed.\n");

		}
		else if (strcmp(command, "Delay") == 0) {
			if (arg1 == NULL)
				fprintf(stderr, "Delay failed: not enough parameters.\n");

			if (delay(arg1) == FAILURE)
				fprintf(stderr, "Delay execution failed.\n");
		}


		else if (strcmp(command, "Print") == 0) {
			printAirport();
		}
		else if (strcmp(command, "Exit") == 0) {
			destroyAirport();
			return 0;
		}
		else {//command doesn't exist
			fprintf(stderr, "Command not found.\n");

		}
	}
	return 0;
}
