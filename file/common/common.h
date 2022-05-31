/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-31 20:08:13
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-05-31 22:42:58
 * @FilePath: /c/unix/file/common/common.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define   USE_BUFF_IO 0
#define   SHARE_FILE  "../common/time"

typedef struct _data_s
{
    time_t time;
}data_s;

#endif