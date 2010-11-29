/* 
 * ./src/movies.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movies.h"

#define MOVIESFILE = "../data/movies.txt"
#define MAXMOVIES = 100
#define MOIVETITLELEN = 80

#define MOVIENOTFOUND = "Movie \"%s not\" found in database\n"

FILE * movie_file;

char * movie_list[MAXMOVIES];
extern int movie_count;

void readMovies(){
	movie_count = 0;

	for(int i; i < MAXMOVIES; i++){
		//check if at EOF
		if(feof(movie_file)){
			break;
		}
		movie_list[i] = maloc(sizeof(char) * MOIVETITLELEN);
		
		//get movie, break loop if error
		if (fgets(movie_list[i], MOIVETITLELEN, movie_file) == NULL){
			break;
		}
		movie_count++;
	}

	fclose(movie_file);
	return;
}

int movies_init(char * file_path)
{
	if (file_path == NULL)
	{
		movie_file = MOVIESFILE;
	}
	else
	{
		movie_file = file_path;
	}

	movie_file = fopen(&movie_file, "r");
	
	if (movie_file == NULL){
		perror("Error opening file");
		exit(1);
	}

	movie_header = maloc(sizeof(char) * 180);

	fgets( movie_header, 80, movie_file);

	readMovies();

	return 0;
}



char * getHeader()
{
	return char_header
}

char * searchMovies( char * movie_query, char * answer){
	for(int i; i < movie_count; i++){
		if (strncmp(movie_query, movie_list[i], strlen(movie_query))){
			fprintf(answer, movie_list[i]i);
			return answer;
		}
	}
	fprintf(answer, MOVIENOTFOUND, movie_query);
	return NULL;
}
