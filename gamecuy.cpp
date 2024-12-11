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
	
	mvprintw(0,39," ______                _  _                ");                              
    mvprintw(1,39,"|  ____|              | |(_)               ");
    mvprintw(2,39,"| |                   | |                  ");
    mvprintw(3,39,"| |__   ___   ___   __| | _  _ __    __ _  ");
    mvprintw(4,39,"|  __| / _ \\ / _ \\ / _` || || '_ \\  / _` | ");
    mvprintw(5,39,"| |   |  __/|  __/| (_| || || | | || (_| | ");
    mvprintw(6,39,"|_|    \\___| \\___| \\__,_||_||_| |_| \\__  | ");
    mvprintw(7,39,"                                    __/  | ");                                  
    mvprintw(8,39,"                                   |____/  ");
	
	mvprintw(9, 40, "****************************************");
	
	for (int i = 10; i <= 18; i++) {
    mvprintw(i, 40, "*");
    mvprintw(i, 79, "*");
}

	mvprintw(12, 50, "     LOGGED IN...   ");
	mvprintw(13, 50, " ------------------ ");
	mvprintw(14, 50, "|                  |");
	mvprintw(15, 50, " ------------------ ");
	
	mvprintw(19, 40, "****************************************");
	
	mvprintw(20,39," ______                              ");                              
    mvprintw(21,39,"|  ____|                             ");
    mvprintw(22,39,"| |     _ __   ___  _ __     _____  _   _ ");
    mvprintw(23,39,"| |__  | '__| / _ \\| '_ \\   |_   / | | | |");
    mvprintw(24,39,"|  __| | |   |  __/| | | |   /  /  | | | |");
    mvprintw(25,39,"| |    | |   |   \\ | | | |  /  /   | |_| |");
    mvprintw(26,39,"|_|    |_|    \\___||_| |_| /____|   \\__, |");
    mvprintw(27,39,"                                     __/ |");                                  
    mvprintw(28,39,"                                    |___/ ");     
		
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
    gotoxy(40, 9);
	cout << "****************************************";
	
	for (int i = 10; i <= 18; i++) {
    gotoxy(40, i);
	cout << "*";
    gotoxy(79, i);
	cout << "*";
}
	gotoxy(40,19);
	cout << "****************************************";

    gotoxy(56,11);
    cout << "SIGN UP" << endl;
    gotoxy(45,14);
    cout << "Enter Username : ";
    cin >> username;
    gotoxy(45,15);
    cout << "Enter Password : ";
    cin >> password;
    cout << endl;
    
    gotoxy(40,19);
	cout << "****************************************";

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
	
	gotoxy(50,17);
    cout <<"Sign Up Successful!" << endl;
    cin.ignore();
    cin.get();
}

bool SignIn() {
    ifstream myFile;
    string username, password, fileUsername, filePassword;
    bool exist = false;

    system("cls");
    gotoxy(40, 9);
	cout << "****************************************";
	
	for (int i = 10; i <= 18; i++) {
    gotoxy(40, i);
	cout << "*";
    gotoxy(79, i);
	cout << "*";
}
	gotoxy(40,19);
	cout << "****************************************";

    gotoxy(56,11);
    cout << "SIGN IN" << endl;
    gotoxy(45,14);
    cout << "Enter Username : ";
    cin >> username;
    gotoxy(45,15);
    cout << "Enter Password : ";
    cin >> password;
    cout << endl;

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
    	gotoxy(50,17);
        cout << "Sign In Successful!" << endl;
        cin.ignore();
        cin.get();
        return true;
    } else {
    	gotoxy(47,17);
        cout << "Sign In Failed! Try Again." << endl;
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
    double frequency = 4;

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
        cout << "WELCOME TO OUR GAME";

        Sleep(5);
    }
}

