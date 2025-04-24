#include "Main.h"
#include "math.h"

double CalculateDistance(Line graph[], int size_graph, char* name, int size)
{
	double distance = 0;

	char* str = (char*)malloc(3 * sizeof(char));
	memset(str, '\0', 3 * sizeof(char));

	for (int i = 0; i < size; i++)
	{
		if (name[i + 1] == '\0')
		{
			free(str);
			return distance;
		}

		str[0] = name[i];
		str[1] = name[i + 1];
		for (int i = 0; i < size_graph; i++)
			if (graph[i].curr_point->name == str[0] &&
				graph[i].next_point->name == str[1])
			{
				distance += graph[i].distance;
				break;
			}

		str[0] = '\0';
		str[1] = '\0';
	}
}

void AddElement(Line graph[], int size_graph, Path* paths, int size_paths, char* name_path)
{
	for (int i = 0; i < size_paths; i++)
		if (paths[i].name == NULL)
		{
			paths[i].name = (char*)malloc((size_paths + 1) * sizeof(char));
			strcpy(paths[i].name, name_path);
			paths[i].distance = CalculateDistance(graph, size_graph, name_path, sqrt(size_paths));
			break;
		}
}

void AddSymbol(char *str, int size, char symbol)
{
	for (int i = 0; i < size; i++)
		if (str[i] == '\0')
		{
			str[i] = symbol;
			str[i + 1] = '\0';
			break;
		}
}

void DeleteLast(char *str, int size)
{
	for (int i = size - 1; i >= 0; i--)
		if (str[i] != '\0')
		{
			str[i] = '\0';
			break;
		}
}

void SearchPaths(Path* paths, Point points[], Line graph[], int size_points, int size_graph, int size_paths)
{
	int iterations = 0;

	char *path = (char*)malloc((size_points + 1) * sizeof(char));
	memset(path, '\0', (size_points + 1) * sizeof(char));

	char curr_point;
	char end_point;

	// Находим стартовую и конечную точку
	for (int i = 0; i < size_points; i++)
	{
		if (points[i].status == Start)
			curr_point = points[i].name;
		else if (points[i].status == End)
			end_point = points[i].name;
	}
	AddSymbol(path, size_points, curr_point);

	//Составляем возможные пути
	int check = 0;
	while (path[0] != '\0')
	{
		// Поиск пути
		check = 0;
		for (int i = 0; i < size_graph; i++)
		{
			if (graph[i].curr_point->name == curr_point &&
				graph[i].next_point->visited == Open &&
				graph[i].visited == Open)
			{
				graph[i].curr_point->visited = Close;
				graph[i].visited = Close;
				curr_point = graph[i].next_point->name;
				AddSymbol(path, size_points, curr_point);

				check = 1;

				break;
			}
		}

		// Возврат к предыдущей точке
		if (check == 0 || curr_point == end_point)
		{
			// Если нашли конечную точку, то сохраняем путь и рассчитываем дистанцию
			if (curr_point == end_point)
				AddElement(graph, size_graph, paths, size_paths, path);

			DeleteLast(path, size_points);

			for (int i = 0; i < size_graph; i++)
				if (graph[i].curr_point->name == curr_point)
				{
					graph[i].curr_point->visited = Open;
					graph[i].visited = Open;
				}

			curr_point = path[0];
			for (int i = size_points - 2; i >= 0; i--)
				if (path[i] != '\0')
				{
					curr_point = path[i];
					break;
				}
		}

		iterations++;
	}
	printf("\n\nКоличество итераций: %d\n", iterations);

	free(path);
}

void AllPrintPaths(Path* paths, int size)
{
	for (int i = 0; i < size; i++)
		if (paths[i].name != NULL)
			printf("\n\nПуть: %s\nРасстояние: %g", paths[i].name, paths[i].distance);
	printf("\n\n");
}

void MinPath(Path *paths, int size)
{
	char* name = paths[0].name; 
	double distance = paths[0].distance;

	for (int i = 0; i < size; i++)
		if (paths[i].distance != 0 &&
			distance > paths[i].distance)
		{
			name = paths[i].name;
			distance = paths[i].distance;
		}

	printf("\nКороткие пути:\n");
	for (int i = 0; i < size; i++)
		if (paths[i].distance == distance)
			printf("\n\tПуть: %s\n\tРасстояние: %g\n\n", paths[i].name, paths[i].distance);
}

int main()
{
	system("chcp 1251");

	Point A = { 'A', Start, Open };
	Point B = { 'B', None, Open };
	Point C = { 'C', None, Open };
	Point D = { 'D', None, Open };
	Point E = { 'E', End, Open };

	Point points[] = {
		A, B, C, D, E
	};
	int size_points = sizeof(points) / sizeof(points[0]);

	Line graph[] =
	{
		{&A, &B, 2.5, Open},
		{&A, &D, 1, Open},

		{&B, &A, 7, Open},
		{&B, &C, 1.5, Open},
		{&B, &D, 3, Open},

		{&D, &A, 1, Open},
		{&D, &B, 2, Open},
		{&D, &C, 4, Open},
		{&D, &E, 6, Open},

		{&C, &B, 1.5, Open},
		{&C, &D, 4, Open},
		{&C, &E, 2.5, Open},

		{&E, &C, 2.5, Open},
		{&E, &D, 6, Open},
	};
	int size_graph = sizeof(graph) / sizeof(graph[0]);

	int size_paths = size_points * size_points;
	Path *paths = (Path*)malloc(size_paths * sizeof(Path));
	memset(paths, '\0', size_paths * sizeof(Path));


	// Ищем все возможные пути
	SearchPaths(paths, points, graph, size_points, size_graph, size_paths);

	// Выводим все найденные пути
	AllPrintPaths(paths, size_paths);

	// Поиск самого короткого пути
	MinPath(paths, size_paths);

	free(paths);
	return 0;
}