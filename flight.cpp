#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "flight.h"
//struct to hold flight properties
struct flight {
	int id;
	FlightType type;
	char dest[4];
	BOOL isEmergency;
};
/*
	function name: createFlight
	Description: create a new flight instance with the given properties
	Parameters: id - flight id, type - FlightType(DOMESTIC/INTERNATIONAL), dest - flight destination, isEmergency - boolean to determine if the flight is an emergency flight
	Return Value: pointer to the new flight instance, NULL is returned if the operation is failed.
*/
pFlight createFlight(int id, FlightType type, char* dest, BOOL isEmergency) {

	int destCheck = isDestValid(dest);//using isDestValid method to check destination validity

	//parameters validation condition - id in range, type is valid, dest is valid, isEmergency is valid
	if (id > 0 && id <= MAX_ID && (type == DOMESTIC || type == INTERNATIONAL) && (isEmergency == FALSE || isEmergency == TRUE) && destCheck == 1) {
		pFlight flight_pointer = (pFlight)malloc(sizeof(struct flight));
		if (flight_pointer == NULL) { //allocation fail
			return NULL;
		}

		else {
			flight_pointer->id = id;
			flight_pointer->type = type;
			//strcpy(flight_pointer->dest, dest);
			int i;
			for (i = 0; i <= 3; i++)
				flight_pointer->dest[i] = dest[i];
			flight_pointer->isEmergency = isEmergency;
			return flight_pointer;
		}
	}

	return NULL;
}
/*
	function name: destroyFlight
	Description: delete the flight that holded by the given pointer
	Parameters: flight - a pointer to struct flight
	Return Value: void
*/
void destroyFlight(pFlight flight) {
	if (flight == NULL)
		return;
	else {
		free(flight);
		return;
	}


}
/*
	function name: printFlight
	Description: print the flight properties of the flight that holded by the given pointer
	Parameters: flight - a pointer to struct flight
	Return Value: void
*/
void printFlight(pFlight flight) {
	if (flight == NULL)
		return;
	else {
		char type = (flight->type == DOMESTIC) ? 'D' : 'I';
		char isEmergency = (flight->isEmergency == TRUE) ? 'E' : 'R';
		printf("Flight %d %c %s %c\n", flight->id, type, flight->dest, isEmergency);
		return;
	}


}

/*
	function name: getFlightType
	Description: a getter function to get the type of the flight that holded by the given pointer
	Parameters: flight - a pointer to struct flight
	Return Value: FlightType
*/
FlightType getFlightType(pFlight flight) {
	//if (flight == NULL)
		//return;
	return flight->type;
}

/*
	function name: getFlightID
	Description: a getter function to get the id of the flight that holded by the given pointer
	Parameters: flight - a pointer to struct flight
	Return Value: int
*/
int getFlightID(pFlight flight) {
	if (flight == NULL)
		return -1;
	return (flight->id);
}

/*
	function name: getIsEmergency
	Description: a getter function to check if the flight that holded by the given pointer is an Emegency flight
	Parameters: flight - a pointer to struct flight
	Return Value: BOOL
*/
BOOL getIsEmergency(pFlight flight) {
	if (flight == NULL)
		return FALSE;
	return flight->isEmergency;
}

/*
	function name: getFlightDest
	Description: a getter function to get the destination of the flight that holded by the given pointer
	Parameters: flight - a pointer to struct flight
	Return Value: char*
*/
char* getFlightDest(pFlight flight) {
	return flight->dest;
}

/*
	function name: changeDestFlight
	Description: changes the destination of a flight to a given destination
	Parameters: flight - a pointer to struct flight, dest - new destionation
	Return Value: void
*/
void changeDestFlight(pFlight flight, char* dest) {
	int i;
	for (i = 0; i <= 3; i++) // due to compilation warnings, we use for loop for string copying
		flight->dest[i] = dest[i];
	return;
}

/*
	function name: isDestValid
	Description: checks if a given destination string is valid
	Parameters: dest - a string of characters to check
	Return Value: int (1 = valid, 0 = invalid)
*/
int isDestValid(char* dest) {
	int destCheck = 1;
	int counter = 0;
	while (dest[counter] != '\0') {
		if (counter >= 3) {//check if dest is 3 letters long
			destCheck = 0;
			break;
		}
		if (dest[counter] < 'A' || dest[counter] > 'Z')//checking if dest is capitalized using ASCII properties
			destCheck = 0;
		counter++;

	}
	return destCheck;


}
