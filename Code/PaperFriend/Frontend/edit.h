#ifndef EDIT_H
#define EDIT_H

#pragma once

#include <QTextEdit>

class Edit : public QTextEdit {
  Q_OBJECT
public:
  explicit Edit(QWidget *parent = nullptr);

signals:

public slots:

protected:
  void contextMenuEvent(QContextMenuEvent *e);
};

#endif // EDIT_H
