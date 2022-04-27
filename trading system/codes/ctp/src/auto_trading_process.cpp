#include "auto_trading_process.h"

auto_trading_process::auto_trading_process(pair_trading_process* ptr, QObject* parent)
    : QObject(parent)
{
    pt_p = ptr;
}

auto_trading_process::~auto_trading_process()
{

}


void auto_trading_process::init_auto_trading(void)
{
    //开启定时器，定时刷新存储。
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_enevt()));
    timer->start(1000);

    connect(pt_p->p_ui->auto_ui, SIGNAL(send_start_event(bool, QStringList)), this, SLOT(start_auto_trading(bool, QStringList)));
}


void auto_trading_process::timer_enevt(void) //5秒一次
{
    if (atuo_tarding_flag)
    {
        //计算目标买卖价格
        int bid_price_int = pt_p->group_price.delta_AaBa_average / pt_p->HYstruct_B.hyds;
        double bid_price_judge = (double)bid_price_int * pt_p->HYstruct_B.hyds;

        bool is_buy = true;
        double buy_price;
        double sell_price;

        if (pt_p->group_price.delta_AaBa_average > (bid_price_judge + (0.5 * pt_p->HYstruct_B.hyds)))
        {
            is_buy = true;
            buy_price = bid_price_judge;
            sell_price = bid_price_judge + pt_p->HYstruct_B.hyds;
        }
        else
        {
            is_buy = false;
            buy_price = bid_price_judge;
            sell_price = bid_price_judge + pt_p->HYstruct_B.hyds;
        }



        //先处理平仓
        QList<position_status>::iterator position_item;

        //更新各个持仓状态
        total_positon_vol = 0;
        for (position_item = pt_p->position_list.begin(); position_item != pt_p->position_list.end(); position_item++)
        {
            if (position_item->close_position_status == 0) //未平仓，则平仓
            {
                int target_tick = 0;
                if (position_item->spd_direction == POSITION_BUY)
                {
                    target_tick = (sell_price - position_item->cost) / pt_p->HYstruct_B.hyds;
                }
                else
                {
                    target_tick = (position_item->cost - buy_price) / pt_p->HYstruct_B.hyds;
                }

                emit pt_p->p_ui->send_position_action(position_item->index, target_tick, 0, 0);
            }
            total_positon_vol += position_item->spd_vol;
        }

        if (total_positon_vol < 2) //持仓数低于15
        {
            if (pt_p->trading_list.size() < 2) // 当前交易数量低于7组
            {
                if (is_buy == true)
                {
                    QList<double> data;

                    data << 0 << 0 << buy_price << 1;
                    pt_p->p_ui->send_buy_event(data);
                }
                else
                {
                    QList<double> data;

                    data << 1 << 0 << sell_price << 1;
                    pt_p->p_ui->send_buy_event(data);
                }
            }
        }
    }
}

void auto_trading_process::start_auto_trading(bool flag, QStringList data)
{
    atuo_tarding_flag = flag;
    if (atuo_tarding_flag)
    {
        pt_p->send_log_message("启动自动化交易");
    }
    else
    {
        pt_p->send_log_message("暂停自动化交易");
    }
}
