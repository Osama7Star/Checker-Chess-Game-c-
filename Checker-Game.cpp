#include<iostream>
#include<fstream>
using namespace std;


void GetFromFile();
char determinator = 'w';
char Board[9][8];
ofstream movementsFile;
fstream boardFile;

////////////////////
void InitializeBoard();
void CheckUserMovement();
void InitializingFile();
int  GetIntFromChar(char c);
char GetEnemey(char determinator);
bool TestEnd();
void Show();





int  main()
{



    movementsFile.open("haraketler.txt");
    boardFile.open("boardfile.txt");


    bool b = true;

    do {

        cout << "Enter [N] For New Game " << endl ;
        char input;
        cin >> input;

        input = tolower(input);

        switch (input)
        {
        case 'n':
        {

            InitializeBoard();

            InitializingFile();
            Show();
            CheckUserMovement();

            b = false;
            break;
        }
       

        }

    } while (b);

    movementsFile.close();
    return  0;

}





void CheckUserMovement()
{


    do {
        boardFile.open("boardfile.txt");
        cout << endl << endl << "[" << determinator << "]" << " : Please Enter Your Movement" << endl;
        string playerMovement;
        cin >> playerMovement;

        if ((playerMovement[0] == 'a' || playerMovement[0] == 'b' || playerMovement[0] == 'c' || playerMovement[0] == 'd' || playerMovement[0] == 'e' || playerMovement[0] == 'f' || playerMovement[0] == 'g' || playerMovement[0] == 'h')
            && (playerMovement[2] == 'a' || playerMovement[2] == 'b' || playerMovement[2] == 'c' || playerMovement[2] == 'd' || playerMovement[2] == 'e' || playerMovement[2] == 'f' || playerMovement[2] == 'g' || playerMovement[2] == 'h')
            && (playerMovement[1] == '1' || playerMovement[1] == '2' || playerMovement[1] == '3' || playerMovement[1] == '4' || playerMovement[1] == '5' || playerMovement[1] == '6' || playerMovement[1] == '7' || playerMovement[1] == '8')
            && (playerMovement[3] == '1' || playerMovement[3] == '2' || playerMovement[3] == '3' || playerMovement[3] == '4' || playerMovement[3] == '5' || playerMovement[3] == '6' || playerMovement[3] == '7' || playerMovement[3] == '8')
            )
        {

            int i = (int)playerMovement[1] - '0';
            i = i - 1;
            int j = GetIntFromChar(playerMovement[0]);


            // check if the source is occupied by the detrminator 

            char UppperDet;
            if (Board[i][j] == 'W')
                determinator = toupper(determinator);
            else if (Board[i][j] == 'B')

                determinator = toupper(determinator);


            if ((Board[i][j] == determinator))
            {
                int k = (int)playerMovement[3] - '0';
                k = k - 1;
                int m = GetIntFromChar(playerMovement[2]);







                if (playerMovement[0] == playerMovement[2])
                {
                    int difference = i - k;



                    if (abs(difference) == 1)
                    {


                        if (difference == 1)
                        {

                            if (Board[i - 1][j] == ' ')
                            {

                                Board[i - 1][j] = determinator;
                                Board[i][j] = ' ';



                                if ((determinator == 'b') && (k == 0))
                                {
                                    Board[i - 1][j] = 'B';
                                    determinator = 'B';

                                }

                                /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                char empty = ' ';
                                boardFile.write(&empty, 1);


                                byteSum = ((i - 1) * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);




                                movementsFile << determinator << ":" << playerMovement << endl;



                                /// change the determinator
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;
                                boardFile.close();

                            }
                        }

                        //MOVEMENT DOWN
                        else if (difference == -1)
                        {

                            if (Board[i + 1][j] == ' ')
                            {

                                Board[i + 1][j] = determinator;
                                Board[i][j] = ' ';

                                //// check if the tile changed to determinator 
                                if ((determinator == 'w') && (k == 7))
                                {
                                    Board[i + 1][j] = 'W';
                                    determinator = 'W';
                                }

                                /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);

                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                byteSum = (i + 1) * 18 + j * 2;
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();


                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;





                            }
                            else {

                            }
                        }
                        else {

                        }
                    }

                    else if (abs(difference) == 2)
                    {
                        if (difference == 2)
                        {
                            if ((Board[i - 1][j] == GetEnemey(determinator) ||
                                (Board[i - 1][j] == toupper(GetEnemey(determinator))) && (Board[i - 2][j] == ' ')))
                            {
                                Board[i - 1][j] = ' ';
                                Board[i - 2][j] = determinator;
                                Board[i][j] = ' ';


                                if ((determinator == 'b') && (k == 0))
                                {
                                    Board[i - 2][j] = 'B';
                                    determinator = 'B';
                                }

                                int byteSum = (i * 18) + (j * 2);

                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                char space = ' ';
                                byteSum = (i - 1) * 18 + j * 2;
                                boardFile.seekg(byteSum, ios::beg);
                                space = ' ';
                                boardFile.write(&space, 1);


                                space = ' ';
                                byteSum = (i - 2) * 18 + j * 2;
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();

                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;


                            }
                        }
                        else if (difference == -2)
                        {
                            if ((Board[i + 1][j] == GetEnemey(determinator)) ||
                                (Board[i + 1][j] == toupper(GetEnemey(determinator))) && (Board[i + 2][j] == ' '))
                            {
                                Board[i + 1][j] = ' '; // remove the enemey from the tile 
                                Board[i + 2][j] = determinator;
                                Board[i][j] = ' ';



                                //// check if the tile changed to determinator 
                                if ((determinator == 'w') && (k == 7))
                                {
                                    Board[i + 2][j] = 'W';
                                    determinator = 'W';
                                }



                                /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                cout << "Byte sum is " << byteSum;
                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                char space = ' ';
                                byteSum = (i + 1) * 18 + j * 2; /////2   enemy tile 
                                boardFile.seekg(byteSum, ios::beg);
                                space = ' ';
                                boardFile.write(&space, 1);


                                byteSum = (i + 2) * 18 + j * 2; /////3   new tile 
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();



                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << " The Movement is not right  ";
                    }

                    Show();
                }///


                //// THE HORIZONTAL MOVEMENT 
                else if (playerMovement[1] == playerMovement[3])
                {
                    int difference = m - j;
                    cout << "The difference is " << difference;

                    /// NORMAL MOVEMENT
                    if (abs(difference) == 1)
                    {

                        // MOVEMENT RIGHT
                        if (difference == 1)
                        {

                            if (Board[i][j + 1] == ' ')
                            {
                                cout << "Right  ";
                                Board[i][j + 1] = determinator;
                                Board[i][j] = ' ';

                                ///////////////////////////
                                 /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                char space = ' ';
                                byteSum = i * 18 + (j + 1) * 2;
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();
                                //////////////////////////

                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;

                            }
                        }

                        //MOVEMENT LEFT
                        else if (difference == -1)
                        {

                            if (Board[i][j - 1] == ' ')
                            {
                                cout << "Left";
                                Board[i][j - 1] = determinator;
                                Board[i][j] = ' ';


                                //////////////////////////////
                                 /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                byteSum = i * 18 + (j - 1) * 2;
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();
                                //////////////////////////////

                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;
                            }
                            else {
                            }
                        }
                        else {

                        }
                    }

                    // ATTACK MOVEMENT

                    else if (abs(difference) == 2)
                    {
                        //////RIGHT
                        if (difference == 2)
                        {
                            if ((Board[i][j + 1] == GetEnemey(determinator) ||
                                (Board[i][j + 1] == toupper(GetEnemey(determinator)))) &&
                                (Board[i][j + 2] == ' '))
                            {
                                Board[i][j + 1] = ' '; // remove the enemey from the tile 
                                Board[i][j + 2] = determinator;
                                Board[i][j] = ' ';

                                ///////////////////////////////////////
                                 /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                char space = ' ';
                                byteSum = (i) * 18 + (j + 1) * 2; /////2   enemy tile 
                                boardFile.seekg(byteSum, ios::beg);
                                space = ' ';
                                boardFile.write(&space, 1);


                                byteSum = (i) * 18 + (j + 2) * 2; /////3   new tile 
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();

                                //////////////////////////////////////
                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;
                                movementsFile << determinator << ":" << playerMovement << endl;

                            }
                        }
                        //////LEFT
                        else if (difference == -2)
                        {
                            if ((Board[i][j - 1] == GetEnemey(determinator) ||
                                (Board[i][j - 1] == toupper(GetEnemey(determinator)))) &&
                                (Board[i][j - 2] == ' '))
                            {
                                Board[i][j - 1] = ' '; // remove the enemey from the tile 
                                Board[i][j - 2] = determinator;
                                Board[i][j] = ' ';


                                /////////////////////////
                                ///////////////////////////////////////
                                 /////UPDAT THE FILE 
                                int byteSum = (i * 18) + (j * 2);
                                boardFile.seekg(byteSum, ios::beg);
                                char c[1];
                                char empty = ' ';
                                boardFile.write(&empty, 1);

                                char space = ' ';
                                byteSum = (i) * 18 + (j - 1) * 2; /////2   enemy tile 
                                boardFile.seekg(byteSum, ios::beg);
                                space = ' ';
                                boardFile.write(&space, 1);


                                byteSum = (i) * 18 + (j - 2) * 2; /////3   new tile 
                                boardFile.seekg(byteSum, ios::beg);
                                boardFile.write(&determinator, 1);

                                boardFile.close();

                                //////////////////////////////////////
                                ////////////////////////
                                // change the determinator 
                                determinator = GetEnemey(determinator);
                                Board[8][0] = determinator;

                                movementsFile << determinator << ":" << playerMovement << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << " The Movement is not True ";
                    }

                    Show();
                }
                else
                {
                    cout << "The Movement Not True";
                }



            }

            else
            {
                cout << "The Tile not occupied by [" << determinator << "],Please Enter Movement Again";
            }
        }


        else
        {
            cout << "Loation out of the board  , Enter the movement again ";
        }

        boardFile.open("boardfile.txt");
        boardFile.seekg(144, ios::beg);


        boardFile.write(&determinator, 1);


        boardFile.close();

    } while (TestEnd());


}



///HERE WE INITIALIZE GAME BOARD
void InitializeBoard()
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Board[i][j] = ' ';
        }
    }

    char B = 'w'; char A = 'b';

    Board[1][0] = B; Board[1][1] = B; Board[1][2] = B; Board[1][3] = B; Board[1][4] = B; Board[1][5] = B; Board[1][6] = B; Board[1][7] = B;
    Board[2][0] = B; Board[2][1] = B; Board[2][2] = B; Board[2][3] = B; Board[2][4] = B; Board[2][5] = B; Board[2][6] = B; Board[2][7] = B;

    Board[5][0] = A; Board[5][1] = A; Board[5][2] = A; Board[5][3] = A; Board[5][4] = A; Board[5][5] = A; Board[5][6] = A; Board[5][7] = A;
    Board[6][0] = A; Board[6][1] = A; Board[6][2] = A; Board[6][3] = A; Board[6][4] = A; Board[6][5] = A; Board[6][6] = A; Board[6][7] = A;

    Board[8][0] = determinator;
}

