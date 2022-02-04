#include "mainWidget.hh"
#include <QIcon>
#include <QPixmap>

mainWidget::mainWidget(QWidget* parent)
  : QWidget(parent) {
  enum { windowWidth = 400, windowHeight = 200, btnWidth = 200, btnHeight = 35 };
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
  setFixedSize(windowWidth, windowHeight);
  QPixmap pix[2];
  for (int i = 0; i < 2; ++i) {
    pBtn[i].reset(new QPushButton(this));
    pBtn[i]->setFixedSize(btnWidth, btnHeight);
    pix[i].load(QString("pic/btn") + QString(i + '0') + QString(".png"));
    pix[i].scaled(btnWidth, btnHeight, Qt::AspectRatioMode::KeepAspectRatio);
    pBtn[i]->setIcon(pix[i]);
  }
  pBtn[0]->setGeometry((windowWidth / 2 - btnWidth) / 2, windowHeight - btnHeight, 0, 0);
  pBtn[1]->setGeometry(3 * windowWidth / 4 - btnWidth / 2, windowHeight - btnHeight, 0, 0);
}

mainWidget::~mainWidget() {}

void mainWidget::closeEvent(QCloseEvent* event) {
  event->ignore();
}
