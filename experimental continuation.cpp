
//Jonathan Morcos


#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <string>
#include <istream>
using namespace std;


const int NUM_ROWS = 3;
const int NUM_COLS = 3;



void userVsCompTTT();

void hangMan();

void oneHundred();

int sum();


void setUpGame(char[][NUM_COLS], char[][NUM_COLS],
 			   int[][NUM_COLS], int[][NUM_COLS],
			   int[][NUM_COLS], bool[][NUM_COLS], bool[][NUM_COLS], int[][NUM_COLS], bool&);

void displayBoard(char[][NUM_COLS], char[][NUM_COLS], int, int );

void displayScore(int, int, int);
void displayRules();
bool coinFlip();
void compRandFirstMove(char[][NUM_COLS], char[][NUM_COLS]);

void updateLogicA(char[][NUM_COLS], int[][NUM_COLS], int[][NUM_COLS],
			      int[][NUM_COLS], bool[][NUM_COLS], bool[][NUM_COLS], int[][NUM_COLS], char);
			      
char check4gameWinner(int[][NUM_COLS], bool[][NUM_COLS], bool&);

void usersTurn(char[][NUM_COLS], char[][NUM_COLS], bool[][NUM_COLS], bool[][NUM_COLS]);

void computersTurn(char[][NUM_COLS], char[][NUM_COLS], bool[][NUM_COLS], bool[][NUM_COLS]);

void displayWinnerUpdateScore(int&, char, int&, int&);	

bool check4tournWinner(int, int);

bool rematchYN();		      
			      
			      
			      

int main()
{
	srand(time(NULL));
	
	char choice;
	bool stay = 1;
	
	
	do
	{
		
		system("cls");
		
		cout << "\n\t\t\t\t Welcome To Million City Game Center! \n";
		cout << "\t\t\t---------------------------------------------\n";
		cout << "\n\t\t Which game would you like to play?  (Type the number and press enter to choose)";
		cout << "\n\n\t\t\t 1. Tic Tac To";
		cout << "\n\n\t\t\t 2. Hangman"; 
		cout << "\n\n\t\t\t 3. The 100 game";
		cout << "\n\n\n\t\t\t Or Enter 0 to close the program \n";
	
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
		switch(choice)
		{
			case '1':
				system("cls");
				userVsCompTTT();
				break;
			case '2':
				system("cls");
				hangMan();
				break;
			case '3':
				system("cls");
				oneHundred();
				break;
			case '0':
				system("cls");
				stay = 0;
				break;
			default:
				system("cls");
				cout << "\n\t\t     Error: Invalid Input. \n";
            	cout << "\t\t--------Enter 1, 2, 3, or 0----------    ";
            	cout << "\n\t\t  Press Enter to Restart \n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			
		}
	
	
	
	} while(stay==1);
	
	
	
	
	
	
    //system("pause");
         
    return 0;
}

