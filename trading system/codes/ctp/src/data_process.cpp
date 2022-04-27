#include "data_process.h"

data_process::data_process(pair_trading_process* pt, QObject* parent)
    : QObject(parent)
{
    /*init*/
    pt_p = pt;
    connect(pt_p, SIGNAL(send_delete_position_table_row(QString)), this, SLOT(delete_position_file(QString)));
    qRegisterMetaType< trading_setting>("trading_setting");
    connect(this, SIGNAL(send_pair_setting(trading_setting)), pt_p->p_ui->setting_ui, SLOT(recieve_setting_value(trading_setting)));
    connect(pt_p->p_ui->setting_ui, SIGNAL(send_setting_value(trading_setting)), this, SLOT(recieve_setting_value(trading_setting)));

    qRegisterMetaType< history_position_status>("history_position_status");
    connect(this, SIGNAL(send_history_data(history_position_status)), pt_p->p_ui, SLOT(receive_add_history_table_row(history_position_status)));
    connect(pt_p, SIGNAL(send_add_history_table_row(history_position_status)), this, SLOT(receive_history_data(history_position_status)));

    m_sProjectPath = QCoreApplication::applicationDirPath() + "/data/";/*文件夹全路径名*/
    QDir dir(m_sProjectPath);
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(m_sProjectPath);
    }

    pair_trading_path = QCoreApplication::applicationDirPath() + "/data/" + pt_p->InsrumentA + "_" + pt_p->InsrumentB + "/";/*文件夹全路径名*/
    dir.setPath(pair_trading_path); //修改文件夹绑定地址
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(pair_trading_path);
    }
    info_path = pair_trading_path + "info.ini";
    QFileInfo file(info_path);

    qDebug() << "开始了，开始了";
    if (file.exists()) //存在储存配置文件
    {
        m_IniFile = new QSettings(info_path, QSettings::IniFormat);
        m_IniFile->beginGroup("parameter");
        int position_index = m_IniFile->value("position_index").toInt();
        int trading_index = m_IniFile->value("trading_index").toInt();
        int history_index = m_IniFile->value("history_index").toInt();
        m_IniFile->endGroup();
        pt_p->position_status_index = position_index;
        pt_p->trading_process_index = trading_index;
        pt_p->history_process_index = history_index;
        //当日撤单次数统计
        m_IniFile->beginGroup("static");
        QString str_time = m_IniFile->value("time").toString();
        pt_p->statistic_data.instrumentB_canceled_order_times = m_IniFile->value("b_cancel_times").toInt();
        pt_p->statistic_data.instrumentA_canceled_order_times = m_IniFile->value("a_cancel_times").toInt();
        m_IniFile->endGroup();

        QDateTime time = QDateTime::fromString(str_time, "yyyy-MM-dd hh:mm:ss");

        QDateTime compare_today_time = QDateTime::currentDateTime();
        compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
        int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);

        QDateTime compare_time = QDateTime::currentDateTime();

        if (delta_secs_now > 0) //在21点以前
        {
            //判断是不是周一，周一要减3天
            QString weekday = compare_time.toString("ddd");
            if (weekday == "星期一")
            {
                compare_time = compare_time.addDays(-3); //减一天
            }
            else
            {
                compare_time = compare_time.addDays(-1); //减一天
            }
        }

        compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

        int delta_secs = time.secsTo(compare_time);

        if (delta_secs > 0) //昨仓算算天数就好
        {
            pt_p->statistic_data.instrumentB_canceled_order_times = 0;
            pt_p->statistic_data.instrumentA_canceled_order_times = 0;
            m_IniFile->beginGroup("static");
            m_IniFile->setValue("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            m_IniFile->setValue("b_cancel_times", pt_p->statistic_data.instrumentB_canceled_order_times);
            m_IniFile->setValue("a_cancel_times", pt_p->statistic_data.instrumentA_canceled_order_times);
            m_IniFile->endGroup();
        }
    }
    else
    {
        m_IniFile = new QSettings(info_path, QSettings::IniFormat);
        m_IniFile->beginGroup("parameter");
        m_IniFile->setValue("position_index", pt_p->position_status_index);
        m_IniFile->setValue("trading_index", pt_p->trading_process_index);
        m_IniFile->setValue("history_index", pt_p->history_process_index);
        m_IniFile->endGroup();

        pt_p->statistic_data.instrumentB_canceled_order_times = 0;
        pt_p->statistic_data.instrumentA_canceled_order_times = 0;
        m_IniFile->beginGroup("static");
        m_IniFile->setValue("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        m_IniFile->setValue("b_cancel_times", pt_p->statistic_data.instrumentB_canceled_order_times);
        m_IniFile->setValue("a_cancel_times", pt_p->statistic_data.instrumentA_canceled_order_times);
        m_IniFile->endGroup();
    }



    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    bool is_setting_file = false;
    for (int i = 0; i < fileCount; i++)
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/
        QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        /*筛选出所有dat文件*/
        if ((QString::compare(suffix, QString("dat"), Qt::CaseInsensitive)) == 0)
        {
            QString filePath = fileInfo.absoluteFilePath();/*获取文件绝对路径即全路径*/
            QString fileName = fileInfo.baseName();/*获取文件后名(不带后缀的文件名)*/
            load_file(filePath, fileName);/*读取文件内容*/

        }
        else if (fileInfo.baseName() == "setting")
        {
            //初始化设置
            if (fileInfo.size() == sizeof(trading_setting)) //先判断文件大小是否一致，不一致直接reset
            {
                QString filePath = fileInfo.absoluteFilePath();/*获取文件绝对路径即全路径*/
                load_setting_file(filePath);
                is_setting_file = true;
                emit send_pair_setting(pt_p->pair_setting);
            }
        }
    }

    if (!is_setting_file)
    {
        recieve_setting_value(pt_p->p_ui->setting_ui->pair_trading_set_struct);
    }

    QString history_dir_path = pair_trading_path + "history/";
    dir.setPath(history_dir_path); //修改文件夹绑定地址
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(history_dir_path);
    }
    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList2 = dir.entryInfoList();
    int fileCount2 = fileList2.count(); /*获取本文件夹内的文件个数*/
    for (int i = 0; i < fileCount2; i++)
    {
        QFileInfo fileInfo2 = fileList2[i]; /*获取每个文件信息*/
        QString suffix2 = fileInfo2.suffix(); /*获取文件后缀名*/
        /*筛选出所有dat文件*/
        if ((QString::compare(suffix2, QString("dat"), Qt::CaseInsensitive)) == 0)
        {
            QString filePath2 = fileInfo2.absoluteFilePath();/*获取文件绝对路径即全路径*/
            load_history_file(filePath2);/*读取文件内容*/

        }
    }



    //初始化统计表格
    model_spd = new QStandardItemModel();

    model_spd->setColumnCount(5);
    model_spd->setRowCount(1);
    model_spd->setHeaderData(0, Qt::Horizontal, "持仓总量");
    model_spd->setHeaderData(1, Qt::Horizontal, "平仓盈亏");
    model_spd->setHeaderData(2, Qt::Horizontal, "持仓盈亏");
    model_spd->setHeaderData(3, Qt::Horizontal, "开仓次数");
    model_spd->setHeaderData(4, Qt::Horizontal, "平仓次数");

    model_insA = new QStandardItemModel();

    model_insA->setColumnCount(5);
    model_insA->setRowCount(1);
    model_insA->setHeaderData(0, Qt::Horizontal, "持仓-本地");
    model_insA->setHeaderData(1, Qt::Horizontal, "持仓-远程");
    model_insA->setHeaderData(2, Qt::Horizontal, "下单次数");
    model_insA->setHeaderData(3, Qt::Horizontal, "成交次数");
    model_insA->setHeaderData(4, Qt::Horizontal, "撤单次数");

    model_insB = new QStandardItemModel();

    model_insB->setColumnCount(5);
    model_insB->setRowCount(1);
    model_insB->setHeaderData(0, Qt::Horizontal, "持仓-本地");
    model_insB->setHeaderData(1, Qt::Horizontal, "持仓-远程");
    model_insB->setHeaderData(2, Qt::Horizontal, "下单次数");
    model_insB->setHeaderData(3, Qt::Horizontal, "成交次数");
    model_insB->setHeaderData(4, Qt::Horizontal, "撤单次数");

    qRegisterMetaType< QVector<int>>("QVector<int>");

    pt_p->p_ui->set_spd_models(model_spd, model_insA, model_insB);
}

