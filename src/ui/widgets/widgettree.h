#pragma once
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>

#include <unordered_map>
#include <unordered_map>

class WidgetTree {
public:
    void setRoot(std::unique_ptr<Widget> root) {
        currentRoot = std::move(root); // Transfer ownership
    }
    

    void updateAndRender(GxEPD_Class &display) {
        if (previousRoot) {
            compareAndRender(currentRoot.get(), previousRoot.get(), display);
        } else {
            renderAll(currentRoot.get(), display);
        }
        previousRoot = cloneTree(currentRoot.get());
    }

private:
    void renderAll(Widget* widget, GxEPD_Class &display) {
        if (widget->isDirty()) {
            widget->updateAndRender(display);
        }
        for (const auto& child : widget->getChildren()) {
            renderAll(child.get(), display);
        }

        display.updateWindow(0, 0, display.width(), display.height(), true);
    }

    void compareAndRender(Widget* newWidget, const Widget* oldWidget, GxEPD_Class &display) {
        Serial.println("Checking changes");
        if (newWidget->hasChanged(*oldWidget)) {
            newWidget->updateAndRender(display);
        }

        std::unordered_map<std::string, const Widget*> oldChildMap;
        for (const auto& child : oldWidget->getChildren()) {
            oldChildMap[child->getConfig().id] = child.get();
        }

        for (const auto& newChild : newWidget->getChildren()) {
            auto it = oldChildMap.find(newChild->getConfig().id);
            if (it == oldChildMap.end()) {
                newChild.get()->updateAndRender(display);
            } else {
                compareAndRender(newChild.get(), it->second, display);
            }
        }
    }

    std::unique_ptr<Widget> cloneTree(const Widget* widget) {
        if (!widget) return nullptr;
        std::unique_ptr<Widget> clone = widget->clone();
        for (const auto& child : widget->getChildren()) {
            clone->addChild(cloneTree(child.get()));
        }
        return clone;
    }

    std::unique_ptr<Widget> currentRoot;
    std::unique_ptr<Widget> previousRoot;
};