void userVsCompTTT()
{
	// Game Board Array: will store the contents of each box on the board
	char board[NUM_ROWS][NUM_COLS] = { ' ', ' ', ' ',
									   ' ', ' ', ' ',
									   ' ', ' ', ' ' };
	// Key (legend) for input: will show the available spots as numbers 
	// corresponding to a position on the board								   
	char key[NUM_ROWS][NUM_COLS] = { '1', '2', '3',
									 '4', '5', '6',
									 '7', '8', '9' };
	//Logic Array 1: will store a number corresponding to the current status of 
	//box on the game board: if the box is empty, 0 will be stored
	//if the box contains an O, then -1 will be stored
	//if the box contains an X, then 1 will be stored 	
	int LA1[NUM_ROWS][NUM_COLS];
	//Logic Array 2 and 3 will be used to calculate the computer's next move
	//this will be explained in another function
	int LA2[NUM_ROWS][NUM_COLS];
	int LA3[NUM_ROWS][NUM_COLS];
	int LA4[NUM_ROWS][NUM_COLS];
	//SpotsTaken Array will keep track of which posistions on the board are still available
	bool spotsTakenArray[NUM_ROWS][NUM_COLS];
	// Good Move Array will be used to point out the best available choices for the computer to make
	bool goodMoveArray[NUM_ROWS][NUM_COLS];
	//the next two boolan variables will tell the program wether or not the tournament is over
	//and whether or not the User wants a rematch
	bool gameOn = 1;
	bool tournOn = 1;
	bool rematch = 1;
	//keeps track of how many wins the computer and user have within the tournament
	//(First to 2)
	int compWinTot = 0;
	int userWinTot = 0;
	//keeps track of how many games have been played within the tournament
	int gameNum = 1;
	//Notifies the program of who one the last game, (will get to start the next one)
	char lastWinner = 'n';
	//Stores whether or not the User won the coin toss to decide who goes first in the first game
	bool flipResult;
	char turn = ' ';
	
	
	//Tournament (OUTER) Loop;  continues until someone wins 2 games AND No rematch is requested
	while((tournOn==1)||(rematch==1))
	{
		
		//srand(time(NULL));
		if((gameNum==1)||(lastWinner == 't')) //If it is the first game of a new Tournament (or there was a tie for the first game(s))
		{
			
			turn = ' '; 														//ADDITION
			setUpGame(board, key, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4, gameOn);
			if(lastWinner =='n')
			{
				displayRules();
			}
			flipResult = coinFlip();
			
			//cout << "\n\t 4  "<< flipResult << endl;
			
			if(flipResult==1)
			{
				cout << "\n\t\t You Get to Go First \n";
				cout << "\n\t\t Press Enter to start the game \n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				displayBoard(board, key, compWinTot, userWinTot);
				turn = 'u'; 														//ADDITION
				
				
				while(gameOn==1)
				{
					usersTurn(board, key, goodMoveArray, spotsTakenArray);
					turn = 'c'; 														//ADDITION
					updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
					displayBoard(board, key, compWinTot, userWinTot);
					lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
					
					if(gameOn==1)
					{
						computersTurn(board, key, goodMoveArray, spotsTakenArray);
						turn = 'u'; 														//ADDITION
						updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
						displayBoard(board, key, compWinTot, userWinTot);
						lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
						
						if(gameOn==0)
						{
							displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
							//displayScore(compWinTot, userWinTot, gameNum);
						}
						///////
					}
					else
					{
						displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
						//displayScore(compWinTot, userWinTot, gameNum);
					}
					///////
					
					
					
				}
				
				
				
			}
			else
			{
				//srand(time(NULL));
				cout << "\n\t\t The Computer will make the first Move \n";
				cout << "\n\t\t Press Enter to start the game \n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				displayBoard(board, key, compWinTot, userWinTot);
				cout << "\n\t\t Press Enter, and the computer will make a move \n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				compRandFirstMove(board, key);
				
				
				turn = 'u'; 														//ADDITION
				updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
				
				displayBoard(board, key, compWinTot, userWinTot);
				
				
				while(gameOn==1)
				{
					usersTurn(board, key, goodMoveArray, spotsTakenArray);
					turn = 'c'; 														//ADDITION
					updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
					displayBoard(board, key, compWinTot, userWinTot);
					lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
					
					if(gameOn==1)
					{
						computersTurn(board, key, goodMoveArray, spotsTakenArray);
						turn = 'u'; 														//ADDITION
						updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
						displayBoard(board, key, compWinTot, userWinTot);
						lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
						
						if(gameOn==0)
						{
							displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
							//displayScore(compWinTot, userWinTot, gameNum);
						}
						///////
					}
					else
					{
						displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
						//displayScore(compWinTot, userWinTot, gameNum);
					}
					///////
					
					
					
				}
				
				
				
				///////////////////////////////////////
				
				
			}
			
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			//displayBoard(board, key, compWinTot, userWinTot);
		
		
		
		
		/////CHECK FOR TOURN WINNER
		tournOn = check4tournWinner(compWinTot, userWinTot);
		
		
		//rematch = rematchYN();
		
		if(tournOn == 0)
		{
			rematch = rematchYN();
			
			if(rematch == 1)
			{
				gameNum = 1;
				compWinTot = 0;
				userWinTot = 0;
			}
			
			
		}
		
		
		
		
		
			
		}
		else //if there has already been one game played
		{
			setUpGame(board, key, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4, gameOn);
			displayScore(compWinTot, userWinTot, gameNum);
			
			displayBoard(board, key, compWinTot, userWinTot);
			
			
			switch (lastWinner)
			{
				case 'c':
					{
						
						//srand(time(NULL));
						cout << "\n\t\t The Computer will make the first Move \n";
						cout << "\n\t\t Press Enter to start the game \n";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						displayBoard(board, key, compWinTot, userWinTot);
						cout << "\n\t\t Press Enter, and the computer will make a move \n";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						compRandFirstMove(board, key);
						
						turn = 'u'; 														//ADDITION
				
						updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
				
						displayBoard(board, key, compWinTot, userWinTot);
				
				
						while(gameOn==1)
						{
							usersTurn(board, key, goodMoveArray, spotsTakenArray);
							turn = 'c'; 														//ADDITION
							updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
							displayBoard(board, key, compWinTot, userWinTot);
							lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
					
							if(gameOn==1)
							{
								computersTurn(board, key, goodMoveArray, spotsTakenArray);
								turn = 'u'; 														//ADDITION
								updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
								displayBoard(board, key, compWinTot, userWinTot);
								lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
						
								if(gameOn==0)
								{
									displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
									displayScore(compWinTot, userWinTot, gameNum);
								}
						///////
							}
							else
							{
								displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
								displayScore(compWinTot, userWinTot, gameNum);
							}
					///////
					
					
					
						}
						
						break;
					}
				case 'u':
					{
						cout << "\n\t\t You Get to Go First \n";
						cout << "\n\t\t Press Enter to start the game \n";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						displayBoard(board, key, compWinTot, userWinTot);
				
				
				
						while(gameOn==1)
						{
							usersTurn(board, key, goodMoveArray, spotsTakenArray);
							turn = 'c'; 														//ADDITION
							updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
							displayBoard(board, key, compWinTot, userWinTot);
							lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
					
							if(gameOn==1)
							{
								computersTurn(board, key, goodMoveArray, spotsTakenArray);
								turn = 'u'; 														//ADDITION
								updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
								displayBoard(board, key, compWinTot, userWinTot);
								lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
						
								if(gameOn==0)
								{
									displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
									displayScore(compWinTot, userWinTot, gameNum);
								}
						///////
							}
							else
							{
								displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
								displayScore(compWinTot, userWinTot, gameNum);
							}
					///////
					
					
					
						}
						
						break;
					}
				case 't':
					{
						setUpGame(board, key, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4, gameOn);
						flipResult = coinFlip();
			
						//cout << "\n\t 4  "<< flipResult << endl;
			
						if(flipResult==1)
						{
							cout << "\n\t\t You Get to Go First \n";
							cout << "\n\t\t Press Enter to start the game \n";
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							displayBoard(board, key, compWinTot, userWinTot);
				
				
				
							while(gameOn==1)
							{
								usersTurn(board, key, goodMoveArray, spotsTakenArray);
								turn = 'c'; 														//ADDITION
								updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
								displayBoard(board, key, compWinTot, userWinTot);
								lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
					
								if(gameOn==1)
								{
									computersTurn(board, key, goodMoveArray, spotsTakenArray);
									turn = 'u'; 														//ADDITION
									updateLogicA(board, LA1, LA2, LA3, spotsTakenArray, goodMoveArray, LA4,turn);
									displayBoard(board, key, compWinTot, userWinTot);
									lastWinner = check4gameWinner(LA1, spotsTakenArray, gameOn);
						
									if(gameOn==0)
									{
										displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
										displayScore(compWinTot, userWinTot, gameNum);
									}
										///////
								}
								else
								{
									displayWinnerUpdateScore(gameNum, lastWinner, userWinTot, compWinTot);
									displayScore(compWinTot, userWinTot, gameNum);
								}
								///////
					
					
					
							}
						
						}
				
						break;
					}
			
			
			
			
			
			
			}
		/////CHECK FOR TOURN WINNER
		tournOn = check4tournWinner(compWinTot, userWinTot);
		
		
		//rematch = rematchYN();
		
		if(tournOn == 0)
		{
			rematch = rematchYN();
			
			if(rematch == 1)
			{
				gameNum = 1;
				compWinTot = 0;
				userWinTot = 0;
			}
			
			
		}
		
		
		}
	
		
	}
}

