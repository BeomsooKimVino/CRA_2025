#include "assemble.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stack[10];

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int run_assemble()
{
    char buf[100];
    QuestionType step = CarType_Q;

    while (1)
    {
        PrintMenuByStep(step);
        UserInputAndRemoveLF(buf);

        if (IsExit(buf))
        {
            printf("바이바이\n");
            break;
        }

        int answer;
        if (InputVaildation(buf, step, answer) != InputValidationResult::Valid)
            continue;
        if (InputCheckForMenuTransition(answer, step) != MenuTranstion::Forward)
            continue;

        if (step != Run_Test)
        {
            SelectCarAndParts(step, answer);
            MenuNormalTransition(step);
        }
        else if (step == Run_Test)
        {
            ProducedCar(answer);
        }
    }
    return 0;
}

void SelectCarAndParts(QuestionType step, int answer)
{
    switch (step)
    {
        case CarType_Q: selectCarType(answer); break;
        case Engine_Q: selectEngine(answer); break;
        case brakeSystem_Q: selectbrakeSystem(answer); break;
        case SteeringSystem_Q: selectSteeringSystem(answer); break;
    }
    delay(800);
}

void MenuNormalTransition(QuestionType& step)
{
    switch (step)
    {
        case CarType_Q: step = Engine_Q; break;
        case Engine_Q: step = brakeSystem_Q; break;
        case brakeSystem_Q: step = SteeringSystem_Q; break;
        case SteeringSystem_Q: step = Run_Test; break;
    }
}

void ProducedCar(int answer)
{
    if (answer == 1)
    {
        runProducedCar();
    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
    }
    delay(2000);
}

int isValidCheckCarTypeAndEachParts()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }

    return true;
}

void runProducedCar()
{
    if (isValidCheckCarTypeAndEachParts() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            PrintProcedureCarType(stack[QuestionType::CarType_Q]);
            PrintProcedureEngine(stack[QuestionType::Engine_Q]);
            PrintProcedureBrakeSystem(stack[QuestionType::brakeSystem_Q]);
            PrintProcedureSteeringSystem(stack[QuestionType::SteeringSystem_Q]);
            printf("자동차가 동작됩니다.\n");
        }
    }
}

void PrintProcedureCarType(int cartype)
{
    char cartypeStr[4][20] = {"", "Sedan", "SUV", "Truck" };
    if (cartype >= 0 && cartype <=  3)
        printf("Car Type : %s\n", cartypeStr[cartype]);
    else
        printf("Car Type : Invalid Input(%d)\n", cartype);
}

void PrintProcedureEngine(int engine)
{
    char engineStr[4][20] = { "", "GM", "TOYOTA", "WIA" };
    if (engine >= 0 && engine <= 3)
        printf("Engine : %s\n", engineStr[engine]);
    else
        printf("Engine : Invalid Input(%d)\n", engine);
}

void PrintProcedureBrakeSystem(int brake)
{
    char brakeStr[4][20] = { "", "Mando", "Continental", "Bosch" };
    if (brake >= 0 && brake <= 3)
        printf("Brake System : %s\n", brakeStr[brake]);
    else
        printf("Brake System : Invalid Input(%d)\n", brake);
}

void PrintProcedureSteeringSystem(int steer)
{
    char steerStr[3][10] = { "", "Bosch", "Mobis" };
    if (steer >= 0 && steer <= 2)
        printf("SteeringSystem : %s\n", steerStr[steer]);
    else
        printf("SteeringSystem : Invalid Input(%d)\n", steer);
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}