#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "airport.h"

struct runwayNode {
	pRunway runway_pointer;
	pRunwayNode nextRunway;
};

pRunwayNode pAirport = NULL;

Result addRunway(int runwayID, FlightType runwayType) {


	if (pAirport == NULL) {
		pAirport = (pRunwayNode)malloc(sizeof(struct runwayNode));
		if (pAirport == NULL)
			return FAILURE;
		pAirport->runway_pointer = createRunway(runwayID, runwayType);
		if (pAirport->runway_pointer == NULL) {
			free(pAirport);
			pAirport = NULL;
			return FAILURE;
		}
		pAirport->nextRunway = NULL;
		return SUCCESS;
	}
	pRunwayNode tmp_pointer = pAirport;
	if (getRunwayID(tmp_pointer->runway_pointer) == runwayID)
		return FAILURE;
	while (tmp_pointer->nextRunway != NULL) {
		if (tmp_pointer->runway_pointer != NULL) {
			if (getRunwayID(tmp_pointer->runway_pointer) == runwayID)
				return FAILURE;
		}
		else
			return FAILURE;//shouldn't get here

		tmp_pointer = tmp_pointer->nextRunway;

	}
	if (getRunwayID(tmp_pointer->runway_pointer) == runwayID)//added last - need to make sure the last node is also different.
		return FAILURE;
	tmp_pointer->nextRunway = (pRunwayNode)malloc(sizeof(struct runwayNode));
	if (tmp_pointer->nextRunway == NULL)
		return FAILURE;
	(tmp_pointer->nextRunway)->runway_pointer = createRunway(runwayID, runwayType);
	if ((tmp_pointer->nextRunway)->runway_pointer == NULL) {
		free(tmp_pointer->nextRunway);
		tmp_pointer->nextRunway = NULL;
		return FAILURE;
	}
	(tmp_pointer->nextRunway)->nextRunway = NULL;
	return SUCCESS;

}




Result removeRunway(int runwayID) {
	if (pAirport == NULL)
		return FAILURE;
	pRunwayNode tmp_pointer = pAirport;
	pRunwayNode tmp_pointer_last = pAirport;
	while (tmp_pointer != NULL) {
		if (getRunwayID(tmp_pointer->runway_pointer) == runwayID) {
			if (tmp_pointer == pAirport) {
				pAirport = pAirport->nextRunway;
			}
			tmp_pointer_last->nextRunway = tmp_pointer->nextRunway;
			destroyRunway(tmp_pointer->runway_pointer);
			free(tmp_pointer);
			return SUCCESS;

		}
		tmp_pointer_last = tmp_pointer;
		tmp_pointer = tmp_pointer->nextRunway;
	}
	return FAILURE; //if the runway doesn't exist
}


Result addFlightToAirport(int flightID, FlightType type, char* dest, BOOL isEmergency) {



	pRunway best_runway = NULL;
	pRunwayNode tmp_pointer = pAirport;
	int current_min = MAX_ID + 1;
	while (tmp_pointer != NULL) {
		if (isFlightExists(tmp_pointer->runway_pointer, flightID) == TRUE)
			return FAILURE;
		if (getRunwayType(tmp_pointer->runway_pointer) == type)
			if (getFlightNum(tmp_pointer->runway_pointer) <= current_min) {
				if (getFlightNum(tmp_pointer->runway_pointer) == current_min)
					best_runway = (getRunwayID(tmp_pointer->runway_pointer) < getRunwayID(best_runway)) ? tmp_pointer->runway_pointer : best_runway;
				else {
					best_runway = tmp_pointer->runway_pointer;
					current_min = getFlightNum(best_runway);
				}
			}
		tmp_pointer = tmp_pointer->nextRunway;
	}

	if (best_runway == NULL)
		return FAILURE;
	else {
		pFlight newFlight = createFlight(flightID, type, dest, isEmergency);
		if (newFlight == NULL)
			return FAILURE;
		if (addFlight(best_runway, newFlight) == SUCCESS)
			return SUCCESS;
		else {
			destroyFlight(newFlight);
			return FAILURE;
		}
	}
	return FAILURE;
}

Result depart() {

	if (pAirport == NULL)
		return FAILURE;
	pRunway departRunway = NULL;
	pRunwayNode tmp_pointer = pAirport;
	int current_max_emergency_flights = -1;
	while (tmp_pointer != NULL) {
		if (getEmergencyNum(tmp_pointer->runway_pointer) > current_max_emergency_flights) {
			departRunway = tmp_pointer->runway_pointer;
			current_max_emergency_flights = getEmergencyNum(departRunway);
		}
		else if (getEmergencyNum(tmp_pointer->runway_pointer) == current_max_emergency_flights) {
			if (getFlightNum(tmp_pointer->runway_pointer) > getFlightNum(departRunway)) {
				departRunway = tmp_pointer->runway_pointer;
			}

			else if (getFlightNum(tmp_pointer->runway_pointer) == getFlightNum(departRunway)) {
				departRunway = (getRunwayID(tmp_pointer->runway_pointer) < getRunwayID(departRunway)) ? tmp_pointer->runway_pointer : departRunway;

			}
		}
		tmp_pointer = tmp_pointer->nextRunway;

	}

	if (departRunway == NULL)
		return FAILURE;
	else
		return departFromRunway(departRunway);

}

Result changeDest(char* last_dest, char* new_dest) {

	if (isDestValid(last_dest) == 0 || isDestValid(new_dest) == 0)
		return FAILURE;
	if (pAirport == NULL)
		return SUCCESS;
	pRunwayNode tmp_pointer = pAirport;
	while (tmp_pointer != NULL) {
		changeDestRunway(tmp_pointer->runway_pointer, last_dest, new_dest);
		tmp_pointer = tmp_pointer->nextRunway;
	}
	return SUCCESS;

}
Result delay(char* dest) {
	if (isDestValid(dest) == 0)
		return FAILURE;
	if (pAirport == NULL)
		return SUCCESS;
	pRunwayNode tmp_pointer = pAirport;
	while (tmp_pointer != NULL) {
		runwayDelay(tmp_pointer->runway_pointer, dest);
		tmp_pointer = tmp_pointer->nextRunway;
	}
	return SUCCESS;
}

void printAirport() {
	pRunwayNode tmp_pointer = pAirport;
	printf("Airport status:\n");
	while (tmp_pointer != NULL) {
		printRunway(tmp_pointer->runway_pointer);
		tmp_pointer = tmp_pointer->nextRunway;
	}
	printf("\n");
	return;
}
void destroyAirport() {
	pRunwayNode tmp_pointer = pAirport;
	pRunwayNode tmp_holder = NULL;
	while (tmp_pointer != NULL) {
		destroyRunway(tmp_pointer->runway_pointer);
		tmp_holder = tmp_pointer->nextRunway;
		free(tmp_pointer);
		tmp_pointer = tmp_holder;

	}
	pAirport = NULL;
	return;
}