void hangMan()
{
    
    string catone[] = { "basketball" , "baseball", "football", "bowling",
        				"snowboarding","skateboarding" ,"golf" ,"swimming",
        				" cricket" ,"archery" ,"badminton","beach volleyball" ,
        				"boxing" ,"cycling" ,"diving" , "fencing" ,
        				"field hockey","gymnastics" ,"handball" ,"judo" ,
       					"shooting ","soccer" ,"table tennis",
        				"track and field" ,"water polo" ,"weightlifting" ,"wrestling" ,
        				"hip hop" , "rock" , "classical" , "pop" ,
        				"country" , "latin" , "electric dance music" , " alternative" ,
        				"indie rock" , "metal" , "jazz" , "blues" ,
        				"trap" ,"apple" , "apricot" , "avocado" , "banana" , "bilberry" , "blackberry" , "cherry" ,
        				"coconut" , "cranberry" , "dragon fruit" , "grape" , "guava" , "lemon" , "lime" , "mango" ,
        				"melon" , "honeydew" , "watermelon" , "miracle fruit" , "nectarine" , "olive" , "orange" ,
        				"papaya" , "passion fruit" , "peach" , "plum" , "pineapple", "raspberry" , " starfruit" };
    
    
    srand(time(NULL));
    
    string word;   // Selecting a random word from the list
    
    
    string copy; // makes a copy of there word to do calculations
    
    string underscore; // delcaring the underscores to be inputed
    
    int wrong;
    
    bool rematch = 1;
    
    
    do
    {
    	system("cls");
    	cout << " Welcome to Hangman. This version of the game is \n"
         	<< " won buy guessing a random word that the program will"
         	<< " select for you \n"
         	<< " There are 3 possible catagories that the word can be selected from \n"
         	<< " Those categories are fruits , olympic sports , or music genres";
    
    
    	word = catone[ rand() % 69 +1 ] ; // Selecting a random word from the list
    
    
    	copy = word; // makes a copy of there word to do calculations
    
    
    	for(int i=0; i!=word.length(); i++)
    	{                                 // loop as long as i ( counter ) is not ==
    	    // to the length
       		 // of the word ( "array" holding each letter for the
        	// string.
        
        	if(word.at(i) == ' ')         // if there is a space in the word
        	{
        	    underscore += " ";            // input a space in place of space in word underscores
        	}
       		else                              // if there is no spaces in the word replace it with score
        	{
            	underscore += "_";
        	}
    	}
    
    	for(int i=0; i!=5; ++i)              // skips 5 lines so user cannot see what the word is.
        
    	{
        	cout << endl;
    	}
    
    	string guess;                         // declaring a string type for the other player to guess
    
    	wrong = 0;                          // initializing wrong to start 0
    
    	while(1)
    	{
        	if(wrong == 6)                    // as long as the user does not make 6 mistakes this
            // will not execute
        	{
            	cout << "you lose! the word was: " << word << endl;
            	break;
        	}
        ////////////////////////////////////////////////jm
        // /*
        {
        	for(int i=0; i!=word.length(); i++)
    	{                                 // loop as long as i ( counter ) is not ==
    	    // to the length
       		 // of the word ( "array" holding each letter for the
        	// string.
        	
        	
        	cout << " " << underscore.at(i);
        
    	}
        }
        // */
        ////////////////////////////////////////////////////
        
        	cout << endl<<endl;
        	//cout << underscore << endl<<endl;
        	
        ///////////////////////////////////////////////////////	jm
        	
        	cout << "*** REMINDER catagories are Fruits,"
        	"*** Olympic Sports , and Music Genres  \n\n";
        	// length will display how many letters it counts inside what is left in word
        
        	cout << "you have " << 6 - wrong << " more tries left" << endl;
        	// will subtract how many tries you have left(l
        
        	if(underscore == word)
        	{
            	cout << "you win!" << endl;
            	break;
        	}
        
        	cout << "guess a letter or a word" <<endl << endl; // displays intructions for the user
        
        	bool reset = 0;
        	
        	do
			{
				getline(cin, guess);                        // user enters a guess for the word
        		//cout << "t" << guess << "t";
        	
        		if((cin.fail())||(guess==""))
        		{
        			reset = 1;
        		}
        		else
        		{
        			reset = 0;
        		}
        		
        	}while(reset==1);
        	
        	
        	if(guess.length() > 1)                      // if the length of the guess is bigger then
            // one letter it will test for the entire word
        	{
            	if(guess == word)                       // if the guessed word is the same as the word
            	{
                	cout << "that's right, you win!" << endl; // display message
                	break;
            	}
            	else
            	{
                	cout << "wrong word " << endl;      // if the user inputs a word or letter and it
                	// is incorrect
                
                	wrong++;                            // increment wrong to keep track of how many
                	// wrong
            	}
        	}
        	else if(copy.find(guess) != -1)             // using the copy of the word ( why is there a
            	// negative 1)
        	{
            
            	while(copy.find(guess) != -1)           // will look for the letter in copy
            	{
                	underscore.replace(copy.find(guess), 1, guess); // this line is replacing the underscore with the letter if it is
                	// found
                	copy.replace(copy.find(guess), 1, "_");         // replaces the underscore with the letter
            	}
        	}
        	else
			{
            
          
            	cout << "that's wrong"<<endl << endl; // displaying message to user
            	wrong++;                        // incrementing wrong for number of strikes left
        	}
        
        
        
        	cout << endl;
    	}
    	
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	rematch = rematchYN();
   
	}while (rematch==1);
    	
    
    
}

void oneHundred()
{
	bool rematch = 1;
	int total;
	
	
	do
	{
		system("cls");

		cout <<   "\n\t    The First To 100 Game \n\n";
		cout << "     ------------------------------------------------------------------------\n";
		cout << "\n\t This is a game for two players.";
		cout << "\n\t Players take turns choosing any whole number from 1 to 10. They keep ";
		cout << "\n\t a running sum of all the chosen numbers. The first player to make ";
 		cout << "\n\t this total reach exactly 100 wins.";
 		cout << "      \n\n";
		cout << "\n\t    **Hello Players, Lets have fun** \n\n";
		cout << "     ------------------------------------------------------------------------\n";
  


	


	
   		total = 0;
   
   		do 
   		{
        	cout << "\n\t Player1, Enter a number between 1-10: ";
        	total += sum();
        	cout << "\t   Total: " << total << endl << endl;
        
        	if(total >= 100)
			{
            	cout << "   Player1 is the winner" << endl;
        	}
			else   
        	{
        		cout << "\n\t Player 2, Enter a number between 1-10: ";
        		total += sum();
        		cout << "\t   Total: " << total << endl << endl;
        
        		if(total >= 100)
				{
             		cout << "\n\n   Player2 is the winner" << endl;
        		}
        	}
        	
   		}while (total < 100);


   		rematch = rematchYN();
   
	}while (rematch==1);
   

}

