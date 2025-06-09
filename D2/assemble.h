#pragma once

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
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

int run_assemble();

void delay(int ms);

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);

void runProducedCar();
void PrintProcedureCarType(int cartype);
void PrintProcedureEngine(int engine);
void PrintProcedureBrakeSystem(int brake);
void PrintProcedureSteeringSystem(int steer);

void testProducedCar();

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

