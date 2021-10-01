import pandas as pd
import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm
import statsmodels.tsa.stattools as ts
import matplotlib.pyplot as plt
import datetime


class cointegration_analysis:
    # init
    def __init__(self, series_A, series_B):
        self.data_A = series_A
        self.data_B = series_B
        self.coin_series = {}
        self.is_co_int = False
        self.std_value = 0
        self.beta = 1

    def ADF_check(self, check_series):
        if len(check_series) == 0:
            print("ADF CHECK 请输入正确序列！！")
            return False, []
        adf = ts.adfuller(check_series)
        if adf[1] < 0.1:  # 小于指定值，证明显著性可以通过检验
            return True, adf
        else:
            return False, adf

    def cointegration_check(self):
        # step2 使用OLS 计算残差序列，验证是否平稳
        model = sm.OLS(self.data_A, self.data_B).fit()
        self.beta = model.params[self.data_B.name]
        self.coin_series = self.data_A - (self.data_B * self.beta)
        res = self.ADF_check(self.coin_series)
        self.is_co_int = res[0]
        self.std_value = np.std(self.coin_series)
        return self.is_co_int, self.std_value

    def run(self):
        return self.cointegration_check()

    def get_result(self):
        return self.is_co_int, self.coin_series, self.std_value, self.beta

    def ecm_analysis(self):
        pass


def get_instrument_info(instrument_id, input_path):

    dir_path = os.path.join(input_path, instrument_id)
    info_file_path = os.path.join(dir_path, trading_instrument + "_info.csv")
    info_data = pd.read_csv(info_file_path, index_col=[0])
    if len(info_data) > 0:
        info_data["change_date"] = pd.to_datetime(info_data["change_date"])
        return info_data
    else:
        print("input err!!")
        return info_data


def get_trade_data(trading_date_start, trading_date_end, df_all):
    return df_all[(df_all["trading_date"] >= trading_date_start)
                  & (df_all["trading_date"] < trading_date_end)]


def get_trade_data_by_workdays(trading_date, direction, days, df_all):
    # 取出数据，包含当天数据 direction 大于0往后，小于等于0往前
    find_date = trading_date
    find_data_count = 0
    res_finding = False
    res_df = pd.DataFrame()

    for i in range(0, 60):
        if find_data_count < days:
            temp_data = df_all[(df_all["trading_date"] >= find_date) & (
                df_all["trading_date"] < (find_date + pd.Timedelta("1 day")))]

            if len(temp_data) > 10:
                find_data_count += 1
                res_df = pd.concat([res_df, temp_data])
        if direction > 0:
            find_date = find_date + pd.Timedelta("1 day")
        else:
            find_date = find_date - pd.Timedelta("1 day")

    if find_data_count >= days:
        res_finding = True
    return res_finding, find_data_count, res_df


