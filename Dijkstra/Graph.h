#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
	char name;
	enum StatusPoint status;
	enum Visited visited;
} Point;

typedef struct Line
{
	struct Point* curr_point;
	struct Point* next_point;
	double distance;
	enum Visited visited;
} Line;

typedef enum StatusPoint
{
	None,
	Start,
	End,
} StatusPoint;

typedef enum Visited
{
	Open,
	Close,
} Visited;