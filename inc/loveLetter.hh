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
#include "refuse.hh"

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
  std::unique_ptr<QMovie> pLoveGif;
  std::unique_ptr<agree> pAgree;
  std::unique_ptr<refuse> pRefuse;
  std::unique_ptr<QGraphicsOpacityEffect> pAgEff, pRfEff;
  std::unique_ptr<QPropertyAnimation> pAgPA, pRfPA;
  int whichEdge(int x, int y);
};