class trading_process():
    def __init__(self,tick_size,single_trading_cost):
        #交易状态参数
        self.direction = None  # "a-b", "b-a"
        self.stop_event = "none"
        self.holding = False
        self.trading_index = 0
        self.data_size = 0
        #结果记录参数
        self.enter_record = []
        self.out_record = []
        self.pnl_res = []
        #交易参数
        self.single_cost = single_trading_cost 
        self.open_threshold = None
        self.close_threshold = None
        self.open_threshold2 = None
        self.close_threshold2 = None
        self.training_data_std = None
        self.biggest_lost = None
        self.biggest_profit = None #止盈
        self.df_orignal = pd.DataFrame()
        self.df_processed = pd.DataFrame()
        #产品信息参数
        self.tick_size = tick_size
        self.beta = 1


    def append(self, trading_df):
        self.df_orignal = pd.concat([self.df_orignal,trading_df])    
        temp = pd.DataFrame()
        temp['ask_price_eps'] = trading_df.bid_A - trading_df.ask_B * self.beta
        temp['bid_price_eps'] = trading_df.ask_A - trading_df.bid_B * self.beta
        temp['ask_price'] = trading_df.bid_A - trading_df.ask_B
        temp['bid_price'] = trading_df.ask_A - trading_df.bid_B
        temp['trading_date'] = trading_df.trading_date
        self.df_processed = pd.concat([self.df_processed,temp])
        self.data_size = len(self.df_processed)

    def set_parameters(self, spd_beta, spd_open_thro, spd_close_thro, spd_biggest_lost = None, spd_biggest_profit = None,spd_open_thro2 = None, spd_close_thro2 = None):
        self.beta = spd_beta
        self.open_threshold = spd_open_thro
        self.close_threshold = spd_close_thro
        self.open_threshold2 = spd_open_thro2
        self.close_threshold2 = spd_close_thro2
        self.biggest_lost = spd_biggest_lost
        self.biggest_profit = spd_biggest_profit

    def trading_run(self, open_enable = True):
        start_index = self.trading_index
        self.trading_index = self.data_size
        for idx in range(start_index, self.data_size):
            ask_price = self.df_processed.ask_price_eps[idx] #获取价格
            bid_price = self.df_processed.bid_price_eps[idx]
            if (self.holding == False) and (open_enable == True):
                # 判断进场条件
                if ask_price > self.open_threshold and self.stop_event != 'up_stop' :
                    self.holding = True
                    self.stop_event = "none"
                    self.direction = 'b-a'
                    #记录进场信息
                    print(self.df_processed.index[idx],'b-a进场', self.df_processed.ask_price[idx], ask_price,' count',len(self.enter_record))
                    self.enter_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx], ask_price, self.df_processed.ask_price[idx],self.direction])
                elif bid_price < -self.open_threshold and self.stop_event != 'down_stop':
                    self.holding = True
                    self.stop_event = "none"
                    self.direction = 'a-b'
                    #记录进场信息
                    print(self.df_processed.index[idx],'a-b进场', self.df_processed.bid_price[idx], bid_price,' count',len(self.enter_record))
                    self.enter_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx], bid_price, self.df_processed.bid_price[idx],self.direction])
            elif(self.holding == True):
                #出场判断，正常出场和止损出场
                # 正常离场
                if self.direction == 'a-b' and ask_price > -self.close_threshold:
                    self.holding = False
                    #计算收益
                    out_price = self.df_processed.ask_price[idx]
                    last_enter_price = self.enter_record[-1][4]
                    single_ret = (out_price - last_enter_price)
                    #判断交易日计算手续费
                    if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                        single_cost = self.single_cost
                    else:
                        single_cost = self.single_cost * 2
                    self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])
                    self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                            ask_price, self.df_processed.ask_price[idx],self.direction,single_ret,single_cost])
                    print(self.df_processed.index[idx],'a-b出场', self.df_processed.ask_price[idx], ask_price,'ret:',single_ret - single_cost)    
                elif self.direction =='b-a' and bid_price < self.close_threshold:
                    self.holding = False
                    #计算收益
                    out_price = self.df_processed.bid_price[idx]
                    last_enter_price = self.enter_record[-1][4]
                    single_ret = (last_enter_price - out_price)
                    #判断交易日计算手续费
                    if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                        single_cost = self.single_cost
                    else:
                        single_cost = self.single_cost * 2
                    self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])
                    self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                            bid_price, self.df_processed.bid_price[idx],self.direction,single_ret,single_cost])
                    print(self.df_processed.index[idx],'b-a出场', self.df_processed.bid_price[idx], bid_price,'ret:',single_ret - single_cost)
                elif self.biggest_lost is not None:
                    #判断是否满足强制离场的条件-止损值
                    if self.direction == 'a-b':
                        #计算实时收益
                        out_price = self.df_processed.ask_price[idx]
                        last_enter_price = self.enter_record[-1][4]
                        single_ret = (out_price - last_enter_price)                
                        if single_ret < self.biggest_lost:
                            self.holding = False
                            self.stop_event = 'down_stop'
                            #判断交易日计算手续费
                            if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                                single_cost = self.single_cost
                            else:
                                single_cost = self.single_cost * 2
                            self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])
                            self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                                    ask_price, self.df_processed.ask_price[idx],self.direction,single_ret,single_cost])
                            print(self.df_processed.index[idx],'a-b止损出场', self.df_processed.ask_price[idx], ask_price,'ret:',single_ret - single_cost) 
                    elif self.direction =='b-a':
                        #计算实时收益
                        out_price = self.df_processed.bid_price[idx]
                        last_enter_price = self.enter_record[-1][4]
                        single_ret = (last_enter_price - out_price)
                        if single_ret < self.biggest_lost:
                            self.holding = False
                            self.stop_event = 'up_stop'
                            #判断交易日计算手续费
                            if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                                single_cost = self.single_cost
                            else:
                                single_cost = self.single_cost * 2
                            self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])
                            self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                                    bid_price, self.df_processed.bid_price[idx],self.direction,single_ret,single_cost])
                            print(self.df_processed.index[idx],'b-a止损出场', self.df_processed.bid_price[idx], bid_price,'ret:',single_ret - single_cost)


    def force_close(self):
        idx = self.data_size - 30 #使用收盘前半个小时的价格强制平仓
        ask_price = self.df_processed.ask_price_eps[idx] #获取价格
        bid_price = self.df_processed.bid_price_eps[idx]
        if self.holding:
            # 强制离场
            if self.direction == 'a-b':
                self.holding = False
                #计算收益
                out_price = self.df_processed.ask_price[idx]
                last_enter_price = self.enter_record[-1][4]
                single_ret = (out_price - last_enter_price)
                #判断交易日计算手续费
                if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                    single_cost = self.single_cost
                else:
                    single_cost = self.single_cost * 2
                self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])

                self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                        ask_price, self.df_processed.ask_price[idx],self.direction,single_ret,single_cost])
                print(self.df_processed.index[idx],'a-b强制出场', self.df_processed.ask_price[idx], ask_price,'ret:',single_ret - single_cost)
            elif self.direction =='b-a':
                self.holding = False
                #计算收益
                out_price = self.df_processed.bid_price[idx]
                last_enter_price = self.enter_record[-1][4]
                single_ret = (last_enter_price - out_price)
                #判断交易日计算手续费-相同交易日只付一次，不同交易日付平仓手续费
                if self.enter_record[-1][2] == self.df_processed.trading_date[idx]:
                    single_cost = self.single_cost
                else:
                    single_cost = self.single_cost * 2
                self.pnl_res.append([single_ret,single_cost,single_ret - single_cost])
                self.out_record.append([idx, self.df_processed.index[idx],self.df_processed.trading_date[idx],\
                                        bid_price, self.df_processed.bid_price[idx],self.direction,single_ret,single_cost])
                print(self.df_processed.index[idx],'b-a强制出场', self.df_processed.bid_price[idx], bid_price,'ret:',single_ret - single_cost)





