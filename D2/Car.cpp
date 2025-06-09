#include "Car.h"

#include <unordered_map>

void Car::Run()
{
    if (!CarPartsValidate())
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (GetEngine()->name() == "Broken")
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            printf("Car Type : %s\n", GetTypeName().c_str());
            printf("Engine : %s\n", GetEngine()->name().c_str());
            printf("Brake System : %s\n", GetBrake()->name().c_str());
            printf("SteeringSystem : %s\n", GetSteering()->name().c_str());
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void Car::Test()
{
    
    if (GetType() == Type::Sedan && GetBrake()->name() == "Continental")
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (GetType() == Type::SUV && GetEngine()->name() == "TOYOTA")
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (GetType() == Type::Truck && GetEngine()->name() == "WIA")
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (GetType() == Type::Truck && GetBrake()->name() == "Mando")
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (GetBrake()->name() == "Bosch" && GetSteering()->name() != "Bosch")
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
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