#pragma once
#include "Graph.h"

typedef struct Path
{
	char* name;
	double distance;
} Path;

double CalculateDistance(Line graph[], int size_graph, char* name, int size);
void AddElement(Line graph[], int size_graph, Path* paths, int size_paths, char* name_path);
void AddSymbol(char* str, int size, char symbol);
void DeleteLast(char* str, int size);
void SearchPaths(Path* paths, Point points[], Line graph[], int size_points, int size_graph, int size_paths);
void AllPrintPaths(Path* paths, int size);
void MinPath(Path* paths, int size);
