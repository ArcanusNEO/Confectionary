#pragma once

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
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
  // std::unique_ptr <
};
