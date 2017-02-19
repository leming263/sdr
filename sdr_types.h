/*
 * sdr_types.h
 *
 *  Created on: 2017-2-19
 *      Author: leiming
 */

#ifndef SDR_TYPES_H_
#define SDR_TYPES_H_

/************************��****************/
enum SDR_BASE_CLASS	//XML�ĵ������ڵ�.���ڵ��ǹ���XML��һ��εĽڵ㣬������SDR_CLASS_ENTRY
{
	SDR_CLASS_START,	//��ʼ
	SDR_CLASS_MACRO,	//�곣��
	SDR_CLASS_STRUCT,	//�ṹ��
	SDR_CLASS_UNION,	//����
	SDR_CLASS_ENTRY		//�ṹ/���ϳ�Ա
};

enum SDR_TYPE	//��������
{
	SDR_T_UNION = 1,	//����
	SDR_T_STRUCT,	//�ṹ��
	SDR_T_COMPOS,	//ռλ��������
	SDR_T_CHAR,	//�ַ�
	SDR_T_UCHAR, //�޷����ַ�
	SDR_T_SHORT,	//������
	SDR_T_USHORT,	//�޷���
	SDR_T_INT,	//����
	SDR_T_UINT,	//�޷�������
	SDR_T_LONG,	//������
	SDR_T_ULONG,	//�޷��ų�����
	SDR_T_FLOAT,	//����
	SDR_T_DOUBLE	//˫���ȸ���
};

#define XML_LEFT_BRACKET '<'
#define XML_RIGHT_BRACKET '>'
#define XML_LABEL_MACRO "macro"
#define XML_LABEL_STRUCT "struct"
#define XML_LABEL_UNION "union"
#define XML_LABEL_ENTRY "entry"
#define XML_LABEL_NAME "name"
#define XML_LABEL_VALUE "value"
#define XML_LABEL_TYPE "type"
#define XML_LABEL_COUNT "count"
#define XML_LABEL_REFER "refer"
#define XML_LABEL_SELECT "select"
#define XML_LABEL_ID "id"
#define XML_LABEL_VERSION "version"
#define XML_LABEL_DESC "desc"

//���͹ؼ���
#define XML_LABEL_CHAR "char"
#define XML_LABEL_UCHAR "uchar"
#define XML_LABEL_SHORT "short"
#define XML_LABEL_USHORT "ushort"
#define XML_LABEL_INT "int"
#define XML_LABEL_UINT "uint"
#define XML_LABEL_LONG "long"
#define XML_LABEL_ULONG "ulong"
#define XML_LABEL_FLOAT "float"
#define XML_LABEL_DOUBLE "double"


#define MAX_NAME_LEN	32	//���ֳ���
#define MAX_DESC_LEN	64	//ע�ͳ���
#define MAX_LINE_LEN 1024	 //�г���
#define MACRO_VALUE_LEN 32	//MACRO ֵ����

#define INFO_NORMAL	1
#define INFO_MAIN	2
#define INFO_ERR	3
/************************�ṹ****************/
/*
 * һ�����͵Ľڵ�
 */
struct _sdr_node
{
	char class;	//�����ڵ�����
	int my_idx;	//�ýڵ�����map�е����
	int version;	//�汾��
	int size;	//�ֽڳ���
	char node_name[MAX_NAME_LEN];
	char node_desc[MAX_DESC_LEN];
	int sibling_idx;	//�ֵܽڵ�
	union
	{
		char macro_value[MACRO_VALUE_LEN];	//SDR_MACRO
		struct	//SDR_STRUCT
		{
			int child_idx;	//��һ��entry��index
		}struct_value;

		struct	//SDR_UNION
		{
			int child_idx;	//��һ��entry��index
		}union_value;

		struct	//SDR_ENTRY
		{
			char entry_type;	//entry������
			int type_idx;	//����Ǹ�������(struct/union)���Ӧ�Ľڵ�ID
			int count;	//��Ŀ:���1������ͨ���� >1����
			char count_name[MAX_NAME_LEN];	//����Ǻ꣬������ŵ�����
			int refer_idx;	//��������飬��Ҫ�ο��ı���
			int select_idx;	//���entry������union����ñ��Ӧ�û��¼���������ID��ĳ��Ա
			int select_id;	//�����union�ĳ�Ա�����¼��ID
			char id_name[MAX_NAME_LEN];	//id������
			int offset;	//��entry����ڸ��ṹ��ƫ��
		}entry_value;
	}data;
}__attribute__((packed));
typedef struct _sdr_node sdr_node_t;

#define DEFAULT_MAX_NODE_COUNT (10*1024)	//Ĭ��NODE ��Ŀ
/*
 * MEM<->FILE MAP ���ڼ�¼���нڵ�����ݽṹ��ͬʱҲ�ɳ־û���BIN�ļ���
 * ˳��洢
 */
struct _sdr_node_map
{
	int count;
	sdr_node_t node_list[0];
}__attribute__((packed));
typedef struct _sdr_node_map sdr_node_map_t;


/***���ű�(ֻ���SDR_MACRO SDR_STRUCT �� SDR_UNION �����SDR_ENTRY��Ա��)*/
struct _sym_entry
{
	char sym_name[MAX_NAME_LEN];
	int index;		//index of node table
}__attribute__((packed));
typedef struct _sym_entry sym_entry_t;

struct _sym_table
{
	int count;
	sym_entry_t entry_list[0];
}__attribute__((packed));
typedef struct _sym_table sym_table_t;


/***�־û��ṹ*/
#define SDR_MAGIC_STR	"!sdr"

struct _sdr_data_res
{
	char magic[4];		//magic
	int max_node;
	sdr_node_map_t *pnode_map;
	sym_table_t *psym_table;
}__attribute__((packed));
typedef struct _sdr_data_res sdr_data_res_t;

/***������INFO*/
struct _sdr_buff_info
{
	char *src;
	int index;
	int length;	//�����Ҫ
};
typedef struct _sdr_buff_info sdr_buff_info_t;

#endif /* SDR_TYPES_H_ */
