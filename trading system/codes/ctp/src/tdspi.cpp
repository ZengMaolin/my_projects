#include "tdspi.h"
#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <QDebug>
#include <QMutex>



Tdspi::Tdspi(QObject* parent)
    : QObject(parent)
{
}

Tdspi::~Tdspi()
{
}

void Tdspi::init()
{
    qDebug() << "初始化交易..." << endl;
    emit td_send_login_status("1:init td...");
    g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
    g_pTradeUserApi->RegisterSpi(this);                      // 注册事件类
    g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
    g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
    g_pTradeUserApi->RegisterFront(jy.TdFrontAddr);              // 设置交易前置地址
    g_pTradeUserApi->Init();
    login_step = 1;
    login_count = 2;

    //开启定时器，定时刷新存储。
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time_event()));
    timer->start(1000);
}

void Tdspi::time_event(void)
{
    if (net_connect_flag)
    {
        if (!loginFlag)
        {
            login_count--;
            if (login_count <= 0)
            {
                login_count = 4;
                switch (login_step)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    if (whether_need_auth == true)
                    {
                        reqAuthCode();
                        emit td_send_login_status("3:td 开始认证!");
                    }
                    else
                    {
                        reqUserLogin();
                    }
                    break;
                case 3:
                    // 投资者结算结果确认
                    reqSettlementInfoConfirm();
                    break;
                case 4:
                    reqQueryTradingAccount();
                    break;
                case 5:
                    reqQueryInstrument();
                    break;
                case 6:
                    reqQueryInvestorPosition();
                    break;
                default:
                    break;
                }
            }
        }
    }
    else
    {
        qDebug() << "网络断开，等待网络连接" << endl;
        emit td_send_login_status("网络断开，等待网络连接");
    }
}



void Tdspi::OnFrontConnected()
{
    qDebug() << "=====建立网络连接成功=====" << endl;
    // 开始登录
    emit td_send_login_status("2:td 连接成功!");
    login_step = 2;
    login_count = 5;
    net_connect_flag = true;
    if (whether_need_auth == true)
    {
        reqAuthCode();
        emit td_send_login_status("3:td 开始认证!");
    }
    else
    {
        reqUserLogin();
    }
}

void Tdspi::OnRspUserLogin(
    CThostFtdcRspUserLoginField* pRspUserLogin,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        emit td_send_login_status("3:td successfully login!");
        login_step = 3;
        login_count = 3;
        qDebug() << "=====账户登录成功=====" << endl;
        qDebug() << "交易日： " << pRspUserLogin->TradingDay << endl;
        qDebug() << "登录时间： " << pRspUserLogin->LoginTime << endl;
        qDebug() << "经纪商： " << pRspUserLogin->BrokerID << endl;
        qDebug() << "帐户名： " << pRspUserLogin->UserID << endl;
        // 保存会话参数
        trade_front_id = pRspUserLogin->FrontID;
        session_id = pRspUserLogin->SessionID;
        strcpy(order_ref, pRspUserLogin->MaxOrderRef);

        // 投资者结算结果确认
        reqSettlementInfoConfirm();
    }
}

void Tdspi::OnRspAuthenticate(
    CThostFtdcRspAuthenticateField* pRspAuthenticateField,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        emit td_send_login_status("3:认证成功!");
        qDebug() << "=====账户认证成功=====" << endl;
        qDebug() << "appID： " << pRspAuthenticateField->AppID << endl;
        qDebug() << "app type： " << pRspAuthenticateField->AppType << endl;
        // 登陆
        reqUserLogin();
    }
}

void Tdspi::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
    isErrorRspInfo(pRspInfo);
}

void Tdspi::OnFrontDisconnected(int nReason)
{
    qDebug() << "=====网络连接断开=====" << endl;
    qDebug() << "错误码： " << nReason << endl;
    net_connect_flag = false;
    loginFlag = false;
    login_step = 1;
    login_count = 2;
}

