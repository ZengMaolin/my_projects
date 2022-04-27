#include "windows_manage.h"
#include <QThread>
#include "ctp_beep.h"


windows_manage::windows_manage(QObject* parent)
    : QObject(parent)
{
    p_login_window = new login(0);
    p_ctp_window = new ctp(0);
    md = new Mdspi(0);
    td = new Tdspi(0);

    //initial process thread 
    QThread* m_objThread;
    m_objThread = new QThread();
    Ins_pro = new instrument_process(md, td);
    Ins_pro->moveToThread(m_objThread);
    connect(m_objThread, &QThread::finished, Ins_pro, &QObject::deleteLater);
    connect(this, SIGNAL(send_ins_process_init(int)), Ins_pro, SLOT(init(int)));
    connect(Ins_pro, SIGNAL(send_dataToUI(QString)), p_ctp_window, SLOT(receive_HQ(QString)));
    connect(Ins_pro, SIGNAL(send_ZJdata_ui(QString)), p_ctp_window, SLOT(receive_ZJ(QString)));
    connect(Ins_pro, SIGNAL(send_CCdata_ui(QString)), p_ctp_window, SLOT(receive_CC(QString)));
    connect(Ins_pro, SIGNAL(send_CJdata_ui(QString)), p_ctp_window, SLOT(receive_CJ(QString)));
    connect(Ins_pro, SIGNAL(send_WTdata_ui(QString)), p_ctp_window, SLOT(receive_WT(QString)));
    connect(Ins_pro, SIGNAL(send_ctp_status(QStringList)), p_ctp_window, SLOT(update_ctp_value(QStringList)));
    m_objThread->start();

    p_ctp_window->set_spd_models(Ins_pro->spd_all_position_model);

    connect(p_login_window, SIGNAL(MD_send_message(QStringList)), this, SLOT(get_md_login_data(QStringList)));
    connect(p_login_window, SIGNAL(TD_send_message(QStringList)), this, SLOT(get_td_login_data(QStringList)));

    connect(md, SIGNAL(send_login_status(QString)), p_login_window, SLOT(set_status(QString)));
    connect(md, SIGNAL(send_login_result()), this, SLOT(get_md_login_ok()));

    connect(td, SIGNAL(td_send_login_status(QString)), p_login_window, SLOT(set_status(QString)));
    connect(td, SIGNAL(td_send_login_result()), this, SLOT(get_td_login_ok()));

    connect(td, SIGNAL(send_HYdata(QString)), p_ctp_window, SLOT(receive_HY(QString)));


    connect(p_ctp_window, SIGNAL(send_add_hq_instrumentID(QString)), Ins_pro, SLOT(add_hq_instrument(QString)));
    connect(p_ctp_window, SIGNAL(send_delete_hq_instrumentID(QString)), Ins_pro, SLOT(delete_hq_instrument(QString)));

    //连接pairtrading初始化事件
    connect(p_ctp_window, SIGNAL(send_pair_trading_init(QStringList)), this, SLOT(init_pair_trading(QStringList)));
    connect(p_ctp_window, SIGNAL(send_xiadan(QStringList)), Ins_pro, SLOT(receive_trading_order(QStringList)));
    connect(p_ctp_window, SIGNAL(send_load_configFile(QString)), this, SLOT(load_config_pair_trading(QString)));

    p_login_window->show();
}

windows_manage::~windows_manage()
{
}


void windows_manage::get_td_login_data(QStringList data)
{
    char* md_addr;
    char* broker_id;
    char* td_addr;
    char* user_id;
    char* user_pwd;
    char* app_id;
    char* auth_code;

    QByteArray bal1 = data.at(0).toLatin1();
    QByteArray bal2 = data.at(1).toLatin1();
    QByteArray bal3 = data.at(2).toLatin1();
    QByteArray bal4 = data.at(3).toLatin1();
    QByteArray bal5 = data.at(4).toLatin1();
    QString bal6 = data.at(5);

    md_addr = bal1.data();
    broker_id = bal2.data();
    td_addr = bal3.data();
    user_id = bal4.data();
    user_pwd = bal5.data();

    //初始化行情数据
    strcpy(md->hq.MdFrontAddr, md_addr);
    strcpy(md->hq.BrokerID, broker_id);
    md->Init();

    //初始化交易数据
    strcpy(td->jy.TdFrontAddr, td_addr);
    strcpy(td->jy.BrokerID, broker_id);
    strcpy(td->jy.InvesterID, user_id);
    strcpy(td->jy.InvesterPassword, user_pwd);

    if (bal6 == "auth") //需要认证
    {
        td->whether_need_auth = true;
        QByteArray bal7 = data.at(6).toLatin1();
        QByteArray bal8 = data.at(7).toLatin1();
        app_id = bal7.data();
        auth_code = bal8.data();
        strcpy(td->jy.AppID, app_id);
        strcpy(td->jy.AuthCode, auth_code);
    }

    //登陆行情和交易
    login_way = 1;
}

