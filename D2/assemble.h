#pragma once

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum InputValidationResult
{
    Valid,
    Invalid,
};

enum MenuTranstion
{
    StartPoint,
    Forward,
    Backward
};

void delay(int ms);

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);

void SelectCarAndParts(QuestionType step, int answer);
void MenuNormalTransition(QuestionType& step);
void ProducedCar(int answer);
MenuTranstion InputCheckForMenuTransition(int answer, QuestionType& step);

InputValidationResult InputVaildation(char* buf, QuestionType& step, int& answer);
void UserInputAndRemoveLF(char  buf[100]);
bool IsExit(char buf[100]);

void PrintMenuByStep(int step);
void PrintSelectRunTest();
void PrintSelectSteerType();
void PrintSelectBrakeType();
void PrintSelectEngineType();
void PrintSelectCarType();

#ifdef NDEBUG
int run_assemble();
#endif