
#include "bsp/type.h"
#include "romfs/romfs.h"

#ifdef UNIT_TEST
#include <stdio.h>
#include <stdlib.h>
#endif

u8* str_cpy(u8* dst,u8* src)
{
    u8* ret = dst;

    while((*dst++=*src++)!='\0');

    return ret;
}

//从str中查找第一个字符ch，返回指针
//如果没有找到，则返回NULL
u8* str_chr(u8* str,u8 ch)
{
    u8* pch;
    pch = str;
    for(;;)
    {
        if(*pch == 0)return NULL;
        if(*pch == ch)return pch;
        pch++;
    }
}

//拷贝n-1个字符，并在n-1的位置添加0
u8* str_ncpy(u8* dst,const u8* src,int n)
{
    u8* cp=dst;
    dst[--n] = 0;
    while(n&&(*cp++=*src++)!='\0')
    {
        n--;
    }
    if(n)
    {
        while(--n)
            *cp++='\0';
    }

    return dst;
}

u8* byte_ncpy(u8* dst,const u8* src,int n)
{
    u8* cp=dst;
    while(n--)
    {
        *cp++=*src++;
    }

    return dst;
}

u8 str_cmp(u8* src1, u8* src2)
{
    if(src1 == NULL && src2 == NULL)return 1;
    if(src1 == NULL)return 0;
    if(src2 == NULL)return 0;
    for(;;)
    {
        if(*src1 != *src2)return 0;
        if(*src1 == 0)return 1;
        src1++;
        src2++;
    }
}

//从dir中查找目录，存入top_dir，返回剩余的路径
u8* romfs_bmap(u8* top_dir,u8* dir)
{
    int n;
    u8* p=str_chr(dir,'/');
    if(!p)//找到最后一级路径
    {
        str_cpy(top_dir,dir);
        return NULL;
    }
    //找到'/'，意味着有目录
    n = (int)(p-dir);
    if(n>ROMFH_MAX_FN)n = ROMFH_MAX_FN;
    str_ncpy(top_dir,dir,n+1);
    p++;
    return p;
}



static u8 romfs_block_buf[ROMFH_INODE_LEN];

//按绝对路径方式，获取文件的inode
//未找到文件，则返回NULL。
struct romfs_inode* romfs_namei(u8* dir)
{
    u8* p;
    u8 cur_dir[ROMFH_MAX_FN];
    u8 type;
    u8 next_dir;
    u32 next_addr;
    u32 curr_addr;
    struct romfs_inode* pinode;
    pinode = (struct romfs_inode*)romfs_block_buf;

    //从根目录的第一个文件开始
    if(dir[0] == '/')
    {
        next_addr = ROMFH_ROOT_FILE;
        curr_addr = ROMFH_ROOT_FILE;
        p = dir+1;
        next_dir = 1;
    }
    else
        return NULL;

    while(1)
    {
        if(next_dir)//切换下一级目录
        {
            next_dir = 0;
            p = romfs_bmap(cur_dir,p);
#ifdef UT_DEBUG
            printf("\ntop_dir: %s",cur_dir);
#endif
        }

#ifdef UT_DEBUG
        printf("\n");
        printf("next_addr: 0x%08x,",next_addr);
#endif

        //读入数据
        romfs_rd_block(next_addr,romfs_block_buf,ROMFH_INODE_LEN);
#ifdef UNIT_TEST
        //转换大小端
        pinode->spec.dir_data = be32_le32(pinode->spec.dir_data);
        pinode->nextfh = be32_le32(pinode->nextfh);
        pinode->size = be32_le32(pinode->size);
        pinode->checksum = be32_le32(pinode->checksum);
#endif
        curr_addr = next_addr;
        type = (u8)(pinode->nextfh & ROMFH_TYPE_MASK);
        next_addr = pinode->nextfh & ROMFH_NEXT_MASK;

#ifdef UT_DEBUG
        printf("name: %s,",pinode->name);
#endif
        if(str_cmp(pinode->name,cur_dir))//名字匹配
        {
            if(p == NULL)
            {
#ifdef UT_DEBUG
                printf("founded\n");
#endif
                //inode.spec存储文件的数据指针
                if(type == ROMFH_REG)
                    pinode->spec.file_data = curr_addr + 32;
                return pinode;
            }
            else if(type == ROMFH_DIR)
            {
                next_dir = 1;//开始搜索下一级目录
                next_addr = pinode->spec.dir_data;
#ifdef UT_DEBUG
                printf("\n");
#endif
            }
        }
        else if(next_addr == 0x00000000)//当前目录搜索完毕，没有找到
            break;
    }

#ifdef UT_DEBUG
    printf("\n");
#endif

