#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cmath>
#include <ctime>
#include <ncurses/ncurses.h>
using namespace std;

bool gameOver = false;                                    
char character = 'O';
const int lebar = 50;                           
const int tinggi = 20;                       
int x, y, posisiBuahX, posisiBuahY, skor;
int posisiEkorX[100], posisiEkorY[100];
int panjangEkor;
enum eArah { BERHENTI = 0, KIRI, KANAN, ATAS, BAWAH };    
eArah arah;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loadingawal() {
    system("color 3F");
	initscr();
	
	curs_set(0);
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);	
	
	bkgd(COLOR_PAIR(2));
	
	attron(COLOR_PAIR(2));
	
	mvprintw(9, 40, "");
	
	for (int i = 10; i <= 18; i++) {
    mvprintw(i, 40, "*");
    mvprintw(i, 79, "*");
}

	mvprintw(12, 50, "     LOGGED IN...   ");
	mvprintw(13, 50, " ------------------ ");
	mvprintw(14, 50, "|                  |");
	mvprintw(15, 50, " ------------------ ");
	
	mvprintw(19, 40, "");
		
	int load = 1;
		
	for (int j = 1; j <= 100; j++){
	if (j % 6 == 0 ) load++;
	attron(COLOR_PAIR(1));
	mvprintw(14, 50 + load, " ");
	attron(COLOR_PAIR(2));
	mvprintw(16, 54, "Loading ");
	mvprintw(16, 63, "  %%", j);
	mvprintw(16, 62, "%d");
	refresh();
	Sleep(50);
	}
	
	endwin();
}

void SignUp() {
    ofstream myFile, accList;
    string username, password;

    system("cls");
    gotoxy(42,13);
    cout << "------------> SIGN UP <------------" << endl;
    gotoxy(42,15);
    cout << "Enter Username: ";
    cin >> username;
    gotoxy(42,16);
    cout << "Enter Password: ";
    cin >> password;
    cout << endl;

    myFile.open(username + ".txt");
    if (!myFile) {
        cout << "Error opening file for user data!" << endl;
        return;
    }
    myFile << password;
    myFile.close();

    accList.open("ListAccount.txt", ios::app);
    if (!accList) {
        cout << "Error opening account list!" << endl;
        return;
    }
    accList << username << endl;
    accList.close();

    cout << " 				   	  Sign Up Successful!" << endl;
    cin.ignore();
    cin.get();
}

bool SignIn() {
    ifstream myFile;
    string username, password, fileUsername, filePassword;
    bool exist = false;

    system("cls");
    cout <<"\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "			  		  ------------> LOGIN <------------" << endl;
    cout << "				  	  Enter Username: ";
    cin >> username;
    cout << "					  Enter Password: ";
    cin >> password;

    myFile.open(username + ".txt");
    if (!myFile) {
        cout << "Error opening user file!" << endl;
        return false;
    }

    getline(myFile, filePassword);
    if (filePassword == password) {
        exist = true;
    }
    myFile.close();

    if (exist) {
        cout << "\n 				   	  Sign In Successful!" << endl;
        cin.ignore();
        cin.get();
        return true;
    } else {
        cout << "\n 				 	  Sign In Failed! Try Again." << endl;
        cin.ignore();
        cin.get();
        return false;
    }
}

