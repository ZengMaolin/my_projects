#include "Mdspi.h"
#include <fstream>
#include <unordered_map>
#include <QDebug>
#include <QDir>

Mdspi::Mdspi(QObject* parent)
    : QObject(parent)
{
}

Mdspi::~Mdspi()
{
}


// ---- ctp_api回调函数 ---- //
// 连接成功应答
void Mdspi::OnFrontConnected()
{
    qDebug() << "======MD 连接成功======" << endl;
    emit send_login_status("MD 连接成功");
    net_connect_flag = true;
    // 开始登录
    CThostFtdcReqUserLoginField loginReq;
    memset(&loginReq, 0, sizeof(loginReq));
    strcpy(loginReq.BrokerID, hq.BrokerID);
    strcpy(loginReq.UserID, "");
    strcpy(loginReq.Password, "");
    static int requestID = 0; // 请求编号
    int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);
    if (!rt)
        qDebug() << "MD 请求登陆" << endl;
    else
        qDebug() << "MD 请求登陆失败" << endl;
}

// 断开连接通知
void Mdspi::OnFrontDisconnected(int nReason)
{
    qDebug() << "=====DISCONNCT=====" << endl;
    qDebug() << "error code: " << nReason << endl;
    loginFlag = false;
    net_connect_flag = false;
}

// 心跳超时警告
void Mdspi::OnHeartBeatWarning(int nTimeLapse)
{
    qDebug() << "=====heart beat over time=====" << endl;
    qDebug() << "gap: " << nTimeLapse << endl;
}


// 登录应答
void Mdspi::OnRspUserLogin(
    CThostFtdcRspUserLoginField* pRspUserLogin,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "login successfully" << endl;
        qDebug() << "date: " << pRspUserLogin->TradingDay << endl;
        qDebug() << "time: " << pRspUserLogin->LoginTime << endl;
        qDebug() << "broker ID: " << pRspUserLogin->BrokerID << endl;
        qDebug() << "user ID: " << pRspUserLogin->UserID << endl;

        emit send_login_status("MD 登陆成功");
        if (first_time_login) //只有第一次登陆才需要发送登陆成功命令
        {
            first_time_login = false;
            emit send_login_result();
        }
        loginFlag = true;
    }
    else
    {
        qDebug() << "received err0!!--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
        emit send_login_status("MD 登陆失败!!!");
    }
}

// 登出应答
void Mdspi::OnRspUserLogout(
    CThostFtdcUserLogoutField* pUserLogout,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "=====logout=====" << endl;
        qDebug() << "company " << pUserLogout->BrokerID << endl;
        qDebug() << "user id " << pUserLogout->UserID << endl;
        loginFlag = false;
    }
    else
        qDebug() << "received err1--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 错误通知
void Mdspi::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bResult)
        qDebug() << "received err2--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 订阅行情应答
void Mdspi::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!pSpecificInstrument) return;
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "=====successfully subscribe=====" << endl;
        qDebug() << "contract id: " << pSpecificInstrument->InstrumentID << endl;
    }
    else
        qDebug() << "received err3--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 取消订阅行情应答
void Mdspi::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "=====successfully cancel subscribe=====" << endl;
        qDebug() << "contract id: " << pSpecificInstrument->InstrumentID << endl;
    }
    else
        qDebug() << "received err4:--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 订阅询价应答
void Mdspi::OnRspSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "=====subscribe price ok!=====" << endl;
        qDebug() << "contract id: " << pSpecificInstrument->InstrumentID << endl;
    }
    else
        qDebug() << "received err5--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 取消订阅询价应答
void Mdspi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        qDebug() << "=====cancel subscribe price ok=====" << endl;
        qDebug() << "contract id: " << pSpecificInstrument->InstrumentID << endl;
    }
    else
        qDebug() << "received err6--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
}

// 行情详情通知
void Mdspi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
    // 打印行情，字段较多，截取部分
#if 0
    cout << "=====get deep data=====" << endl;
    cout << "date: " << pDepthMarketData->TradingDay << endl;
    cout << "broker ID: " << pDepthMarketData->ExchangeID << endl;
    cout << "contract id: " << pDepthMarketData->InstrumentID << endl;
    cout << "contract id in broker: " << pDepthMarketData->ExchangeInstID << endl;
    cout << "last price " << pDepthMarketData->LastPrice << endl;
    cout << "number: " << pDepthMarketData->Volume << endl;
#endif 

    emit send_market_data(*pDepthMarketData);

}

// 询价详情通知
void Mdspi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
    // 部分询价结果
    qDebug() << "=====got the price result=====" << endl;
    qDebug() << "date: " << pForQuoteRsp->TradingDay << endl;
    qDebug() << "broker id: " << pForQuoteRsp->ExchangeID << endl;
    qDebug() << "contract id: " << pForQuoteRsp->InstrumentID << endl;
    qDebug() << "ask index: " << pForQuoteRsp->ForQuoteSysID << endl;
}

void Mdspi::Init()
{
    // 初始化行情线程
    qDebug() << "init market data" << endl;
    QString con_path = "conn_file/md/";   //md不需要保存在多个账户下
    QDir temp;
    if (!temp.exists(con_path))
        temp.mkpath(con_path);

    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi(con_path.toStdString().c_str(), true);  // 创建行情实例
    g_pMdUserApi->RegisterSpi(this);                     // 注册事件类
    g_pMdUserApi->RegisterFront(hq.MdFrontAddr);         // 设置行情前置地址
    g_pMdUserApi->Init();                                // 连接运行
}
