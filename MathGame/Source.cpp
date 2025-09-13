#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

// Enum for question difficulty level
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, QL_Mix = 4 };

// Enum for operation type
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, OT_Mix = 5 };

// Struct to hold question numbers and operator
struct stQuestionElements {
    short num1;
    short num2;
    char arithmeticOperator;
};

// Struct to hold final results
struct stFinalResults {
    short questionsNum;
    enQuestionLevel quesLevel;
    enOperationType operType;
    short numOfRightAnswers;
    short numOfWrongAnswers;
};

// Generate a random number between two numbers
short randomNum(short from, short to) {
    return rand() % (to - from + 1) + from;
}

// Ask user how many questions to solve
void numOfQuestions(stFinalResults& finalResults) {
    cout << "How many questions do you want to answer? ";
    cin >> finalResults.questionsNum;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter a valid one : ";
        cin >> finalResults.questionsNum;
    }
}

// Ask user for question difficulty level
enQuestionLevel questionLevel(stFinalResults& finalResults) {
    short quesLevel;
    cout << "Enter question level [1]Easy, [2]Med, [3]Hard, [4]Mix : ";
    cin >> quesLevel;
    while (cin.fail() || quesLevel < 1 || quesLevel > 4) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter 1, 2, 3 or 4 : ";
        cin >> quesLevel;
    }

    finalResults.quesLevel = static_cast<enQuestionLevel>(quesLevel);
    return static_cast<enQuestionLevel>(quesLevel);
}

// Generate and print question numbers based on difficulty
void printQuestionNums(enQuestionLevel quesLevel, stQuestionElements& quesElements) {
    int from = 1, to = 9;

    if (quesLevel == enQuestionLevel::QL_Mix)
        quesLevel = static_cast<enQuestionLevel>(randomNum(1, 3));

    if (quesLevel == enQuestionLevel::Med) { from = 10; to = 50; }
    else if (quesLevel == enQuestionLevel::Hard) { from = 51; to = 99; }

    quesElements.num1 = randomNum(from, to);
    quesElements.num2 = randomNum(from, to);

    cout << quesElements.num1 << '\n' << quesElements.num2;
}

// Ask user for operation type
enOperationType operationType(stFinalResults& finalResults) {
    short operType;

    cout << "Enter operation type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix : ";
    cin >> operType;
    while (cin.fail() || operType < 1 || operType > 5) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid choice, Enter 1, 2, 3, 4 or 5 : ";
        cin >> operType;
    }

    finalResults.operType = static_cast<enOperationType>(operType);
    return static_cast<enOperationType>(operType);
}

// Pick random operator if Mix was chosen
enOperationType returnArithmeticOperator(enOperationType& operType) {
    if (operType == enOperationType::OT_Mix)
        operType = static_cast<enOperationType>(randomNum(1, 4));

    return operType;
}

// Print the arithmetic operator
void printArithmeticOperators(enOperationType arithmeticOperato) {
    switch (arithmeticOperato) {
    case enOperationType::Add: cout << " +"; break;
    case enOperationType::Sub: cout << " -"; break;
    case enOperationType::Mul: cout << " *"; break;
    case enOperationType::Div: cout << " /"; break;
    }
}

// Return the correct answer for a given question
short returnResult(enOperationType arithmeticOperato, const stQuestionElements& quesElements) {
    short result = 0;

    switch (arithmeticOperato) {
    case enOperationType::Add: result = quesElements.num1 + quesElements.num2; break;
    case enOperationType::Sub: result = quesElements.num1 - quesElements.num2; break;
    case enOperationType::Mul: result = quesElements.num1 * quesElements.num2; break;
    case enOperationType::Div: result = quesElements.num1 / quesElements.num2; break;
    }

    return result;
}

// Show result of a single question
void showResult(short enteredResult, enOperationType arithmeticOperator,
                const stQuestionElements& quesElements, stFinalResults& finalResults) {

    if (enteredResult == returnResult(arithmeticOperator, quesElements))
    {
        finalResults.numOfRightAnswers++;
        system("color 2F");
        cout << "Right Answer :-)" << endl;
    }
    else 
    {
        finalResults.numOfWrongAnswers++;
        system("color 4F");
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is: " << returnResult(arithmeticOperator, quesElements) << endl;
    }
}

// Print a single question
void printQuestion(short currentQuesNum, short numOfQues, enQuestionLevel quesLevel,
                   enOperationType operType, stQuestionElements& quesElements, stFinalResults& finalResults) {

    short enteredResult;
    enOperationType arithmeticOperator = returnArithmeticOperator(operType);

    cout << "\nQuestion [" << currentQuesNum << '/' << numOfQues << "]\n\n";
    printQuestionNums(quesLevel, quesElements);
    printArithmeticOperators(arithmeticOperator);
    cout << "\n_________________\n";
    cin >> enteredResult;

    showResult(enteredResult, arithmeticOperator, quesElements, finalResults);
}

// Print all questions
void printQuestions(stFinalResults& finalResults) {
    stQuestionElements quesElements{};
    numOfQuestions(finalResults);
    short numOfQues = finalResults.questionsNum;

    enQuestionLevel quesLevel = questionLevel(finalResults);
    enOperationType operType = operationType(finalResults);

    for (int i = 1; i <= numOfQues; i++) {
        printQuestion(i, numOfQues, quesLevel, operType, quesElements, finalResults);
    }

    cout << "\nPress any key to go to Final Results Screen...";
    system("pause>0");
}

// Print final results
void printFinalResults(const stFinalResults& finalResults) {
    system("cls");
    system("color 07");

    cout << "__________________________________\n\n";
    cout << "Final Results Is ";
    (finalResults.numOfRightAnswers >= finalResults.numOfWrongAnswers) ?
        cout << "Pass :-)" : cout << "Fail :-(";
    cout << "\n__________________________________\n\n";

    cout << "Number of Questions    : " << finalResults.questionsNum << "\n";
    cout << "Questions Level        : ";
    switch (finalResults.quesLevel) {
    case enQuestionLevel::Easy:   cout << "Easy\n"; break;
    case enQuestionLevel::Med:    cout << "Med\n";  break;
    case enQuestionLevel::Hard:   cout << "Hard\n"; break;
    case enQuestionLevel::QL_Mix: cout << "Mix\n";  break;
    }

    cout << "Operation Type         : ";
    switch (finalResults.operType) {
    case enOperationType::Add:    cout << "+\n";   break;
    case enOperationType::Sub:    cout << "-\n";   break;
    case enOperationType::Mul:    cout << "*\n";   break;
    case enOperationType::Div:    cout << "/\n";   break;
    case enOperationType::OT_Mix: cout << "Mix\n"; break;
    }

    cout << "Number of Right Answers: " << finalResults.numOfRightAnswers << "\n";
    cout << "Number of Wrong Answers: " << finalResults.numOfWrongAnswers << "\n";
    cout << "\n\n__________________________________\n" << endl;
}

// Main math game loop
void MathGame() {
    srand((unsigned)time(NULL));
    stFinalResults finalResults;
    char playAgain;

    do {
        finalResults = {};
        printQuestions(finalResults);
        printFinalResults(finalResults);

        cout << "Do you want to play again? Y/N? ";
        cin >> playAgain;
        while (toupper(playAgain) != 'Y' && toupper(playAgain) != 'N') {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, please enter Y or N: ";
            cin >> playAgain;
        }
    } while (toupper(playAgain) == 'Y');
}

int main() {
    MathGame();
}
