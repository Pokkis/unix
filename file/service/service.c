/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-31 20:07:55
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-05-31 23:03:30
 * @FilePath: /c/unix/file/service.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <err.h>
#include "../common/common.h"

int main()
{
    
    #if USE_BUFF_IO
        FILE *fp = fopen( SHARE_FILE, "wb");
        if(NULL == fp)
        {
            perror("open failed!");
        }
    #else
        int fd = open( SHARE_FILE, O_CREAT | O_WRONLY, 0644);
        if(-1 >= fd)
        {
            perror("open failed!");
        }
    #endif

    while(1)
    {
        data_s data = { 0 };
        time(&data.time);
        #if USE_BUFF_IO
            fwrite(&data, sizeof(data_s), 1, fp);
            fflush(fp);
            fseek(fp, 0, SEEK_SET);
        #else
            int n = write(fd, &data, sizeof(data_s));
            lseek(fd, 0, SEEK_SET);
        #endif
        printf("time:%ld n:%d\n", data.time, n);
        sleep(1);
    }

    #if USE_BUFF_IO
        fclose(fp);
    #else
        close(fd);
    #endif

    return 0;
}