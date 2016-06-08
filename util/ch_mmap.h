/*************************************************************************
 > File Name: ch_mmap.h
 > Author: shajf
 > Mail: csp001314@163.com 
 > Created Time: 2016年06月08日 星期三 10时25分29秒
 ************************************************************************/

#ifndef CH_MMAP_H
#define CH_MMAP_H

/*Before declaration */
typedef struct ch_mmap_t ch_mmap_t;
typedef struct ch_mmap_header_t ch_mmap_header_t;
typedef struct ch_mmap_buf_t ch_mmap_buf_t;

#include <apr_pools.h>

struct ch_mmap_t {

	/*The memory pool used to allocate the instance of ch_mmap_t */
	apr_pool_t *mp;

	/*The file name used to mmap*/
	const char *fname;

	/*file decs used to mmap*/
	int fd; 

	/*The size of file used to mmap*/
	size_t fsize;

	/*whether used to write*/
	unsigned is_write:1;

	/*The instance of mmap header*/
	ch_mmap_header_t *mmap_header;
};

#pragma pack(push,1)
struct ch_mmap_header_t {
	uint64_t mmap_entries_start;
	uint32_t mmap_entries_count;
	uint32_t mmap_entry_size;
	uint32_t mmap_write_entry_pos;
	uint32_t mmap_read_entry_pos;

};
#pragma pack(pop)

struct ch_mmap_buf_t {
	ch_mmap_t *fmp;
	uint32_t entry_index;
	void *start;
	void *pos;
	void *end;
};

extern ch_mmap_t * ch_mmap_create(apr_pool_t *mp,const char *fname,size_t fsize,uint32_t  entry_size,int is_write);

extern void ch_mmap_destroy(ch_mmap_t *fmp);

extern ch_mmap_buf_t* ch_mmap_alloc(ch_mmap_t *fmp,ch_mmap_buf_t *mb);

extern ch_mmap_buf_t* ch_mmap_calloc(ch_mmap_t *fmp,ch_mmap_buf_t *mb);

extern void ch_mmap_buf_flush(ch_mmap_t *fmp,ch_mmap_buf_t *mb);

#endif /*CH_MMAP_H*/
