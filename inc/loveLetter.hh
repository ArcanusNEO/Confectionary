#pragma once

#include <QCloseEvent>
#include <QEasingCurve>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QMovie>
#include <QPropertyAnimation>
#include <QToolButton>
#include <QWidget>
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
  std::unique_ptr<QToolButton>            pBtn[2];
  std::unique_ptr<QLabel>                 pLb, pTo, pFrom, pTxt1, pTxt2;
  std::unique_ptr<QMovie>                 pLoveGif;
  std::unique_ptr<agree>                  pAgree;
  std::unique_ptr<refuse>                 pRefuse;
  std::unique_ptr<QGraphicsOpacityEffect> pAgEff, pRfEff;
  std::unique_ptr<QPropertyAnimation>     pAgPA, pRfPA;
  int                                     whichEdge(int x, int y);
};
