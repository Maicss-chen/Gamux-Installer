//
// Created by maicss on 22-7-12.
//

#include "GWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <utility>
#include <QMouseEvent>
#include <QPoint>
#include <QLayout>
#include <QTimer>
#include <QDebug>


GWidget::GWidget(QWidget *parent)
        : QWidget(parent)
        , m_isDragging(false)
        , m_allowDrag(true)
        , m_radius(0)
        , m_updateTimer(new QTimer)
        , m_shadow(new QGraphicsDropShadowEffect(this))
        , m_padding(WidgetPadding{0,0,0,0})
{
    initUI();
}

void GWidget::initUI() {
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    this->setGraphicsEffect(m_shadow);
    m_shadow->setEnabled(false);
    if (parent() == nullptr) {
        setBackground(QColor("#fff"));
    }
    m_shadow->setOffset(9,9);
    m_shadow->setBlurRadius(18);
    m_updateTimer->setInterval(1000/60+1);
    connect(m_updateTimer, &QTimer::timeout,[=](){
        if(layout() != nullptr) {
            int top_w = m_shadow->blurRadius()/2 - m_shadow->offset().y();
            int left_w = m_shadow->blurRadius()/2- m_shadow->offset().x();
            int right_w = m_shadow->blurRadius()/2+ m_shadow->offset().x();
            int bottom_w = m_shadow->blurRadius()/2+ m_shadow->offset().y();
            if (windowShadow()->isEnabled() && !isMaximized())
                layout()->setContentsMargins(left_w,top_w,right_w,bottom_w);
            else
                layout()->setMargin(0);
        }
    });
    m_updateTimer->start();
    this->setMouseTracking(true);
}

void GWidget::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);	// 反锯齿;

    QRect rect = this->rect();
    QPainterPath painterPath;

    if (isMaximized()) {
        painterPath.addRect(rect);
    } else {
        rect.setLeft(padding().left);
        rect.setTop(padding().top);
        rect.setWidth(rect.width() - padding().right);
        rect.setHeight(rect.height() - padding().bottom);
        painterPath.addRoundedRect(rect, radius(), radius());
    }
    painter.fillPath(painterPath,QBrush(background()));
}

void GWidget::setRadius(int radius) {
    m_radius = radius;
}

int GWidget::radius() const {
    return m_radius;
}

void GWidget::setBackground(QBrush brush) {
    m_background = std::move(brush);
}

QBrush GWidget::background() {
    return m_background;
}

void GWidget::setAllowDrag(bool allow) {
    m_allowDrag = allow;
}

bool GWidget::allowDrag() const {
    return m_allowDrag;
}

void GWidget::mousePressEvent(QMouseEvent *event) {
    m_isDragging = true;
    m_startDragPoint = event->globalPos();
    m_startPositionPoint = this->pos();
    QWidget::mousePressEvent(event);
}

void GWidget::mouseReleaseEvent(QMouseEvent *event) {
    m_isDragging = false;
    QWidget::mouseReleaseEvent(event);
}

void GWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging && allowDrag()) {
        QPoint pos = event->globalPos();
        this->move(m_startPositionPoint+ pos - m_startDragPoint);
    }
    event->accept();
    QWidget::mouseMoveEvent(event);

}

void GWidget::setLayout(QLayout *layout) {
    QWidget::setLayout(layout);
}

QGraphicsDropShadowEffect *GWidget::windowShadow() {
    return m_shadow;
}

int GWidget::borderWidth() {
    return windowShadow()->blurRadius() + 3;
}

void GWidget::setPadding(int padding) {
    setPadding(padding,padding,padding,padding);
}

void GWidget::setPadding(int top, int right, int bottom, int left) {
    m_padding = WidgetPadding{top, right, bottom, left};
}

void GWidget::setPadding(WidgetPadding padding) {
    m_padding=padding;
}
WidgetPadding GWidget::padding() {
    return m_padding;
}