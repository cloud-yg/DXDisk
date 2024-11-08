#ifndef WEBDISKWIGET_H
#define WEBDISKWIGET_H

#include <QWidget>
#include <QTreeWidget>
#include "protocol.h"
#include "sharefilewidget.h"

namespace Ui {
class WebDiskWiget;
}

class WebDiskWiget : public QWidget
{
    Q_OBJECT

public:
    explicit WebDiskWiget(QWidget *parent = nullptr);
    ~WebDiskWiget();
    //设置显示文件图标，类型
    void refreshFileList(std::shared_ptr<PDU> pdu);     //刷新当前文件夹的文件信息
    void refresh();
    QString getUploadFilePath();
    QString getSaveFilePath();
    QString getShareFileName();
    QString getMoveFilePath();

private slots:
    void on_m_pCreateDirPB_clicked();   //新建文件夹

    void on_m_pRefreshDirPB_clicked();  //刷新当前文件夹内容

    void on_m_pDeletePB_clicked();      //删除文件

    void on_m_pRenameFilePB_clicked();  //重命名文件

    void on_m_pFileInfoTreeW_doubleClicked(const QModelIndex &index);

    void on_m_pReturnPB_clicked();

    void on_m_pUploadFilePB_clicked();

    void on_m_pDownloadFilePB_clicked();

    void on_m_pShareFilePB_clicked();

    void on_m_pMoveFilePB_clicked();

private:
    Ui::WebDiskWiget *ui;
    QMap<QString,QPair<int,qint64>> m_mapFileInfo;   //保存当前路径所有的文件信息,使用QList会有奇怪的BUG,不知道为什么
    QString m_strUploadFilePath;    //上传文件路径
    QString m_strSaveFilePath;      //下载文件保存的路径
    QString m_strShareFileName;     //分享文件名
    QString m_strMoveFilePath;      //移动文件名
};

#endif // WEBDISKWIGET_H
