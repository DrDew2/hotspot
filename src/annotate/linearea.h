#pragma once

#include <QWidget>
#include "codeviewer.h"

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeViewer *editor) : QWidget(editor) {
        codeViewer = editor;
    }

    QSize sizeHint() const override {
        return {codeViewer->lineNumberAreaWidth(), 0};
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeViewer->lineNumberAreaPaintEvent(event);
    }

private:
    CodeViewer* codeViewer;
};