data_process::~data_process()
{
    delete model_spd;
    delete model_insA;
    delete model_insB;
    delete m_IniFile;
}

void data_process::load_setting_file(QString path)
{
    //to do 
    qDebug() << "加载:" + path;
    //新建文件

    QFile file(path);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (isOk == true)
    {
        //更新数据
        file.read((char*)&pt_p->pair_setting, sizeof(trading_setting));
        file.close();
    }
}

void data_process::recieve_setting_value(trading_setting set_value)
{
    pt_p->pair_setting = set_value;

    QFile new_file(pair_trading_path + "setting");
    bool isOk = new_file.open(QIODevice::WriteOnly);
    if (isOk == true)
    {
        new_file.write((const char*)&pt_p->pair_setting, sizeof(trading_setting));
        new_file.close();
    }
}
void data_process::load_history_file(QString path)
{
    //更新数据
    save_history_position data;
    history_position_status send_data;
    qDebug() << "加载:" + path;
    //新建文件
    QFile file(path);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (isOk == true)
    {

        file.read((char*)&data, sizeof(save_history_position));
        file.close();

        send_data.index = QString::fromUtf8(data.index);
        send_data.instrumentA = QString::fromUtf8(data.instrumentA);
        send_data.instrumentB = QString::fromUtf8(data.instrumentB);
        send_data.spd_direction = QString::fromUtf8(data.spd_direction);
        send_data.spd_vol = QString::fromUtf8(data.spd_vol);
        send_data.start_time = QString::fromUtf8(data.start_time);
        send_data.start_target_price = QString::fromUtf8(data.start_target_price);
        send_data.start_price = QString::fromUtf8(data.start_price);
        send_data.end_time = QString::fromUtf8(data.end_time);
        send_data.end_target_price = QString::fromUtf8(data.end_target_price);
        send_data.end_price = QString::fromUtf8(data.end_price);
        send_data.profit = QString::fromUtf8(data.profit);

        emit send_history_data(send_data);//send to ui
    }
}

void data_process::receive_history_data(history_position_status data)
{
    QFile new_file(pair_trading_path + "history/" + data.index + ".dat");
    save_history_position save_data;
    //更新数据
    char* ptr;
    QByteArray ba;

    ba = data.index.toUtf8();
    ptr = ba.data();
    strcpy(save_data.index, ptr);

    ba = data.instrumentA.toUtf8();
    ptr = ba.data();
    strcpy(save_data.instrumentA, ptr);

    ba = data.instrumentB.toUtf8();
    ptr = ba.data();
    strcpy(save_data.instrumentB, ptr);

    ba = data.spd_direction.toUtf8();
    ptr = ba.data();
    strcpy(save_data.spd_direction, ptr);

    ba = data.spd_vol.toUtf8();
    ptr = ba.data();
    strcpy(save_data.spd_vol, ptr);

    ba = data.start_time.toUtf8();
    ptr = ba.data();
    strcpy(save_data.start_time, ptr);

    ba = data.start_target_price.toUtf8();
    ptr = ba.data();
    strcpy(save_data.start_target_price, ptr);

    ba = data.start_price.toUtf8();
    ptr = ba.data();
    strcpy(save_data.start_price, ptr);

    ba = data.end_time.toUtf8();
    ptr = ba.data();
    strcpy(save_data.end_time, ptr);

    ba = data.end_target_price.toUtf8();
    ptr = ba.data();
    strcpy(save_data.end_target_price, ptr);

    ba = data.end_price.toUtf8();
    ptr = ba.data();
    strcpy(save_data.end_price, ptr);

    ba = data.profit.toUtf8();
    ptr = ba.data();
    strcpy(save_data.profit, ptr);


    bool isOk = new_file.open(QIODevice::WriteOnly);
    if (isOk == true)
    {
        new_file.write((const char*)&save_data, sizeof(save_history_position));
        new_file.close();
    }
}

