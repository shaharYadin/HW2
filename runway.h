#pragma once
#ifndef _RUNWAY_H
#define _RUNWAY_H
#include "ex2.h"
#include "flight.h"

struct flightNode;
struct runway;
typedef struct flightNode* pNode;
typedef struct runway* pRunway;
pRunway createRunway(int runwayID, FlightType type);
void destroyRunway(pRunway runway_pointer);
BOOL isFlightExists(pRunway runway_pointer, int flight_id);
int getFlightNum(pRunway runway_pointer);
int getEmergencyNum(pRunway runway_pointer);
Result addFlight(pRunway runway_pointer, pFlight flight_pointer);
Result removeFlight(pRunway runway_pointer, int flightID);
Result departFromRunway(pRunway runway_pointer);
void printRunway(pRunway runway_pointer);

//for internal use
int getRunwayID(pRunway runway_pointer);
FlightType getRunwayType(pRunway runway_pointer);
void changeDestRunway(pRunway runway_pointer, char* old_dest, char* new_dest);
pNode unlinkFlight(pNode previousNode);
void runwayDelay(pRunway runway_pointer, char* dest);
pRunway createTempRunway(int runwayID, FlightType type);
#endif
