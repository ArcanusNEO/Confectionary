#pragma once

#include <QWidget>
#include <QCloseEvent>
#include <QToolButton>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMovie>
#include <memory>
#include <random>
#include "agree.hh"

class loveLetter : public QWidget {
  Q_OBJECT

public:
  loveLetter(QWidget* parent = nullptr);
  ~loveLetter();

protected:
  void closeEvent(QCloseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

private:
  std::unique_ptr<QToolButton> pBtn[2];
  std::unique_ptr<QLabel> pLb;
  std::unique_ptr<QMovie> loveGif;
  std::unique_ptr<agree> pAgree;
  std::unique_ptr<QGraphicsOpacityEffect> pEff;
  std::unique_ptr<QPropertyAnimation> ppa;
  int whichEdge(int x, int y);
};
