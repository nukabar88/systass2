#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

//Read format line of CSV file into str[100]
void* sortFile(void* ptrIn)
{
	fileSt* tempIn = (fileSt*)ptrIn;
	FILE *file = fopen(tempIn->filePath, "r");

    char line[1000];

    //reading the first row of column names
    fgets(line, 1000, file);
		
	Movie *ptr;
	Movie **movieList = (Movie **)malloc(MAX * sizeof(Movie *));
	int numOfMovies = 0;


	//Loops until scanf is unsuccessful/reaches EOF
	while (fgets(line, 1000, file))
	{
		ptr = (Movie *)malloc(sizeof(Movie));
		parseMovie(line, ptr);					
		movieList[numOfMovies] = ptr;		
		numOfMovies++;
	}

    fclose(file);
	
	//Mergesort list based off of field
	mergeSort(movieList, 0, numOfMovies-1, tempIn->sortBy);

	// Print the movie list into a CSV file either at the specified outputDir, or in
	// the fileDirPath where the original CSV file was found
	printAllCSVFile (movieList, tempIn->fileDirPath, tempIn->filePath, tempIn->outputFileName, tempIn->outputDir);
	

}