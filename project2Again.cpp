#include <iostream>   
#include <cstdlib>    
#include <ctime>      
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
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

enQuestionsLevel ReadQuestionsLevel()
{
	short QustionLevel;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? \n";
		cin >> QustionLevel;
	} while (QustionLevel < 1 || QustionLevel > 4);

	return (enQuestionsLevel)QustionLevel;
}

enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?\n ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

short ReadHowManyQuestions()
{
	int Num;
	cout << "How Many Questions do you want to answer?:\n ";
	cin >> Num;
	return Num;
}

string GetOpTypeSympol(enOperationType OpType)
{
	string arrOpType[5] = { "Addation","Sub","Multiplication","Div", "Mix" };
	return arrOpType[OpType - 1];
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
   
    string arrLevel[4] = { "Easy","Meduim","Hard","Mix" };
    return arrLevel[QuestionLevel - 1];
        
}

string Operation(enOperationType OpType)
{
	
	
	switch (OpType)
	{
	case 1:
		return "+";
		break;
	case 2:
		return "-";
		break;
	case 3:
		return "*";
		break;
	default:
		return"/";
	}
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer; 
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << " \ " << Quizz.NumberOfQuestions << " ]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout <<"       " << Operation(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
    cout << "__________\n";

}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult == true)
        system("Color 2F");
    else
        system("Color 4F");
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
    for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
 
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add :
        return Number1 + Number2;
        break;
    case enOperationType::Sub :
        return Number1 - Number2;
        break;
    case enOperationType::Mult :
        return Number1 * Number2;
        break;
    case enOperationType::Div :
        return Number1 / Number2;
        break;
    }
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

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel :
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2  = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::MedLevel :
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType); 
        Question.QuestionLevel = QuestionLevel; 
        return Question; 
    }

    return Question; 
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (int Question = 0;Question < Quizz.NumberOfQuestions;Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

string GetFinalResultsText(bool Pass)
{
    if (Pass == true)
       return "Pass";
    else
        return "Fail";
}

void PrintQuizzResult(stQuizz Quizz)
{
    cout << "\n";
    cout << "    *************** E N D I N G   G A M E ***************\n\n";
    cout << "             Final Results is  " << GetFinalResultsText(Quizz.isPass)  << endl;
    cout << "\n             Number Of Questions is :" << Quizz.NumberOfQuestions  << endl;
    cout << "\n           Questions Level :" <<GetQuestionLevelText(Quizz.QuestionsLevel ) << endl;
    cout << "\n            OP Type :" << GetOpTypeSympol(Quizz.OpType )  << endl;
    cout << "\n         Number Of Right Answers is : " << Quizz.NumberOfRightAnswers  << endl;
    cout << "\n             Number Of Wrong Answers is : " << Quizz.NumberOfWrongAnswers  << endl;
    cout << "                   _____________________________________\n";
                  
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
}