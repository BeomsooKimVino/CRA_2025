
#include <gmock/gmock.h>
#include "assemble.h"
#include "Car.h"

#include <utility>
#include <vector>
#include <unordered_map>

extern int stack[10];
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
                    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
                    {
                        expect = false;
                    }
                    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
                    {
                        expect = false;
                    }
                    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
                    {
                        expect = false;
                    }
                    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
                    {
                        expect = false;
                    }
                    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
                    {
                        expect = false;
                    }

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

                    runProducedCar();
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

                    testProducedCar();
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
