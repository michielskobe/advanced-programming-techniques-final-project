#include "protagonistview.h"

ProtagonistView::ProtagonistView()
    : levels(std::make_shared<std::vector<std::unique_ptr<Level>>>())
    , gameController(GameController::GetInstance())
{}