void Tdspi::OnHeartBeatWarning(int nTimeLapse)
{
    qDebug() << "=====网络心跳超时=====" << endl;
    qDebug() << "距上次连接时间： " << nTimeLapse << endl;
}

void Tdspi::OnRspUserLogout(
    CThostFtdcUserLogoutField* pUserLogout,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        loginFlag = false; // 登出就不能再交易了 
        qDebug() << "=====账户登出成功=====" << endl;
        qDebug() << "经纪商： " << pUserLogout->BrokerID << endl;
        qDebug() << "帐户名： " << pUserLogout->UserID << endl;
        login_step = 1;
        login_count = 2;
    }
}

void Tdspi::OnRspSettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        qDebug() << "=====投资者结算结果确认成功=====" << endl;
        qDebug() << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << endl;
        qDebug() << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << endl;

        // 请求查询投资者资金账户
        if (!loginFlag)
        {
            emit td_send_login_status("4:投资者结算结果确认成功!");
            login_step = 4;
            login_count = 3;
            reqQueryTradingAccount();
        }
    }
}

void Tdspi::OnRspQryInstrument(
    CThostFtdcInstrumentField* pInstrument,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        QString dm = pInstrument->InstrumentID;
        QString mc = QString::fromLocal8Bit(pInstrument->InstrumentName);
        QString cs = QString::number(pInstrument->VolumeMultiple);
        QString ds = QString::number(pInstrument->PriceTick);
        QString jys = pInstrument->ExchangeID;
        QString HYdata = dm + ',' + mc + ',' + cs + ',' + ds;

        hy_save[k][0] = dm;
        hy_save[k][1] = mc;
        hy_save[k][2] = cs;
        hy_save[k][3] = ds;
        hy_save[k][4] = jys;
        k++;
        if (k >= 15000)
        {
            k = 0;
        }

        emit send_HYdata(HYdata);
    }
    if (bIsLast == true)
    {
        k = 0;
        // 请求查询投资者持仓
        if (!loginFlag)
        {
            emit td_send_login_status("6:合约种类查询成功!");
            login_step = 6;
            login_count = 2;
            reqQueryInvestorPosition();
        }
    }
}

void Tdspi::OnRspQryTradingAccount(
    CThostFtdcTradingAccountField* pTradingAccount,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        emit send_ZJdata(*pTradingAccount);

        // 请求查询合约
        if (bIsLast)
        {
            if (!loginFlag)
            {
                emit td_send_login_status("5:查询投资者资金账户成功!");
                login_step = 5;
                login_count = 4;
                reqQueryInstrument();
            }
        }

    }
}

void Tdspi::OnRspQryInvestorPosition(
    CThostFtdcInvestorPositionField* pInvestorPosition,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        qDebug() << "=====查询投资者持仓成功=====" << endl;
        if (pInvestorPosition)
        {
            if (pInvestorPosition->Position != 0)
            {
                emit send_CCdata(*pInvestorPosition);
            }
        }
        else
            qDebug() << "----->该合约未持仓" << endl;

        if (bIsLast)
        {
            emit td_send_login_status("7:查询投资者持仓成功!");
            if (first_time_login)//只有第一次登陆才需要发送登陆成功命令
            {
                first_time_login = false;
                emit td_send_login_result();
            }
            loginFlag = true;
            login_step = 0;
            login_count = 10000;
        }

    }

}

void Tdspi::OnRspOrderInsert(
    CThostFtdcInputOrderField* pInputOrder,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        qDebug() << "=====报单录入成功=====" << endl;
        qDebug() << "合约代码： " << pInputOrder->InstrumentID << endl;
        qDebug() << "价格： " << pInputOrder->LimitPrice << endl;
        qDebug() << "数量： " << pInputOrder->VolumeTotalOriginal << endl;
        qDebug() << "开仓方向： " << pInputOrder->Direction << endl;
    }
}