void windows_manage::get_td_login_ok()
{
    //行情连接成功
    td_status = 1;
    if (md_status == 1) //如果行情连接成功直接登陆
    {
        p_login_window->hide();
        p_ctp_window->show();
        emit send_ins_process_init(login_way);
    }
}

void windows_manage::get_md_login_ok()
{
    //行情连接成功
    md_status = 1;
    if (login_way == 0) //只登陆行情
    {
        p_login_window->hide();
        p_ctp_window->show();
        emit send_ins_process_init(login_way);
    }
    else //登陆行情
    {
        td->init();
    }
}

void windows_manage::get_md_login_data(QStringList data)
{
    char* ch1;
    char* ch2;


    QByteArray bal1 = data.at(0).toLatin1();
    QByteArray bal2 = data.at(1).toLatin1();

    ch1 = bal1.data();
    ch2 = bal2.data();

    strcpy(md->hq.MdFrontAddr, ch1);
    strcpy(md->hq.BrokerID, ch2);
    md->Init(); //只初始化行情数据

    //只登陆行情
    login_way = 0;
    //get_md_login_ok(); //for test
}

void windows_manage::init_pair_trading(QStringList parameters)
{
    //增加判断当前是否存在此组合交易窗口，如果存在则不初始化，提示已经存在

    pair_struct pts = generate_pair_trading();
    pts.p_process->InsrumentA = parameters.at(0);
    pts.p_process->InsrumentB = parameters.at(1);
    pts.p_process->group_mode = parameters.at(2);
    pts.p_process->beta = parameters.at(3).toDouble();
    pts.p_process->widget_tab_index = p_ctp_window->add_new_pair_trading(pts.p_ui,
        pts.p_process->InsrumentA + "-" + pts.p_process->InsrumentB + " (beta=" + QString::number(pts.p_process->beta) + ")");

    disconnect(this, SIGNAL(send_pair_process_init()), 0, 0);
    connect(this, SIGNAL(send_pair_process_init()), pts.p_process, SLOT(init_ui_data()));
    connect(pts.p_process, SIGNAL(send_tabwidget_text_color(QString)), p_ctp_window, SLOT(set_tabwidget_text_color(QString)), Qt::QueuedConnection);

    emit p_ctp_window->send_add_hq_instrumentID(pts.p_process->InsrumentA);
    emit p_ctp_window->send_add_hq_instrumentID(pts.p_process->InsrumentB);

    //先初始化存储线程，再开始pair trading
    pts.data_Save_process = new data_process(pts.p_process);
    //将数据处理类放到单独的线程运行。
    QThread* m_objThread;
    m_objThread = new QThread();
    pts.data_Save_process->moveToThread(m_objThread);
    m_objThread->start();
    pts.thread_Data = m_objThread;

    connect(this, SIGNAL(send_pair_process_init()), pts.data_Save_process, SLOT(start_data_process()));
    qRegisterMetaType< position_status>("position_status");
    connect(pts.p_process, SIGNAL(sync_position_data(position_status)), pts.data_Save_process, SLOT(sync_position_file(position_status)));
    connect(pts.p_ui, SIGNAL(send_close_data(QStringList)), this, SLOT(get_pair_quit_event(QStringList)), Qt::QueuedConnection);

    //存储相关变量
    pts.index = pair_list.size();
    pair_list.append(pts);

    emit send_pair_process_init();


}


