/* 
 * ./src/movies.c
 */

#include <stdio.h>
#include <stlib.h>
#include <string.h>

#define MOVIESFILE = "../data/movies.txt"
#define MAXMOVIES = 15

#define MOVIENOTFOUND = "Movie \"%s not\" found in database\n"

FILE * movie_file;

char ** movie_list;
int movie_count;

void readMovies()
{
	movie_count = 0;
	movie_list = (char**) malloc(MAXMOVIES);

	for(int i, i < MAXMOVIES)
	{
	movie_list[i] = maloc(sizeof(char) * 80);
	
	}
}

int init(char * file_path)
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
	
	movie_header = maloc(sizeof(char) * 180);

	fgets( movie_header, 80, movie_file);

	readMovies();
}



char * getHeader()
{
	return char_header
}
