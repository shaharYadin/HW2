#pragma once
#ifndef EX2_H_
#define EX2_H_

typedef enum ftype_t {
	DOMESTIC, INTERNATIONAL
} FlightType;
typedef enum boolean_t {
	FALSE, TRUE
} BOOL;
typedef enum result_t {
	FAILURE, SUCCESS
} Result;

#define MAX_ID (100000)
#define MAX_LINE_SIZE (256)

#endif /* EX2_H_ */
