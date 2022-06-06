/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-31 20:08:13
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-06-06 21:03:01
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

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
inline int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock	lock;

	lock.l_type = type;		/* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset;	/* byte offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	return (fcntl(fd, cmd, &lock));
}

#define	read_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define	readw_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define	write_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define	writew_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define	un_lock(fd, offset, whence, len) \
			lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

#endif