#include "ReadMNIST.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Load a unsigned int from raw data.
* MSB first.
*  Ҳ����ʹ������ĺ�����ReverseInt((int*)tmp)
*/
static unsigned int mnist_bin_to_int(char *v)
{
	int i;
	unsigned int ret = 0;
	for (i = 0; i < 4; ++i) {
		ret <<= 8;
		ret |= (unsigned char)v[i];
	}
	return ret;
}

static int ReverseInt(int *i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = *i & 255;
	ch2 = (*i >> 8) & 255;
	ch3 = (*i >> 16) & 255;
	ch4 = (*i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

/*
* MNIST dataset loader.
*
* Returns 0 if successed.
* Check comments for the return codes.
*/
_STATIC int mnist_load(
	const char *image_filename,
	const char *label_filename,
	mnist_data **data,
	unsigned int *count)
{
	int return_code = 0;
	int i;
	char tmp[4];//һ��int

	unsigned int image_cnt, label_cnt;
	unsigned int image_dim[2];//row and col

	FILE *ifp = fopen(image_filename, "rb");//���ݼ�ͼƬ 28*28
	FILE *lfp = fopen(label_filename, "rb");//���ݼ�label  0~9

	if (!ifp || !lfp) {//�ж��ļ��Ƿ���ڣ��������˳�
		return_code = -1; /* No such files */
		goto cleanup;
	}
	/*Magic numberһ����ָӲд���������������������ֵ�Ǳ�����Լ�ָ���ģ�
	�����˲�֪����ֵ��ʲô�������壬��ʾ�����������ͳ���magic number��*/
	fread(tmp, 1, 4, ifp);//��images�ļ��ж�ȡmagic number
	if (mnist_bin_to_int(tmp) != 2051) {
		return_code = -2; /* Not a valid image file */
		goto cleanup;
	}
	//printf("magic number: %d (%s)\n", mnist_bin_to_int(tmp), tmp);

	fread(tmp, 1, 4, lfp);//��label�ļ��ж�ȡmagic number
	if (mnist_bin_to_int(tmp) != 2049) {
		return_code = -3; /* Not a valid label file */
		goto cleanup;
	}
	//printf("magic number: %d (%s)\n", mnist_bin_to_int(tmp), tmp);

	fread(tmp, 1, 4, ifp);//��images�ļ��ж�ȡͼƬ������28*28
	image_cnt = mnist_bin_to_int(tmp);
	//printf("number of images: %d (%s)\n", mnist_bin_to_int(tmp), tmp);

	fread(tmp, 1, 4, lfp);//��label�ļ��ж�ȡͼƬ������28*28
	label_cnt = mnist_bin_to_int(tmp);
	//printf("number of images: %d (%s)\n", mnist_bin_to_int(tmp), tmp);

	if (image_cnt != label_cnt) {//���images��label��ͷ�ļ��ж�Ӧ��ͼƬ��������ͬ���򷵻��˳�
		return_code = -4; /* Element counts of 2 files mismatch */
		goto cleanup;
	}

	for (i = 0; i < 2; ++i) {//��ȡͼƬ��ά�ȣ�row �� col
		fread(tmp, 1, 4, ifp);
		image_dim[i] = mnist_bin_to_int(tmp);
	}
	//printf("image dimension: %d * %d\n", image_dim[0], image_dim[1]);

	if (image_dim[0] != 28 || image_dim[1] != 28) {
		return_code = -2; /* Not a valid image file */
		goto cleanup;
	}
	/*����ͼƬ����60000*/
	*count = image_cnt;
	/*Ϊָ�루���飩����60000��mnist��ʽ�ռ�*/
	*data = (mnist_data *)malloc(sizeof(mnist_data) * image_cnt);

	/*��ȡ60000��28*28��ͼƬ*/
	for (i = 0; i < image_cnt; ++i) {
		int j;
		unsigned char read_data[28 * 28];
		mnist_data *d = &(*data)[i];

		fread(read_data, 1, 28 * 28, ifp);//��ȡ28*28��ͼƬ

#ifdef MNIST_DOUBLE//�����double�ͣ�����д˲���
		//printf("double.\n");
		for (j = 0; j < 28 * 28; ++j) {
			d->data[j / 28][j % 28] = read_data[j] / 255.0;
		}
#else//�����char������д˲���
		memcpy(d->data, read_data, 28 * 28);//�Ѷ�ȡ��28*28ͼƬ��ֵ���ṹ���data
#endif

		fread(tmp, 1, 1, lfp);//��ȡ��Ӧ��label
		d->label = tmp[0];//���ṹ���label��ֵ
	}

cleanup://��Ӧ�����goto
	if (ifp) fclose(ifp);
	if (lfp) fclose(lfp);

	return return_code;
}

//#ifdef __cplusplus//c++֧��
//}
//#endif
