#ifndef DIFFICULTYCONTROLLER_H
#define DIFFICULTYCONTROLLER_H

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
};

#endif // DIFFICULTYCONTROLLER_H
