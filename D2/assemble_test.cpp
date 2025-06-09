
#include <gmock/gmock.h>
#include "assemble.h"
#include "Car.h"

#include <utility>
#include <vector>
#include <unordered_map>

extern Car car;

TEST(CarPartsTest, CarPartsValidationAllValidCase)
{
    bool expect = true;
    for (int caridx = 1; caridx <= 3; caridx++)
    {
        selectCarType(caridx);
        for (int engine = 1; engine <= 4; engine++)
        {
            selectEngine(engine);
            for (int brake = 1; brake <= 3; brake++)
            {
                selectbrakeSystem(brake);
                for (int steer = 1; steer <= 2; steer++)
                {
                    selectSteeringSystem(steer);

                    expect = true;
                    if (car.GetType() == Type::Sedan && car.GetBrake()->name() == "Continental")
                        expect = false;

                    if (car.GetType() == Type::SUV && car.GetEngine()->name() == "TOYOTA")
                        expect = false;

                    if (car.GetType() == Type::Truck && car.GetEngine()->name() == "WIA")
                        expect = false;

                    if (car.GetType() == Type::Truck && car.GetBrake()->name() == "Mando")
                        expect = false;

                    if (car.GetBrake()->name() == "Bosch" && car.GetSteering()->name() != "Bosch")
                        expect = false;

                    bool actual = car.CarPartsValidate();
                    EXPECT_EQ(actual, expect);
                }
            }
        }
    }
}

TEST(CarPartsTest, runProducedCarAllCov)
{
    for (int caridx = 1; caridx <= 3; caridx++)
    {
        selectCarType(caridx);
        for (int engine = 1; engine <= 4; engine++)
        {
            selectEngine(engine);
            for (int brake = 1; brake <= 3; brake++)
            {
                selectbrakeSystem(brake);
                for (int steer = 1; steer <= 2; steer++)
                {
                    selectSteeringSystem(steer);

                    car.Run();
                }
            }
        }
    }
}

TEST(CarPartsTest, testProducedCarAllCov)
{
    for (int caridx = 1; caridx <= 3; caridx++)
    {
        selectCarType(caridx);
        for (int engine = 1; engine <= 4; engine++)
        {
            selectEngine(engine);
            for (int brake = 1; brake <= 3; brake++)
            {
                selectbrakeSystem(brake);
                for (int steer = 1; steer <= 2; steer++)
                {
                    selectSteeringSystem(steer);

                    car.Test();
                }
            }
        }
    }
}

TEST(CarPartsTest, printTest)
{
    for (int step = 0; step <= 4; step++)
    {
        PrintMenuByStep(step);
    }
}

using pii = std::pair<int, int>;

std::vector<QuestionType> qtype = {
    QuestionType::CarType_Q,
    QuestionType::Engine_Q,
    QuestionType::brakeSystem_Q,
    QuestionType::SteeringSystem_Q,
    QuestionType::Run_Test
};

std::unordered_map<QuestionType, pii> validRangeMenu = {
    {QuestionType::CarType_Q, {1, 3}},
    {QuestionType::Engine_Q, {0, 4}},
    {QuestionType::brakeSystem_Q, {0, 3}},
    {QuestionType::SteeringSystem_Q, {0, 2}},
    {QuestionType::Run_Test, {0, 2}}
};

TEST(TestCaseInputVaidation, TestInputInvalidNonDigit)
{
    char* input = (char*)"a";
    int answer = 0;

    for (QuestionType step : qtype)
    {
        InputValidationResult expected = InputValidationResult::Invalid;
        InputValidationResult actual = InputVaildation(input, step, answer);
        EXPECT_EQ(actual, expected);
    }
}

TEST(TestCaseInputVaidation, TestInputInvalidDigit)
{
    char input[10];
    int answer = 0;

    for (QuestionType step : qtype)
    {
        QuestionType varstep = QuestionType::CarType_Q;
        InputValidationResult expected = InputValidationResult::Invalid;
        InputValidationResult actual = InputValidationResult::Valid;
        int validStart = validRangeMenu[step].first - 1;
        int validEnd = validRangeMenu[step].second + 1;

        varstep = step;
        sprintf_s(input, "%d", validStart);
        if (step >= QuestionType::Engine_Q)
            expected = InputValidationResult::Invalid;
        actual = InputVaildation(input, varstep, answer);
        EXPECT_EQ(actual, expected);

        varstep = step;
        sprintf_s(input, "%d", validEnd);
        expected = InputValidationResult::Invalid;
        actual = InputVaildation(input, varstep, answer);
        EXPECT_EQ(actual, expected);
    }
}

TEST(TestCaseInputVaidation, TestInputValidDigit)
{
    char input[10];
    int answer = 0;

    for (QuestionType step : qtype)
    {
        InputValidationResult expected = InputValidationResult::Valid;
        InputValidationResult actual = InputValidationResult::Valid;
        int validStart = validRangeMenu[step].first;
        int validEnd = validRangeMenu[step].second;

        sprintf_s(input, "%d", validStart);
        actual = InputVaildation(input, step, answer);
        EXPECT_EQ(actual, expected);

        sprintf_s(input, "%d", validEnd);
        actual = InputVaildation(input, step, answer);
        EXPECT_EQ(actual, expected);
    }
}

TEST(TestCaseInputVaidation, TestInputTransitionBackward)
{
    char input[10];
    int answer = 0;

    for (QuestionType step : qtype)
    {
        InputValidationResult expected = InputValidationResult::Valid;
        InputValidationResult actual = InputValidationResult::Valid;
        int validStart = validRangeMenu[step].first;
        int validEnd = validRangeMenu[step].second;

        sprintf_s(input, "%d", validStart);
        actual = InputVaildation(input, step, answer);
        EXPECT_EQ(actual, expected);

        sprintf_s(input, "%d", validEnd);
        actual = InputVaildation(input, step, answer);
        EXPECT_EQ(actual, expected);
    }
}


/*
TEST(CarPartsTest, carGetTypeName)
{
    Car c;
    std::string Car::GetTypeName()
    {
        switch (GetType())
        {
        case Type::Sedan: return "Sedan";
        case Type::SUV: return "SUV";
        case Type::Truck: return "Truck";
        };
        return "";
    }

    c.SetCarType()
}
*/