void getConsoleSize(int &width, int &height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void loadingAnimation() {
    int WIDTH, HEIGHT;
    getConsoleSize(WIDTH, HEIGHT); 
    
    double amplitude1 = HEIGHT / 8.0; 
    double amplitude2 = HEIGHT / 10.0;
    double frequency = 3;

    for (int i = 0; i < WIDTH; i++) {
        int x = i % WIDTH;
        int y1 = (int)(amplitude1 * sin(frequency * i));
        int y2 = (int)(amplitude2 * sin(frequency * i + M_PI));
        int y3 = (int)(amplitude1 * sin(frequency * i + M_PI));
        int y4 = (int)(amplitude2 * sin(frequency * i));

        gotoxy(x, HEIGHT / 4 + y1);
        cout << "{==>>";
        gotoxy(x + 7, HEIGHT / 4 + y2);
        cout << "*";

        gotoxy(x, 3 * HEIGHT / 4 + y3); 
        cout << "{==>>";
        gotoxy(x + 7, 3 * HEIGHT / 4 + y4);
        cout << "*";

        Sleep(50);

        gotoxy(WIDTH / 2 - 10, HEIGHT / 2); 
        cout << "FEEDING FRENZY";

        Sleep(5);
    }
}

void Setup()                     
{
    gameOver = false;
    arah = BERHENTI;
    x = lebar / 2;
    y = tinggi / 2;
    posisiBuahX = rand() % lebar;    
    posisiBuahY = rand() % tinggi;
    skor = 0;
}

void Draw()                          
{
    erase();

    printw("\n ");
    for (int i = 0; i < lebar + 1; i++)  
        printw("#");
    printw("\n");


    for (int i = 0; i < tinggi; i++)                   
    {
        for (int j = 0; j < lebar; j++)
        {
            if (j == 0)
                printw(" #");                          
            if (i == y && j == x)
                printw("%c", character);                                     
            else if (i == posisiBuahY && j == posisiBuahX)    
                printw("@");
            else
            {
                bool print = false;
                for (int k = 0; k < panjangEkor; k++)
                {
                    if (posisiEkorX[k] == j && posisiEkorY[k] == i)
                    {
                        printw("~");                       
                        print = true;
                    }
                }
                if (!print)
                    printw(" ");
            }

            if (j == lebar - 2)
                printw("#");
        }
        printw("\n");
    }

    printw(" ");
    for (int i = 0; i < lebar + 2; i++)
        printw("#");
    printw("\n\n SCORE : %d\n", skor);   

        mvprintw(24,15,"W = UP");
        mvprintw(25,15,"A = LEFT");     
        mvprintw(26,15,"S = DOWN");
        mvprintw(27,15,"D = RIGHT");
        
        mvprintw(2,57," ______                _  _                ");                              
        mvprintw(3,57,"|  ___|              | |()               ");
        mvprintw(4,57,"| |                   | |                  ");
        mvprintw(5,57,"| |__   ___   ___   __| | _  _ __    __ _  ");
        mvprintw(6,57,"|  _| / _ \\ / _ \\ / _` || || ' \\  / _` | ");
        mvprintw(7,57,"| |   |  _/|  __/| (| || || | | || (_| | ");
        mvprintw(8,57,"||    \\| \\| \\,||||| || \\_  | ");
        mvprintw(9,57,"                                    __/  | ");                                  
        mvprintw(10,57,"                                   |/  ");     
		mvprintw(12,57," ______                              ");                              
        mvprintw(13,57,"|  ____|                             ");
        mvprintw(14,57,"| |     _ __   ___  _ __     _____  _   _ ");
        mvprintw(15,57,"| |__  | '| / _ \\| '_ \\   |_   / | | | |");
        mvprintw(16,57,"|  __| | |   |  __/| | | |   /  /  | | | |");
        mvprintw(17,57,"| |    | |   |   \\ | | | |  /  /   | |_| |");
        mvprintw(18,57,"||    ||    \\||| || /|   \\_, |");
        mvprintw(19,57,"                                     __/ |");                                  
        mvprintw(20,57,"                                    |_/ ");                           

        mvprintw(24,30,"HOW TO PLAY :");
        mvprintw(25,30,"1. MOVE WITH WASD KEYS");
        mvprintw(26,30,"2. COLLECT THE @");
        mvprintw(27,30,"3. DON'T HIT THE WALL!");                             
}

void Input()                    
{
    int ch = getch(); 

    switch (ch)                         
    {                                    
    case 'a':                             
        if (arah != KANAN)  
            arah = KIRI;
        break;
    case 'd':
        if (arah != KIRI) 
            arah = KANAN;
        break;
    case 'w':
        if (arah != BAWAH) 
            arah = ATAS;
        break;
    case 's':
        if (arah != ATAS)  
            arah = BAWAH;
        break;
    default:
        break;
    }
}

void Logic()                           
{
    int prevX = posisiEkorX[0];
    int prevY = posisiEkorY[0];
    int prev2X, prev2Y;
    posisiEkorX[0] = x;                  
    posisiEkorY[0] = y;
    for (int i = 1; i < panjangEkor; i++)
    {
        prev2X = posisiEkorX[i];                     
        prev2Y = posisiEkorY[i];
        posisiEkorX[i] = prevX;
        posisiEkorY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (arah)
    {
    case KIRI:
		character = '<';                   
        x--;
        break;
    case KANAN:
    	character = '>';
        x++;
        break;
    case ATAS:
    	character = '^';
        y--;
        break;
    case BAWAH:
    	character = 'v';
        y++;
        break;
    default:
    	break;
    }
    if (x > lebar || x < 0 || y > tinggi || y < 0)   
        gameOver = true;

    for (int i = 0; i < panjangEkor; i++)
        if (posisiEkorX[i] == x && posisiEkorY[i] == y)
            gameOver = true;

    if (x == posisiBuahX && y == posisiBuahY)
    {
        srand(time(0));
        skor += 2;
        posisiBuahX = rand() % lebar;     
        posisiBuahY = rand() % tinggi;
        panjangEkor++;
    }
}

void GameOver() {
	endwin();
    system("cls");
    
 cout << " " << endl;
 cout << " " << endl;
 cout << " " << endl;
cout << "                         O000O    O=O   OO  OO OOOO    OOOOO O     O OOOO  OOOOO " << endl;
cout << "                         O       O= =O  O OO O O       O   O  O   O  O     O   O " << endl;     
cout << "                         O  0O  O=   =O O    O O```    O   O   O O   O```  Oo``` " << endl;
cout << "                         O000O O=     = O    O O000    OOOOO    0    OOOO  O  `O  " << endl;

 cout << " " << endl;
 cout << " " << endl;
	cout << "                                       Game Over! Your score was: " << skor << endl;
   	char pilih;
	cout << "                                    Apakah Ingin Bermain Lagi? : [Y/N]" << endl;
	cin >> pilih;

	if (pilih == 'Y' || pilih == 'y') {
   system("cls");
} else {
    cout << "                        Keluar dari Feeding Frenzy" << endl;
    exit(0); 
}

}

void startGame() {
    system("cls");
    cout <<"\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "			  		  Start The Game... \n";
    cout <<"			  		  Selamat Bermain Feeding Frenzy! \n";
    getch();
    Setup();
    nodelay(stdscr, TRUE);
    while (!gameOver)             
    {
        Draw();
        Input();
        Logic();
        napms(160);
    }
    GameOver();
}

int main() {
    int pil;
    bool loggedIn = false;

    system("color 3F");
    loadingawal();
    loadingAnimation();

   while (true) { 
       system("cls");

       for (int i = 1; i <= 118; i++) {
           gotoxy(i, 1);
           printf("{-->>");
           gotoxy(i, 4);
           printf("{-->>");
           gotoxy(i, 20);
           printf("{-->>");
           gotoxy(i, 24);
           printf("{-->>");
           Sleep(0.8);
       }

       for (int i = 1; i <= 24; i++) {
           gotoxy(1, i);
           printf("{-->>");
           gotoxy(112, i);
           printf("{-->>");
           Sleep(0.5);
       }

       for (int i = 4; i <= 20; i++) {
           gotoxy(40, i);
           printf("*");
           Sleep(0.5);
       }
       

gotoxy(50, 2);
       cout << "FEEDING FRENZY GAME";
       gotoxy(55, 3);
       cout << "Kelompok 7";
       gotoxy(55, 22);
       cout << "ILKOMP B";

       gotoxy(8, 6);
       cout << "1. Sign In";
       gotoxy(8, 7);
       cout << "2. Sign Up";
       gotoxy(8, 8);
       cout << "3. Play Game";
       gotoxy(8, 9);
       cout << "4. Exit";
       
       gotoxy(44, 6);
       cout << "Masukkan Pilihan Anda [1,2,3,4]: ";
       cin >> pil;
       
       switch (pil) {
            case 1:
                loggedIn = SignIn();
                break;
            case 2:
                SignUp();
                break;
            case 3:
                if (loggedIn) {
                    startGame();
                    
                } else {
                	endwin();
                    cout << "\n \n \n \n \n \n                     			        		Please Sign In to play the game. \n";
                    cin.ignore();
        			cin.get();
                }
                break;
            case 4:
            	endwin();
                cout << "\n	\n \n \n \n \n								Exiting the game. Goodbye! \n";
                cin.ignore();
        		cin.get();
                return 0;
            default:
                cout << "\n \n \n \n \n \n  										Invalid choice. Please choose between 1 and 4.\n";
                cin.ignore();
        		cin.get();
        }
    }
    
   endwin();
   return 0;
}
