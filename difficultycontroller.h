#ifndef DIFFICULTYCONTROLLER_H
#define DIFFICULTYCONTROLLER_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"
#include <QtLogging>
#include <QLoggingCategory>

class DifficultyController
{
public:
    DifficultyController();

    static DifficultyController* difficultyController;

    // Singletons should not be cloneable or assignable.
    DifficultyController(DifficultyController &other) = delete;
    void operator=(const DifficultyController &) = delete;

    // This is the static method that controls the access to the singleton instance.
    static DifficultyController *GetInstance();

    int difficultySetting{0};
    std::vector<int> xEnemyUpdateTime{20, 10, 3};
    std::vector<float> xEnemyHealthLossMove{50.f, 10.f, 5.f};
    std::vector<int> PoisonTileLingeringTime{10, 30, 60};
    std::vector<float> PoisonTileDamageMul{2.0f, 5.0f, 10.0f};
    std::vector<int> PoisonTileSpreadRadius{2, 3, 4};
    std::vector<float> WalkingEnergyLoss{0.1f, 0.3f, 0.5f};
    std::vector<float> PEnemyHealthLossAttack{5.f, 10.f, 20.f};
    std::vector<float> ProtagonistHealthLossAttack{5.0f, 10.0f, 20.0f};

    int getXEnemyUpdateTime();
    float getXEnemyHealthLossMove();
    int getPoisonTileLingeringTime();
    float getPoisonTileDamageMul();
    int getPoisonTileSpreadRadius();
    float getWalkingEnergyLoss();
    float getPEnemyHealthLossAttack();
    float getProtagonistHealthLossAttack();

    int getDifficultySetting() const;
    void setDifficultySetting(int newDifficultySetting);
};

#endif // DIFFICULTYCONTROLLER_H
