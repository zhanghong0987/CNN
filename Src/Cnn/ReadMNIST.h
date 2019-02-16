#ifndef __MNIST_H__//定义mnist数据集的头文件宏，就像_omp_
#define __MNIST_H__
/* Copyright (c) 2014 Nuri Park
* MNIST loader by Nuri Park - https://github.com/projectgalateia/mnist
*/
//#ifdef USE_MNIST_LOADER /* Fundamental macro to make the code active 主程序调用该时需对其进行宏定义*/

/*/////////////////////////////////////////////////////////////////////
TRAINING SET LABEL FILE(train - labels - idx1 - ubyte) :

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number(MSB first)
0004     32 bit integer  60000            number of items
0008     unsigned byte ? ? label
0009     unsigned byte ? ? label
........
xxxx     unsigned byte ? ? label
The labels values are 0 to 9.

TRAINING SET IMAGE FILE(train - images - idx3 - ubyte) :

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000803(2051) magic number
0004     32 bit integer  60000            number of images
0008     32 bit integer  28               number of rows
0012     32 bit integer  28               number of columns
0016     unsigned byte ? ? pixel
0017     unsigned byte ? ? pixel
........
xxxx     unsigned byte ? ? pixel
Pixels are organized row - wise.Pixel values are 0 to 255. 0 means background(white), 255 means foreground(black).

TEST SET LABEL FILE(t10k - labels - idx1 - ubyte) :

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number(MSB first)
0004     32 bit integer  10000            number of items
0008     unsigned byte ? ? label
0009     unsigned byte ? ? label
........
xxxx     unsigned byte ? ? label
The labels values are 0 to 9.

TEST SET IMAGE FILE(t10k - images - idx3 - ubyte) :

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000803(2051) magic number
0004     32 bit integer  10000            number of images
0008     32 bit integer  28               number of rows
0012     32 bit integer  28               number of columns
0016     unsigned byte ? ? pixel
0017     unsigned byte ? ? pixel
........
xxxx     unsigned byte ? ? pixel
Pixels are organized row - wise.Pixel values are 0 to 255. 0 means background(white), 255 means foreground(black).
/////////////////////////////////////////////////////////////////////*/


#ifdef __cplusplus//满足C++编译条件
extern "C" {
#endif
	/*
	* Make mnist_load function static.
	* Define when the header is included multiple time.
	*/
#ifdef MNIST_STATIC
#define _STATIC static
#else
#define _STATIC 
#endif
	/*
	* Make mnist loader to load image data as double type.
	* It divides unsigned char values by 255.0, so the results ranges from 0.0 to 1.0
	*/
#ifdef MNIST_DOUBLE
#define MNIST_DATA_TYPE double //如果定义了MNIST_DOUBLE，那么28*28的矩阵中将保存double
#else
#define MNIST_DATA_TYPE unsigned char//否则28*28矩阵中保存的是unsigned char类型
#endif

	//一个mnist数据集image的结构体
	typedef struct mnist_data 
	{
		MNIST_DATA_TYPE data[28][28]; /* 28x28 data for the image */
		unsigned int label; /* label : 0 to 9 */
	} mnist_data;

	_STATIC int mnist_load(
		const char *image_filename,
		const char *label_filename,
		mnist_data **data,
		unsigned int *count);

#ifdef __cplusplus//c++支持
}
#endif

//#endif /* USE_MNIST_LOADER */
#endif /* __MNIST_H__ */

