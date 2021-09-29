import pandas as pd
import os
import sys
import matplotlib.pyplot as plt

#加载主力合约
main_instrument_csv_path = "wind_main_contract.csv"
dir_instrument = "G:\\tick" #数据地址
df_main_instrument = pd.read_csv(main_instrument_csv_path)
df_main_instrument.rename(columns={'Unnamed: 0' :'trading_date'}, inplace=True)
df_main_instrument.set_index('trading_date', inplace=True, drop=True)
df_main_instrument['FU.SHF']

#加载所有文件地址和文件名
all_file_name_list = []
all_file_path_list = []
dir_list = os.listdir(dir_instrument)
for i in range(0,len(dir_list)):
        dir_path = os.path.join(dir_instrument,dir_list[i])
        dir_list2 = os.listdir(dir_path)
        for j in range(0,len(dir_list2)):
            dir_path2 = os.path.join(dir_path,dir_list2[j])
            files_list = os.listdir(dir_path2)
            for file_name in files_list:
                all_file_name_list.append(file_name)
                all_file_path_list.append(os.path.join(dir_path2,file_name))
for x in range(len(all_file_name_list)):
    all_file_name_list[x] = all_file_name_list[x].lower()

print("step1 ok!")

# 遍历每一列
df_res_list = []

for name, item in df_main_instrument.iteritems():
    instrument_id = name.split(".")[0].lower()
    print("process: ",instrument_id)
    #结果存储
    main_instrument_id_list = [] #主力合约id
    second_instrument_id_list = [] #次主力合约id
    instrument_change_date = [] #主力合约换约日
    save_flag = True
    #通过去重找到换约日。-
    item.drop_duplicates(keep='first',inplace=True) 
    item.dropna(inplace=True)
    for trading_date,val in item.items():
        # print(trading_date,val)
        #寻找次主力合约
        main_instrument_id = val.split(".")[0].lower()
        start_year_month = int("".join(list(filter(str.isdigit,val))))
        max_second_instrument_file_size = 0
        find_second_instrument_id = ""
        for index_year_month in range(start_year_month + 1,start_year_month+13):
            find_year_month = index_year_month
            if (find_year_month % 100) > 12:
                find_year_month = find_year_month + 100 - 12
            #处理只有3个数字长度的合约名
            find_year_month_str = str(find_year_month)
            if find_year_month < 100:
                find_year_month_str = find_year_month_str.zfill(3)

            #组装换约日次主力合约名字
            find_second_instrument_name = instrument_id + find_year_month_str + "_" + trading_date.replace("-","") + ".csv"
            res_index = all_file_name_list.index(find_second_instrument_name) if (find_second_instrument_name in all_file_name_list) else -1
            if res_index != -1:
                #获取文件大小
                file_size = os.path.getsize(all_file_path_list[res_index])
                if file_size > max_second_instrument_file_size:
                    max_second_instrument_file_size = file_size
                    find_second_instrument_id = instrument_id + find_year_month_str
        if find_second_instrument_id != "":
            # print("找到次主力合约：",find_second_instrument_id)
            main_instrument_id_list.append(main_instrument_id)
            second_instrument_id_list.append(find_second_instrument_id)
            instrument_change_date.append(trading_date)
        else:
            #合约太不活跃，不再进行处理
            # print(instrument_id,":未找到次主力合约：")
            save_flag = False
    if save_flag:
        print(main_instrument_id_list)
        print(second_instrument_id_list)
        print(instrument_change_date)

        df_save = pd.DataFrame()
        df_save['change_date'] = instrument_change_date
        df_save['a_id'] = main_instrument_id_list
        df_save['b_id'] = second_instrument_id_list
        df_res_list.append([instrument_id,df_save])
    else:
        print("此合约太不活跃，不再研究！！！")

print("step2 ok!")