void Setup()                     
{
    gameOver = false;
    arah = BERHENTI;
    x = lebar / 2;
    y = tinggi / 2;
    posisiBuahX = (rand() % (lebar - 2)) + 1;  
    posisiBuahY = (rand() % (tinggi - 2)) + 1;
    skor = 0;
    panjangEkor = 0;
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
    for (int i = 0; i < lebar + 1; i++)
    printw("#");
    printw("\n\n SCORE : %d\n", skor);   

        mvprintw(24,15,"W = UP");
        mvprintw(25,15,"A = LEFT");     
        mvprintw(26,15,"S = DOWN");
        mvprintw(27,15,"D = RIGHT");
        
        mvprintw(2,57," ______                _  _                ");                              
        mvprintw(3,57,"|  ____|              | |(_)               ");
        mvprintw(4,57,"| |                   | |                  ");
        mvprintw(5,57,"| |__   ___   ___   __| | _  _ __    __ _  ");
        mvprintw(6,57,"|  __| / _ \\ / _ \\ / _` || || '_ \\  / _` | ");
        mvprintw(7,57,"| |   |  __/|  __/| (_| || || | | || (_| | ");
        mvprintw(8,57,"|_|    \\___| \\___| \\__,_||_||_| |_| \\__  | ");
        mvprintw(9,57,"                                    __/  | ");                                  
        mvprintw(10,57,"                                   |____/  ");     
		mvprintw(12,57," ______                              ");                              
        mvprintw(13,57,"|  ____|                             ");
        mvprintw(14,57,"| |     _ __   ___  _ __     _____  _   _ ");
        mvprintw(15,57,"| |__  | '__| / _ \\| '_ \\   |_   / | | | |");
        mvprintw(16,57,"|  __| | |   |  __/| | | |   /  /  | | | |");
        mvprintw(17,57,"| |    | |   |   \\ | | | |  /  /   | |_| |");
        mvprintw(18,57,"|_|    |_|    \\___||_| |_| /____|   \\__, |");
        mvprintw(19,57,"                                     __/ |");                                  
        mvprintw(20,57,"                                    |___/ ");                         

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
    if (x >= lebar -1 || x < 0 || y >= tinggi-1 || y < 0)   
        gameOver = true;

    for (int i = 0; i < panjangEkor; i++)
        if (posisiEkorX[i] == x && posisiEkorY[i] == y)
            gameOver = true;

    if (x == posisiBuahX && y == posisiBuahY)
    {
        srand(time(0));
        skor += 2;
        posisiBuahX = (rand() % (lebar - 2)) + 1;     
        posisiBuahY = (rand() % (tinggi - 2)) + 1;
        panjangEkor++;
    }
}

void ending(){
	endwin();
	system("cls");
	gotoxy(30, 9);
	cout << "***********************************************************";

	for (int i = 10; i <= 15; i++) {
    gotoxy(30, i);
	cout << "*";
    gotoxy(88, i);
	cout << "*";
}
	gotoxy(30,15);
	cout << "***********************************************************";
	
	gotoxy(33,12);
	cout << "Keluar dari Feeding Freenzy, Hope You Always Happy :D" << endl;
	gotoxy(33,18);
	exit(0);
}

