

#ifndef __ROMFS_H__
#define __ROMFS_H__

#define ROMFH_MAX_FN 16//inode�����ֳ��ȣ�������β��0��
#define ROMFH_ROOT_FILE 0x60//��Ŀ¼�ĵ�һ���ļ�λ��
#define ROMFH_INODE_LEN	0x20//һ��inode��ռ��32B����Ҫ��������16B��


#define ROMFH_HRD 0
#define ROMFH_DIR 1
#define ROMFH_REG 2
#define ROMFH_LNK 3
#define ROMFH_BLK 4
#define ROMFH_CHR 5
#define ROMFH_SCK 6
#define ROMFH_FIF 7
#define ROMFH_EXEC 8

#define ROMFH_NEXT_MASK 0xfffffff0
#define ROMFH_TYPE_MASK 0x00000007
#define ROMFH_EXEC_MASK 0x00000008

#define be32_le32(x)	((u32)(((u32)x & 0x000000ff) << 24) | \
						(((u32)x & 0x0000ff00) << 8) | \
						(((u32)x & 0x00ff0000) >> 8) | \
						(((u32)x & 0xff000000) >> 24))


struct romfs_super_block {
	u32 word0;
	u32 word1;
	u32 size;
	u32 checksum;
	u8  name[0];
};

//�ڱ�׼�regular file��spec��û��ʹ�ã��˽ṹ���������Ϊ�ļ����ݵ�λ��reg_data
//Ŀ¼�ĵ�һ���ļ�λ�ã���Ϊdir_data
union romfs_spec {
	u32 hrd_dest;//hard link	link destination [file header]
	u32 dir_data;//directory	first file's header
	u32 file_data;//regular file	unused, must be zero [MBZ]
	u32 lnk_unused;//unused, MBZ (file data is the link content)
	u32 blk_major_minor;//block device	16/16 bits major/minor number
	u32 chr_flag;//char device		    - " -
	u32 sck_unused;//socket		unused, MBZ
	u32 fifo_unused;//fifo		unused, MBZ
};

struct romfs_inode {
	u32 nextfh;
	union romfs_spec spec;
	u32 size;
	u32 checksum;
	u8  name[0];
};

struct romfs_init
{
	//��block�豸��ַΪaddr��λ�ö�len�����ݣ�����buf��
	u8 (*romfs_rd_block)(u8* buf, u32 addr, u8 len);
};


#endif
