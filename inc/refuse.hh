#pragma once

#include <QLabel>
#include <QPaintEvent>
#include <QWidget>
#include <memory>

class refuse : public QWidget {
  Q_OBJECT

public:
  refuse(QWidget* parent = nullptr);
  ~refuse();

protected:
  void closeEvent(QCloseEvent* event);
  void paintEvent(QPaintEvent* event);

private:
};