void GameOver() {
	endwin();
    system("cls");
    
    cout << endl << endl;
	cout <<"	       GGGGGGGGGGGGGG            aaaaaa          mmmmmm   mmmmmm   mmmmmm     eeeeeeeeeeeeee        "<<endl;
	cout <<"	     G::::::::::::::G           a::::::a         m:::::m::::::::::m:::::m    e::::::::::::::ee      "<<endl;
	cout <<"	    G::::GGGGGGGGGGGG          a::::::::a        m::::m m::::::::m m::::m   e::::::eeeee:::::ee     "<<endl;
	cout <<"  	   G:::::G                    a::::::::::a       m::::m  m::::::m  m::::m  e::::::e     e:::::e     "<<endl;
	cout <<"          G::::G                     a:::::aa:::::a      m::::m   m::::m   m::::m  e:::::::eeeee::::::e     "<<endl;
	cout <<"	  G:::::G    GGGGGGGGGGGG   a::::a    a::::a     m::::m   m::::m   m::::m  e:::::::eeeeeeeeeee      "<<endl;
	cout <<"	   G::::G       G::::::G   a:::::a    a:::::a    m::::m   m::::m   m::::m  e::::::e                 "<<endl;
	cout <<"	    GG:::GGGGGGGG:::::G   a:::::::aaaa:::::::a   m::::m   m::::m   m::::m  e::::::::eeeeeeee        "<<endl;
	cout <<"	     GGGG::::::::::::G   a::::::aa    aa::::::a  m::::m   m::::m   m::::m   ee:::::::::::::::e      "<<endl;
	cout <<"	       GGGGGGGGGGGGGG    aaaaaaaa      aaaaaaaa  mmmmmm   mmmmmm   mmmmmm     eeeeeeeeeeeeeee       "<<endl;
	cout <<"              																		              "<<endl;
	cout <<" 	       ooooooooooo     vvvvvv           vvvvvv        eeeeeeeeeeee         rrrrr   rrrrrrrrr       "<<endl;
	cout <<" 	     oo:::::::::::oo   v:::::v         v:::::v     ee::::::::::::ee        r::::rrr:::::::::r      "<<endl;
	cout <<"	     o:::::::::::::::o   v:::::v       v:::::v     e::::::eeeee:::::ee      r:::::::::::::::::r     "<<endl;
	cout <<"	     o:::::ooooo:::::o    v:::::v     v:::::v     e::::::e     e:::::e      rr:::::rrrrr::::::r     "<<endl;
	cout <<"	     o::::o     o::::o     v:::::v   v:::::v      e:::::::eeeee::::::e      r:::::r     rrrrrr      "<<endl;
	cout <<"	     o::::o     o::::o      v:::::v v:::::v       e::::::eeeeeeeeeeee       r:::::r                 "<<endl;                                                                            
	cout <<"	     o:::::ooooo:::::o       v:::::v:::::v        e:::::e                   r:::::r                 "<<endl;                                                                           
	cout <<"	     o:::::::::::::::o        v:::::::::v         e::::::::eeeeeeee         r:::::r                   "<<endl;                                                                                
	cout <<"	      oo:::::::::::oo          v:::::::v           ee::::::::::::::e        r:::::r                   "<<endl;                                                                              
	cout <<"	        ooooooooooo             vvvvvvv              eeeeeeeeeeeeee         rrrrrrr                   "<<endl;   
 	
 	gotoxy(45,26);
	cout << "Game Over! Your score was: " << skor << endl;
   	char pilih;
   	gotoxy(45,28);
	cout << "Apakah Ingin Bermain Lagi? [Y/N] : ";
	cin >> pilih;

	if (pilih == 'Y' || pilih == 'y') {
	    Setup();
   	
	} else {
        ending();
	}
}

void startGame() {
    system("cls");
    gotoxy(40, 9);
	cout << "****************************************";
	
	for (int i = 10; i <= 18; i++) {
    gotoxy(40, i);
	cout << "*";
    gotoxy(79, i);
	cout << "*";
}
	gotoxy(40,19);
	cout << "****************************************";
	
    gotoxy(45,14);
    cout <<"Starting The Feeding Frenzy...";
    gotoxy(43,15);
    cout <<"Hope You Enjoy The Game & Be Happy!";
    getch();
    Setup();
    while (!gameOver)             
    {
        Draw();
        Input();
        Logic();
    }
    GameOver();
}

int main() {
    int pil;
    bool loggedIn = false;

    system("color 3F");
    loadingawal();
// 	loadingAnimation();

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
                	gotoxy(44,6);
                    cout << "Please Sign In to able playing the game.";
                    cin.ignore();
        			cin.get();
                }
                break;
            case 4:
            	endwin();
            	gotoxy(44,6);
                cout << "Exiting the game. Thankyou for playing our game:) !";
                cin.ignore();
        		cin.get();
                return 0;
            default:
            	gotoxy(44,6);
                cout << "Pilihan Tidak Ada. Silahkan Pilih antara 1 sampai 4.";
                cin.ignore();
        		cin.get();
        }
    }
    
   endwin();
   return 0;
}
