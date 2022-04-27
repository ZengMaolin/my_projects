#pragma once

#include <QObject>
#include "ThostFtdcTraderApi.h"
#include <QTimer>
#pragma execution_character_set("utf-8")
class Tdspi : public QObject, public CThostFtdcTraderSpi
{
    Q_OBJECT

public:
    Tdspi(QObject* parent);
    ~Tdspi();
    void init();

public:
    typedef struct
    {
        char TdFrontAddr[100];                   // 模拟行情前置地址
        TThostFtdcBrokerIDType BrokerID;         // 模拟经纪商代码
        TThostFtdcInvestorIDType InvesterID;     // 投资者账户名
        TThostFtdcPasswordType InvesterPassword; // 投资者密码
        TThostFtdcAuthCodeType  AuthCode;        ///认证码
        TThostFtdcAppIDType AppID;               ///App代码
    }TDstruct;

    TDstruct jy;

    CThostFtdcTraderApi* g_pTradeUserApi = nullptr;                    // 交易指针
    bool loginFlag = false; // 登陆成功的标识
    bool net_connect_flag = false; // 网络连接的标识
    bool whether_need_auth = false;
    typedef struct
    {
        int hycs;
        double hyds;
        QString chinese_name;
        QString exchangeID;
    }HYstruct;

    QString hy_save[20000][5];
    int k = 0;
    // 会话参数
    TThostFtdcFrontIDType   trade_front_id; //前置编号
    TThostFtdcSessionIDType session_id; //会话编号
    TThostFtdcOrderRefType  order_ref;  //报单引用

    QTimer* timer;
    int login_step = 0;
    int login_count = 10000;
    bool first_time_login = true;
public:

signals:
    void td_send_login_status(QString);
    void td_send_login_result();
    void send_HYdata(QString);
    void send_ZJdata(CThostFtdcTradingAccountField);
    void send_CCdata(CThostFtdcInvestorPositionField);
    void send_WTdata(CThostFtdcOrderField);
    void send_CJdata(CThostFtdcTradeField);




    // ---- ctp_api部分回调接口 ---- //
public:
    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected();

    ///登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    void OnFrontDisconnected(int nReason);

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    void OnHeartBeatWarning(int nTimeLapse);

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///投资者结算结果确认响应
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询合约响应
    void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询资金账户响应
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///请求查询投资者持仓响应
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///报单录入请求响应
    void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///报单操作请求响应
    void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

    ///报单通知
    void OnRtnOrder(CThostFtdcOrderField* pOrder);

    ///成交通知
    void OnRtnTrade(CThostFtdcTradeField* pTrade);

    // ---- 自定义函数 ---- //
public:
    HYstruct get_HYinfo(QString);
    QString reqOrderInsert_new(QString instrumentID, TThostFtdcDirectionType direction, char open_or_close, char price_type, double price, int volume, QString jys);
    void reqOrderInsert(
        QString instrumentID,
        QString direction,
        double price,
        int volume); // 个性化报单录入，外部调用
    void reqOrderAction(QString brokerid, QString wth, QString jys, QString instrument); // 请求报单操作
public:
    void reqUserLogin(); // 登录请求
    void reqAuthCode();
    void reqUserLogout(); // 登出请求
    void reqSettlementInfoConfirm(); // 投资者结果确认
    void reqQueryInstrument(); // 请求查询合约
    void reqQueryTradingAccount(); // 请求查询资金帐户
    void reqQueryInvestorPosition(); // 请求查询投资者持仓
    void reqQueryInvestorPosition(QString position);
    void reqOrderInsert(); // 请求报单录入

    bool isErrorRspInfo(CThostFtdcRspInfoField* pRspInfo); // 是否收到错误信息
    bool isMyOrder(CThostFtdcOrderField* pOrder); // 是否我的报单回报
    bool isTradingOrder(CThostFtdcOrderField* pOrder); // 是否正在交易的报单

private slots:
    void time_event(void);
};
