#include "assemble.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Car.h"

#define CLEAR_SCREEN "\033[H\033[2J"

extern Car car;

void PrintSelectRunTest()
{
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void PrintSelectSteerType()
{
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void PrintSelectBrakeType()
{
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void PrintSelectEngineType()
{
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void PrintSelectCarType()
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
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
    printf("차량 타입으로 %s을 선택하셨습니다.\n", car.GetTypeName().c_str());
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
        printf("%s 엔진을 선택하셨습니다.\n", car.GetEngine()->name().c_str());
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
    printf("%s 제동장치를 선택하셨습니다.\n", car.GetBrake()->name().c_str());

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
    printf("%s 조향장치를 선택하셨습니다.\n", car.GetSteering()->name().c_str());
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
    // TODO: 제출할 때는 800으로 변경 필요
    int delay_ms = 800;

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delay(delay_ms);
        return InputValidationResult::Invalid;
    }

    return InputValidationResult::Valid;
}
#ifdef NDEBUG

void UserInputAndRemoveLF(char  buf[100])
{
    // 사용자 입력 받아오기
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

MenuTranstion InputCheckForMenuTransition(int answer, QuestionType& step)
{
    // 처음으로 돌아가기
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return MenuTranstion::StartPoint;
    }

    // 이전으로 돌아가기
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
