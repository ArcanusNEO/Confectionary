#include "refuse.hh"
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include <QCloseEvent>
#include <QPixmap>
#include <QPainter>
#include <iostream>

enum { windowWidth = 200, windowHeight = 200 };
refuse::refuse(QWidget* parent)
  : QWidget(parent) {
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setFixedSize(windowWidth, windowHeight);
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
  auto cx = (scrGeo.x() + scrGeo.width()) / 2, cy = (scrGeo.y() + scrGeo.height()) / 2;
  setGeometry(cx - windowWidth / 2, cy - windowHeight / 2, 0, 0);
}

refuse::~refuse() {

}

void refuse::closeEvent(QCloseEvent* event) {
  event->ignore();
}

void refuse::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawPixmap(rect(), QPixmap(":/pic/flower"), QRect());
}
