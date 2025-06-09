#pragma once
#include <string>
#include <memory>

#include "Engine.h"
#include "BrakeSystem.h"
#include "SteeringSystem.h"

// enum 추가하여 확장
enum class Type : int { Sedan, SUV, Truck };

class Car {
public:
    void SetCarType(Type settype) { type = settype; }
    void SetEngine(std::unique_ptr<IEngine> e) { engine = std::move(e); }
    void SetBrake(std::unique_ptr<IBrakeSystem> b) { brake = std::move(b); }
    void SetSteering(std::unique_ptr<ISteeringSystem> s) { steering = std::move(s); }

    bool CarPartsValidate();
    void Run();
    void Test();

    Type GetType() { return type; }
    std::string GetTypeName();
    IEngine* GetEngine() { return engine.get(); }
    IBrakeSystem* GetBrake() { return brake.get(); }
    ISteeringSystem* GetSteering() { return steering.get(); }

private:
    Type type;
    std::unique_ptr<IEngine> engine;
    std::unique_ptr<IBrakeSystem> brake;
    std::unique_ptr<ISteeringSystem> steering;

};
