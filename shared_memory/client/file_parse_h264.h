/*
 * @Author: Pokkis 1004267454@qq.com
 * @Date: 2022-05-07 20:47:59
 * @LastEditors: Pokkis 1004267454@qq.com
 * @LastEditTime: 2022-05-08 00:44:18
 * @FilePath: /shared_memory/client/file_parse_h264.h
 * @Description:
 */
#ifndef _FILE_PARSE_H264_H_
#define _FILE_PARSE_H264_H_

/**
 * @description: 
 * @param {unsigned char} *p_data 源数据
 * @param {int} *p_pre_len nal type前的长度
 * @return {*}
 */
unsigned char *find_nal_position(const unsigned char *p_data, const int data_len, int *p_pre_len);

#endif