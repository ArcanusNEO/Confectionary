#pragma once

#include <QWidget>
#include <QCloseEvent>
#include <QToolButton>
#include <memory>
#include <random>

class mainWidget : public QWidget {
  Q_OBJECT

public:
  mainWidget(QWidget* parent = nullptr);
  ~mainWidget();

protected:
  void closeEvent(QCloseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

private:
  std::unique_ptr<QToolButton> pBtn[2];
  int whichEdge(int x, int y);
};
