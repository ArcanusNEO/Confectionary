#pragma once

#include <QLabel>
#include <QPaintEvent>
#include <QWidget>
#include <memory>

class agree : public QWidget {
  Q_OBJECT

public:
  agree(QWidget* parent = nullptr);
  ~agree();

protected:
  void closeEvent(QCloseEvent* event);
  void paintEvent(QPaintEvent* event);

private:
};
