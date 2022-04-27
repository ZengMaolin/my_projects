#include "instrument_process.h"
#include <iostream>
#include <QDebug>
#include <QMetaType>
#include "data_process.h"
#include "ctp_beep.h"


instrument_process::instrument_process(Mdspi* p_md, Tdspi* p_td, QObject* parent)
    : QObject(parent)
{
    //初始化接收的参数。
    md = p_md;
    td = p_td;
    qRegisterMetaType<CThostFtdcDepthMarketDataField>("CThostFtdcDepthMarketDataField");
    qRegisterMetaType<CThostFtdcTradingAccountField>("CThostFtdcTradingAccountField");
    qRegisterMetaType<CThostFtdcInvestorPositionField>("CThostFtdcInvestorPositionField");
    qRegisterMetaType<CThostFtdcOrderField>("CThostFtdcOrderField");
    qRegisterMetaType<CThostFtdcTradeField>("CThostFtdcTradeField");
    connect(md, SIGNAL(send_market_data(CThostFtdcDepthMarketDataField)), this, SLOT(receive_hq_data(CThostFtdcDepthMarketDataField)));
    connect(td, SIGNAL(send_ZJdata(CThostFtdcTradingAccountField)), this, SLOT(receive_ZJ_data(CThostFtdcTradingAccountField)));
    connect(td, SIGNAL(send_CCdata(CThostFtdcInvestorPositionField)), this, SLOT(receive_CC_data(CThostFtdcInvestorPositionField)));
    connect(td, SIGNAL(send_WTdata(CThostFtdcOrderField)), this, SLOT(receive_WT_data(CThostFtdcOrderField)));
    connect(td, SIGNAL(send_CJdata(CThostFtdcTradeField)), this, SLOT(receive_CJ_data(CThostFtdcTradeField)));

    //初始化持仓表格
    spd_all_position_model = new QStandardItemModel();
    spd_all_position_model->setColumnCount(5);
    spd_all_position_model->setHeaderData(0, Qt::Horizontal, "合约名称");
    spd_all_position_model->setHeaderData(1, Qt::Horizontal, "多仓数量");
    spd_all_position_model->setHeaderData(2, Qt::Horizontal, "多仓平均成本");
    spd_all_position_model->setHeaderData(3, Qt::Horizontal, "空仓数量");
    spd_all_position_model->setHeaderData(4, Qt::Horizontal, "空仓平均成本");
    qRegisterMetaType< QVector<int>>("QVector<int>");
    qRegisterMetaType< Qt::Orientation>("Qt::Orientation");


    log_file_path = QCoreApplication::applicationDirPath() + "/log/";/*文件夹全路径名*/
    QDir dir(log_file_path);
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(log_file_path);
    }
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    log_file_path = log_file_path + strDateTime + "/";
    dir.setPath(log_file_path);
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(log_file_path);
    }
    strDateTime = QDateTime::currentDateTime().toString("hh-mm-ss");
    log_file_path = log_file_path + strDateTime + ".txt";
}

instrument_process::~instrument_process()
{
}

void instrument_process::receive_hq_data(CThostFtdcDepthMarketDataField MarketData)
{
    QString HQdata[11];
    QString HQtickdata;

    HQdata[0] = MarketData.InstrumentID;
    HQdata[1] = MarketData.UpdateTime;
    HQdata[2] = QString::number(MarketData.LastPrice);
    HQdata[3] = QString::number(MarketData.BidPrice1);
    HQdata[4] = QString::number(MarketData.BidVolume1);
    HQdata[5] = QString::number(MarketData.AskPrice1);
    HQdata[6] = QString::number(MarketData.AskVolume1);
    HQdata[7] = QString::number(((MarketData.LastPrice - MarketData.PreClosePrice) * 100 / MarketData.PreClosePrice), 'f', 2);
    HQdata[8] = QString::number(MarketData.Volume);
    HQdata[9] = QString::number(MarketData.UpperLimitPrice);
    HQdata[10] = QString::number(MarketData.LowerLimitPrice);

    for (int i = 0; i < 10; i++)
    {
        HQtickdata = HQtickdata + HQdata[i];
        HQtickdata = HQtickdata + ',';
    }
    HQtickdata = HQtickdata + HQdata[10];

    emit send_dataToUI(HQtickdata);
}

void instrument_process::add_hq_instrument(QString id)
{
    for (int i = 0; i < InstrumentID.size(); i++)
    {
        if (id == InstrumentID.at(i))
        {
            qDebug() << "此合约已经存在" << endl;
            return;
        }
    }
    //增加一个id有效性检测，使用td里面的那个数组
    QByteArray bal = id.toLatin1();
    char* g_pInstrument = bal.data();
    g_pInstrumentID[0] = g_pInstrument;
    int rt = md->g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, 1);
    if (!rt)
    {
        qDebug() << ">>>>>>send subscribe ok!" << endl;
        InstrumentID.append(id);
    }
    else
    {
        qWarning() << "--->>>fail to send subscribe!" << endl;
    }
}

