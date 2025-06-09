#include "Car.h"

#include <unordered_map>

void Car::Run()
{
    if (!CarPartsValidate())
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (GetEngine()->name() == "Broken")
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            printf("Car Type : %s\n", GetTypeName().c_str());
            printf("Engine : %s\n", GetEngine()->name().c_str());
            printf("Brake System : %s\n", GetBrake()->name().c_str());
            printf("SteeringSystem : %s\n", GetSteering()->name().c_str());
            printf("자동차가 동작됩니다.\n");
        }
    }
}

void Car::Test()
{
    
    if (GetType() == Type::Sedan && GetBrake()->name() == "Continental")
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (GetType() == Type::SUV && GetEngine()->name() == "TOYOTA")
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (GetType() == Type::Truck && GetEngine()->name() == "WIA")
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (GetType() == Type::Truck && GetBrake()->name() == "Mando")
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (GetBrake()->name() == "Bosch" && GetSteering()->name() != "Bosch")
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}

std::string Car::GetTypeName()
{
    std::string typestr("");
    switch(GetType())
    {
        case Type::Sedan: typestr = "Sedan";
        case Type::SUV: typestr = "SUV";
        case Type::Truck: typestr = "Truck";
    };
    return typestr;
}

bool Car::CarPartsValidate()
{
    // TODO: Considering what to do when adding a Cat Type -> Separate the Validator into a Class?
    if (GetType() == Type::Sedan && GetBrake()->name() == "Continental")
        return false;

    if (GetType() == Type::SUV && GetEngine()->name() == "TOYOTA")
        return false;

    if (GetType() == Type::Truck && GetEngine()->name() == "WIA")
        return false;

    if (GetType() == Type::Truck && GetBrake()->name() == "Mando")
        return false;

    if (GetBrake()->name() == "Bosch" && GetSteering()->name() != "Bosch")
        return false;

    return true;
}