#include "edit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include "texteditor.h"
Edit::Edit(QWidget *parent) : QTextEdit(parent)
{
}
void Edit::contextMenuEvent(QContextMenuEvent *e)
{
    // Create a menu
    QMenu *menu = createStandardContextMenu();
    menu->addAction(tr("复制"), this, SLOT(copy()));
    menu->addAction(tr("粘贴"), this, SLOT(paste()));
    menu->addAction(tr("剪切"), this, SLOT(cut()));
    menu->addAction(tr("全选"), this, SLOT(selectAll()));
    menu->exec(e->globalPos());
    delete menu;
}
