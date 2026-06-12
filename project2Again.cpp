#include <iostream>   
#include <cstdlib>    
#include <ctime>      
#include <string>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? \n";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?\n";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

short ReadHowManyQuestions()
{
    short Num;
    do 
    {
        cout << "How Many Questions do you want to answer? (1 to 100):\n";
        cin >> Num;
    } while (Num < 1 || Num > 100);
    return Num;
}

string GetOpTypeSymbol(enOperationType OpType)
{
    string arrOpType[5] = { "Addition", "Sub", "Multiplication", "Div", "Mix" };
    return arrOpType[OpType - 1];
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrLevel[4] = { "Easy", "Medium", "Hard", "Mix" };
    return arrLevel[QuestionLevel - 1];
}

string GetOperationSymbolText(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;
    default:
        return 0;
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer; 
}

void PrintTheQuestion(const stQuizz& Quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << " / " << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << "       " << GetOperationSymbolText(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
    cout << "__________\n";
}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult)
        system("Color 2F"); // Green
    else
        system("Color 4F"); // Red
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        cout << "Correct!\n";
        Quizz.NumberOfRightAnswers++;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        cout << "Wrong! Correct Answer is : " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
        Quizz.NumberOfWrongAnswers++;
    }
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = (enOperationType)RandomNumber(1, 4);
    }

    Question.OperationType = OpType;
    Question.QuestionLevel = QuestionLevel;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    default:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    }

    // حماية إضافية لعملية القسمة: منع ظهور الصفر في الرقم الثاني، وضمان أن البسط يقبل القسمة بدون كسور
    if (Question.OperationType == enOperationType::Div)
    {
        if (Question.Number2 == 0) Question.Number2 = 2;
        // تعديل الرقم الأول ليصبح ناتج ضرب الرقمين، لضمان خروج ناتج القسمة كعدد صحيح دائماً
        Question.Number1 = Question.Number1 * Question.Number2;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question; 
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

string GetFinalResultsText(bool Pass)
{
    return (Pass) ? "Pass" : "Fail";
}

void PrintQuizzResult(const stQuizz& Quizz)
{
    cout << "\n";
    cout << "    *************** E N D I N G   G A M E ***************\n\n";
    cout << "             Final Results is  " << GetFinalResultsText(Quizz.isPass) << endl;
    cout << "\n             Number Of Questions is : " << Quizz.NumberOfQuestions << endl;
    cout << "\n           Questions Level : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "\n            OP Type : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "\n         Number Of Right Answers is : " << Quizz.NumberOfRightAnswers << endl;
    cout << "\n             Number Of Wrong Answers is : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "                    _____________________________________\n";
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz); 

    AskAndCorrectQuestionListAnswers(Quizz);

    PrintQuizzResult(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartTheGame()
{
    char PlayAgain;
    do
    {
        ResetScreen(); 
        PlayMathGame();

        cout << "Do you want to play again? [Y , N ] :\n";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));  
    StartTheGame();
    return 0;
}
