#pragma once

#include <QWidget>
#include <QCloseEvent>

class mainWidget : public QWidget {
  Q_OBJECT

public:
  mainWidget(QWidget* parent = nullptr);
  ~mainWidget();
protected:
  void closeEvent(QCloseEvent* event);
};
