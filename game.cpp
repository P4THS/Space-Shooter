/*
	GROUP MEMBER DETAILS

	Qasim Naveed		21L-5231	BCS-1J	l215231@lhr.nu.edu.pk
	Khawaja Afnan Asif	21L-1864	BCS-1J	l211864@lhr.nu.edu.pk
	Abubakar Tahir		21L-1837	BCS-1J	l211837@lhr.nu.edu.pk
	Abdullah Saeed		21L-1819	BCS-1J	l211819@lhr.nu.edu.pk
*/


#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

char space[20] = "S P A C E";
char shooter[20] = "S H O O T E R";
char level[20] = "LEVEL ";
char score[20] = "SCORE ";
char lives[20] = "LIVES = ";
int x = 25;		// ship's y coordinate
int y = 25;		// ship's x coordinate
int arrx[25];	// bullet y coordinate array
int arry[25];	// bullet x coordiante array
int scount = 0;	// count of bullets currently ingame which are active
int timer = 0;	// timer variable which control speed of aliens
int x1 = 1;	// aliens starting y coordinate
int x1e = 1;	// aliens ending y coordinate
int al1y[5][12];	// aliens2d array x coordinate
bool al1[5][12];	// whether alien is alive or dead
int al1x[5][12];	// aliens2d array y coordinate
int score1 = 0;		// score storing variable
int lives1 = 3;		// lives variable
int levels = 1;		// level variable
int chk1 = 0, chk2 = 0; // chk1 intializes aliens only at the start of level
int outl = 0;	// control how many rows of aliens will be printed
int inl = 0;	// controls number of aliens in a loop
int check = 0;	// stores whether a life is lost in that level
char c;	// store user's choice
int count3 = 0;		// stores the lives lost in a level
char name[50];	// user name is stored here
int spcaliensx = 2;	// special alien y coordinate store
int spcaliensy = 38;	// spcalien x coordinate store 
bool spcaliens = true;	// whether it is dead or alive
int checkl = 1;	// tells the alien to move left or right
int timer2 = 0;	// special alien timer which makes it alive again
int asteroidx[6];	// asteroid's y coordinate
int asteroidy[6];	// asteroids x coordinate
bool asteroid[6];	// whether has been hit or not
int ca[6] = { 0,0,0,0,0,0 };	// whether asteroid is active or not
int achk = 0;	// does not let more than one asteroid in one column during a single loop
int maxscore = 0;	// stores maximum score of player
int tries = 0;	// whether user has played more than 1 time
int tempscore = 0;	// stores the score at the starting of a level
int aliencount = 0;	// stores how many alien are dead
bool barier[24];	// whether barier is active or not
int barierx = 21;	// stores y coordinate of barier
int bariery[24];	// stores x coordinate of barier
int bchk = 0;	// activates barrier at the start of game
int bl = 1;	// whether barier has to move left or right
bool tempbar[24];	// reinvigorate the barier if esc key is pressed
int tempalien;	// restores alien count if esc key is pressed

void ShowConsoleCursor(bool showFlag)	// removes white cursor from the console
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void bariers()	// activates barrier and control its movement
{
	for (int j = 0; j < 24; j++)
	{
		if (bchk == 0)
		{

			if ((j >= 4 && j <= 7) || (j >= 10 && j <= 13) || (j >= 16 && j <= 19))
			{
				bariery[j] = 15 + j;
				barier[j] = true;
			}
			else
			{
				barier[j] = false;
			}
			tempbar[j] = false;
		}

		if (bl == 1)
		{
			bariery[j]--;
		}
		else
		{
			bariery[j]++;
		}
	}

	bchk = 1;

	if (bariery[4] == 15)
	{
		bl = 0;
	}
	if (bariery[19] == 37)
	{
		bl = 1;
	}
}

void lvlbarier()	// refresher tempbarier
{
	for (int j = 0; j < 24; j++)
	{
		tempbar[j] = false;
	}
}

void escbarrier()	// restores barrier condition which was at the start of level
{
	for (int j = 0; j < 24; j++)
	{
		if (tempbar[j] == true)
		{
			barier[j] = true;
		}
	}
}