int sum() 
{
   int num=0;
   cin >> num;
   if (cin.fail())     // If wrong data type, discard entry
   {
		cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t   Invalid Input Type.  Try Again \n";
	}           
  while (num <= 0 || num >10){
    cout << "\n\t Enter a number Between 1-10: ";
    cin >> num;
   }
   return (num);
}

void setUpGame(char boxes[][NUM_COLS], char spotKey[][NUM_COLS],
 			   int logic1[][NUM_COLS], int logic2[][NUM_COLS],
			   int logic3[][NUM_COLS], bool spotTaken[][NUM_COLS], bool goodMove[][NUM_COLS], int logic4[][NUM_COLS], bool &gameOn)
{
	//This Function clears and resets the game board and key to default starting values
	//Also clears and Rests all arrays used for logic 
	
	int x, y;
	
	gameOn = 1;
	
	//clear gameboard
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			boxes[y][x] = ' ';
		}
	}
	
	//reset key;  because choices dissapear as spots are taken
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			if(y==0)
			{
				switch(x)
				{
					case 0:
					spotKey[y][x] = '1';
					break;
					
					case 1:
					spotKey[y][x] = '2';
					break;
					
					case 2:
					spotKey[y][x] = '3';
					break;
				}
			}
			else if(y==1){
				switch(x)
				{
					case 0:
					spotKey[y][x] = '4';
					break;
					
					case 1:
					spotKey[y][x] = '5';
					break;
					
					case 2:
					spotKey[y][x] = '6';
					break;
				}
			}
			else
			{
				switch(x)
				{
					case 0:
					spotKey[y][x] = '7';
					break;
					
				    case 1:
				    spotKey[y][x] = '8';	
					break;
					
					case 2:
					spotKey[y][x] = '9';
					break;
				}
			}
		}
	}
	
	
	//The rest are all Logic Arrays
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			logic1[y][x] = 0;
			logic2[y][x] = 0;
			logic3[y][x] = 0;
			logic4[y][x] = 0;
		}
	}

	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			spotTaken[y][x] = 0;
			goodMove[y][x] = 0;
		}
	}
								   							   
}

							
void displayBoard(char boxes[][NUM_COLS], char spots[][NUM_COLS], int compScore, int userScore)
{
	//Clear screen and display the gameboard and key with all current information
	//system("cls");
	
	cout << "\n\n\t\t\t" << "Tic Tac Toe Tournament \n\n";
	cout << "\t\t" << "KEY:\n";
	
	cout << left << "                                                     |     |     " << endl;
	
	cout << setw(50) << "  " << spots[0][0] << "  |  " << spots[0][1] << "  |  " << spots[0][2] << endl;
	
	cout << "                                                _____|_____|_____" << endl;
	cout << "                                                     |     |     " << endl;
	
	cout << setw(50) << "  " << spots[1][0] << "  |  " << spots[1][1] << "  |  " << spots[1][2] << endl;
	
	cout << "                                                _____|_____|_____" << endl;
	cout << "                                                     |     |     " << endl;
	
	cout << setw(50) << "  " << spots[2][0] << "  |  " << spots[2][1] << "  |  " << spots[2][2] << endl;
	
	cout << "                                                     |     |     " << endl;
	
	cout << "\n\n\t\t" << "Player 1 (X)  -  Computer (O)" << endl << endl;
	cout << "\t\t" << "     " << userScore << " wins   -   " << compScore << " wins" << endl << endl<< "\n\n";
	
	
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << boxes[0][0] << "  |  " << boxes[0][1] << "  |  " << boxes[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << boxes[1][0] << "  |  " << boxes[1][1] << "  |  " << boxes[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << boxes[2][0] << "  |  " << boxes[2][1] << "  |  " << boxes[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;	
	
}

void displayScore(int compWs, int userWs, int gNum)
{
	cout << "\n\t\t Tic Tac Toe Tournament \n";
	cout << "\n\t\t Score:  Computer |   User   ";
	cout << "\n\t\t             " << compWs  <<  "    |     " << userWs << "\n";
	cout << "\n\t\t Beginning Game Number " << gNum << ". . . \n";
	cout << "\n\t\t Press Enter to continue...";
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayRules()  // Explains How the Game works
{
	cout << "\n\n\n\n\t\t\t\t Tic Tac Toe Tournament \n";
	cout << "\t\t\t---------------------------------------------\n";
	cout << "\t\t\t---------------------------------------------\n";
	cout << "\n\t\t\t\t Player 1  VS.   The Computer \n";
	cout << "\t\t\t____________________________________________________________________\n";
	cout << "\n\t\t\t Game Rules and Description:  \n\n";
	cout << "\t\t\t-----------------------------------------------------------------------------------------------------------------\n";
	cout << "\n\t\t\t\t Standard 3 x 3 Tic Tac Toe against THE COMPUTER \n";
	cout << "\n\t\t\t\t Your mark will be X.  The computer will be O \n";
	cout << "\n\t\t\t\t The first Player to win 2 games will win the turnament \n\n";
	cout << "\n\t\t\t\t First, we flip a coin to decide who goes first \n";
	cout << "\n\t\t\t\t Then, we will start the game. \n\n";
	cout << "\n\t\t\t\t To make your move, you will enter a number between 1 and 9 \n";
	cout << "\n\t\t\t\t A key will be displayed to show which number corresponds to each position on the board \n";
	cout << "\n\t\t\t\t Lets Begin...  Press Enter When you're ready...";
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool coinFlip()
{
	//This Function allows the User to choose heads or Tails and flip a coin
	//against the computer to see who goes first for the first game of the tournament
	
	
	
	
	
	
	char tossChoice;
	bool reset = 1;
	int num;
	char flipResult;
	string leftover;
	int i = 0;
	int reps = 0;
	
	
	system("cls");
	
	
	for(i=0; i<5; i++)
	{
	
	reps = 3 + rand() % 7;
	
	/*
	cout << "\n\t\t\t\t " << num;
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	*/
	}
	
	
	
	cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
	cout << "\n\t\t Lets Flip A Coin To See Who goes first \n";
	cout << "\n\t\t Please Choose Heads or tails \n";
	cout << "\n\t\t Enter h for Heads or t for Tails: ";
	
	
	
	
	
	/*
	while (reset == 1)
	{
		//cin.get(tossChoice);
		cin >> tossChoice;
		getline(cin, leftover);
		
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		//cout << "\n\t\t  0  " << leftover << endl;
		
		//cout << "\n\t\t  1  " << tossChoice << endl;
				
		if (cin.fail())     // If wrong data type, discard entry and repeat loop
		{
			cin.clear();
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n     Error: Invalid Input Type.  Try Again \n";
            cout << "--------Enter h or t----------\n\n";
    
            
			reset = 1;
        }           
        else				// If correct data type
        {
            switch(tossChoice)
            {
            	case 'h':
            		if((leftover == "")||(leftover == "eads"))
            		{
            			reset = 0;
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            			cout << "\t\t--------Enter h or t----------    ";
            			reset = 1;
            			break;
            		}
            	case 'H':
            		tossChoice = 'h';
            		if((leftover == "")||(leftover == "eads"))
            		{
            			reset = 0;
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            			cout << "\t\t--------Enter h or t----------    ";
            			reset = 1;
            			break;
            		}
            	case 't':
            		if((leftover == "")||(leftover == "ails"))
            		{
            			reset = 0;
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            			cout << "\t\t--------Enter h or t----------    ";
            			reset = 1;
            			break;
            		}
            	case 'T':
            		tossChoice = 't';
            		if((leftover == "")||(leftover == "ails"))
            		{
            			reset = 0;
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            			cout << "\t\t--------Enter h or t----------    ";
            			reset = 1;
            			break;
            		}
            	default:
            		cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            		cout << "\t\t--------Enter h or t----------    ";
            		reset = 1;
            		break;
            }   
        }	
	}
	
	*/
	
	
	
	
	
	
	
	i = 0;
	for(i=0; i<reps; i++)
	{
	
	num = 1 + rand() % 2;
	
	/*
	cout << "\n\t\t\t\t " << num;
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	*/
	}
	
	if(num==1)
	{
		tossChoice = 'h';
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t Coin Toss user guess:  Heads \n";
	}
	else
	{
		tossChoice = 't';
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t Coin Toss user guess:  Tails \n";
	}
	
	cout << "\n\t\t  2 " << tossChoice << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	
	

	i = 0;
	for(i=0; i<reps; i++)
	{
	
	num = 1 + rand() % 2;
	
	/*
	cout << "\n\t\t\t\t " << num;
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	*/
	}
	
	if(num==1)
	{
		flipResult = 'h';
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t Coin Toss Result:  Heads \n";
	}
	else
	{
		flipResult = 't';
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t Coin Toss Result:  Tails \n";
	}
	
	cout << "\n\t\t " << flipResult << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if (tossChoice == flipResult)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
	
	cout << "\n\t\t\t\t Lets Begin...  Press Enter When you're ready...";
	//cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
}

void compRandFirstMove(char boxes[][NUM_COLS], char spotKey[][NUM_COLS])
{
	int randChoice = 0;
	int i = 0;
	
	for(i=0; i<5; i++)
	{
		randChoice = 1 + rand() % 9;
	}
	
	
	switch(randChoice)
	{
		case 1:
			boxes[0][0] = 'O';
			spotKey[0][0] = ' ';
			break;
		case 2:
			boxes[0][1] = 'O';
			spotKey[0][1] = ' ';
			break;
		case 3:
			boxes[0][2] = 'O';
			spotKey[0][2] = ' ';
			break;
		case 4:
			boxes[1][0] = 'O';
			spotKey[1][0] = ' ';
			break;
		case 5:
			boxes[1][1] = 'O';
			spotKey[1][1] = ' ';
			break;
		case 6:
			boxes[1][2] = 'O';
			spotKey[1][2] = ' ';
			break;
		case 7:
			boxes[2][0] = 'O';
			spotKey[2][0] = ' ';
			break;
		case 8:
			boxes[2][1] = 'O';
			spotKey[2][1] = ' ';
			break;
		case 9:
			boxes[2][2] = 'O';
			spotKey[2][2] = ' ';
			break;
	}
	
	
}

void updateLogicA(char boxes[][NUM_COLS], int logic1[][NUM_COLS], int logic2[][NUM_COLS],
			      int logic3[][NUM_COLS], bool spotTaken[][NUM_COLS], bool goodMove[][NUM_COLS], int logic4[][NUM_COLS],char trn)
{
	int hor1 = 0, hor2 = 0, hor3 = 0, vert1 = 0, vert2 = 0, vert3 = 0, diag1 = 0, diag2 = 0;
	unsigned int absHor1 = 0, absHor2 = 0, absHor3 = 0, absVert1 = 0, absVert2 = 0, absVert3 = 0, absDiag1 = 0, absDiag2 = 0;
	
	int x, y;
	int best = 0;
	int goodMoves = 0;
	
	
	
	for(y=0; y < NUM_ROWS; y++ )    // clearing all arrays
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			logic1[y][x] = 0;
			logic2[y][x] = 0;
			logic3[y][x] = 0;
			logic4[y][x] = 0;
			goodMove[y][x] = 0;
		}
	}
	
	
	
	
	
	
	
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			if(trn=='c')
			{
				switch(boxes[y][x])
				{
					case ' ':
						logic1[y][x] = 0;
						spotTaken[y][x] = 0;
						break;
					case 'X':
						logic1[y][x] = 1;
						spotTaken[y][x] = 1;
						break;
					case 'O':
						logic1[y][x] = -1;
						spotTaken[y][x] = 1;
						break;
				}
			}
			else if(trn=='u')
			{
				switch(boxes[y][x])
				{
					case ' ':
						logic1[y][x] = 0;
						spotTaken[y][x] = 0;
						break;
					case 'O':
						logic1[y][x] = 1;
						spotTaken[y][x] = 1;
						break;
					case 'X':
						logic1[y][x] = -1;
						spotTaken[y][x] = 1;
						break;
				}
			}			
			
		}
	}
	
	
	hor1 = logic1[0][0]+logic1[0][1]+logic1[0][2];
	absHor1 = abs(hor1);
	hor2 = logic1[1][0]+logic1[1][1]+logic1[1][2];
	absHor2 = abs(hor2);
	hor3 = logic1[2][0]+logic1[2][1]+logic1[2][2];
	absHor3 = abs(hor3);
	vert1 = logic1[0][0]+logic1[1][0]+logic1[2][0];
	absVert1 = abs(vert1);
	vert2 = logic1[0][1]+logic1[1][1]+logic1[2][1];
	absVert2 = abs(vert2);
	vert3 = logic1[0][2]+logic1[1][2]+logic1[2][2];
	absVert3 = abs(vert3);
	diag1 = logic1[0][0]+logic1[1][1]+logic1[2][2];
	absDiag1 = abs(diag1);
	diag2 = logic1[0][2]+logic1[1][1]+logic1[2][0];
	absDiag2 = abs(diag2);
	
	logic2[0][0] = hor1+vert1+diag1;
	logic3[0][0] = absHor1+absVert1+absDiag1;
	
	logic2[0][1] = hor1+vert2;
	logic3[0][1] = absHor1+absVert2;
	
	logic2[0][2] = hor1+vert3+diag2;
	logic3[0][2] = absHor1+absVert3+absDiag2;
	
	logic2[1][0] = hor2+vert1;
	logic3[1][0] = absHor2+absVert1;
	
	logic2[1][1] = hor2+vert2+diag1+diag2;
	logic3[1][1] = absHor2+absVert2+absDiag1+absDiag2;
	
	logic2[1][2] = hor2+vert3;
	logic3[1][2] = absHor2+absVert3;
	
	logic2[2][0] = hor3+vert1+diag2;
	logic3[2][0] = absHor3+absVert1+absDiag2;
	
	logic2[2][1] = hor3+vert2;
	logic3[2][1] = absHor3+absVert2;
	
	logic2[2][2] = hor3+vert3+diag1;
	logic3[2][2] = absHor3+absVert3+absDiag1;
	
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			if((logic2[y][x]<=1)&&(logic3[y][x]!=0))
			{
				if(spotTaken[y][x] == 0)
				{
					//goodMove[y][x] = 1;
					logic4[y][x]++;
					
					//logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
					logic4[y][x] += (logic3[y][x] - logic2[y][x])*2;
					
					{
						if((logic2[y][x]==0)&&(logic3[y][x]!=0))
						{
							logic4[y][x]++;
						}
						
						
					}
					
					
					
					
					
					
					
					if(logic4[y][x] > best)
					{
						best = logic4[y][x];
					}
				}
			}
			else
			{
				goodMove[y][x] = 0;
			}
			
		}
	}
	
	/////////////////////////////////////
	
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\             //////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (absHor1==2)
	{
		if (spotTaken[0][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[0][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
		else if (spotTaken[0][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
	}
	
	
	
	
	if (absHor2==2)
	{
		if (spotTaken[1][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
		else if (spotTaken[1][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
	}
	
	
	
	
	
	
	if (absHor3==2)
	{
		if (spotTaken[2][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
		else if (spotTaken[2][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}
		}
	}
	
	
	
	if (absVert1==2)
	{
		if (spotTaken[0][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
	}
	
	
	
	
	if (absVert2==2)
	{
		if (spotTaken[0][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==1))
					{
						//goodMove[y][x] = 1;
						
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
						
						
						
						
						
						
						
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==1))
					{
						
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	if (absVert3==2)
	{
		if (spotTaken[0][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
	}
	
	
	
	
	
	if (absDiag1==2)
	{
		if (spotTaken[0][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
	}
	
	
	
	
	
	
	
	if (absDiag2==2)
	{
		if (spotTaken[0][2]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==0)&&(x==2))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[1][1]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==1)&&(x==1))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
		else if (spotTaken[2][0]==0)
		{
			for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if((y==2)&&(x==0))
					{
						//goodMove[y][x] = 1;
						if(spotTaken[y][x] == 0)
						{
							if (hor2== -2)
							{
								logic4[y][x]+=5;
							}
							else if (hor2== 2)
							{
								logic4[y][x]++;
							}
							
							//goodMove[y][x] = 1;
							logic4[y][x]+=4;
					
							logic4[y][x] += (((logic3[y][x])*2) - logic2[y][x]);
					
							if(logic4[y][x] > best)
							{
								best = logic4[y][x];
							}
						}
					}
					else
					{
						goodMove[y][x] = 0;
					}
			
				}
			}	
		}
	}
	
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   \\\\\\\\\     /////////////     \\\\\\\\\\\       //////////	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	////////////////////////
	
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			
			if((best>0)&&(logic4[y][x] == best))
					{
						goodMove[y][x] = 1;
					}
					else
					{
						goodMove[y][x] = 0;
					}
		}
	}
			
			
			
////////////////////////////////////////////			
			
	
	
	

	
	
	for(y=0; y < NUM_ROWS; y++ )
	{
		for(x=0; x < NUM_COLS; x++ )
		{
			
			if(goodMove[y][x] == 1)
			{
				goodMoves++;
			}
					
		}
	}
	
	if(goodMoves==0)
	{
		for(y=0; y < NUM_ROWS; y++ )
		{
			for(x=0; x < NUM_COLS; x++ )
			{
			
				if(spotTaken[y][x] == 0)
				{
					goodMove[y][x] = 1;
				}
				else
				{
					goodMove[y][x] = 1;
				}
				
					
			}
		}
	}
	else if ((goodMoves==8)&&(logic1[1][1] == 1))
	{
		for(y=0; y < NUM_ROWS; y++ )
		{
			for(x=0; x < NUM_COLS; x++ )
			{
				goodMove[y][x] = 0;
			}
		}
		
		
		
		goodMove[0][0] = 1;
		goodMove[0][2] = 1;
		goodMove[2][0] = 1;
		goodMove[2][2] = 1;
	}
	
	
	  /*
	
	{
	
	
	cout << "\n\n\t Logic 1   \n";
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic1[0][0] << "  |  " << logic1[0][1] << "  |  " << logic1[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic1[1][0] << "  |  " << logic1[1][1] << "  |  " << logic1[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic1[2][0] << "  |  " << logic1[2][1] << "  |  " << logic1[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;	
	
	
	
	
	cout << "\n\n\t Logic 2   \n";
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic2[0][0] << "  |  " << logic2[0][1] << "  |  " << logic2[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic2[1][0] << "  |  " << logic2[1][1] << "  |  " << logic2[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic2[2][0] << "  |  " << logic2[2][1] << "  |  " << logic2[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;	
	
	
	
	
	cout << "\n\n\t Logic 3   \n";
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic3[0][0] << "  |  " << logic3[0][1] << "  |  " << logic3[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic3[1][0] << "  |  " << logic3[1][1] << "  |  " << logic3[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic3[2][0] << "  |  " << logic3[2][1] << "  |  " << logic3[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;	
	
	
	
	
	cout << "\n\n\t Logic 4   \n";
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic4[0][0] << "  |  " << logic4[0][1] << "  |  " << logic4[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic4[1][0] << "  |  " << logic4[1][1] << "  |  " << logic4[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << logic4[2][0] << "  |  " << logic4[2][1] << "  |  " << logic4[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;
	
	
	
	
	cout << "\n\n\t Good moves   \n";
	
	cout << left << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << goodMove[0][0] << "  |  " << goodMove[0][1] << "  |  " << goodMove[0][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << goodMove[1][0] << "  |  " << goodMove[1][1] << "  |  " << goodMove[1][2] << endl;
	
	cout << "\t\t       _____|_____|_____" << endl;
	cout << "\t\t            |     |     " << endl;
	
	cout << setw(25) << "  " << goodMove[2][0] << "  |  " << goodMove[2][1] << "  |  " << goodMove[2][2] << endl;
	
	cout << "\t\t            |     |     " << endl;
	
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	   */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
}

char check4gameWinner(int logA1[][NUM_COLS], bool spot[][NUM_COLS], bool &gameOn)
{
	int hor1 = 0, hor2 = 0, hor3 = 0, vert1 = 0, vert2 = 0, vert3 = 0, diag1 = 0, diag2 = 0;
	int spotsLeft=0;
	int x=0, y=0;
	
	
	
	hor1 = logA1[0][0]+logA1[0][1]+logA1[0][2];
	hor2 = logA1[1][0]+logA1[1][1]+logA1[1][2];
	hor3 = logA1[2][0]+logA1[2][1]+logA1[2][2];
	vert1 = logA1[0][0]+logA1[1][0]+logA1[2][0];
	vert2 = logA1[0][1]+logA1[1][1]+logA1[2][1];
	vert3 = logA1[0][2]+logA1[1][2]+logA1[2][2];
	diag1 = logA1[0][0]+logA1[1][1]+logA1[2][2];
	diag2 = logA1[0][2]+logA1[1][1]+logA1[2][0];
	
	if(hor1==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (hor1==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(hor2==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (hor2==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(hor3==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (hor3==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(vert1==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (vert1==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(vert2==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (vert2==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(vert3==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (vert3==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(diag1==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (diag1==3)
	{
		gameOn=0;
		return 'u';
	}
	else if(diag2==-3)
	{
		gameOn=0;
		return 'c';
	}
	else if (diag2==3)
	{
		gameOn=0;
		return 'u';
	}
	else
	{
		for(y=0; y < NUM_ROWS; y++ )
			{
				for(x=0; x < NUM_COLS; x++ )
				{
					if(spot[y][x] == 0)
					{
						spotsLeft++;
					}
			
				}
			}
		
		
		if(spotsLeft==0)
		{
			gameOn=0;
			return 't';
		}
		else
		{
			gameOn=1;
			return 'n';
			
		}
			
			
			
	}
	
	
	
	
}

void usersTurn(char table[][NUM_COLS], char pos[][NUM_COLS], bool best[][NUM_COLS], bool opt[][NUM_COLS])
{
	/*
	int choice = 0;
	int reset = 1;
	
	cout << "\n\t\t Its your turn \n";
	cout << "\n\t\t Enter a number from the key to choose your move:  ";
	
	//int i = 0;
	
	
	while (reset == 1)
	{
		//for(i=0; i<5; i++)
		//{
		//	choice = 1 + rand() % 9;
		//}
		
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
		if (cin.fail())     // If wrong data type, discard entry and repeat loop
		{
			cin.clear();
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n     Error: Invalid Input Type.  Try Again \n";
            cout << "------Enter whole number between 1 and 9------\n\n";
    
            
			reset = 1;
        }           
        else				// If correct data type
        {
            switch(choice)
            {
            	case 1:
            		if(spotsTake[0][0]==0)
            		{
            			reset = 0;
            			square[0][0] = 'X';
						legend[0][0] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            	case 2:
            		if(spotsTake[0][1]==0)
            		{
            			reset = 0;
            			square[0][1] = 'X';
						legend[0][1] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 3:
            		if(spotsTake[0][2]==0)
            		{
            			reset = 0;
            			square[0][2] = 'X';
						legend[0][2] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
					case 4:
            		if(spotsTake[1][0]==0)
            		{
            			reset = 0;
            			square[1][0] = 'X';
						legend[1][0] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 5:
            		if(spotsTake[1][1]==0)
            		{
            			reset = 0;
            			square[1][1] = 'X';
						legend[1][1] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 6:
            		if(spotsTake[1][2]==0)
            		{
            			reset = 0;
            			square[1][2] = 'X';
						legend[1][2] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 7:
            		if(spotsTake[2][0]==0)
            		{
            			reset = 0;
            			square[2][0] = 'X';
						legend[2][0] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 8:
            		if(spotsTake[2][1]==0)
            		{
            			reset = 0;
            			square[2][1] = 'X';
						legend[2][1] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		case 9:
            		if(spotsTake[2][2]==0)
            		{
            			reset = 0;
            			square[2][2] = 'X';
						legend[2][2] = ' ';
            			break;
            		}
            		else
            		{
            			cout << "\n\t\t     That spot has been taken already.  Try Again \n";
            			cout << "\t\t------Enter one of the numbers left in the key--------    ";
            			reset = 1;
            			break;
            		}
            		default:
            		cout << "\n\t\t     Error: Invalid Input.  Try Again \n";
            		cout << "\t\t--------Number must be between 1 and 9----------    ";
            		reset = 1;
            		break;
            }   
        }	
	}
	
	*/
	
	
		
	int randChoice = 0;
	int i = 0;
	bool retry = 1;
	
	do
	{
		for(i=0; i<5; i++)
		{
			randChoice = 1 + rand() % 9;
		}
	
	
		switch(randChoice)
		{
			case 1:
			{
			
				if((best[0][0]==1)&&(opt[0][0]==0))
				{
					table[0][0] = 'X';
					pos[0][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 2:
			{
			
				if((best[0][1]==1)&&(opt[0][1]==0))
				{
					table[0][1] = 'X';
					pos[0][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 3:
			{
				if((best[0][2]==1)&&(opt[0][2]==0))
				{
					table[0][2] = 'X';
					pos[0][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 4:
			{
				if((best[1][0]==1)&&(opt[1][0]==0))
				{
					table[1][0] = 'X';
					pos[1][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 5:
			{
				if((best[1][1]==1)&&(opt[1][1]==0))
				{
					table[1][1] = 'X';
					pos[1][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 6:
			{
				if((best[1][2]==1)&&(opt[1][2]==0))
				{
					table[1][2] = 'X';
					pos[1][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 7:
			{
				if((best[2][0]==1)&&(opt[2][0]==0))
				{
					table[2][0] = 'X';
					pos[2][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 8:
			{
				if((best[2][1]==1)&&(opt[2][1]==0))
				{
					table[2][1] = 'X';
					pos[2][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 9:
			{
				if((best[2][2]==1)&&(opt[2][2]==0))
				{
					table[2][2] = 'X';
					pos[2][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
		}	
		
	}while(retry==1);
	
	cout << "\n\t\t It is now the USERS Turn \n";
	cout << "\n\t\t Press Enter to Continue \n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	
	
	
	
	
	
	
	
	
}

void computersTurn(char table[][NUM_COLS], char pos[][NUM_COLS], bool best[][NUM_COLS], bool opt[][NUM_COLS])
{
	
	
	
	
	int randChoice = 0;
	int i = 0;
	bool retry = 1;
	
	do
	{
		for(i=0; i<5; i++)
		{
			randChoice = 1 + rand() % 9;
		}
	
	
		switch(randChoice)
		{
			case 1:
			{
			
				if((best[0][0]==1)&&(opt[0][0]==0))
				{
					table[0][0] = 'O';
					pos[0][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 2:
			{
			
				if((best[0][1]==1)&&(opt[0][1]==0))
				{
					table[0][1] = 'O';
					pos[0][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 3:
			{
				if((best[0][2]==1)&&(opt[0][2]==0))
				{
					table[0][2] = 'O';
					pos[0][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 4:
			{
				if((best[1][0]==1)&&(opt[1][0]==0))
				{
					table[1][0] = 'O';
					pos[1][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 5:
			{
				if((best[1][1]==1)&&(opt[1][1]==0))
				{
					table[1][1] = 'O';
					pos[1][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 6:
			{
				if((best[1][2]==1)&&(opt[1][2]==0))
				{
					table[1][2] = 'O';
					pos[1][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 7:
			{
				if((best[2][0]==1)&&(opt[2][0]==0))
				{
					table[2][0] = 'O';
					pos[2][0] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 8:
			{
				if((best[2][1]==1)&&(opt[2][1]==0))
				{
					table[2][1] = 'O';
					pos[2][1] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
			case 9:
			{
				if((best[2][2]==1)&&(opt[2][2]==0))
				{
					table[2][2] = 'O';
					pos[2][2] = ' ';
					retry = 0;
				}
				else
				{
					retry = 1;
				}
				break;
			}
		}	
		
	}while(retry==1);
	
	cout << "\n\t\t It is now the Computers Turn \n";
	cout << "\n\t\t Press Enter to Continue \n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	

}

void displayWinnerUpdateScore(int &gameNum, char lastWinner, int &userWinTot, int &compWinTot)
{
	switch(lastWinner)
	{
		case 't':
			cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
			cout << "\n\t\t TIE GAME! \n";
			gameNum++;
			break;
		case 'u':
			cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
			cout << "\n\t\t You Just Won This Game \n";
			userWinTot++;
			gameNum++;
			break;
		case 'c':
			cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
			cout << "\n\t\t The Computer Just Beat You This Game \n";
			compWinTot++;
			gameNum++;
			break;
			
	}
	
	cout << "\n\t\t Press Enter to Continue \n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	
	
}

bool check4tournWinner(int cWins, int uWins)
{
	if(cWins>=2)
	{
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t The Computer Won the tournament.  You need to sharpen your skills... and re-evaluate your career goals. \n";
		return 0;
	}
	else if(uWins>=2)
	{
		cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
		cout << "\n\t\t You Won the Tournament \n";
		return 0;
	}
	else
	{
		return 1;
	}
}

bool rematchYN()
{
	char playerChoice;
	bool reset = 1;
	bool decision;
	
	
	cout << "\n\t-------------------------------------------------------------------------------------------------------\n\n";
	cout << "\n\t\t Would you like a REMATCH. \n";
	cout << "\n\t\t Type 'y' and press enter for rematch, \n";
	cout << "\t\t or type n and press enter to return to main menu. \n"; 
	while (reset == 1)
	{
		cin >> playerChoice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
		if (cin.fail())     // If wrong data type, discard entry and repeat loop
		{
			cin.clear();
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n     Error: Invalid Input Type.  Try Again \n";
            cout << "--------Enter Y or N----------\n\n";
    
            
			reset = 1;
        }           
        else				// If correct data type
        {
        	reset = 0;
            switch(playerChoice)
            {
            	case 'y':
            		decision = 1;
            		break;
            	case 'Y':
            		decision = 1;
            		break;
            	default:
            		cout << "\n\t\t   I Guess Not \n";
					decision = 0;
            		break;
            }   
        }	
	}
	
	return decision;
	
	
}


/*




                        Tic Tac Toe Tournament

                KEY:
                                                     |     |
                                                     |  2  |  3
                                                _____|_____|_____
                                                     |     |
                                                  4  |     |  6
                                                _____|_____|_____
                                                     |     |
                                                     |     |  9
                                                     |     |


                Player 1 (X)  -  Computer (O)

                     1 wins   -   0 wins



                            |     |
                         O  |   c  |   u
                       _____|_____|_____
                            |     |
                            |  X  |
                       _____|_____|_____
                            |     |
                         O  |  X  |  u
                            |   c  |

                 Its your turn

                 Enter a number from the key to choose your move:  2




I could make the computer play against the computer...

prove that if two players make the right moves, either the one who starts wins or its a tie.



make sure to clear screen
game wont start  find bug



*/

 
	
        
