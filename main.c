#include "stdio.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


// Требуется разработать программу для визуального просмотра оглавлений каталогов файловых систем OS UNIX, которая позволяет определить состав любого доступного каталога. Имя каталога должно передаваться программе через аргумет командной строки ее вызова. В результате обработки оглавления заданного каталога программа должна обеспечивать стандартный вывод списков имен подкаталогов и файлов, которые содержаться в нем. Имена файлов и подкаталогов обоих списков должны перечисляться в словарном порядке в соответствие с кодами ASCI, образующих их символов. Стандартный вывод оглавления данного каталога должен завершаться информационным сообщением, которое идентифицирует число подкаталогов и файлов в нем. Это информационное сообщение должно отображаться через протокол стандартной диагностики. При разработке программы необходимо использовать библиотечные функции просмотра каталогов opendir, readdir, closedir и getcwd, а также системные вызовы chdir, sbrk, stat, write и exit.
// Реализовать вывод оглавления заданного каталога в указанное число колонок, В коорых имена файлов и подкаталогов выровнены по левой границе.


int main(void) {
	int length(char* string);
	
	DIR* directory = opendir("hui");
	if (directory == NULL) {
		printf("Error opening directory\n");
		exit(1);
	}

	// allocating space for array of strings.
	char** filenames = calloc(0, sizeof(char*));
	struct dirent* info;
	int AmountOfObjects = 0;
	while ((info = readdir(directory)) != NULL) {
		AmountOfObjects++;
		filenames = realloc(filenames, AmountOfObjects * sizeof(char*));
		filenames[AmountOfObjects - 1] = calloc(length(info->d_name), sizeof(char));
		filenames[AmountOfObjects - 1] = info->d_name;
		printf("%s\n", info->d_name);
	}

	
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
	// printf("%d", (int)'a');
	
	for (int i = 0; i < AmountOfObjects; i++) {
		printf("%s\n", filenames[i]);
	}

	closedir(directory);
}

int length(char* string) {
	int length = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		length++;
	}
	return length;
}
