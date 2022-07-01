//
// Created by maicss on 22-6-24.
//

#ifndef GAMEINSTALLER_PAGE_H
#define GAMEINSTALLER_PAGE_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLayout>
#include <QLabel>

class Page : public QWidget {
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    /**
     * 获取父控件（翻页控件）
     * @return
     */
    QStackedWidget *getParentStackedWidget();
    /**
     * 当切换到当前页时触发的事件。
     */
    virtual void showed() = 0;

    /**
     * 当点击下一步时会触发，用于将页面中的设置信息保存
     */
    virtual void updateData() = 0;

public slots:
    void lastStep();
    void nextStep();
    QWidget *mainWidget();
    void setTitle(QString title);
protected:
    QPushButton *btn_next;
    QPushButton *btn_last;
    void updateButtonStatus();
private:
    QWidget *main_widget;
    QVBoxLayout *layout;
    QHBoxLayout *btn_layout;
    QLabel *m_title;
};


#endif //GAMEINSTALLER_PAGE_H
