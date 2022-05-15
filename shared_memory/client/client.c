/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-14 23:56:25
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-05-15 20:22:24
 * @FilePath: /shared_memory/server/service.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <unistd.h>
//#include "../test/my_printf.h"
#include "share_memory.h"

int main()
{
    my_share_buf share_buf = { 0 };
    int n_ret = share_memory_init(&share_buf, SHARE_READ);
    DBG("n_ret:%d\n", n_ret);

    int data = 0;
    int data_size = 0;

    while(1)
    {
        n_ret = share_memory_read(&share_buf, (char *)&data, sizeof(data));
        DBG("n_ret:%d data:%d\n", n_ret, data);
        usleep(500*1000);
    }

    //my_printf();

    return 0;
}