void data_process::load_file(QString path, QString name)
{
    emit pt_p->send_log_message("加载:" + path);
    //新建文件
    data_group new_data;

    new_data.file_index = name.toInt();
    new_data.file_path = path;
    new_data.file = new QFile(new_data.file_path);
    bool isOk = new_data.file->open(QIODevice::ReadOnly);
    if (isOk == true)
    {
        //更新数据
        new_data.file->read((char*)&new_data.position, sizeof(save_position_struct));
        new_data.file->close();
        data_list.append(new_data);

        position_status new_position;

        new_position.index = new_data.position.index;
        new_position.spd_direction = (POSITION_DIRECTION)new_data.position.spd_direction;
        new_position.spd_vol = new_data.position.spd_vol;
        new_position.close_spd_vol = new_data.position.close_spd_vol;
        new_position.instrumentA = QString::fromUtf8(new_data.position.instrumentA);
        new_position.direction_A = (POSITION_DIRECTION)new_data.position.direction_A; // 0: buy other :sell
        new_position.vol_A = new_data.position.vol_A;
        new_position.instrumentB = QString::fromUtf8(new_data.position.instrumentB);
        new_position.direction_B = (POSITION_DIRECTION)new_data.position.direction_B; // 0: buy other :sell
        new_position.vol_B = new_data.position.vol_B;
        new_position.profit = new_data.position.profit;
        new_position.profit_ticks = new_data.position.profit_ticks;
        new_position.profit_target = new_data.position.profit_target;
        new_position.is_B_optimal = new_data.position.is_B_optimal;
        new_position.cost_A = new_data.position.cost_A;
        new_position.cost_B = new_data.position.cost_B;
        new_position.cost = new_data.position.cost;
        new_position.position_time = QString::fromUtf8(new_data.position.position_time);
        new_position.button.button_text = QString::fromUtf8(new_data.position.button_text);
        new_position.button.enbale = new_data.position.enable;

        new_position.A_CJ = new_data.position.A_CJ;
        new_position.B_CJ = new_data.position.B_CJ;

        //平仓相关
        new_position.close_position_status = new_data.position.close_position_status;
        new_position.start_target_price = new_data.position.start_target_price;

        if (new_data.file_index == new_position.index)
        {
            pt_p->position_list.append(new_position);
        }
        else
        {
            emit pt_p->send_log_message("加载持仓失败，异常持仓:" + name);
        }
    }
}


void data_process::update_statistic_tables()
{
    model_spd->setData(model_spd->index(0, 0), pt_p->statistic_data.spd_total_positions);
    model_spd->setData(model_spd->index(0, 1), pt_p->statistic_data.spd_close_profit);
    model_spd->setData(model_spd->index(0, 2), pt_p->statistic_data.spd_rt_profit);
    model_spd->setData(model_spd->index(0, 3), pt_p->statistic_data.spd_open_times);
    model_spd->setData(model_spd->index(0, 4), pt_p->statistic_data.spd_close_times);

    model_insA->setData(model_insA->index(0, 0), pt_p->statistic_data.instrumentA_local_positons);
    model_insA->setData(model_insA->index(0, 1), pt_p->statistic_data.instrumentA_remote_positions);
    model_insA->setData(model_insA->index(0, 2), pt_p->statistic_data.instrumentA_order_times);
    model_insA->setData(model_insA->index(0, 3), pt_p->statistic_data.instrumentA_finished_order_times);
    model_insA->setData(model_insA->index(0, 4), pt_p->statistic_data.instrumentA_canceled_order_times);

    model_insB->setData(model_insB->index(0, 0), pt_p->statistic_data.instrumentB_local_positons);
    model_insB->setData(model_insB->index(0, 1), pt_p->statistic_data.instrumentB_remote_positions);
    model_insB->setData(model_insB->index(0, 2), pt_p->statistic_data.instrumentB_order_times);
    model_insB->setData(model_insB->index(0, 3), pt_p->statistic_data.instrumentB_finished_order_times);
    model_insB->setData(model_insB->index(0, 4), pt_p->statistic_data.instrumentB_canceled_order_times);
}
/*定时更新函数，定时更新持仓和资金相关信息
*/
void data_process::update_event(void)
{
    //可以更新点啥
    update_statistic_tables();
    //做一个撤单次数以及部分信息存储
    if (update_event_count % 6 == 0) //同步慢一些
    {
        sync_statistic_data();
        //更新index
        m_IniFile->beginGroup("parameter");
        m_IniFile->setValue("position_index", pt_p->position_status_index);
        m_IniFile->setValue("trading_index", pt_p->trading_process_index);
        m_IniFile->setValue("history_index", pt_p->history_process_index);
        m_IniFile->endGroup();
    }
    update_event_count++;
    if (update_event_count % 20 == 0) //15秒计算波动率
    {
        calculateVolatility(pt_p->A_price.last_price_series, 30, pt_p->A_price.price_volatility);
    }

}

