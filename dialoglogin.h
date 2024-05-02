#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QMouseEvent>


namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

private:
    QString m_user;
    QString m_pswd;
    int try_count = 0;
    void wirte_settings();
    void read_settings();
    QString en_crypt(const QString &str);

    //重载 实现点击拖拽
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool m_moving = false;
    QPoint m_last_position;



public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

private slots:
    void on_btnOK_clicked();

private:
    Ui::DialogLogin *ui;
};





#endif // DIALOGLOGIN_H
