#include "assemble.h"
#include "Car.h"

#include <stdio.h>

// TODO: The menu operation function should be classified into a class and global variables should be removed.
Car car;

void delay(int ms)
{
#ifdef NDEBUG

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
#endif
}

#ifdef NDEBUG
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
        car.Run();
    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        car.Test();
    }
    delay(2000);
}
#endif