bool data_process::calculateVolatility(QList <double> queue, int periodOfSecond, double& fVolatility)
{
    if (queue.size() <= 60)
        return false;

    QList <double> aRet;
    double ret_temp;

    for (int i = queue.size() - 60; i <= queue.size() - 7; i = i + 6)
    {
        ret_temp = 0;
        if (abs(queue[i]) > 0.001)
        {
            ret_temp = (queue[i + 6] / queue[i] - 1) * 100; //转换为百分比
            aRet.append(ret_temp);
        }
    }
    double sum = 0;
    for (int i = 0; i < aRet.size(); ++i)
    {
        sum += aRet[i];
    }
    double meanVal = sum / aRet.size();
    sum = 0;
    for (int i = 0; i < aRet.size(); ++i)
    {
        sum += powf(aRet[i] - meanVal, 2);
    }


    double fSeconds = (1.25 + 1 + 1.5 + 4) * 60 * 60;
    fVolatility = sqrt(sum / (aRet.size() - 1)) * sqrt(fSeconds / periodOfSecond);
    return true;
}

void data_process::sync_statistic_data(void)
{
    //当日撤单次数统计
    m_IniFile->beginGroup("static");
    QString str_time = m_IniFile->value("time").toString();
    m_IniFile->endGroup();

    QDateTime time = QDateTime::fromString(str_time, "yyyy-MM-dd hh:mm:ss");

    QDateTime compare_today_time = QDateTime::currentDateTime();
    compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
    int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);

    QDateTime compare_time = QDateTime::currentDateTime();

    if (delta_secs_now > 0) //在21点以前
    {
        //判断是不是周一，周一要减3天
        QString weekday = compare_time.toString("ddd");
        if (weekday == "星期一")
        {
            compare_time = compare_time.addDays(-3); //减一天
        }
        else
        {
            compare_time = compare_time.addDays(-1); //减一天
        }
    }

    compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

    int delta_secs = time.secsTo(compare_time);

    if (delta_secs > 0) //昨仓算算天数就好
    {
        pt_p->statistic_data.instrumentB_canceled_order_times = 0;
        pt_p->statistic_data.instrumentA_canceled_order_times = 0;
        m_IniFile->beginGroup("static");
        m_IniFile->setValue("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        m_IniFile->setValue("b_cancel_times", pt_p->statistic_data.instrumentB_canceled_order_times);
        m_IniFile->setValue("a_cancel_times", pt_p->statistic_data.instrumentA_canceled_order_times);
        m_IniFile->endGroup();
    }
    else
    {
        m_IniFile->beginGroup("static");
        m_IniFile->setValue("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        m_IniFile->setValue("b_cancel_times", pt_p->statistic_data.instrumentB_canceled_order_times);
        m_IniFile->setValue("a_cancel_times", pt_p->statistic_data.instrumentA_canceled_order_times);
        m_IniFile->endGroup();
    }
}
void data_process::start_data_process(void)
{
    //开启定时器，定时刷新存储。
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_event()));
    timer->start(1500);

}

void data_process::delete_position_file(QString index)
{
    bool is_existed = false;
    QList<data_group>::iterator data_item;
    int i = 0;

    for (data_item = data_list.begin(); data_item != data_list.end(); data_item++)
    {
        if (data_item->file_index == index.toInt())
        {
            is_existed = true;
            break;
        }
        i++;
    }

    if (is_existed) //如果存在则删除文件和内存
    {
        data_item->file->remove();
        data_item->file->close();
        data_list.removeAt(i);
    }
}

