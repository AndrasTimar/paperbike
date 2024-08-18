#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include "widget.h"
#include <memory>
#include <utility>
#include <vector>

class RootWidget : public Widget {
    private:
        std::vector<std::unique_ptr<Widget>> children;
        int w;
        int h;
    public:
        RootWidget(std::vector<std::unique_ptr<Widget>> children, int w, int h) : children(std::move(children)), w(w), h(h) {};
        void render(GxEPD_Class &display, int globalX, int globalY) const override {
            for (const auto& child : children) {
                if (child) {
                    child->render(display, globalX, globalY);
                }
            }
        };
};

#endif