#include "protocol.h"
#include "UniversalFunction.h"
#include <QDebug>

std::shared_ptr<PDU> mk_shared_PDU(uint uiMsgLen)
{
    uint uiPDULen = sizeof(PDU) + uiMsgLen; //计算总协议数据单元大小
    std::shared_ptr<PDU> pdu ((PDU*)malloc(uiPDULen));      //分配大小

    //若分配空间失败，结束程序
    if(pdu == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    memset(pdu.get(),0,uiPDULen);     //清空
    pdu->uiPDULen = uiPDULen;
    pdu->uiMsgLen = uiMsgLen;

    return pdu;
}

FileInfo* getFileInfobyName(const QList<FileInfo*> &fileInfoList, QString name)
{
    for(auto a:fileInfoList)
    {
        qDebug() << a->caFileNameUtf8 << (strcmp(a->caFileNameUtf8 , "答辩.pptx") == 0);
    }

    for(int i=0; i<fileInfoList.size();++i)
    {
        qDebug() << fileInfoList.at(i)->caFileNameUtf8;
        if(fileInfoList.at(i)->caFileNameUtf8 == name.toUtf8())
            return fileInfoList.at(i);
    }
    return nullptr;
}

void showPDUInfo(std::shared_ptr<PDU> pdu)
{
    qDebug() << "PDU INFO BEGIN:";
    qDebug() << "PDULen:" << pdu->uiPDULen;
    qDebug() << "MsgType:" << pdu->uiMsgType;
    QString data = extractValidString(pdu->caData,64);
    qDebug() << "Data:" << data;
    qDebug() << "MsgLen:" <<pdu->uiMsgLen;
    QString msg = extractValidString(pdu->caMsg,pdu->uiMsgLen);
    qDebug() << "Msg:" << msg;
    qDebug() << "PDU INFO END:";
}
