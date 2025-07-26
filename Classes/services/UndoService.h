#pragma once
#include "models/UndoModel.h"
#include "views/CardView.h"

class UndoService {
public:
    void recordCardMove(UndoModel* undoModel,
        CardView* cardView,
        const std::string& fromZone,
        const std::string& toZone,
        int fromIndex = -1,
        int toIndex = -1);

    void undoLastMove(UndoModel* undoModel, GameModel* gameModel);
};