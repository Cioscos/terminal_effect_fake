#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#if defined _WIN64 || defined _WIN32
	#include <windows.h>
#endif

//Import SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MUS_PATH "music.mp3"
#define TEXT_PATH "code.txt"

//Music file
Mix_Music *music = NULL;

//Catch Ctrl-C
void signal_handler(int signal_value);

int main(int argc, char* argv[])
{
	signal(SIGINT, signal_handler);

	//0 means false - 1 true
	int no_args = 0;

	if(argc == 1)
	{
		no_args = 1;
	}
	else if (argc != 2)
	{
		puts("Usage:\nterminal_effect <path of file>\n");
		exit(EXIT_FAILURE);
	}

	//Initialize SDL
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
		exit(-1);

	//Initialize SDL_mixer
	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		exit(-1);

	//Load music
	music = Mix_LoadMUS(MUS_PATH);
	if(!music)
		fprintf(stderr, "Error to open file '%s': %s", MUS_PATH, Mix_GetError());

	if(Mix_PlayMusic(music, -1) == -1)
		fprintf(stderr, "Mix_PlayMusic: %s\n", Mix_GetError());
	
	char *path;

	if(no_args)
		path = TEXT_PATH;
	else
		path = argv[1];

	FILE *fp;

	#if defined _WIN64 || defined _WIN32
	errno_t err;

	if((err = fopen_s(&fp, path, "r")) != 0)
	{
		fprintf(stderr, "Cannot open file '%s': %s\n", path, strerror(err));
	}
	#else
	if ((fp=fopen(path, "r")) == NULL)
	{
		fprintf(stderr, "Cannot open the file '%s\n", path);
	}
	#endif
	else
	{
		char *string;
		char c;
		int number_of_char = 0;
		
		while((c = getc(fp)) != EOF)
		{
			number_of_char++;
		}

		rewind(fp);

		string = calloc(number_of_char, sizeof(char));

		// Check if memory had been correctly allocated
		do
		{
			if(!string)
			{
				free(string);
				string = calloc(number_of_char, sizeof(char));
				puts("Reallocating memory...");
			}
		} while (string == NULL);
		
		while((c = getc(fp)) != EOF)
		{
			strncat(string, &c, 1);
		}

		fclose(fp);

		unsigned int size_string = strlen(string);

		//Change color of writes
		#if defined _WIN64 || defined _WIN32
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		#else
			printf("\033[0;32m");
		#endif
		
		for (size_t i = 0; i < size_string; i++)
		{
			if(string[i] == '\\')
			{
				//Menage the escapes character
				if(string[i + 1] == 'n')
				{
					putc('\n', stdout);
					i += 2;
				}
			}
			else
			{
				putc(string[i], stdout);
				fflush(stdout);
				usleep(10000);
			}
			
		}

		#if defined _WIN64 || defined _WIN32
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		#else
			printf("\033[0m");
		#endif
	}

	SDL_Quit();
	return 0;
}

void signal_handler(int signal_value)
{
	#if defined _WIN64 || defined _WIN32
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	#else
		printf("\033[0m");
	#endif

	//Clean up resources
	Mix_FreeMusic(music);
	//quit SDL
	Mix_CloseAudio();
	SDL_Quit();

	printf("\n\nProcess finished with: %d", signal_value);
	exit(EXIT_SUCCESS);
}
