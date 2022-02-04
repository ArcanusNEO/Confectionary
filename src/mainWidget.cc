#include "mainWidget.hh"

mainWidget::mainWidget(QWidget* parent)
  : QWidget(parent) {
  setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint);

}

mainWidget::~mainWidget() {}

void mainWidget::closeEvent(QCloseEvent* event) {
  event->ignore();
}
