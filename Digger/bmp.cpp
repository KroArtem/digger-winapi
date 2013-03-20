#ifndef __BMP__
#define __BMP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


unsigned char *read_bmp(char *fname) {
	unsigned char head[54];
	FILE *f = fopen(fname,"rb");
	fread((void *)&head[0],1,54,f);
	int _w, _h;
	_w = head[18] + ( ((int)head[19]) << 8) + ( ((int)head[20]) << 16) + ( ((int)head[21]) << 24);
	_h = head[22] + ( ((int)head[23]) << 8) + ( ((int)head[24]) << 16) + ( ((int)head[25]) << 24);
//	printf("w = %d, h = %d\n", *_w, *_h);
	//if(((head.biBitCount != 24) && (head.biBitCount != 32)) || (head.biCompression != 0)) { return 0; }
	const int fileSize = ((_w)*3+((_w)%4))*(_h);
	unsigned char *img = (unsigned char*)malloc((_w)*(_h)*3), *data = (unsigned char*)malloc(fileSize);
	fseek(f,54,SEEK_SET); fread(data,1,fileSize,f);
	int i,j,k,rev_j;
	for(j = 0, rev_j = (_h) - 1; j < (_h) ; j++, rev_j--) {
		for(i = 0 ; i < (_w) ; i++) {
			int fpos = j*((_w) * 3 + (_h) % 4) + i*3, pos = rev_j * (_w) * 3 + i*3;
			for(k = 0 ; k < 3 ; k++) img[pos+k] = data[fpos+k];
		}
	}
	fclose(f);
	//free(data);
	return img;
}


#endif