void data_process::sync_position_file(position_status receive_position)
{
    //增加一个文件
    bool is_existed = false;
    QList<data_group>::iterator data_item;

    for (data_item = data_list.begin(); data_item != data_list.end(); data_item++)
    {
        if (data_item->file_index == receive_position.index)
        {
            is_existed = true;
            break;
        }
    }

    if (is_existed) //如果存在只更新就好
    {
        bool isOk = data_item->file->open(QIODevice::WriteOnly);
        if (isOk == true)
        {
            //更新数据
            char* ptr;
            QByteArray ba;

            data_item->position.index = receive_position.index;
            data_item->position.spd_direction = receive_position.spd_direction;
            data_item->position.spd_vol = receive_position.spd_vol;
            data_item->position.close_spd_vol = receive_position.close_spd_vol;

            ba = receive_position.instrumentA.toUtf8();
            ptr = ba.data();
            strcpy(data_item->position.instrumentA, ptr);

            data_item->position.direction_A = receive_position.direction_A; // 0: buy other :sell
            data_item->position.vol_A = receive_position.vol_A;

            ba = receive_position.instrumentB.toUtf8();
            ptr = ba.data();
            strcpy(data_item->position.instrumentB, ptr);

            data_item->position.direction_B = receive_position.direction_B; // 0: buy other :sell
            data_item->position.vol_B = receive_position.vol_B;
            data_item->position.profit = receive_position.profit;
            data_item->position.profit_ticks = receive_position.profit_ticks;
            data_item->position.profit_target = receive_position.profit_target;
            data_item->position.is_B_optimal = receive_position.is_B_optimal;
            data_item->position.cost_A = receive_position.cost_A;
            data_item->position.cost_B = receive_position.cost_B;
            data_item->position.cost = receive_position.cost;

            ba = receive_position.position_time.toUtf8();
            ptr = ba.data();
            strcpy(data_item->position.position_time, ptr);

            ba = receive_position.button.button_text.toUtf8();
            ptr = ba.data();
            strcpy(data_item->position.button_text, ptr);

            data_item->position.enable = receive_position.button.enbale;
            data_item->position.A_CJ = receive_position.A_CJ;
            data_item->position.B_CJ = receive_position.B_CJ;
            data_item->position.close_position_status = receive_position.close_position_status;
            data_item->position.start_target_price = receive_position.start_target_price;

            //data_item->file->
            data_item->file->write((const char*)&data_item->position, sizeof(save_position_struct));
            data_item->file->close();
        }
    }
    else
    {
        //新建文件
        data_group new_data;

        new_data.file_index = receive_position.index;
        new_data.file_path = pair_trading_path + QString::number(new_data.file_index) + ".dat";
        new_data.file = new QFile(new_data.file_path);

        bool isOk = new_data.file->open(QIODevice::WriteOnly);
        if (isOk == true)
        {
            //更新数据
            char* ptr;
            QByteArray ba;

            new_data.position.index = receive_position.index;
            new_data.position.spd_direction = receive_position.spd_direction;
            new_data.position.spd_vol = receive_position.spd_vol;
            new_data.position.close_spd_vol = receive_position.close_spd_vol;

            ba = receive_position.instrumentA.toUtf8();
            ptr = ba.data();
            strcpy(new_data.position.instrumentA, ptr);

            new_data.position.direction_A = receive_position.direction_A; // 0: buy other :sell
            new_data.position.vol_A = receive_position.vol_A;

            ba = receive_position.instrumentB.toUtf8();
            ptr = ba.data();
            strcpy(new_data.position.instrumentB, ptr);

            new_data.position.direction_B = receive_position.direction_B; // 0: buy other :sell
            new_data.position.vol_B = receive_position.vol_B;
            new_data.position.profit = receive_position.profit;
            new_data.position.profit_ticks = receive_position.profit_ticks;
            new_data.position.profit_target = receive_position.profit_target;
            new_data.position.is_B_optimal = receive_position.is_B_optimal;
            new_data.position.cost_A = receive_position.cost_A;
            new_data.position.cost_B = receive_position.cost_B;
            new_data.position.cost = receive_position.cost;

            ba = receive_position.position_time.toUtf8();
            ptr = ba.data();
            strcpy(new_data.position.position_time, ptr);

            ba = receive_position.button.button_text.toUtf8();
            ptr = ba.data();
            strcpy(new_data.position.button_text, ptr);

            new_data.position.enable = receive_position.button.enbale;
            new_data.position.A_CJ = receive_position.A_CJ;
            new_data.position.B_CJ = receive_position.B_CJ;
            new_data.position.close_position_status = receive_position.close_position_status;
            new_data.position.start_target_price = receive_position.start_target_price;

            new_data.file->write((const char*)&new_data.position, sizeof(save_position_struct));
            new_data.file->close();
            data_list.append(new_data);
        }
    }
}
