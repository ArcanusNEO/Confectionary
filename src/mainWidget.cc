#include "mainWidget.hh"
#include <QIcon>

mainWidget::mainWidget(QWidget* parent)
  : QWidget(parent) {
  enum { windowWidth = 400, windowHeight = 200, btnWidth = 100, btnHeight = 35 };
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
  setFixedSize(windowWidth, windowHeight);
  for (int i = 0; i < 2; ++i) {
    pBtn[i].reset(new QPushButton(this));
    pBtn[i]->setFixedSize(btnWidth, btnHeight);
  }
  pBtn[0]->setGeometry((windowWidth / 2 - btnWidth) / 2, windowHeight - btnHeight, 0, 0);
  pBtn[0]->setIcon(QIcon("/home/lucas/src/Confectionary/pic/b站害羞.png"));
  pBtn[0]->setText(tr("我愿意"));
  pBtn[1]->setGeometry(3 * windowWidth / 4 - btnWidth / 2, windowHeight - btnHeight, 0, 0);
  pBtn[1]->setIcon(QIcon("/home/lucas/src/Confectionary/pic/b站傲娇.png"));
  pBtn[1]->setText(tr("我不！"));
}

mainWidget::~mainWidget() {}

void mainWidget::closeEvent(QCloseEvent* event) {
  event->ignore();
}