void windows_manage::load_config_pair_trading(QString file_path)
{
    //先加载csv文件
    QFile file(file_path);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (isOk == true)
    {
        QTextStream* out = new QTextStream(&file);//文本流
        QStringList tempOption = out->readAll().split("\n");//每行以\n区分

        if (tempOption.size() <= 1)
        {
            file.close();
            qDebug() << "文件不对";
            return;
        }

        QStringList head = tempOption.at(0).split(",");
        if (head.size() < 4)
        {
            return;
        }
        if ((head.value(0) != "A") ||
            (head.value(1) != "B") ||
            (head.value(2) != "volume") ||
            (head.value(3) != "target"))
        {
            qDebug() << "文件不对";
            return;
        }

        for (int i = 1; i < tempOption.size(); i++)
        {
            QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分
            if (tempbar.size() > 4)
            {
                //判断是否已经存在此窗口
                bool is_exit = false;
                for (int m = 0; m < pair_list.size(); m++)
                {
                    if (pair_list.value(m).p_process->InsrumentA == tempbar.at(0) &&
                        pair_list.value(m).p_process->InsrumentB == tempbar.at(1) &&
                        pair_list.value(m).p_process->beta == 1)
                    {
                        is_exit = true;
                    }
                }
                if (!is_exit)
                {

                    pair_struct pts = generate_pair_trading();
                    pts.p_process->InsrumentA = tempbar.at(0);
                    pts.p_process->InsrumentB = tempbar.at(1);
                    pts.p_process->group_mode = "A-B";
                    pts.p_process->beta = 1;
                    pts.p_ui->set_config_file_parameter(tempbar);
                    p_ctp_window->add_new_pair_trading(pts.p_ui,
                        pts.p_process->InsrumentA + "-" + pts.p_process->InsrumentB + " (beta=" + QString::number(pts.p_process->beta) + ")");

                    disconnect(this, SIGNAL(send_pair_process_init()), 0, 0);
                    connect(this, SIGNAL(send_pair_process_init()), pts.p_process, SLOT(init_ui_data()));

                    emit p_ctp_window->send_add_hq_instrumentID(pts.p_process->InsrumentA);
                    emit p_ctp_window->send_add_hq_instrumentID(pts.p_process->InsrumentB);

                    //先初始化存储线程，再开始pair trading
                    pts.data_Save_process = new data_process(pts.p_process);
                    //将数据处理类放到单独的线程运行。
                    QThread* m_objThread;
                    m_objThread = new QThread();
                    pts.data_Save_process->moveToThread(m_objThread);
                    m_objThread->start();
                    pts.thread_Data = m_objThread;

                    connect(this, SIGNAL(send_pair_process_init()), pts.data_Save_process, SLOT(start_data_process()));
                    qRegisterMetaType< position_status>("position_status");
                    connect(pts.p_process, SIGNAL(sync_position_data(position_status)), pts.data_Save_process, SLOT(sync_position_file(position_status)));
                    connect(pts.p_ui, SIGNAL(send_close_data(QStringList)), this, SLOT(get_pair_quit_event(QStringList)), Qt::QueuedConnection);

                    //存储相关变量
                    pts.index = pair_list.size();
                    pair_list.append(pts);

                    emit send_pair_process_init();
                }
            }
        }
        file.close();
        qDebug() << "load ok";
    }


}

windows_manage::pair_struct windows_manage::generate_pair_trading(void)
{
    pair_struct ret;
    pair_trading* pts = new pair_trading();
    pair_trading_process* ptt = new pair_trading_process(pts, md, td);

    //将处理类放到单独的线程运行。
    QThread* m_objThread;
    m_objThread = new QThread();
    ptt->moveToThread(m_objThread);
    m_objThread->start();

    ret.threadID = m_objThread;
    ret.p_ui = pts;
    ret.p_process = ptt;
    return ret;
}

void windows_manage::get_pair_quit_event(QStringList data)
{
    int size = pair_list.size();

    QString instrumentA = data[0];
    QString instrumentB = data[1];

    for (int i = 0; i < size; i++)
    {
        if (instrumentA == pair_list[i].p_process->InsrumentA && instrumentB == pair_list[i].p_process->InsrumentB)
        {
            //严格退出顺序
            connect(pair_list[i].threadID, SIGNAL(finished()), pair_list[i].p_process->timer, SLOT(stop()));
            connect(pair_list[i].thread_Data, SIGNAL(finished()), pair_list[i].data_Save_process->timer, SLOT(stop()));
            pair_list[i].thread_Data->quit();
            pair_list[i].threadID->quit();
            pair_list[i].thread_Data->wait();
            pair_list[i].threadID->wait();
            delete pair_list[i].thread_Data;
            delete pair_list[i].threadID;
            delete pair_list[i].data_Save_process;
            delete pair_list[i].p_process;
            delete pair_list[i].p_ui;
            pair_list.removeAt(i);
            break;
        }
    }
}