void instrument_process::delete_hq_instrument(QString id)
{
    for (int i = 0; i < InstrumentID.size(); i++)
    {
        if (id == InstrumentID.at(i))
        {
            InstrumentID.removeAt(i);
            //增加一个id有效性检测，使用td里面的那个数组
            QByteArray bal = id.toLatin1();
            char* g_pInstrument = bal.data();
            g_pInstrumentID[0] = g_pInstrument;
            int rt = md->g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, 1);
            if (!rt)
            {
                qDebug() << ">>>>>>send unsubscribe ok!" << endl;
            }
            else
            {
                qWarning() << "--->>>fail to unsend subscribe!" << endl;
            }
            return;
        }
    }
    qDebug() << "此合约不存在" << endl;
}

//存储所有的合约
void instrument_process::receive_HY_data(QString hy_data)
{
    QStringList strlist = hy_data.split(',');
    All_instruments_info.append(strlist);
}

void instrument_process::receive_ZJ_data(CThostFtdcTradingAccountField zj_data)
{
    //本地进行操作。。。todo
    QString account = zj_data.AccountID;
    double zqy = zj_data.Balance;
    double bzj = zj_data.CurrMargin;
    double kyzj = zj_data.Available;
    double fxd = bzj * 100 / zqy;

    QString ZJdata = account + ',' + QString("%1").arg(zqy, 0, 'f', 2) + ',' + QString("%1").arg(bzj, 0, 'f', 2) + ',' + QString("%1").arg(kyzj, 0, 'f', 2) + ',' + QString::number(fxd);

    emit send_ZJdata_ui(ZJdata);
}

void instrument_process::receive_CC_data(CThostFtdcInvestorPositionField cc_data)
{
    //本地进行操作。。。todo
    QString dm = cc_data.InstrumentID;
    QString lx = cc_data.PosiDirection;
    int lots = cc_data.Position;
    double cb = cc_data.OpenCost;

    QString CC_data = dm + ',' + lx + ',' + QString::number(lots) + ',' + QString::number(cb);
    emit send_CCdata_ui(CC_data);
}

void instrument_process::receive_WT_data(CThostFtdcOrderField wt_data)
{
    //本地进行操作。。。todo
    QString zt;
    if (wt_data.OrderStatus == THOST_FTDC_OST_AllTraded)
    {
        zt = QString::fromUtf8("全部成交");
    }
    else if (wt_data.OrderStatus == THOST_FTDC_OST_PartTradedQueueing)
    {
        zt = QString::fromUtf8("部分成交");
    }
    else if (wt_data.OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing)
    {
        zt = QString::fromUtf8("部分成交");
    }
    else if (wt_data.OrderStatus == THOST_FTDC_OST_NoTradeQueueing)
    {
        zt = QString::fromUtf8("未成交");
    }
    else if (wt_data.OrderStatus == THOST_FTDC_OST_Canceled)
    {
        zt = QString::fromUtf8("已撤单");
    }
    else { return; }

    QString wttime = wt_data.InsertTime;
    QString dm = wt_data.InstrumentID;
    QString bs = wt_data.Direction;
    QString kp = wt_data.CombOffsetFlag;
    QString lots = QString::number(wt_data.VolumeTotalOriginal);
    QString price = QString::number(wt_data.LimitPrice);
    QString wth = wt_data.OrderSysID;
    QString jys = wt_data.ExchangeID;

    QString WTdata = wttime + ',' + dm + ',' + bs + ',' + kp + ',' + lots + ',' + price + ',' + zt + ',' + wth + ',' + jys;
    emit send_WTdata_ui(WTdata);
    qDebug() << WTdata << endl;
}

void instrument_process::receive_CJ_data(CThostFtdcTradeField cj_data)
{
    //本地进行操作。。。todo
    qDebug() << "=====报单成功成交=====" << endl;
    qDebug() << "成交时间： " << cj_data.TradeTime << endl;
    qDebug() << "合约代码： " << cj_data.InstrumentID << endl;
    qDebug() << "成交价格： " << cj_data.Price << endl;
    qDebug() << "成交量： " << cj_data.Volume << endl;
    qDebug() << "买卖方向： " << cj_data.Direction << endl;
    qDebug() << "开平仓方向： " << cj_data.OffsetFlag << endl;
    qDebug() << "成交号： " << cj_data.TradeID << endl;
    qDebug() << "委托号： " << cj_data.OrderSysID << endl;

    QString cjtime = cj_data.TradeTime;
    QString dm = cj_data.InstrumentID;
    QString bs = cj_data.Direction;
    QString kp = cj_data.OffsetFlag;
    QString lots = QString::number(cj_data.Volume);
    QString price = QString::number(cj_data.Price);
    QString wth = cj_data.OrderSysID;
    QString jys = cj_data.ExchangeID;

    QString CJdata = cjtime + ',' + dm + ',' + bs + ',' + kp + ',' + lots + ',' + price + ',' + wth + ',' + jys;
    emit send_CJdata_ui(CJdata);
}