void firstscreen()	// shows starting screen until user presses any key
{
	while (!_kbhit())
	{
		cout << "\n\n     \t\t\t\t\t";
		cout << "I N S T R U C T I O N S";
		cout << "\n\n\n     \t\t\t\tUse 'A' to move left and 'D' to move right";
		cout << "\n\n     \t\t\t\tPress 'space' to fire bullets";
		cout << "\n\n     \t\t\t\tAvoid hitting aliens and dont let aliens reach bottom level";
		cout << "\n\n     \t\t\t\tAvoid hitting debris, their score depends on color";
		cout << "\n\n     \t\t\t\t'Esc' key during game restarts level";
		cout << "\n\n\n\n   \t\t\t\t\tPress any key to start level 1";
		cout << "\n\n   \t\t\t\t\tPress 'Esc' key to exit game";
		cout << "\n\n\n\t\t\t\t\t\t\t\tMade by: Qasim naveed\t\t21L-5231\n\t\t\t\t\t\t\t\t\t Khawaja Afnan Asif     21L-1864";
		cout << "\n\t\t\t\t\t\t\t\t\t Abubakar Tahir\t\t21L-1837\n\t\t\t\t\t\t\t\t\t Abdullah Saeed\t\t21L-1819";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
	}
}

void shoot()	// initializes the bullets
{
	if (scount != 25)
	{
		arrx[scount] = x - 1;
		arry[scount] = y;
		scount++;
	}
}

void spcalien()	// moves the special alien and restores it value
{
	if (checkl == 1)
	{
		spcaliensy--;
	}
	else
	{
		spcaliensy++;
	}
	if (spcaliensy == 12)
	{
		checkl = 0;
	}
	if (spcaliensy == 40)
	{
		checkl = 1;
	}
	if (spcaliens == false)
	{
		timer2++;
		if (timer2 % 100 == 0)
		{
			spcaliens = true;
		}
	}
}

void asteroids()	// initialzes asteroids and moves them
{
	achk = 0;
	for (int i = 0; i < 6; i++)
	{
		if (timer % (i+1) == 0)
		{
			if (ca[i] == 0 && spcaliens == true && spcaliensy >= 15 && spcaliensy <= 37 && achk == 0)
			{
				achk = 1;
				asteroidx[i] = spcaliensx;
				asteroidy[i] = spcaliensy;
				ca[i] = 1;
				asteroid[i] = true;
			}
			asteroidx[i]++;
		}
	}
}

void glevels()
{	
	if (chk1 == 0)
	{
		for (int i = 0; i < outl; i++)
		{	
			for (int j = 0; j < inl; j++)
			{
				al1y[i][j] = 15 + j * 2;
				al1[i][j] = true;
			}
		}
		chk1 = 1;
	}

	timer++;

	if (timer % (25-(levels*3)) == 0)
	{
		x1++;
		x1e++;
	}
}

void reducingbullet(int t, int& idx)
{
	arrx[t] = arrx[t + 1];
	arrx[t + 1] = 0;
	arry[t] = arry[t + 1];
	arry[t + 1] = 0;
	idx = t;
}

