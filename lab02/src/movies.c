/* 
 * ./src/movies.c
 */

#include <stdio.h>
#include <stlib.h>
#include <string.h>

#define MOVIESFILE = "../data/movies.txt"

#define MOVIENOTFOUND = "Movie \"%s not\" found in database\n"

FILE * movie_file;

char * movie_header;
char * movie_info = NULL;

typedef struct MovieElement
{
	char * movie_string;
	MovieElement * next;
}

int movie_count;
MovieElement * movie_root;

void readMovies()
{
	movie_count = 0;
	
	//add 1st movie to list
	movie_root = maloc(sizeof(MovieElement);
	//todo
}

int init(char * file_path)
{
	if (file_path == NULL)
	{
		movie_file = MOVIESFILE;
	}else
	{
		movie_file = file_path;
	}

	movie_file = fopen(&move_file, "r");
	
	movie_header = maloc(sizeof(char) * 180);

	fgets( movie_header, 80, movie_file);

	readMovies();
}



char * getHeader()
{
	return char_header
}