void instrument_process::receive_trading_order(QStringList data)
{
    QString instrumentID = data.value(0);
    TThostFtdcDirectionType direction;
    char open_or_close;
    char price_type;
    double price = data.value(4).toDouble();
    int volume = data.value(5).toInt();

    if (data.value(2) == "XJ")
    {
        price_type = THOST_FTDC_OPT_LimitPrice;
    }
    else
    {
        //todo 添加策略
        price_type = THOST_FTDC_OPT_LimitPrice;
    }

    if (data.value(1) == "kd")
    {
        ///买卖方向: 买入
        direction = THOST_FTDC_D_Buy;
        ///组合开平标志: 开仓
        open_or_close = THOST_FTDC_OF_Open;
    }
    else if (data.value(1) == "pd")
    {
        ///买卖方向: 卖出
        direction = THOST_FTDC_D_Sell;
        ///组合开平标志: 平仓
        if (data.value(3) == "PJ")
        {
            open_or_close = THOST_FTDC_OF_CloseToday;
        }
        else
        {
            open_or_close = THOST_FTDC_OF_CloseYesterday;
        }
    }
    else if (data.value(1) == "kk")
    {
        ///买卖方向: 卖出
        direction = THOST_FTDC_D_Sell;
        ///组合开平标志: 开仓
        open_or_close = THOST_FTDC_OF_Open;
    }
    else if (data.value(1) == "pk")
    {
        ///买卖方向: 买入
        direction = THOST_FTDC_D_Buy;
        ///组合开平标志: 平仓
        if (data.value(3) == "PJ")
        {
            open_or_close = THOST_FTDC_OF_CloseToday;
        }
        else
        {
            open_or_close = THOST_FTDC_OF_CloseYesterday;
        }
    }
    //td->reqOrderInsert_new(instrumentID, direction, open_or_close, price_type, price, volume);
}

void instrument_process::process_connect(void)
{
    static bool is_MD_disconnetted = false;

    if (md->net_connect_flag)
    {
        if (md->loginFlag)
        {
            CTP_status.MD_status = QString::fromUtf8("已登录");
            QTime current_time = QTime::currentTime();
            QTime time_start1 = QTime::fromString("08:59:58", "hh:mm:ss");
            QTime time_start2 = QTime::fromString("13:29:58", "hh:mm:ss");
            QTime time_start3 = QTime::fromString("20:59:58", "hh:mm:ss");
            QTime time_end1 = QTime::fromString("09:00:00", "hh:mm:ss");
            QTime time_end2 = QTime::fromString("13:30:00", "hh:mm:ss");
            QTime time_end3 = QTime::fromString("21:00:00", "hh:mm:ss");
            if (is_MD_disconnetted ||
                (current_time > time_start1 && current_time < time_end1) ||
                (current_time > time_start2 && current_time < time_end2) ||
                (current_time > time_start3 && current_time < time_end3))
            {
                //重新订阅合约
                char* g_pInstrumentID[1000];
                QByteArray bal[1000];
                char* g_pInstrument;

                int size = InstrumentID.size();
                for (int i = 0; i < size; i++)
                {
                    bal[i] = InstrumentID[i].toLatin1();
                    g_pInstrument = bal[i].data();
                    g_pInstrumentID[i] = g_pInstrument;
                }

                int rt = md->g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, size);
                if (!rt)
                {
                    qDebug() << ">>>>>>send subscribe ok!" << endl;
                    is_MD_disconnetted = false;
                }
                else
                {
                    qWarning() << "--->>>fail to send subscribe!" << endl;
                }
            }
        }
        else
        {
            CTP_status.MD_status = QString::fromUtf8("未登录");
        }
    }
    else
    {
        CTP_status.MD_status = QString::fromUtf8("网络断开");
        is_MD_disconnetted = true;
    }
}

void instrument_process::process_inquire(void)
{
    QStringList message;

    if (td->net_connect_flag)
    {
        if (td->loginFlag)
        {
            CTP_status.TD_Status = QString::fromUtf8("已登录");
            CTP_status.account = td->jy.InvesterID;
            //已登录所以，查询想要的信息。资金、持仓等
            td->reqQueryTradingAccount();
        }
        else
        {
            CTP_status.TD_Status = QString::fromUtf8("未登录");
        }
    }
    else
    {
        CTP_status.TD_Status = QString::fromUtf8("网络断开");
    }

    message << CTP_status.MD_status <<
        CTP_status.TD_Status <<
        CTP_status.account;
    emit send_ctp_status(message);
}