import datetime
#合成生成主力合约和次主力合约结果
dir_result = "RESULT_ALL_1min"
for m in range(23,len(df_res_list)):

    instrument_ID = df_res_list[m][0]
    print(instrument_ID,m)
    df_info = df_res_list[m][1]
    if not os.path.exists(dir_result):
        os.mkdir(dir_result)
    dir_instrument_result = os.path.join(dir_result,instrument_ID)
    if not os.path.exists(dir_instrument_result):
        os.mkdir(dir_instrument_result)
    df_info.to_csv(os.path.join(dir_instrument_result,instrument_ID + "_info.csv"))

    for row_index in range(0,len(df_info)):
        #找出合约起始和结束的时间
        start_date = datetime.datetime.strptime(df_info.change_date[row_index], '%Y-%m-%d')
        start_date = start_date.date()
        if row_index == len(df_info) - 1:
            end_date = datetime.datetime.now().date()
        else:
            end_date = datetime.datetime.strptime(df_info.change_date[row_index + 1], '%Y-%m-%d').date()
        #起始时间往前加20天，结束时间往后加10天，增加缓冲数据
        start_date = start_date - datetime.timedelta(days=20)
        end_date = end_date + datetime.timedelta(days=10) #不包括最后一天

        #然后根据此时间区间寻找相关合约地址
        instrument_file_id_list_a = [] #主力合约id
        instrument_file_id_list_b = [] #次主力合约id
        for day_count in range((end_date - start_date).days):
            process_date =  start_date + datetime.timedelta(days=day_count)
            process_date_str = process_date.strftime('%Y%m%d')
            #先寻找主力合约
            main_ins_name = df_info.a_id[row_index] + "_" + process_date_str +".csv"
            second_ins_name = df_info.b_id[row_index] + "_" + process_date_str +".csv"
            a_index = all_file_name_list.index(main_ins_name) if (main_ins_name in all_file_name_list) else -1
            b_index = all_file_name_list.index(second_ins_name) if (second_ins_name in all_file_name_list) else -1
            if a_index != -1 and b_index != -1:
                instrument_file_id_list_a.append(all_file_path_list[a_index])
                instrument_file_id_list_b.append(all_file_path_list[b_index])

        print(instrument_file_id_list_a)
        print(instrument_file_id_list_b)

        #加载主力合约数据
        df_new = pd.DataFrame()
        for i in range(0,len(instrument_file_id_list_a)):
            print(i,end=" ")
            df = pd.read_csv(instrument_file_id_list_a[i],header=0,encoding='gb2312')
            df.drop(df.columns[26:42], axis=1, inplace=True)
            df.drop(df.columns[[2,3,5,6,7,8,9,10,14,15,16,17,18,19]], axis=1, inplace=True)
            df['date_time'] = df['业务日期'].astype(str) + " "  + df['最后修改时间'] + '.'+ df['最后修改毫秒'].astype(str) 
            df['交易日'] = df['交易日'].astype(str) #转换交易日为str，之后交易日期需要用到此数据
            df_new = pd.concat([df_new,df],ignore_index=True)
            #去除涨停跌停时价格和数量为0的情况，已经不活跃合约开盘没数据的情况
            df_new=df_new[~df_new['申买量一'].isin([0])]
            df_new=df_new[~df_new['申买价一'].isin([0])]
            df_new=df_new[~df_new['申卖量一'].isin([0])]
            df_new=df_new[~df_new['申卖价一'].isin([0])]

        print("主力合约处理成功")

        #加载次主力合约数据
        df_new2 = pd.DataFrame()
        for i in range(0,len(instrument_file_id_list_b)):
            print(i,end=" ")
            df = pd.read_csv(instrument_file_id_list_b[i],header=0,encoding='gb2312')
            df.drop(df.columns[26:42], axis=1, inplace=True) 
            df.drop(df.columns[[2,3,5,6,7,8,9,10,14,15,16,17,18,19]], axis=1, inplace=True) 
            df['date_time'] = df['业务日期'].astype(str) + " "  + df['最后修改时间'] + '.'+ df['最后修改毫秒'].astype(str) 
            df_new2 = pd.concat([df_new2,df],ignore_index=True)
            #去除涨停跌停时价格和数量为0的情况，已经不活跃合约开盘没数据的情况
            df_new2=df_new2[~df_new2['申买量一'].isin([0])]
            df_new2=df_new2[~df_new2['申买价一'].isin([0])]
            df_new2=df_new2[~df_new2['申卖量一'].isin([0])]
            df_new2=df_new2[~df_new2['申卖价一'].isin([0])]

        print("次主力合约处理成功")

        #merge数据，按照时间merge，出现空值的地方使用前一行数据填充
        df_last = pd.merge(df_new,df_new2,on='date_time',how='outer',suffixes=('_A', '_B')).sort_values(by=['date_time'])
        df_last.drop(df_last.columns[[6,7,13,21,22,28]], axis=1, inplace=True)
        df_last.fillna(method='ffill',inplace=True) #填空值
        df_last['SPD_ask'] = df_last['申买价一_A'] - df_last['申买价一_B']
        df_last['SPD_bid'] = df_last['申卖价一_A'] - df_last['申卖价一_B']
        df_last['SPD_last'] = df_last['最新价_A'] - df_last['最新价_B']
        df_last['date_time'] = pd.DatetimeIndex(df_last['date_time'])
        df_last['trading_date'] = pd.DatetimeIndex(df_last['交易日_A']) #获取交易日
        df_last.set_index('date_time', inplace=True, drop=True)

        #抽取数据，直接按照1min数据抽取一个方法抽取数据
        res = df_last.resample('1min').last()
        res = res.dropna(how='all')

        #去除夜盘结束到开盘前后10分钟数据
        start_time = datetime.time(2,30,0)
        end_time = datetime.time(9,10,0)
        res.drop(res.index[res.index.indexer_between_time(start_time, end_time)], inplace=True)
        #直接删除收盘10分钟和夜盘开盘十分钟
        start_time = datetime.time(14,50,0)
        end_time = datetime.time(21,10,0)
        res.drop(res.index[res.index.indexer_between_time(start_time, end_time)], inplace=True)
        #夜盘收盘时间判断1-凌晨2.30收盘的
        start_time = datetime.time(2,20,0)
        start_time1 = datetime.time(0,50,0)
        end_time = datetime.time(2,40,0)
        #2.30收盘
        if len(res.index.indexer_between_time(start_time, end_time)) > 1:
            res.drop(res.index[res.index.indexer_between_time(start_time, end_time)], inplace=True)
        elif len(res.index.indexer_between_time(start_time1, end_time)) > 1:
            #1.00收盘
            res.drop(res.index[res.index.indexer_between_time(start_time1, end_time)], inplace=True)
        else:
            #23.00收盘
            start_time2 = datetime.time(22,50,0)
            end_time = datetime.time(23,59,59)
            res.drop(res.index[res.index.indexer_between_time(start_time2, end_time)], inplace=True)
            start_time2 = datetime.time(00,00,0)
            end_time = datetime.time(2,40,0)
            res.drop(res.index[res.index.indexer_between_time(start_time2, end_time)], inplace=True)

        #存储我们需要的数据
        df_result = pd.DataFrame()
        df_result["id_A"] = res['合约代码_A']
        df_result["ask_A"] = res['申卖价一_A']
        df_result["ask_vol_A"] = res['申卖量一_A']
        df_result["bid_A"] = res['申买价一_A']
        df_result["bid_vol_A"] = res['申买量一_A']
        df_result["last_A"] = res['最新价_A']
        df_result["id_B"] = res['合约代码_B']
        df_result["ask_B"] = res['申卖价一_B']
        df_result["ask_vol_B"] = res['申卖量一_B']
        df_result["bid_B"] = res['申买价一_B']
        df_result["bid_vol_B"] = res['申买量一_B']
        df_result["last_B"] = res['最新价_B']
        df_result["spd_ask"] = res['SPD_ask']
        df_result["spd_bid"] = res['SPD_bid']
        df_result["spd_last"] = res['SPD_last']
        df_result["trading_date"] = res['trading_date']
        df_result.index = res.index
        df_result.to_csv(os.path.join(dir_instrument_result,df_info.a_id[row_index]+"_"+ df_info.b_id[row_index] + "_final.csv"),encoding='utf_8_sig')

        #存储last价差的图片
        plt.figure(figsize=(25, 8))
        plt.plot(df_result["spd_last"],".", color = "r")
        plt.xlabel("price")
        plt.ylabel("index")
        plt.title("spd_last")
        plt.savefig(os.path.join(dir_instrument_result,df_info.a_id[row_index]+"_"+ df_info.b_id[row_index] +'result.png'))

print(df_res_list)


