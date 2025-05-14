#include <iostream>
#include <cstdlib>
using namespace std;

// data

enum enlevel { easy = 1, medium, hard, insane, MixOfNumbers };

enum enoptype { add = 1, Subtract, Multiply, Divide, MixOfOpTypes };

struct stquastion
{
    int num1;
    int num2;
    enlevel level;
    char optype;
    int true_answare;
    int player_answer;
};

struct stgame
{
    stquastion quastion[100];
    short q_number;
    enlevel q_level;
    enoptype q_optype;
    short current_quastion;
    short total_righr_answare = 0 ;
    short total_wrong_answare = 0 ;
    bool final_result;
};


// general

int ReadDecision()
{
    int number;
    do
    {
        cout << "Do you want to play again ? 1(play) / 0(exit) : ";
        cin >> number;
    } while (number < 0 || number > 1);
    return number;
}

int ReadAnswareFromPlayer()
{
    int number;
    cin >> number;
    return number;
}

int ReadHowManyQuastion()
{
    int number;
    do
    {
        cout << "How many question you want to answer (minimum 1 , max 100) ? ";
        cin >> number;
    } while (number < 1 || number > 100);
    return number;
}

enlevel ReadQuastionLevel()
{
    int number;
    do
    {
        cout << "Enter quastions level [1] Easy, [2] Medium, [3] Hard, [4] Insane, [5] Mix ? ";
        cin >> number;
    } while (number < 1 || number > 5);
    return (enlevel)number;
}

enoptype ReadOpType()
{
    int number;
    do
    {
        cout << "Enter operation type [1] Add, [2] Subtract, [3] Multiply, [4] Divide, [5] Mix ? ";
        cin >> number;
    } while (number < 1 || number > 5);
    return (enoptype)number;
}

int RandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

string GetFinalResultText(stgame game)
{
    if (game.final_result)
        return "Pass";
    else
        return "Fail";
}

string enLevelToString(stgame game)
{
    string levelarray[5] = { "easy" , "medium", "hard", "insane", "mix" };
    return levelarray[game.q_level - 1];
}

string enOptypeToString(stgame game)
{
    string optypearray[5] = { "(+)", "(-)", "(*)", "(/)", "(+, -, *, /)" };
    return optypearray[game.q_optype - 1];
}

void ResetScreenToBlack()
{
    system("color 0f");
    system("cls");
}

void PaintConsle(stgame game)
{
    if (game.final_result)
        system("color 2f");
    else
        system("color 4f");
}


// print

void PrintQuastion(stgame game)
{
    cout << "\n\nQuastion [" << game.current_quastion + 1 << "/" << game.q_number << "]" << endl
         << game.quastion[game.current_quastion].num1 << endl
         << game.quastion[game.current_quastion].num2 << " " 
         << game.quastion[game.current_quastion].optype << endl
         << "----------\n";
}

void PrintGameResult(stgame game)
{
    cout << "\n\nExam has end\nPress enter to show game result\n";
    cin.ignore();
    cin.get();

    PaintConsle(game);
    cout << "\n\n---------------------------------------" << endl;
    cout << "Final result is " << GetFinalResultText(game) << endl;
    cout << "---------------------------------------" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Number of quastions     : " << game.q_number << endl;
    cout << "Quastions level         : " << enLevelToString(game) << endl;
    cout << "Optype                  : " << enOptypeToString(game) << endl;
    cout << "Number of right answare : " << game.total_righr_answare << endl;
    cout << "Number of wrong answare : " << game.total_wrong_answare << endl;
    cout << "---------------------------------------\n\n" << endl;
}


// process

void DoWrongAnswareThings(stgame& game)
{
    system("color 4f");
    cout << "wrong answare\nthe right answare is " << game.quastion[game.current_quastion].true_answare;
    game.total_wrong_answare++;
}

void DoRightAnswareThings(stgame& game)
{
    system("color 2f");
    cout << "right answare";
    game.total_righr_answare++;
}

bool CheckeIfAnswareTrue(stgame game)
{
    return game.quastion[game.current_quastion].true_answare == game.quastion[game.current_quastion].player_answer;
}

void correctAnswer(stgame& game)
{
    if (CheckeIfAnswareTrue(game))
        DoRightAnswareThings(game);
    else
        DoWrongAnswareThings(game);
}

void ReadAndCheckAllQuastions(stgame& game)
{
    for (int i = 0; i <= game.q_number - 1; i++)
    {
        game.current_quastion = i;

        PrintQuastion(game);

        game.quastion[i].player_answer = ReadAnswareFromPlayer();

        correctAnswer(game);
    }
    game.final_result = (game.total_righr_answare >= game.total_wrong_answare);
}

int TrueAnsware(stquastion quastion)
{
    switch (quastion.optype)
    {
    case('+'):
        return quastion.num1 + quastion.num2;
    case('-'):
        return quastion.num1 - quastion.num2;
    case('*'):
        return quastion.num1 * quastion.num2;
    case('/'):
        return quastion.num1 / quastion.num2;
    }
}

int GetOpType(stquastion quastion)
{
    switch (quastion.optype)
    {
    case(add):
        return '+';
    case(Subtract):
        return '-';
    case(Multiply):
        return '*';
    case(Divide):
        return '/';
    }
}

int GetNumber(stquastion quastion)
{
    switch (quastion.level)
    {
    case(easy):
        return RandomNumber(1, 10);
    case(medium):
        return RandomNumber(10, 20);
    case(hard):
        return RandomNumber(20, 50);
    case(insane):
        return RandomNumber(50, 100);
    }
}

stquastion GenerateQuastion(stgame game)
{
    stquastion quastion;

    if (game.q_level == enlevel::MixOfNumbers)
        game.q_level = (enlevel)RandomNumber(1, 4);
    quastion.level = game.q_level;

    quastion.num1 = GetNumber(quastion);
    quastion.num2 = GetNumber(quastion);

    if (game.q_optype == enoptype::MixOfOpTypes)
        game.q_optype = (enoptype)RandomNumber(1, 4);
    quastion.optype = game.q_optype;

    quastion.optype = GetOpType(quastion);

    quastion.true_answare = TrueAnsware(quastion);

    return quastion;
}

void GenerateAllQuastions(stgame& game)
{
    for (int i = 0; i <= game.q_number - 1; i++)
        game.quastion[i] = GenerateQuastion(game);
}

void ReadGameInfoFromUser(stgame& game)
{
    game.q_number = ReadHowManyQuastion();
    game.q_level = ReadQuastionLevel();
    game.q_optype = ReadOpType();
}

void StartGame()
{
    stgame game;

    ReadGameInfoFromUser(game);

    GenerateAllQuastions(game);

    ReadAndCheckAllQuastions(game);

    PrintGameResult(game);
}


// main

void StartMainGame()
{
    short decision;
    do
    {
        ResetScreenToBlack();
        StartGame();
        decision = ReadDecision();
    } while (decision);
}

int main()
{
    srand((unsigned)time(NULL));
    StartMainGame();
    return 0;
}