int  GetIntFromChar(char x)
{
    if (x == 'a')
        return 0;
    else if (x == 'b')
        return 1;
    else if (x == 'c')
        return 2;
    else if (x == 'd')
        return 3;
    else if (x == 'e')
        return 4;
    else if (x == 'f')
        return 5;
    else if (x == 'g')
        return 6;
    else if (x == 'h')
        return 7;


}


char GetEnemey(char det) {

    if ((det == 'w') || (det == 'W'))
        return 'b';
    else
        return 'w';
}



bool TestEnd()
{

    int white = 0, black = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            if (Board[i][j] == 'w')
                white++;
            else if (Board[i][j] == 'b')
                black++;

        }
    }

    if ((white == 0) || (black == 0))
        return  false;
    else
        return true;
}

void Show()
{
    int i;
    for (i = 0; i < 9; i++)
    {
        cout << "   _______________________________ " << endl;
        cout << i + 1 << " | " << Board[i][0] << " | " << Board[i][1] << " | " << Board[i][2] << " | " << Board[i][3] << " | " << Board[i][4] << " | " << Board[i][5] << " | " << Board[i][6] << " | " << Board[i][7] << " |" << endl;
    }
    cout << "   _______________________________ " << endl;
    cout << "    A   B   C   D   E   F   G   H  " << endl;
}



void InitializingFile()
{

    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            // boardFile >>"Hello World " ;
            boardFile.write((char*)&Board[i][j], sizeof(char)) << ' ';
            /* char space = '\t';
            boardFile.write((char*)&space, sizeof(char));
            */



        }
        char n = '\n';

        boardFile.write((char*)&n, sizeof(char));


    }
    boardFile.close();
}


void GetFromFile()
{

    boardFile.open("boardfile.txt");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char c = ' ';
            boardFile.seekg(((i * 18) + (j * 2)), ios::beg);
            boardFile.read(&c, 1);
            Board[i][j] = c;
            cout << c << endl;
        }
        cout << endl;
    }
}