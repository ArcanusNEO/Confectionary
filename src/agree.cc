#include "agree.hh"
#include <QPixmap>
#include <QIcon>
#include <QApplication>
#include <QScreen>
#include <QCloseEvent>
#include <QPixmap>
#include <QPainter>
#include <iostream>

enum { windowWidth = 200, windowHeight = 200 };
agree::agree(QWidget* parent)
  : QWidget(parent) {
  setWindowIcon(QIcon(":/pic/heart"));
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setFixedSize(windowWidth, windowHeight);
  auto scrGeo = QGuiApplication::primaryScreen()->availableGeometry();
  auto cx = (scrGeo.x() + scrGeo.width()) / 2, cy = (scrGeo.y() + scrGeo.height()) / 2;
  setGeometry(cx - windowWidth / 2, cy - windowHeight / 2, 0, 0);
}

agree::~agree() {

}

void agree::closeEvent(QCloseEvent* event) {
  event->ignore();
}

void agree::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawPixmap(rect(), QPixmap(":/pic/agree"), QRect());
}
