#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include <QMessageBox>
#include <QSettings>

void DialogLogin::wirte_settings()
{
    QSettings settings("AXB-Qt","test_setting");
    settings.setValue("Username", m_user);
    settings.setValue("PSWD", m_pswd);
    settings.setValue("saved", ui->chkBoxSave->isChecked());
}

void DialogLogin::read_settings()
{
    QSettings settings("AXB-Qt", "test_setting");
    bool saved = settings.value("saved", false).toBool();
    m_user = settings.value("Username", "user").toString();
    QString default_PSWD = en_crypt("12345");
    m_pswd = settings.value("PSWD", default_PSWD).toString();

    if(saved)
        ui->editUser->setText(m_user);
    ui->chkBoxSave->setChecked(saved);

}

#include<QCryptographicHash>
QString DialogLogin::en_crypt(const QString &str)
{
    QByteArray bt_array = str.toUtf8();

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(bt_array);
    QByteArray result = hash.result();
    QString md5 = result.toHex();

    return md5;
}

void DialogLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_moving = true;
        m_last_position = (event->globalPosition() - pos()).toPoint();
    }
    return QDialog::mousePressEvent(event);
}

void DialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() && Qt::LeftButton)){
        move((event->globalPosition() - m_last_position).toPoint());
        m_last_position = (event->globalPosition() - pos()).toPoint();
    }
    return QDialog::mouseMoveEvent(event);
}

void DialogLogin::mouseReleaseEvent(QMouseEvent *event)
{
    m_moving = false;
}


DialogLogin::DialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::SplashScreen);

    read_settings();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}


void DialogLogin::on_btnOK_clicked()
{
    QString user = ui->editUser->text().trimmed();
    QString pswd = ui->editPSWD->text().trimmed();

    if(user==m_user && en_crypt(pswd)==m_pswd){
        wirte_settings();
        accept();
    }
    else{
        try_count++;
        if(try_count > 3){
            QMessageBox::critical(this, "警告", "错误次数太多，退出");
            reject();
        }
        else{
            QMessageBox::warning(this, "警告", "用户名或密码错误");
        }

    }

}

