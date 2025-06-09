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
            printf("���̹���\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            PrintProcedureCarType(stack[QuestionType::CarType_Q]);
            PrintProcedureEngine(stack[QuestionType::Engine_Q]);
            PrintProcedureBrakeSystem(stack[QuestionType::brakeSystem_Q]);
            PrintProcedureSteeringSystem(stack[QuestionType::SteeringSystem_Q]);
            printf("�ڵ����� ���۵˴ϴ�.\n");
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
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}