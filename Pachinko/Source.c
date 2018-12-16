#include <stdio.h>
#include <ctype.h>

#define LINESIZE (1024)
#define MINIMUM_CREDITS (100)
#define BEGINNING_CREDITS (1000)
#define NUMBER_OF_SYMBOLS (5)
#define NUMBER_PER_LINE (3)
#define JACKPOT_MULTIPLIER (3)

int credits;
int playedCredits;
char symbols[NUMBER_OF_SYMBOLS];
char spunSymbols[NUMBER_PER_LINE];


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

void Spin()
{
	/* Use current time as seed for random generator */
	srand((unsigned int)time(0));
	spunSymbols[0] = symbols[rand() % NUMBER_OF_SYMBOLS];
	spunSymbols[1] = symbols[rand() % NUMBER_OF_SYMBOLS];
	spunSymbols[2] = symbols[rand() % NUMBER_OF_SYMBOLS];
}

void UpdateWin()
{
	credits -= playedCredits;
	credits += playedCredits * JACKPOT_MULTIPLIER;
}

void UpdateLoss()
{
	credits -= playedCredits;
}

void RenderResults() 
{
	printf("\nSpinning...\n");
	printf("%c %c %c\n", spunSymbols[0], spunSymbols[1], spunSymbols[2]);

	if (spunSymbols[0] == spunSymbols[1] && spunSymbols[0] == spunSymbols[2])
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

void EvaluateResults() 
{
	if (spunSymbols[0] == spunSymbols[1] && spunSymbols[0] == spunSymbols[2]) 
	{
		UpdateWin();
	}
	else
	{
		UpdateLoss();
	}
}

void Play()
{
	Spin();
	EvaluateResults();
}

void RenderInvalidInput() 
{
	fprintf(stderr, "You must enter %d or more credits to play.\n", MINIMUM_CREDITS);
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
		if ((sscanf_s(line, "%d", &playedCredits) == 1) && (playedCredits >= MINIMUM_CREDITS))
		{
			Play();
			break;
		}
		else
		{
			RenderInvalidInput();
		}
	}
}

void RenderPrompt() 
{
	printf("You have %d credits.\n", credits);
	printf("Input number of credits to play: \n");
}

void Release()
{
	getchar();
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
	Release();
	return 0;
}
