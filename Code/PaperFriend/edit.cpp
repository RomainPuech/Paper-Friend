#include "edit.h"
#include "texteditor.h"
#include <QContextMenuEvent>
#include <QMenu>

Edit::Edit(QWidget *parent) : QTextEdit(parent) {}
void Edit::contextMenuEvent(QContextMenuEvent *e) {
  // Create a menu
  QMenu *menu = createStandardContextMenu();
  menu->addAction(tr("Copy"), this, SLOT(copy()));
  menu->addAction(tr("Paste"), this, SLOT(paste()));
  menu->addAction(tr("Cut"), this, SLOT(cut()));
  menu->addAction(tr("Sellect All"), this, SLOT(selectAll()));
  menu->exec(e->globalPos());
  delete menu;
}
