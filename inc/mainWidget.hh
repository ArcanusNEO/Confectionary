#pragma once

#include <QWidget>
#include <QCloseEvent>
#include <QToolButton>
#include <memory>

class mainWidget : public QWidget {
  Q_OBJECT

public:
  mainWidget(QWidget* parent = nullptr);
  ~mainWidget();

protected:
  void closeEvent(QCloseEvent* event);

private:
  std::unique_ptr<QToolButton> pBtn[2];
};
