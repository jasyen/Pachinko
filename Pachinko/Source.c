#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define BEGINNING_CREDITS (1000)
#define JACKPOT_MULTIPLIER (3)
#define LINESIZE (1024)
#define MINIMUM_CREDITS (100)
#define NUMBER_OF_SYMBOLS (5)
#define NUMBER_PER_LINE (3)

size_t credits;
int playedCredits;
char spunSymbols[NUMBER_PER_LINE];
char symbols[NUMBER_OF_SYMBOLS];

/* 

enum eSymbol
{
	X,
	Y,
	A,
	B,
	C
};
enum eSymbol symbolsSpun[NUMBER_PER_LINE];
*/

bool EvaluateResults()
{
	if (spunSymbols[0] == spunSymbols[1] && spunSymbols[0] == spunSymbols[2])
	{
		credits -= playedCredits;
		credits += playedCredits * JACKPOT_MULTIPLIER;
		return true;
	}
	else
	{
		credits -= playedCredits;
		return false;
	}
}

void Init() 
{
	symbols[0] = '^';
	symbols[1] = '%';
	symbols[2] = 'X';
	symbols[3] = '7';
	symbols[4] = '*';
	credits = BEGINNING_CREDITS;
	playedCredits = 0;
}

void RenderResults() 
{
	printf("\nSpinning...\n");
	printf("%c %c %c\n", spunSymbols[0], spunSymbols[1], spunSymbols[2]);

	if (EvaluateResults())
	{
		printf("Jackpot! You won %d credits!\n\n", (playedCredits * JACKPOT_MULTIPLIER));
	}
	else
	{
		printf("You busted. You lost %d credits.\n\n", playedCredits);
	}
	if (credits < MINIMUM_CREDITS)
	{
		printf("You don't have enough credits to continue playing. Goodbye.\n");
	}
}

void RenderPrompt() 
{
	printf("You have %d credits.\n", credits);
	printf("Input number of credits to play: \n");
}

void Spin()
{
	/* Use current time as seed for random generator */
	srand((unsigned int)time(0));
	spunSymbols[0] = symbols[rand() % NUMBER_OF_SYMBOLS];
	spunSymbols[1] = symbols[rand() % NUMBER_OF_SYMBOLS];
	spunSymbols[2] = symbols[rand() % NUMBER_OF_SYMBOLS];
}

void Update()
{
	char line[LINESIZE];
	while (1)
	{
		if (!fgets(line, LINESIZE, stdin)) /* if we fail to read a line */
		{
			clearerr(stdin);
		}
		if ((sscanf_s(line, "%d", &playedCredits) == 1) && (playedCredits >= MINIMUM_CREDITS) && (playedCredits <= credits))
		{
			Spin();
			break;
		}
		else
		{
			fprintf(stderr, "You must enter %d or more credits to play.\n", MINIMUM_CREDITS);
		}
	}
}

int main(void)
{
	Init();
	while (credits >= MINIMUM_CREDITS)
	{
		RenderPrompt();
		Update();
		RenderResults();
	}
	getchar();
	return 0;
}