    return NULL;
}


u8 romfs_is_dir(struct romfs_inode* inode)
{
    inode = inode;
    return 0;
}

u8 romfs_is_file(struct romfs_inode* inode)
{
    inode = inode;
    return 0;
}

u8* romfs_name(struct romfs_inode* inode)
{
    inode = inode;
    return inode->name;
}



#ifdef UNIT_TEST

//增加依赖文件,以冒号结尾
//#DEP_FILE: :
//添加编译文件需要的gcc参数
//#CMP_FLAG: -I. -I..:

#include "unit_test.h"

char* ut_str_cpy()
{
    char ch_src[] = "1111111111111";
    char ch_dst[20] = {0,};

    UT_STR_EQ(str_cpy(ch_dst,ch_src),ch_src);

    return 0;
}

char* ut_str_ncpy()
{
    char ch_src[] = "abcdefghijklmnopqrstuvwxyz";
    char ch_dst[6] = {0,};

    str_ncpy(ch_dst,ch_src,3);
    UT_STR_EQ(ch_dst,"ab");
    str_ncpy(ch_dst,ch_src,6);
    UT_STR_EQ(ch_dst,"abcde");

    return 0;
}

char* ut_str_chr()
{
    char ch_src[] = "abcdefghijklmnopqrstuvwxyz";
    char* p;

    p = str_chr(ch_src,'a');
    UT_STR_EQ(p,ch_src);

    p = str_chr(ch_src,'b');
    UT_STR_EQ(p,"bcdefghijklmnopqrstuvwxyz");

    p = str_chr(ch_src,'m');
    UT_STR_EQ(p,"mnopqrstuvwxyz");

    p = str_chr(ch_src,'y');
    UT_STR_EQ(p,"yz");

    p = str_chr(ch_src,'z');
    UT_STR_EQ(p,"z");

    p = str_chr(ch_src,'5');
    UT_ASSERT("p == NULL",p == NULL);

    return 0;
}

char* ut_romfs_bmap()
{
    char ch_dir[] = "123/456/789a/bcdefg";
    char ch_top[128] = {0,};
    char* ch_ret;

    ch_ret = ch_dir;

    ch_ret = romfs_bmap(ch_top,ch_ret);
    UT_STR_EQ(ch_ret,"456/789a/bcdefg");
    UT_STR_EQ(ch_top,"123");

    ch_ret = romfs_bmap(ch_top,ch_ret);
    UT_STR_EQ(ch_ret,"789a/bcdefg");
    UT_STR_EQ(ch_top,"456");

    ch_ret = romfs_bmap(ch_top,ch_ret);
    UT_STR_EQ(ch_ret,"bcdefg");
    UT_STR_EQ(ch_top,"789a");

    ch_ret = romfs_bmap(ch_top,ch_ret);
    UT_ASSERT("ch_ret == NULL",ch_ret == NULL);
    UT_STR_EQ(ch_top,"bcdefg");

    return 0;
}


//在文件的后面定义
extern const u8 romfs_data[];

u8 ut_read_block(u8* buf, u32 addr, u8 len)
{
    byte_ncpy(buf,&romfs_data[addr],len);
    return len;
}

