/*
  resultsannotatepage.cpp

  This file is part of Hotspot, the Qt GUI for performance analysis.

  Copyright (C) 2017-2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Nate Rogers <nate.rogers@kdab.com>

  Licensees holding valid commercial KDAB Hotspot licenses may use this file in
  accordance with Hotspot Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "resultsannotatepage.h"

#include "parsers/perf/perfparser.h"
#include "resultsutil.h"

#include "models/hashmodel.h"
#include "models/treemodel.h"
#include "codeviewer.h"

#include <QVBoxLayout>
#include <QTextBlock>

ResultsAnnotatePage::ResultsAnnotatePage(PerfParser* parser, QWidget* parent)
    : QWidget(parent)
{
    this->wrapper = new QVBoxLayout(this);

    this->viewer = new CodeViewer();
    this->viewer->setReadOnly(true);

    QFont font;
    font.setFamily(QStringLiteral("Courier"));
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);

    this->viewer->setFont(font);
    this->viewer->setTabStopWidth(4 * QFontMetrics(font).width(QChar::fromLatin1(' ')));

    this->wrapper->addWidget(this->viewer);
}

void ResultsAnnotatePage::annotate(const QString& filename, int line)
{
    if (!QFile::exists(filename))
    {
        this->viewer->setPlainText(tr("Could not find file %1").arg(filename));
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->viewer->setPlainText(tr("Could not open file %1").arg(filename));
        return;
    }

    auto content = QString::fromUtf8(file.readAll());
    this->viewer->setPlainText(content);

    QTextCursor cursor(this->viewer->document()->findBlockByLineNumber(line - 1));
    this->viewer->setTextCursor(cursor);
}

ResultsAnnotatePage::~ResultsAnnotatePage() = default;
