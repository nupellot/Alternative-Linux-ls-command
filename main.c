#include "stdio.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


// Требуется разработать программу для визуального просмотра оглавлений каталогов файловых систем OS UNIX, которая позволяет определить состав любого доступного каталога. Имя каталога должно передаваться программе через аргумет командной строки ее вызова. В результате обработки оглавления заданного каталога программа должна обеспечивать стандартный вывод списков имен подкаталогов и файлов, которые содержаться в нем. Имена файлов и подкаталогов обоих списков должны перечисляться в словарном порядке в соответствие с кодами ASCI, образующих их символов. Стандартный вывод оглавления данного каталога должен завершаться информационным сообщением, которое идентифицирует число подкаталогов и файлов в нем. Это информационное сообщение должно отображаться через протокол стандартной диагностики. При разработке программы необходимо использовать библиотечные функции просмотра каталогов opendir, readdir, closedir и getcwd, а также системные вызовы chdir, sbrk, stat, write и exit.
// Реализовать вывод оглавления заданного каталога в указанное число колонок, В коорых имена файлов и подкаталогов выровнены по левой границе.


int main(void) {
	void PrintFilenames(char** filenames, int AmountOfObjects);
	int length(char* string);
	void SortFilenames(char** filenames, int AmountOfObjects);
	
	DIR* directory = opendir("Test catalog");
	if (directory == NULL) {
		printf("Error opening directory\n");
		exit(1);
	}

	// allocating space for array of strings.
	char** filenames = calloc(0, sizeof(char*)); 
	struct dirent* info;  // struct containing information about file or subcatalog.
	int AmountOfObjects = 0;  // amount of files and subcatalogs.
	// Getting all the filesnames.
	while ((info = readdir(directory)) != NULL) {
		AmountOfObjects++;
		filenames = realloc(filenames, AmountOfObjects * sizeof(char*));
		filenames[AmountOfObjects - 1] = calloc(length(info->d_name), sizeof(char));
		filenames[AmountOfObjects - 1] = info->d_name;
		// printf("%s\n", info->d_name);
	}


	SortFilenames(filenames, AmountOfObjects);
	PrintFilenames(filenames, AmountOfObjects);


	// Releasing dynamically allocated memory.
	// closedir(directory);
	// for (int i = 0; i < AmountOfObjects; i++) {
	// 	free(filenames[i]);
	// }
	// free(filenames);
}


void SortFilenames(char** filenames, int AmountOfObjects) {
	int AmountOfSwaps;
	do {
		AmountOfSwaps = 0;
		for (int i = 0; i < AmountOfObjects - 1; i++) {
			int LeftIsBigger = 0;
			for (int j = 0; j < length(filenames[i]) || j < length(filenames[i + 1]); j++) {
				if (filenames[i][j] < filenames[i + 1][j]) {
					break;
				} else
				if (filenames[i][j] > filenames[i + 1][j]) {
					LeftIsBigger = 1;
				} else continue;
			}
			if (LeftIsBigger) {  // Swapping elements.
				char* TemporaryVariable = filenames[i];
				filenames[i] = filenames[i + 1];
				filenames[i + 1] = TemporaryVariable;
				AmountOfSwaps++;
			}
		}
	} while (AmountOfSwaps != 0);
}


void PrintFilenames(char** filenames, int AmountOfObjects) {
	// Getting required amount of collumns.
	printf("\033[32mInput amount of collumns\033[0m\n");
	int AmountOfCollumns = 1;
	scanf("%d", &AmountOfCollumns);
	// Checking number of collumns for correctness.
	if (AmountOfCollumns > AmountOfObjects || AmountOfCollumns < 1) {
		AmountOfCollumns = AmountOfObjects;
	}

	printf("\n");
	// Printing filenames.
	for (int i = 0; i < AmountOfObjects;) {
		for (int j = 0; j < AmountOfCollumns && i < AmountOfObjects; j++, i++) {
			printf("%-10s", filenames[i]);
		}
		printf("\n");
	}

	printf("\033[34mTotal amount of objects: \033[35m%d\033[0m", AmountOfObjects);
}


// Returns length of a string.
int length(char* string) {
	int length = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		length++;
	}
	return length;
}
