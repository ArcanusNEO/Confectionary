#include "mainWidget.hh"
#include <QIcon>
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <iostream>
#include <random>

enum { windowWidth = 350, windowHeight = 250, btnWidth = 75, btnHeight = 50, pending = 5 };
mainWidget::mainWidget(QWidget* parent)
  : QWidget(parent) {
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
  setFixedSize(windowWidth, windowHeight);
  setMouseTracking(true);
  for (int i = 0; i < 2; ++i) {
    pBtn[i].reset(new QToolButton(this));
    pBtn[i]->setFixedSize(btnWidth, btnHeight);
    pBtn[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    pBtn[i]->setIcon(QIcon(QString("pic/btn") + QString(i + '0') + QString(".png")));
  }
  pBtn[0]->setGeometry((windowWidth / 2 - btnWidth) / 2, windowHeight - btnHeight - pending, 0, 0);
  pBtn[0]->setText(tr("我愿意！"));
  pBtn[1]->setGeometry(3 * windowWidth / 4 - btnWidth / 2, windowHeight - btnHeight - pending, 0, 0);
  pBtn[1]->setText(tr("我不要～"));
  std::random_device rd;
  srand(rd());
#define refuseBoxx1 (pBtn[1]->geometry().x() - pending)
#define refuseBoxx2 (pBtn[1]->geometry().x() + btnWidth + pending)
#define refuseBoxy1 (pBtn[1]->geometry().y() - pending)
#define refuseBoxy2 (pBtn[1]->geometry().y() + btnHeight + pending)
}

mainWidget::~mainWidget() {}

void mainWidget::closeEvent(QCloseEvent* event) {
  event->ignore();
}
int mainWidget::whichEdge(int x, int y) {
  if (x < refuseBoxx1 || x > refuseBoxx2 || y < refuseBoxy1 || y > refuseBoxy2) goto NONE;
  if (x <= refuseBoxx1 + pending && y <= refuseBoxy1 + pending) return 0;
  if (x > refuseBoxx1 + pending && x < refuseBoxx2 - pending && y <= refuseBoxy1 + pending) return 1;
  if (x >= refuseBoxx2 - pending && y <= refuseBoxy1 + pending) return 2;
  if (x >= refuseBoxx2 - pending && y > refuseBoxy1 + pending && y < refuseBoxy2 - pending) return 3;
  if (x >= refuseBoxx2 - pending && y >= refuseBoxy2 - pending) return 4;
  if (x > refuseBoxx1 + pending && x < refuseBoxx2 - pending && y >= refuseBoxy2 - pending) return 5;
  if (y >= refuseBoxy2 - pending && x <= refuseBoxx1 + pending) return 6;
  if (y > refuseBoxy1 + pending && x <= refuseBoxx1 + pending && y < refuseBoxy2 - pending) return 7;
NONE:
  return -1;
}
void mainWidget::mouseMoveEvent(QMouseEvent* event) {
  auto& px = event->pos().rx();
  auto& py = event->pos().ry();
  if (px < refuseBoxx1 || px > refuseBoxx2 || py < refuseBoxy1 || py > refuseBoxy2) return;
  // static uint64_t i = 0;
  // std::cout << "Message" << i++ << std::endl;
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
  auto sx = scrGeo.x(), sy = scrGeo.y();
  auto sw = scrGeo.width(), sh = scrGeo.height();
#define adjust (pending * (rand() % 20 + 30))
#define wx (geometry().x())
#define wy (geometry().y())
#define ww (geometry().width())
#define wh (geometry().height())
  switch (whichEdge(px, py)) {
  case 0: {
    setGeometry(wx + adjust, wy + adjust, 0, 0);
    break;
  }
  case 1: {
    setGeometry(wx, wy + adjust, 0, 0);
    break;
  }
  case 2: {
    setGeometry(wx - adjust, wy + adjust, 0, 0);
    break;
  }
  case 3: {
    setGeometry(wx - adjust, wy, 0, 0);
    break;
  }
  case 4: {
    setGeometry(wx - adjust, wy - adjust, 0, 0);
    break;
  }
  case 5: {
    setGeometry(wx, wy - adjust, 0, 0);
    break;
  }
  case 6: {
    setGeometry(wx + adjust, wy - adjust, 0, 0);
    break;
  }
  case 7: {
    setGeometry(wx + adjust, wy, 0, 0);
    break;
  }
  default: break;
  }
}