void Tdspi::OnRspOrderAction(
    CThostFtdcInputOrderActionField* pInputOrderAction,
    CThostFtdcRspInfoField* pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    if (!isErrorRspInfo(pRspInfo))
    {
        qDebug() << "=====报单操作成功=====" << endl;
        qDebug() << "合约代码： " << pInputOrderAction->InstrumentID << endl;
        qDebug() << "操作标志： " << pInputOrderAction->ActionFlag;
    }
}

void Tdspi::OnRtnOrder(CThostFtdcOrderField* pOrder)
{
    //本地进行操作。。。todo
    if (!pOrder)
        return;
    emit send_WTdata(*pOrder);
}

void Tdspi::OnRtnTrade(CThostFtdcTradeField* pTrade)
{
    //本地进行操作。。。todo
    if (!pTrade)
        return;
    emit send_CJdata(*pTrade);
}

bool Tdspi::isErrorRspInfo(CThostFtdcRspInfoField* pRspInfo)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bResult)
    {
        qDebug() << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << QString::fromLocal8Bit(pRspInfo->ErrorMsg) << endl;
        emit td_send_login_status("ErrorMsg = " + QString::fromLocal8Bit(pRspInfo->ErrorMsg));
    }
    return bResult;
}

void Tdspi::reqUserLogin()
{
    CThostFtdcReqUserLoginField loginReq;
    memset(&loginReq, 0, sizeof(loginReq));
    strcpy(loginReq.BrokerID, jy.BrokerID);
    strcpy(loginReq.UserID, jy.InvesterID);
    strcpy(loginReq.Password, jy.InvesterPassword);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqUserLogin(&loginReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送登录请求成功" << endl;
    else
        qDebug() << "--->>>发送登录请求失败" << endl;
}

void Tdspi::reqAuthCode()
{
    CThostFtdcReqAuthenticateField authReq;
    memset(&authReq, 0, sizeof(authReq));
    strcpy(authReq.BrokerID, jy.BrokerID);
    strcpy(authReq.UserID, jy.InvesterID);
    strcpy(authReq.AppID, jy.AppID);
    strcpy(authReq.AuthCode, jy.AuthCode);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqAuthenticate(&authReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送认证请求成功" << endl;
    else
        qDebug() << "--->>>发送认证请求失败" << endl;
}

void Tdspi::reqUserLogout()
{
    CThostFtdcUserLogoutField logoutReq;
    memset(&logoutReq, 0, sizeof(logoutReq));
    strcpy(logoutReq.BrokerID, jy.BrokerID);
    strcpy(logoutReq.UserID, jy.InvesterID);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqUserLogout(&logoutReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送登出请求成功" << endl;
    else
        qDebug() << "--->>>发送登出请求失败" << endl;
}


void Tdspi::reqSettlementInfoConfirm()
{
    CThostFtdcSettlementInfoConfirmField settlementConfirmReq;
    memset(&settlementConfirmReq, 0, sizeof(settlementConfirmReq));
    strcpy(settlementConfirmReq.BrokerID, jy.BrokerID);
    strcpy(settlementConfirmReq.InvestorID, jy.InvesterID);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqSettlementInfoConfirm(&settlementConfirmReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送投资者结算结果确认请求成功" << endl;
    else
        qDebug() << "--->>>发送投资者结算结果确认请求失败" << endl;
}

void Tdspi::reqQueryInstrument()
{
    CThostFtdcQryInstrumentField instrumentReq;
    memset(&instrumentReq, 0, sizeof(instrumentReq));
    //strcpy(instrumentReq.InstrumentID, g_pTradeInstrumentID);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqQryInstrument(&instrumentReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送合约查询请求成功" << endl;
    else
        qDebug() << "--->>>发送合约查询请求失败" << endl;
}

void Tdspi::reqQueryTradingAccount()
{
    CThostFtdcQryTradingAccountField tradingAccountReq;
    memset(&tradingAccountReq, 0, sizeof(tradingAccountReq));
    strcpy(tradingAccountReq.BrokerID, jy.BrokerID);
    strcpy(tradingAccountReq.InvestorID, jy.InvesterID);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqQryTradingAccount(&tradingAccountReq, requestID);
    if (rt)
        qDebug() << "--->>>发送投资者资金账户查询请求失败" << endl;
}

void Tdspi::reqQueryInvestorPosition()
{
    CThostFtdcQryInvestorPositionField postionReq;
    memset(&postionReq, 0, sizeof(postionReq));
    strcpy(postionReq.BrokerID, jy.BrokerID);
    strcpy(postionReq.InvestorID, jy.InvesterID);
    //strcpy(postionReq.InstrumentID, g_pTradeInstrumentID);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqQryInvestorPosition(&postionReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送投资者持仓查询请求成功" << endl;
    else
        qDebug() << "--->>>发送投资者持仓查询请求失败" << endl;
}

void Tdspi::reqQueryInvestorPosition(QString position)
{
    CThostFtdcQryInvestorPositionField postionReq;
    QByteArray ba = position.toLatin1();
    const char* str = ba.data();

    memset(&postionReq, 0, sizeof(postionReq));
    strcpy(postionReq.BrokerID, jy.BrokerID);
    strcpy(postionReq.InvestorID, jy.InvesterID);
    strcpy(postionReq.InstrumentID, str);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqQryInvestorPosition(&postionReq, requestID);
    if (!rt)
        qDebug() << ">>>>>>发送投资者持仓查询请求成功" << endl;
    else
        qDebug() << "--->>>发送投资者持仓查询请求失败" << endl;
}

void Tdspi::reqOrderInsert()
{
    CThostFtdcInputOrderField orderInsertReq;
    memset(&orderInsertReq, 0, sizeof(orderInsertReq));
    ///经纪公司代码
    strcpy(orderInsertReq.BrokerID, jy.BrokerID);
    ///投资者代码
    strcpy(orderInsertReq.InvestorID, jy.InvesterID);
    ///合约代码
    //strcpy(orderInsertReq.InstrumentID, g_pTradeInstrumentID);
    ///报单引用
    strcpy(orderInsertReq.OrderRef, order_ref);
    ///报单价格条件: 限价
    orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    ///买卖方向: 
    //orderInsertReq.Direction = gTradeDirection;
    ///组合开平标志: 开仓
    orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    ///组合投机套保标志
    orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    ///价格
    //orderInsertReq.LimitPrice = gLimitPrice;
    ///数量：1
    orderInsertReq.VolumeTotalOriginal = 1;
    ///有效期类型: 当日有效
    orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
    ///成交量类型: 任何数量
    orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量: 1
    orderInsertReq.MinVolume = 1;
    ///触发条件: 立即
    orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
    ///强平原因: 非强平
    orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    orderInsertReq.IsAutoSuspend = 0;
    ///用户强评标志: 否
    orderInsertReq.UserForceClose = 0;

    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
    if (!rt)
        qDebug() << ">>>>>>发送报单录入请求成功" << endl;
    else
        qDebug() << "--->>>发送报单录入请求失败" << endl;
}

static int requestID = 0; // 请求编号
QMutex mutex_trading;
void Tdspi::reqOrderInsert(
    QString instrumentID,
    QString direction,
    double price,
    int volume)
{
    mutex_trading.lock();
    CThostFtdcInputOrderField orderInsertReq;

    memset(&orderInsertReq, 0, sizeof(orderInsertReq));
    ///经纪公司代码
    strcpy(orderInsertReq.BrokerID, jy.BrokerID);
    ///投资者代码
    strcpy(orderInsertReq.InvestorID, jy.InvesterID);
    ///合约代码
    strcpy(orderInsertReq.InstrumentID, instrumentID.toStdString().data());
    ///报单引用
    sprintf(order_ref, "%d", requestID);
    strcpy(orderInsertReq.OrderRef, order_ref);
    ///报单价格条件: 限价
    orderInsertReq.OrderPriceType = THOST_FTDC_OPT_LimitPrice;

    if (direction == "kd")
    {
        ///买卖方向: 买入
        orderInsertReq.Direction = THOST_FTDC_D_Buy;
        ///组合开平标志: 开仓
        orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    else if (direction == "pd")
    {
        ///买卖方向: 卖出
        orderInsertReq.Direction = THOST_FTDC_D_Sell;
        ///组合开平标志: 平仓
        orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    }
    else if (direction == "kk")
    {
        ///买卖方向: 卖出
        orderInsertReq.Direction = THOST_FTDC_D_Sell;
        ///组合开平标志: 开仓
        orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    else if (direction == "pk")
    {
        ///买卖方向: 买入
        orderInsertReq.Direction = THOST_FTDC_D_Buy;
        ///组合开平标志: 平仓
        orderInsertReq.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    }

    ///组合投机套保标志
    orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    ///价格
    orderInsertReq.LimitPrice = price;
    ///数量：1
    orderInsertReq.VolumeTotalOriginal = volume;
    ///有效期类型: 当日有效
    orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
    ///成交量类型: 任何数量
    orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量: 1
    orderInsertReq.MinVolume = 1;
    ///触发条件: 立即
    orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
    ///强平原因: 非强平
    orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    orderInsertReq.IsAutoSuspend = 0;
    ///用户强评标志: 否
    orderInsertReq.UserForceClose = 0;

    int rt = g_pTradeUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
    if (!rt)
        qDebug() << ">>>>>>发送报单录入请求成功" << endl;
    else
        qDebug() << "--->>>发送报单录入请求失败" << endl;
    mutex_trading.unlock();
}

void Tdspi::reqOrderAction(QString brokerid, QString wth, QString jys, QString instrument)
{
    CThostFtdcInputOrderActionField orderActionReq;
    QByteArray ba = brokerid.toLatin1();
    char* pbid = ba.data();
    QByteArray wa = wth.toLatin1();
    char* pwth = wa.data();
    QByteArray ja = jys.toLatin1();
    char* pjys = ja.data();
    QByteArray ia = instrument.toLatin1();
    char* pins = ia.data();


    memset(&orderActionReq, 0, sizeof(orderActionReq));
    ///经纪公司代码
    strcpy(orderActionReq.BrokerID, pbid);
    ///投资者代码
    strcpy(orderActionReq.InvestorID, jy.InvesterID);
    ///用户代码
    strcpy(orderActionReq.UserID, jy.InvesterID);
    //  TThostFtdcUserIDType    UserID;
    ///报单操作引用
    //  TThostFtdcOrderActionRefType    OrderActionRef;
    ///报单引用
    //strcpy(orderActionReq.OrderRef, pOrder->OrderRef);
    ///请求编号
    //  TThostFtdcRequestIDType RequestID;
    ///前置编号
    //orderActionReq.FrontID = trade_front_id;
    ///会话编号
    //orderActionReq.SessionID = session_id;
    ///交易所代码
    //  TThostFtdcExchangeIDType    ExchangeID;
    strcpy(orderActionReq.ExchangeID, pjys);
    ///报单编号
    //  TThostFtdcOrderSysIDType    OrderSysID;
    strcpy(orderActionReq.OrderSysID, pwth);
    ///操作标志
    orderActionReq.ActionFlag = THOST_FTDC_AF_Delete;
    ///价格
    //  TThostFtdcPriceType LimitPrice;
    ///数量变化
    //  TThostFtdcVolumeType    VolumeChange;

    ///合约代码
    strcpy(orderActionReq.InstrumentID, pins);
    static int requestID = 0; // 请求编号
    int rt = g_pTradeUserApi->ReqOrderAction(&orderActionReq, ++requestID);
    if (!rt)
    {
        qDebug() << ">>>>>>发送报单操作请求成功" << endl;
        qDebug() << wth + "," + jys + "," + instrument << endl;
    }
    else
    {
        qDebug() << "--->>>发送报单操作请求失败" << endl;
        qDebug() << wth + "," + jys + "," + instrument << endl;
    }
}

bool Tdspi::isMyOrder(CThostFtdcOrderField* pOrder)
{
    return ((pOrder->FrontID == trade_front_id) &&
        (pOrder->SessionID == session_id) &&
        (strcmp(pOrder->OrderRef, order_ref) == 0));
}

bool Tdspi::isTradingOrder(CThostFtdcOrderField* pOrder)
{
    return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
        (pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
        (pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}


Tdspi::HYstruct Tdspi::get_HYinfo(QString HY_code)
{
    HYstruct my_hy;
    for (int i = 0; i < 15000; i++)
    {
        if (HY_code == hy_save[i][0])
        {
            my_hy.hycs = hy_save[i][2].toInt();
            my_hy.hyds = hy_save[i][3].toDouble();
            my_hy.chinese_name = hy_save[i][1];
            my_hy.exchangeID = hy_save[i][4];
            break;
        }
    }

    return my_hy;
}

//新写报单录入函数
QString Tdspi::reqOrderInsert_new(
    QString instrumentID,
    TThostFtdcDirectionType direction,
    char open_or_close,
    char price_type,
    double price,
    int volume,
    QString jys)
{
    CThostFtdcInputOrderField orderInsertReq;
    QString sReturnOrderRef;

    mutex_trading.lock();
    memset(&orderInsertReq, 0, sizeof(orderInsertReq));
    ///经纪公司代码
    strcpy(orderInsertReq.BrokerID, jy.BrokerID);
    ///投资者代码
    strcpy(orderInsertReq.InvestorID, jy.InvesterID);
    ///合约代码
    strcpy(orderInsertReq.InstrumentID, instrumentID.toStdString().data());
    //交易所代码
    strcpy(orderInsertReq.ExchangeID, jys.toStdString().data());
    ///报单引用
    sprintf(order_ref, "%d", requestID);
    strcpy(orderInsertReq.OrderRef, order_ref);
    sReturnOrderRef = QString(order_ref);
    ///报单价格条件: 限价
    orderInsertReq.OrderPriceType = price_type;

    ///买卖方向: 
    orderInsertReq.Direction = direction;
    ///组合开平标志
    orderInsertReq.CombOffsetFlag[0] = open_or_close;

    ///组合投机套保标志
    orderInsertReq.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    ///价格
    orderInsertReq.LimitPrice = price;
    ///数量：1
    orderInsertReq.VolumeTotalOriginal = volume;
    ///有效期类型: 当日有效
    orderInsertReq.TimeCondition = THOST_FTDC_TC_GFD;
    ///成交量类型: 任何数量
    orderInsertReq.VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量: 1
    orderInsertReq.MinVolume = 1;
    ///触发条件: 立即
    orderInsertReq.ContingentCondition = THOST_FTDC_CC_Immediately;
    ///强平原因: 非强平
    orderInsertReq.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    orderInsertReq.IsAutoSuspend = 0;
    ///用户强评标志: 否
    orderInsertReq.UserForceClose = 0;
    //stop_price
    orderInsertReq.StopPrice = 0;

    int rt = g_pTradeUserApi->ReqOrderInsert(&orderInsertReq, ++requestID);
    if (!rt)
    {
        qDebug() << ">>>>>>发送报单录入请求成功" << endl;
        qDebug() << instrumentID << "," << direction << "," << open_or_close << "," << price_type << "," << price << "," << volume << endl;
    }
    else
    {
        qDebug() << "--->>>发送报单录入请求失败" << endl;
        qDebug() << instrumentID << "," << direction << "," << open_or_close << "," << price_type << "," << price << "," << volume << endl;
    }
    mutex_trading.unlock();

    return sReturnOrderRef;
}