void valuereset()
{
	x = 25; y = 25; scount = 0; timer = 0; tempalien = 0;
	x1 = 3; x1e = 3; score1 = 0; lives1 = 3; levels = 1; chk1 = 0, chk2 = 0; outl = 1; inl = 12;
	check = 0; count3 = 0; spcaliensx = 2; spcaliensy = 38; spcaliens = true; checkl = 1; timer2 = 0;
	ca[0] = 0; ca[1] = 0; ca[2] = 0; ca[3] = 0; ca[4] = 0; ca[5] = 0;
	asteroid[0] = false; asteroid[2] = false; asteroid[3] = false; asteroid[4] = false; asteroid[1] = false; asteroid[5] = false;
	achk = 0; tempscore = 0; aliencount = 0; bchk = 0; bl = 1;
}

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void board()
{
	char boardc[27][76];

	cout << endl;

	for (int i = 0; i < 27; i++)
	{
		int idx = -1;

		for (int j = 0; j < 76; j++)
		{
			if (i == 0 || i == 26 || (i == 10 && j >= 53) || (i == 14 && j >= 53))
			{
				boardc[i][j] = (char)219;
			}

			else if (j == 0 || j == 1 || j == 53 || j == 52 || j == 74 || j == 75)
			{
				boardc[i][j] = (char)219;
			}

			else if (i == 4 && j >= 59 && j <= 67)
			{
				boardc[i][j] = space[j - 59];
			}

			else if (i == 6 && j >= 57 && j <= 69)
			{
				boardc[i][j] = shooter[j - 57];
			}

			else if (i == 12 && j >= 60 && j <= 66)
			{	
				if (j == 66)
				{
					boardc[i][j] = (char)levels + 48;
				}
				else
				boardc[i][j] = level[j - 60];
			}

			else if (i == 19 && j >= 60 && j <= 68)
			{	
				if (j == 66)
				{
					boardc[i][j] = (char)(score1 / 100 +48);
				}

				else if (j == 67)
				{
					boardc[i][j] = (char)(score1 / 10 +48);

					if (score1 >= 100)
					{
						boardc[i][j] = (char)(score1 / 10 + 48 - (score1/100 * 10));
					}
				}

				else if (j == 68)
				{
					boardc[i][j] = (char)(score1 % 10 +48);
				}

				else
				{
					boardc[i][j] = score[j - 60];
				}
			}

			else if (i == 21 && j >= 59 && j <= 67)
			{	
				if (j == 67)
				{
					boardc[i][j]=(char)lives1 + 48;
				}
				else
				boardc[i][j] = lives[j - 59];
			}

			else if (x == i && y == j)
			{
				boardc[i][j] = (char)202;
			}

			else
			{
				boardc[i][j] = ' ';

				for (int g = 0; g < 24; g++)
				{
					if (barier[g] == true && i == barierx && bariery[g] == j)
					{
						boardc[i][j] = (char)219;
					}
				}

				for (int k = 0; k < scount; k++)
				{
					if (arrx[k] == i && arry[k] == j)
					{
						boardc[i][j] = '|';
						arrx[k]--;
					}

					if (arrx[k] == 0)
					{
						reducingbullet(k, idx);
					}
				}

				for (int k = 0; k < 6; k++)
				{
					if (asteroidx[k] == i && asteroidy[k] == j && asteroid[k] != false)
					{
						boardc[i][j] = (char)153;
					}

					if (asteroidx[k] == 26)
					{
						asteroid[k] = false;
						ca[k] = 0;
					}
				}

				if (spcaliensx == i && spcaliensy == j && spcaliens == true)
				{
					boardc[i][j] = (char)206;
				}

				for (int k = 0; k < outl; k++)
				{
					check = 0;
					for (int g = 0; g < inl; g++)
					{
						for (int l = 0; l < scount; l++)
						{
							if (arrx[l] == al1x[k][g] && arry[l] == al1y[k][g] && al1[k][g] != false)
							{
								al1[k][g] = false;
								reducingbullet(l, idx);
								aliencount++;
								score1++;
								cout << "\a";
							}

							if (arrx[l] == spcaliensx && arry[l] == spcaliensy && spcaliens != false)
							{
								spcaliens = false;
								reducingbullet(l, idx);
								score1+=20;
								cout << "\a";
							}

							for (int z = 0; z < 6; z++)
							{
								if (arrx[l] == asteroidx[z] && arry[l] == asteroidy[z] && asteroid[z] != false)
								{
									asteroid[z] = false;
									ca[z] = 0;
									reducingbullet(l, idx);
									score1+=(6-z)*2;
									cout << "\a";
								}
							}
						}
						
						if ((al1y[k][g] == y && al1x[k][g] == x && al1[k][g] == true) || (al1x[k][g] == 27 && al1[k][g] == true) && (check == 0))
						{
							lives1--;
							count3++;
							x1 = 3;
							x1e = 3 + levels-1;
							check = 1;
							cout << "\a";
						}

						for (int n = 0; n < 24; n++)
						{
							if (al1x[k][g] == barierx && al1[k][g] == true && al1y[k][g] == bariery[n] && barier[n] == true)
							{
								barier[n] = false;
							}
						}

						for (int z = 0; z < 6; z++)
						{
							if ( (asteroidy[z] == y && asteroidx[z] == x && asteroid[z] == true) && check == 0)
							{
								asteroid[z] = false;
								ca[z] = 0;
								lives1--;
								count3++;
								check = 1;
								cout << "\a";
								break;
							}

							for (int n = 0; n < 24; n++)
							{
								if (asteroidx[z] == barierx && asteroid[z] == true && asteroidy[z] == bariery[n] && barier[n] == true)
								{
									barier[n] = false;
									tempbar[n] = true;
									asteroid[z] = false;
								}
							}
						}
						
						for(int a = 0; a < outl; a++)
						{
							for (int b = 0; b < inl; b++)
							{
								al1x[a][b] = x1 + a;
							}
						}

						if (i == al1x[k][g])
						{
							if (j == al1y[k][g] && al1[k][g] == true)
							{
								boardc[i][j] = (char)254;
							}
						}
					}
				}
			}
		}

		if (idx != -1)
		{
			scount--;
		}
	}

	if (lives1 != 0)
	{
		for (int i = 0; i < 27; i++)
		{
			cout << "\t\t      ";

			for (int j = 0; j < 76; j++)
			{
				for (int z = 0; z < 6; z++)
				{
					if (asteroidx[z] == i && asteroidy[z] == j && asteroid[z] == true)
					{
						Color(z + 1);
						cout << boardc[i][j];
						Color(7);
						j++;
					}
				}
				for (int z = 0; z < 24; z++)
				{
					if (bariery[z] == j && barierx == i && barier[z] == true)
					{
						Color(9);
						cout << boardc[i][j];
						Color(7);
						j++;
					}
				}
				if (i == x && j == y)
				{
					Color(13);
					cout << boardc[i][j];
					Color(7);
				}
				else if (spcaliensx == i && spcaliensy == j && spcaliens == true)
				{
					Color(12);
					cout << boardc[i][j];
					Color(7);
				}
				else
				{
					cout << boardc[i][j];
				}
			}

			cout << endl;
		}
	}
}

