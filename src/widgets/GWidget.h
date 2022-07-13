//
// Created by maicss on 22-7-12.
//

#ifndef GAMUX_INSTALLER_GWIDGET_H
#define GAMUX_INSTALLER_GWIDGET_H


#include <QWidget>
#include <QGraphicsDropShadowEffect>

    /**
     * 光标所在窗口的位置，除了Content外，分别代表四个边缘和四个角。
     */
    enum CursorPosition {
        Top,
        RightTop,
        Right,
        RightBottom,
        Bottom,
        LeftBottom,
        Left,
        LeftTop,
        Content
    };

    /**
     * 小部件内边距
     */
    struct WidgetPadding {
        int top;
        int right;
        int bottom;
        int left;
    };

    class GWidget : public QWidget{
    Q_OBJECT
    public:
        GWidget(QWidget *parent = nullptr);

    public:
        /**
         * 设置圆角大小
         * @param radius 圆角大小
         */
        void setRadius(int radius);
        /**
         * 获取圆角大小
         * @return 当前圆角大小
         */
        int radius() const;

        /**
         * 设置背景颜色
         * @param color 背景颜色
         */
        void setBackground(QBrush brush);

        /**
         * 获取背景颜色
         * @return 当前背景颜色
         */
        QBrush background();
        /**
         * 设置是否允许在任意位置拖动窗口
         * @param allow 是否允许拖动
         */
        void setAllowDrag(bool allow);
        /**
         * 获取当前窗口是否允许拖动
         * @return 当前窗口是否允许拖动
         */
        bool allowDrag() const;
        /**
         * 将设置其layout，并将layout的Margin自动设置为阴影宽度。若需要手动修改Margin，则需要在调用此方法之后修改。
         * @param layout 要设置的布局指针。
         */
        void setLayout(QLayout *layout);
        /**
         * 获取控制窗口阴影的QGraphicsDropShadowEffect指针。
         * @return 控制窗口阴影的QGraphicsDropShadowEffect指针。
         */
        QGraphicsDropShadowEffect *windowShadow();

        /**
         * 设置是否允许拖动边缘调整窗口大小
         * @param allow 是否允许拖动边缘调整窗口大小
         */
        void setAllowResize(bool allow);
        /**
         * 获取是否允许拖动边缘调整窗口大小
         * @param allow 是否允许拖动边缘调整窗口大小
         */
        bool allowResize() const;
        /**
         * 获取可控制调整大小的边缘宽度
         * @return 边缘宽度
         */
        int borderWidth();
        /**
         * 获取光标所在区域
         * @return 光标所在区域
         */
        CursorPosition getCursorPosition();
        /**
         * 设置所有内边距，此内边距包括阴影部分，当内边距为0且该Widget为顶层窗口时，阴影将无法渲染。
         * 若无特殊情况，内边距部分为透明状态
         * @param padding 内边距
         */
        void setPadding(int padding);
        /**
         * 分别设置内边距
         * @param top 上边距
         * @param right 右边距
         * @param bottom 下边距
         * @param left 左边距
         */
        void setPadding(int top, int right, int bottom, int left);
        /**
         * 分别设置内边距
         * @param padding 内边距
         */
        void setPadding(WidgetPadding padding);
        /**
         * 获取内边距
         * @return
         */
        WidgetPadding padding();
    private:
        void initUI();
        virtual void paintEvent(QPaintEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);
    private:
        int m_radius;
        QBrush m_background;
        bool m_allowDrag;
        bool m_isDragging;
        WidgetPadding m_padding;
        QPoint m_startDragPoint;
        QPoint m_startPositionPoint;
        CursorPosition m_startCursorPosition;
        QGraphicsDropShadowEffect *m_shadow;
        QTimer *m_updateTimer;
    };


#endif //GAMUX_INSTALLER_GWIDGET_H
