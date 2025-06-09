#include "assemble.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Car.h"

#define CLEAR_SCREEN "\033[H\033[2J"

extern Car car;

void PrintSelectRunTest()
{
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void PrintSelectSteerType()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void PrintSelectBrakeType()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void PrintSelectEngineType()
{
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void PrintSelectCarType()
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void selectCarType(int answer)
{
    switch (answer)
    {
    case 1:
        car.SetCarType(Type::Sedan);
        break;
    case 2:
        car.SetCarType(Type::SUV);
        break;
    case 3:
        car.SetCarType(Type::Truck);
        break;
    }
    printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", car.GetTypeName().c_str());
}

void selectEngine(int answer)
{
    std::unique_ptr<IEngine> engine;
    switch (answer)
    {
        case 1:
            engine = std::move(std::make_unique<GMEngine>());
            break;
        case 2:
            engine = std::move(std::make_unique<ToyotaEngine>());
            break;
        case 3:
            engine = std::move(std::make_unique<WiaEngine>());
            break;
        case 4:
            engine = std::move(std::make_unique<BrokenEngine>());
            break;
    }

    car.SetEngine(std::move(engine));
    if (answer < 4)
        printf("%s ������ �����ϼ̽��ϴ�.\n", car.GetEngine()->name().c_str());
}

void selectbrakeSystem(int answer)
{
    std::unique_ptr<IBrakeSystem> brake;
    switch (answer)
    {
    case 1:
        brake = std::move(std::make_unique<MandoBrakeSystem>());
        break;
    case 2:
        brake = std::move(std::make_unique<ContinentalBrakeSystem>());
        break;
    case 3:
        brake = std::move(std::make_unique<BoschBrakeSystem>());
        break;
    }

    car.SetBrake(std::move(brake));
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", car.GetBrake()->name().c_str());

}

void selectSteeringSystem(int answer)
{
    std::unique_ptr<ISteeringSystem> steer;
    switch (answer)
    {
    case 1:
        steer = std::move(std::make_unique<BoschSteeringSystem>());
        break;
    case 2:
        steer = std::move(std::make_unique<MobisSteeringSystem>());
        break;
    }

    car.SetSteering(std::move(steer));
    printf("%s ������ġ�� �����ϼ̽��ϴ�.\n", car.GetSteering()->name().c_str());
}

void PrintMenuByStep(int step)
{
    printf(CLEAR_SCREEN);

    switch (step)
    {
        case CarType_Q: PrintSelectCarType(); break;
        case Engine_Q: PrintSelectEngineType(); break;
        case brakeSystem_Q: PrintSelectBrakeType(); break;
        case SteeringSystem_Q: PrintSelectSteerType(); break;
        case Run_Test: PrintSelectRunTest(); break;
    }

    printf("===============================\n");
}

InputValidationResult InputVaildation(char* buf, QuestionType& step, int &answer)
{
    // TODO: ������ ���� 800���� ���� �ʿ�
    int delay_ms = 800;

    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    return InputValidationResult::Valid;
}
#ifdef NDEBUG

void UserInputAndRemoveLF(char  buf[100])
{
    // ����� �Է� �޾ƿ���
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

MenuTranstion InputCheckForMenuTransition(int answer, QuestionType& step)
{
    // ó������ ���ư���
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return MenuTranstion::StartPoint;
    }

    // �������� ���ư���
    if (answer == 0 && step >= 1)
    {
        step = static_cast<QuestionType>(static_cast<int>(step) - 1);
        return MenuTranstion::Backward;
    }
    return MenuTranstion::Forward;
}

bool IsExit(char buf[100])
{
    if (!strcmp(buf, "exit"))
    {
        return true;
    }
    return false;
}
#endif