void instrument_process::update_event(void)
{
    static int tick = 0;
    process_connect();
    process_inquire();
    if ((tick % 4) == 0)
    {
        //update_all_position(); //可能会有线程冲突，暂时关闭这部分程序。
        //更新log文件
        update_logFile();
    }
    tick++;
}

extern QStringList log_data;
extern QMutex mutex_log;
void instrument_process::update_logFile(void)
{
    static int file_name_index = 1;
    mutex_log.lock();
    QStringList temp = log_data;
    log_data.clear();
    mutex_log.unlock();

    int size = temp.size();

    if (size > 0)
    {
        //将调试信息写入文件
        QFile file(log_file_path);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&file);
        for (int i = 0; i < size; i++)
        {
            text_stream << temp.value(i);
        }
        file.flush();
        file.close();

        if (file.size() > 1024 * 1024 * 10)
        {
            log_file_path = log_file_path + "_" + QString::number(++file_name_index);
        }
    }

}

void instrument_process::update_all_position(void)
{
    //第一步，clear表格
    spd_all_position_model->clear();
    spd_all_position_model->setColumnCount(5);
    spd_all_position_model->setHeaderData(0, Qt::Horizontal, "合约名称");
    spd_all_position_model->setHeaderData(1, Qt::Horizontal, "多仓数量");
    spd_all_position_model->setHeaderData(2, Qt::Horizontal, "多仓平均成本");
    spd_all_position_model->setHeaderData(3, Qt::Horizontal, "空仓数量");
    spd_all_position_model->setHeaderData(4, Qt::Horizontal, "空仓平均成本");

    QString m_sProjectPath = QCoreApplication::applicationDirPath() + "/data/";/*文件夹全路径名*/
    QDir dir(m_sProjectPath);
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(m_sProjectPath);
    }

    dir.setFilter(QDir::Dirs); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList dirList = dir.entryInfoList();
    int dirCount = dirList.count(); /*获取本文件夹内的文件个数*/
    for (int i = 0; i < dirCount; i++)
    {
        QFileInfo fileInfo = dirList[i]; /*获取每个文件信息*/
        QString name = fileInfo.fileName(); /*获取文件后缀名*/
        QStringList str_list = name.split("_");
        if (str_list.size() == 2)
        {
            QString dir_path = fileInfo.absoluteFilePath() + "/";
            load_position(dir_path, name);
        }

    }
}
void instrument_process::load_position(QString dir_path, QString name)
{
    QDir dir(dir_path);
    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    bool is_setting_file = false;
    int buy_vol = 0;
    int sell_vol = 0;
    double buy_cost = 0;
    double sell_cost = 0;

    for (int i = 0; i < fileCount; i++)
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/
        QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        /*筛选出所有dat文件*/
        if ((QString::compare(suffix, QString("dat"), Qt::CaseInsensitive)) == 0)
        {
            QString filePath = fileInfo.absoluteFilePath();/*获取文件绝对路径即全路径*/
            QFile file(filePath);
            save_position_struct position;
            bool isOk = file.open(QIODevice::ReadOnly);
            if (isOk == true)
            {
                //更新数据
                file.read((char*)&position, sizeof(save_position_struct));
                file.close();

                if (position.spd_direction == 0)
                {
                    buy_vol += position.spd_vol;
                    buy_cost += position.spd_vol * position.cost;
                }
                else
                {
                    sell_vol += position.spd_vol;
                    sell_cost += position.spd_vol * position.cost;
                }

            }

        }
    }
    buy_cost = buy_cost / buy_vol;
    sell_cost = sell_cost / sell_vol;

    if (buy_vol == 0 && sell_vol == 0)
    {
        return;
    }

    int size = spd_all_position_model->rowCount();
    int i = size;

    spd_all_position_model->insertRow(i);
    spd_all_position_model->setData(spd_all_position_model->index(i, 0), name);
    spd_all_position_model->setData(spd_all_position_model->index(i, 1), QString::number(buy_vol));
    spd_all_position_model->setData(spd_all_position_model->index(i, 2), QString::number(buy_cost));
    spd_all_position_model->setData(spd_all_position_model->index(i, 3), QString::number(sell_vol));
    spd_all_position_model->setData(spd_all_position_model->index(i, 4), QString::number(sell_cost));

}

void instrument_process::init(int mode)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_event()));
    timer->start(1500);

    ctp_beep_set(0);//登陆成功，提示音

    process_connect();
    process_inquire();
    update_all_position();

}
