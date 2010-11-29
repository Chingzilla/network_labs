/* 
 * ./src/movies.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movies.h"

#define MOVIESFILE "../data/movies.txt"
#define MAXMOVIES 100
#define MOVIETITLELEN 128

#define MOVIENOTFOUND "Movie \"%s not\" found in database\n"

FILE * movie_file;

char * movie_list[MAXMOVIES];
char  movie_header[2 * MOVIETITLELEN];

int movie_count;

void readMovies(){
	movie_count = 0;

    printf("Started reading file\n%s", movie_header);
	for(int i; i < MAXMOVIES; i++){
		//check if at EOF
		if(feof(movie_file)){
			break;
		}
		movie_list[i] = (char *) malloc(sizeof(char) * MOVIETITLELEN);
		
		//get movie, break loop if error
		if (fgets(movie_list[i], MOVIETITLELEN, movie_file) == NULL){
			break;
		}
        printf("Read from file: %s\n", movie_list[i]);
		movie_count++;
	}

	fclose(movie_file);
	return;
}

int movies_init(char * file_path)
{
	if (file_path == NULL)
	{
		file_path = MOVIESFILE;
	}

	movie_file = fopen(file_path, "r");
	
	if (movie_file == NULL){
		perror("Opening file");
		exit(1);
	}

	//Read header for movies
    //1st line
    fgets( movie_header, MOVIETITLELEN, movie_file);
    //2nd line
    fgets( &movie_header[strlen(movie_header)], MOVIETITLELEN, movie_file);
    
    printf("Reading Movie File\n");
	readMovies();

	return 0;
}

char * getHeader()
{
	return movie_header;
}

char * searchMovies( char * movie_query, char * answer){
	for(int i; i < movie_count; i++){
		if (strncmp(movie_query, movie_list[i], strlen(movie_query))){
			sprintf(answer, "%s%s", movie_header, movie_list[i]);
			return answer;
		}
	}
	sprintf(answer, MOVIENOTFOUND, movie_query);
	return NULL;
}
