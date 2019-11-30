#pragma once
#ifndef _AIRPORT_H
#define _AIRPORT_H
#include "ex2.h"
#include "runway.h"

struct runwayNode;
typedef struct runwayNode* pRunwayNode;
//pRunwayNode pAirport;
Result addRunway(int runwayID, FlightType runwayType);
Result removeRunway(int runwayID);
Result addFlightToAirport(int flightID, FlightType type, char* dest, BOOL isEmergency);
Result depart();
Result changeDest(char* last_dest, char* new_dest);
Result delay(char* dest);
void printAirport();
void destroyAirport();
#endif