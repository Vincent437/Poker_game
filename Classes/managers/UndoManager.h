#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include <functional>
#include <vector>
#include <memory>

class UndoManager {
public:
    using UndoAction = std::function<void()>;

    void recordAction(UndoAction undoAction, UndoAction redoAction);
    bool undo();
    bool redo();
    void clear();

private:
    struct ActionPair {
        UndoAction undo;
        UndoAction redo;
    };

    std::vector<ActionPair> _undoStack;
    std::vector<ActionPair> _redoStack;
    size_t _maxSteps = 50; // 最大可撤销步数
};

#endif // __UNDO_MANAGER_H__