char* ut_romfs_namei()
{
    struct romfs_inode* inode;

    //printf("sizeof(u32) == %d\n",sizeof(u32));

    for(int i=0; i<32; i++)
    {
        romfs_block_buf[i] = 0xff;
        //printf("%02x ",romfs_block_buf[i]);
    }
    //
    romfs_block.romfs_rd_block = ut_read_block;

    inode = romfs_namei("/dir1/dir1_dir1");
    UT_ASSERT("inode != NULL",inode != NULL);
    UT_STR_EQ(inode->name,"dir1_dir1");
    printf("dir_data: %08x\n",inode->spec.dir_data);
    UT_INT_EQ(inode->spec.dir_data,0x000000e0);
    UT_INT_EQ(inode->size,0);

    inode = romfs_namei("/dir1/dir1_dir1/d1_d1_file1");
    UT_ASSERT("inode != NULL",inode != NULL);
    UT_STR_EQ(inode->name,"d1_d1_file1");
    printf("file_data: %08x\n",inode->spec.file_data);
    UT_INT_EQ(inode->spec.file_data,0x000001a0);
    UT_INT_EQ(inode->size,0x15);

    inode = romfs_namei("/dir1/dir1_dir1/no_exist");
    UT_ASSERT("inode == NULL",inode == NULL);

    inode = romfs_namei("../a");
    UT_ASSERT("inode == NULL",inode == NULL);


    return 0;
}


//定义自己的ut_all_tests
char* ut_all_tests()
{
    UT_TEST(ut_str_cpy);
    UT_TEST(ut_str_chr);
    UT_TEST(ut_str_ncpy);
    UT_TEST(ut_romfs_bmap);
    UT_TEST(ut_romfs_namei);
    return 0;
}

/*
使用genrofs生成的镜像数据，目录和文件结构如下。
/
	dir1
		dir1_dir1
			d1_d1_d1
			d1_d1_file1
			d1_d1_file2
			d1_d1_file3
		dir1_file1
		dir1_file2
	dir2
	file1
	file2
*/
const u8 romfs_data[1024] = {
    0x2D, 0x72, 0x6F, 0x6D, 0x31, 0x66, 0x73, 0x2D, 0x00, 0x00, 0x03, 0x60, 0xF6, 0x0A, 0x46, 0xE6,
    0x72, 0x6F, 0x6D, 0x20, 0x35, 0x62, 0x63, 0x37, 0x63, 0x63, 0x32, 0x31, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFF, 0x97,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD1, 0xFF, 0x80,
    0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0xA9, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x96, 0x8A, 0xA6,
    0x64, 0x69, 0x72, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFF, 0x00,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD1, 0xFF, 0x20,
    0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x49, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x32, 0x21, 0x34,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x64, 0x69, 0x72, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFE, 0x40,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD1, 0xFE, 0x80,
    0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x89, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x6A, 0x6F, 0x39, 0xA2,
    0x64, 0x31, 0x5F, 0x64, 0x31, 0x5F, 0x64, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFD, 0x80,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD1, 0xFF, 0x40,
    0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xFE, 0x0A, 0x07, 0x54,
    0x64, 0x31, 0x5F, 0x64, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x31, 0x5F,
    0x64, 0x61, 0x74, 0x61, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xFE, 0x0A, 0x06, 0x14,
    0x64, 0x31, 0x5F, 0x64, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x32, 0x5F,
    0x64, 0x61, 0x74, 0x61, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xFE, 0x0A, 0x07, 0x14,
    0x64, 0x31, 0x5F, 0x64, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x33, 0x5F,
    0x64, 0x61, 0x74, 0x61, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xD6, 0xFF, 0x21, 0xD9,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x31, 0x5F, 0x64, 0x61, 0x74, 0x61, 0x0A,
    0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xD6, 0xFE, 0x24, 0x49,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x69, 0x72, 0x31, 0x5F, 0x66, 0x69, 0x6C, 0x65, 0x32, 0x5F, 0x64, 0x61, 0x74, 0x61, 0x0A,
    0x00, 0x00, 0x03, 0x09, 0x00, 0x00, 0x02, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x96, 0x88, 0x05,
    0x64, 0x69, 0x72, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0xE0, 0x00, 0x00, 0x02, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xFF, 0xFA, 0x80,
    0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xD1, 0xD1, 0xFF, 0xE0,
    0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x68, 0x96, 0x90, 0x56,
    0x66, 0x69, 0x6C, 0x65, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x66, 0x69, 0x6C, 0x65, 0x31, 0x20, 0x64, 0x61, 0x74, 0x61, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x67, 0x96, 0x93, 0x86,
    0x66, 0x69, 0x6C, 0x65, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x66, 0x69, 0x6C, 0x65, 0x32, 0x20, 0x64, 0x61, 0x74, 0x61, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif


