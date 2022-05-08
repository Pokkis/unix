/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-07 21:47:49
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-05-08 18:50:57
 * @FilePath: /shared_memory/client/clien.c
 * @Description: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "file_parse_h264.h"

#ifndef DBG
#define DBG(fmt, args...) do { \
                 fprintf(stdout, "[%s:%5d] " fmt, (char *)__FILE__,__LINE__,## args);     \
             } while(0)
#endif

#define TEST_PRINT_FRAM  0
#define TEST_FILE "../test01.h264"
#define TEST_WRITE_FILE "send_01.h264"


static int file_read(const char *p_path, char **p_data)
{
    assert(NULL != p_path);
    assert(NULL != p_data);

    FILE *pf = fopen(p_path, "r");
    if(NULL == pf)
    {
        return -1;
    }
    
    fseek(pf, 0, SEEK_END);
    int file_size = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    if(file_size <= 0)
    {
        fclose(pf);
        return -2;
    }
    *p_data = (char *)malloc(file_size*sizeof(char));
    if(NULL == *p_data)
    {
        fclose(pf);
        return -3;
    }

    int read_len = fread(*p_data, 1, file_size, pf);
    if(file_size != read_len)
    {
        fclose(pf);
        return -4;
    }

    fclose(pf);

    return file_size;

}

static int file_write(const char *p_path, char *p_data, const int data_size)
{
    assert(NULL != p_path);
    assert(NULL != p_data);

    FILE *pf = fopen(p_path, "a+");
    if(NULL == pf)
    {
        return -1;
    }

    int read_len = fwrite(p_data, 1, data_size, pf);
    if(data_size != read_len)
    {
        fclose(pf);
        return -2;
    }

    fclose(pf);

    return read_len;

}

#if TEST_PRINT_FRAM
static void fram_printf(const unsigned char *p_data, const int end_count)
{
    assert(NULL != p_data);
    static int n = 0;
    for(int i = 0; i < end_count; i++)
    {
        printf("%x ", p_data[i]);
        if(i!= 0 && i%16 == 0)
            printf("\n");
    }

    printf("\n");
}
#endif

int nal_type()
{
    enum { NAL_NIDR = 1, NAL_PARTITION_A = 2, NAL_IDR = 5, NAL_SEI = 6, NAL_SPS = 7, NAL_PPS = 8, NAL_AUD = 9, };

    return 0;
}

int main()
{

    unsigned char *p_data = NULL;
    int data_len = file_read(TEST_FILE, &p_data);
    if(data_len > 0 && p_data)
    {
        unsigned char *p_data_tmp = p_data;
        int cur_nal_len = 0;
        int rest_len = data_len;
        int cur_nal_pre = 0;
        unsigned char* last_nal_start = 0;
        int pos = 0;
        pos = find_nal_position(p_data_tmp, rest_len, &cur_nal_pre);
        unsigned char* cur_nal_start = pos >= 0 ? p_data_tmp + pos: NULL;
        last_nal_start = cur_nal_start;

        while(NULL != cur_nal_start && rest_len - cur_nal_pre > 0)
        {
            p_data_tmp = cur_nal_start + cur_nal_pre;
            rest_len -= cur_nal_pre;

            pos = find_nal_position(p_data_tmp, rest_len, &cur_nal_pre);
            cur_nal_start = pos >= 0 ? p_data_tmp + pos: NULL;
            //DBG("p_data_tmp:%x cur_nal_start:%x last_nal_start:%x cur_nal_pre:%d rest_len:%d\n", p_data_tmp, cur_nal_start, last_nal_start, cur_nal_pre, rest_len);
            if(cur_nal_start > 0)
            {
                cur_nal_len = cur_nal_start - last_nal_start;
                #if TEST_PRINT_FRAM
                    fram_printf(last_nal_start, cur_nal_len);
                #endif
                file_write(TEST_WRITE_FILE, last_nal_start, cur_nal_len);
                DBG("pos:%d cur_nal_len:%d type:%x\n", pos, cur_nal_len, last_nal_start[4] & 0x1f);
                last_nal_start = cur_nal_start;
               
            }
            else
            {
                break;
            }
        }
        
        cur_nal_len = p_data + data_len - last_nal_start;

        #if TEST_PRINT_FRAM
            fram_printf(last_nal_start, cur_nal_len);
        #endif

        file_write(TEST_WRITE_FILE, last_nal_start, cur_nal_len);

        DBG("cur_nal_len:%d type:%x\n", cur_nal_len, last_nal_start[4] & 0x1f);
        
    }
    
    DBG("data_len:%d\n", data_len);    

    return 0;
}