int main()
{
	char temp;

	ShowConsoleCursor(false);

	firstscreen();

	temp = _getch();

	if (temp != (char)27)
	{
		system("CLS");
		cout << "\n\n\n\n\n\n\n\t\t\t\tEnter your name: ";
		cin.getline(name, 50);

		while (1)
		{
			system("cls");

			valuereset();

			while (1)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

				c = 'z';

				if (_kbhit())
				{
					c = _getch();

					if (c == 'a' || c == 'A')
					{
						if (y != 3)
						{
							y--;
						}
					}

					if (c == 'd' || c == 'D')
					{
						if (y != 50)
						{
							y++;
						}
					}

					if (c == ' ')
					{
						shoot();
					}
				}

				if (aliencount >= 180)
				{
					while (!_kbhit())
					{
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\t\t\t    Congratulations you have won the game!";
						cout << "\n\n\t\t\t    Press 'Esc' to quit or press any other key to restart the game";
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
					}

					c = _getch();
					break;
				}

				bariers();
				spcalien();
				asteroids();

				chk2 = levels;
				if (aliencount >= 120)
				{
					levels = 5;
				}
				else if (aliencount >= 72)
				{
					levels = 4;
				}
				else if (aliencount >= 36)
				{
					levels = 3;
				}
				else if (aliencount >= 12)
				{
					levels = 2;
				}
				
				chk2 = levels - chk2;

				if (chk2)
				{
					scount = 0;
					cout << "\a";
					x1 = 3;
					x1e = 3+(levels-1);
					outl = levels;
					inl = 12;
					tempscore = score1;
					count3 = 0;
					chk1 = 0;
					tempalien = aliencount;
					lvlbarier();
				}
				glevels();

				if (c == (char)27)
				{
					scount = 0;
					x1 = 3;
					x1e = 3 + (levels - 1);
					score1 = tempscore;
					lives1 += count3;
					aliencount = tempalien;
					count3 = 0;
					chk1 = 0;
					spcaliens = true;
					escbarrier();
					asteroid[0] = false; asteroid[2] = false; asteroid[3] = false; asteroid[4] = false; asteroid[1] = false; asteroid[5] = false;
				}

				board();

				if (lives1 == 0)
				{
					system("CLS");

					while (!_kbhit())
					{
						cout << "\n\n\n\n\n\n\n\n\n\t\t\tOh you have lost the game :(";
						cout << "\n\n\t\t\tPress 'Esc' to quit or press any other key to restart the game";
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
						tries++;
					}

					c = _getch();
					break;
				}

			}

			if (tries == 1)
			{
				maxscore = score1;
			}

			else
			{
				if (maxscore < score1)
				{
					maxscore = score1;
				}
			}

			if (c == (char)27)
			{
				break;
			}
		}
		
		ofstream scorefile("score.txt", ios :: app);
		scorefile << name;
		scorefile << "\t\t\t" << maxscore;
		scorefile << "\n";
		scorefile.close();
	}
	
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t you have exited the game\n";
	cout << "\n\n\t\t\t\t\t Your Score is: " << score1 << endl;
	cout << "\n\n\t\t\t\t\t Your maximum Score is: " << maxscore << endl;
	system("pause");
	return 0;
}