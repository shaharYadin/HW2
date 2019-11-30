#pragma once

#ifndef _FLIGHT_H 
#define _FLIGHT_H

#include "ex2.h"

struct flight;
typedef struct flight* pFlight;
pFlight createFlight(int id, FlightType type, char* dest, BOOL isEmergency);
void destroyFlight(pFlight flight);
void printFlight(pFlight flight);

//internal use functions

int isDestValid(char* dest);
FlightType getFlightType(pFlight flight);
int getFlightID(pFlight flight);
BOOL getIsEmergency(pFlight flight);
char* getFlightDest(pFlight flight);
void changeDestFlight(pFlight flight, char* dest);
#endif