def trading(start_day, end_day, df_all, trading_entity, setting):
    #交易处理函数，轮询时间，生成交易参数回测交易
    print('process:', start_day, 'to', end_day)
    trading_day = start_day
    trading_count = 0
    while trading_day <= end_day:
        if trading_count % setting['trading_delta_work_days'] == 0:
            res_find = get_trade_data_by_workdays(trading_day - pd.Timedelta("1 day"),0,setting['train_data_work_days'],df_all)
            df_train_data = res_find[2]
            #some calculate
            coin_test = cointegration_analysis(df_train_data.last_A,df_train_data.last_B)
            coin_test.run()
            res = coin_test.get_result()
            temp_std = res[2]
            temp_beta = res[3]
            open_thro = temp_std * setting['open_thro_k_std']
            close_thro = temp_std * setting['close_thro_k_std']
            #计算各种阈值，并设置到交易实体当中
            trading_entity.set_parameters(temp_beta, open_thro, close_thro, spd_biggest_lost = setting['biggest_lost'], spd_biggest_profit = setting['biggest_profit'])          

        #取出交易数据
        trading_data = get_trade_data(trading_day,
                                      trading_day + pd.Timedelta("1 day"),
                                      df_all)
        if len(trading_data) > 0:  #有数据
            trading_entity.append(trading_data)
            trading_entity.trading_run()
            trading_count += 1  #交易计数，用作更新参数计数,只有交易日才增加

        #今天数据处理完成，往后增加一天退出循环的关键。
        trading_day += pd.Timedelta("1 day")
    #根据交易的持仓情况进行最后的处理
    if trading_entity.holding == True:
        #再取几天数据进行平仓
        for j in range(0,5):
            #再最多取出5天交易数据
            trading_data = get_trade_data(trading_day,trading_day + pd.Timedelta("1 day"), df_all)
            if len(trading_data) > 0:  #有数据
                trading_entity.append(trading_data)
                trading_entity.trading_run(open_enable = False)
            trading_day += pd.Timedelta("1 day")
            if trading_entity.holding == False:
                break
        #循环结束还没有平仓，则强制平仓
        if trading_entity.holding:
            trading_entity.force_close()
    #整理交易结果

    return trading_day



