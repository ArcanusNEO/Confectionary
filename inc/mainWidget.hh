#pragma once

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>
#include <memory>

class mainWidget : public QWidget {
  Q_OBJECT

public:
  mainWidget(QWidget* parent = nullptr);
  ~mainWidget();

protected:
  void closeEvent(QCloseEvent* event);

private:
  std::unique_ptr<QPushButton> pBtn[2];
};
