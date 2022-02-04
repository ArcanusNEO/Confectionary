#include "mainWidget.hh"
#include <QIcon>
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <QSettings>
#include <iostream>
#include <random>

void setTaskManagerVisable(bool flag) {
#define TASKMANAGER "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
  std::unique_ptr<QSettings> settings(new QSettings(TASKMANAGER, QSettings::NativeFormat));
  if (flag) settings->remove("DisableTaskMgr");
  else settings->setValue("DisableTaskMgr", "1");
}

enum { windowWidth = 350, windowHeight = 450, btnWidth = 75, btnHeight = 50, pending = 5, loveHeight = 300, loveWidth = 300 };
mainWidget::mainWidget(QWidget* parent)
  : QWidget(parent) {
#ifdef Q_OS_WIN
  setTaskManagerVisable(false);
#endif

#ifdef Q_OS_LINUX

#endif

#ifdef Q_OS_MAC

#endif
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setFixedSize(windowWidth, windowHeight);
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
  auto cx = (scrGeo.x() + scrGeo.width()) / 2, cy = (scrGeo.y() + scrGeo.height()) / 2;
  setGeometry(cx - windowWidth / 2, cy - windowHeight / 2, 0, 0);
  setMouseTracking(true);
  pLb.reset(new QLabel(this));
  pLb->setFixedSize(loveWidth, loveHeight);
  loveGif.reset(new QMovie(":/pic/love"));
  pLb->setMovie(loveGif.get());
  loveGif->start();
  pLb->setGeometry(0, 0, 0, 0);
  for (int i = 0; i < 2; ++i) {
    pBtn[i].reset(new QToolButton(this));
    pBtn[i]->setFixedSize(btnWidth, btnHeight);
    pBtn[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    pBtn[i]->setIcon(QIcon(QString(":/pic/btn") + QString(i + '0')));
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

mainWidget::~mainWidget() {
#ifdef Q_OS_WIN
  setTaskManagerVisable(true);
#endif

#ifdef Q_OS_LINUX

#endif

#ifdef Q_OS_MAC

#endif
}

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
  auto px = event->pos().x();
  auto py = event->pos().y();
  // static uint64_t i = 0;
  // std::cout << "Message" << i++ << std::endl;
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
#define sx (scrGeo.x())
#define sy (scrGeo.y())
#define sw (scrGeo.width())
#define sh (scrGeo.height())
#define adjust (pending * (rand() % 20 + 30))
#define wx (geometry().x())
#define wy (geometry().y())
#define ww (geometry().width())
#define wh (geometry().height())
  auto x = wx, y = wy;
  switch (whichEdge(px, py)) {
  case 0: {
    x += adjust, y += adjust;
    break;
  }
  case 1: {
    y += adjust;
    break;
  }
  case 2: {
    x -= adjust, y += adjust;
    break;
  }
  case 3: {
    x -= adjust;
    break;
  }
  case 4: {
    x -= adjust, y -= adjust;
    break;
  }
  case 5: {
    y -= adjust;
    break;
  }
  case 6: {
    x += adjust, y -= adjust;
    break;
  }
  case 7: {
    x += adjust;
    break;
  }
  default: break;
  }
  using std::min;
  using std::max;
  x = max(x, sx);
  x = min(x, sx + sw);
  y = max(y, sy);
  y = min(y, sy + sh);
  if (x <= sx + pending) x = sx + sw - ww - adjust / 10;
  else if (x + ww >= sx + sw - pending) x = sx + adjust / 10;
  if (y <= sy + pending) y = sy + sh - wh - adjust / 10;
  else if (y + wh >= sy + sh - pending) y = sy + adjust / 10;
  setGeometry(x, y, 0, 0);
}