if __name__ == "__main__":
    trading_instrument = "al"
    dir_data_path = "RESULT_ALL_new"
    trade_start_date = datetime.datetime(2020, 5, 1)
    trade_end_date = datetime.datetime(2020,8, 1)
    #在这里定义交易参数：
    trading_setting = {
        'trading_delta_work_days':1,
        "train_data_work_days": 2,
        "instrument_tick_size": 5,
        "trading_cost": 1.2,
        "biggest_lost": -20,
        "biggest_profit": 10,
        "open_thro_k_std": 1,
        "close_thro_k_std": 0
    }

    df_info = get_instrument_info(trading_instrument, dir_data_path)
    #生成交易实例
    trading_entity = trading_process(trading_setting['instrument_tick_size'],trading_setting['trading_cost'])
    print(df_info)
    #找出交易的时段
    trading_date = trade_start_date
    #找到起始日
    if trading_date < df_info.change_date[0]:
        trading_date = df_info.change_date[0]
    for i in range(0, len(df_info) - 1):
        if trading_date >= df_info.change_date[i] and trading_date < df_info.change_date[i + 1] and trading_date < trade_end_date:
            file_path = os.path.join(dir_data_path, trading_instrument)
            data_all_path = os.path.join(file_path, df_info.a_id[i] + "_" + df_info.b_id[i] + "_final.csv")
            df_data = pd.read_csv(data_all_path, index_col=[0], parse_dates=[0])
            df_data['trading_date'] = pd.to_datetime(df_data['trading_date']) #改变时间列的格式
            end_date = df_info.change_date[i + 1]
            #确保交易到设置的最后一天
            if end_date > trade_end_date:
                end_date = trade_end_date
            #输入交易时段和数据进行交易，以及交易一个主力合约的时段
            trading_date = trading(trading_date, end_date, df_data, trading_entity, trading_setting)
    #如果交易到最后一个主力合约
    if (trading_date >= df_info.change_date[len(df_info) - 1]) and (trading_date < trade_end_date):

        file_path = os.path.join(dir_data_path, trading_instrument)
        data_all_path = os.path.join(file_path, df_info.a_id[len(df_info) - 1] + "_" + df_info.b_id[len(df_info) - 1] + "_final.csv")
        df_data = pd.read_csv(data_all_path, index_col=[0], parse_dates=[0])
        df_data['trading_date'] = pd.to_datetime(df_data['trading_date']) #改变时间列的格式
        end_date = df_info.change_date[len(df_info) - 1] + pd.Timedelta("60 day")
        #确保交易到设置的最后一天
        if end_date > trade_end_date:
            end_date = trade_end_date
        #输入交易时段和数据进行交易，以及交易一个主力合约的时段
        trading_date = trading(trading_date, end_date, df_data, trading_entity, trading_setting)

    #输出结果
    ret = [i[2] for i in trading_entity.pnl_res]
    print('总收益：',np.array(ret).sum())

    import matplotlib.pyplot as plt
    plt.figure(figsize=(10,6))
    plt.plot(np.array(ret).cumsum(), label='pnl')
    plt.legend()
    plt.show()