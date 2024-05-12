#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义数据结构表示电阻值和对应的温度
typedef struct
{
    float resistance;
    float temperature;
} DataPoint;

// 定义数据表格的最大大小
#define MAX_DATA_SIZE 351

float binarySearch(DataPoint data[], int data_size, float cur_resistance)
{
    float cur_temperature;

    int low = 0;
    int high = data_size - 1;

    float epsilon = 0.000001; // 定义一个很小的误差范围

    if (cur_resistance > data[0].resistance)
    {
        printf("R Value above lower bound. Returning lowest temperature.\n");
        return data[0].temperature;
    }
    if (cur_resistance < data[data_size - 1].resistance)
    {
        printf("R Value below upper bound. Returning highest temperature.\n");
        return data[data_size - 1].temperature;
    }

    // 二分查找函数
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        printf("data[%d].resistance:%f\n", mid, data[mid].resistance);
        if (fabs(data[mid].resistance - cur_resistance) < epsilon)
        {
            // 找到匹配的电阻值
            cur_temperature = data[mid].temperature;
            printf("finded temperature for cur_resistance %f: %f\n", cur_resistance, cur_temperature);
            return cur_temperature;
        }
        else if (data[mid].resistance > cur_resistance)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
        printf("low:%d,high:%d\n", low, high);
    }

    // 没有找到匹配的电阻值
    printf("cur_resistance:%f\n", cur_resistance);
    printf("low:%d,R:%f,cur_temperature:%f\n", low, data[low].resistance, data[low].temperature);
    printf("high:%d,R:%f,cur_temperature:%f\n", high, data[high].resistance, data[high].temperature);

    if (low != high)
    {
        // 计算插值比例
        float ratio = (cur_resistance - data[low].resistance) / (data[high].resistance - data[low].resistance);

        // 计算插值温度
        cur_temperature = data[low].temperature + ratio * (data[high].temperature - data[low].temperature);

        // 输出插值结果
        printf("nofind temperature for cur_resistance %f: %f\n", cur_resistance, cur_temperature);
    }
    else
    {
        cur_temperature = data[low].temperature;
    }

    return cur_temperature;
}

int main()
{
    FILE *file = fopen("temp.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    DataPoint data[MAX_DATA_SIZE];
    int data_size = 0;

    // 从CSV文件中读取第二列数据（电阻值）
    while (fscanf(file, "%f,%*f,%f,%*f\n", &data[data_size].temperature, &data[data_size].resistance) == 2)
    {
        data_size++;
        if (data_size >= MAX_DATA_SIZE)
        {
            printf("Exceeded maximum data size.\n");
            break;
        }
    }
    fclose(file);

    for (int i = 0; i < MAX_DATA_SIZE; i++)
    {
        printf("i:%d,t:%f,r:%f\n", i, data[i].temperature, data[i].resistance);
        // printf("{%f,%f},\n", data[i].temperature, data[i].resistance);
    }

    // 二分查找给定电阻值
    float given_resistance = 0.0542; // 假设要查找的电阻值为10.0
    float result = binarySearch(data, data_size, given_resistance);
    printf("result:%f\n", result);

    return 0;
}
