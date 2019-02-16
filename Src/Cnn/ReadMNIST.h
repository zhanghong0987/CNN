#ifndef __MNIST_H__//����mnist���ݼ���ͷ�ļ��꣬����_omp_
#define __MNIST_H__
/* Copyright (c) 2014 Nuri Park
* MNIST loader by Nuri Park - https://github.com/projectgalateia/mnist
*/
//#ifdef USE_MNIST_LOADER /* Fundamental macro to make the code active ��������ø�ʱ�������к궨��*/

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


#ifdef __cplusplus//����C++��������
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
#define MNIST_DATA_TYPE double //���������MNIST_DOUBLE����ô28*28�ľ����н�����double
#else
#define MNIST_DATA_TYPE unsigned char//����28*28�����б������unsigned char����
#endif

	//һ��mnist���ݼ�image�Ľṹ��
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

#ifdef __cplusplus//c++֧��
}
#endif

//#endif /* USE_MNIST_LOADER */
#endif /* __MNIST_H__ */

