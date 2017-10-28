#pragma warning(disable:4996) //VS ����������

#include<functions.h>

struct _finddata_t;

char* get_name(void)											//����������
{
	char *name, *temp;
	int j = 1;

	name = (char*)malloc(sizeof(char)*(j + 1));
	if (NULL == name)
	{
		exit(1);
	}

	while ((name[j - 1] = getchar()) != '\n')
	{
		j++;
		temp = (char*)malloc(j + 1);
		if (NULL == temp)
		{
			exit(1);
		}
		name[j - 1] = '\0';
		strcpy(temp, name);
		free(name);

		name = (char*)malloc(sizeof(char)*(j + 1));
		if (NULL == name)
		{
			exit(1);
		}
		strcpy(name, temp);
		free(temp);
	}

	name[j - 1] = '\0';

	return(name);
}

char* get_address(void)
{
	char * file_loc;
	printf("##### �����ļ��е�ַ(./****/) #####\n");								//�ļ���ַ
	file_loc = get_name();
	return file_loc;
}

char* get_key(void)
{
	char * key;
	printf("##### ����ؼ��� #####\n");								//�ؼ���
	key = get_name();
	return key;
}

int type_cmp(char* file_name)
{
	char type[4];
	int i = 0,l=0;
	l = strlen(file_name);
	for (i = 0; i < 4; i++)
		type[i] = file_name[l - 4 + i];
	
	//for(i=0;i<4;i++)
		//printf("%c", type[i]);

	//printf("\n");

	if (strcmp(type, ".txt"))
		return 1;
	else
		return 0;
}

char* file_end_change(char* file_name,char* fileinfo_name)
{
	int l1 = strlen(file_name);
	int lenth = l1+strlen(fileinfo_name)-3;
	//int lenth = strlen(fileinfo_name) + 2 - 3;

	char* name_ch;												// *.*->[],+fileinfo.name
	name_ch = (char*)malloc(lenth);
	if (NULL == name_ch)
		exit(1);
	//strcpy(name_ch, "./");
	//strcat(name_ch, fileinfo_name);

	strcpy(name_ch, file_name);
	name_ch[l1 - 3] = '\0';
	strcat(name_ch, fileinfo_name);

	printf("%s\n", name_ch);
	return name_ch;
}

void file_search(char* file_loc, char* key)
{
	/*���ı��ļ������ҹؼ��ʣ�����ؼ��ʵĵ�һ���ֵ�λ��*/
	FILE *fp;
	if ((fp = fopen(file_loc, "rb")) == NULL)
	{
		printf("Open failure...\n");                        // �����ʱ���������"�򲻿�"����Ϣ    
		system("pause");
	}

	//����һ�е��ַ����ṹ��
	typedef struct String
	{
		char string[1024];				//�ַ���
		int len;						//һ�г���
		int line;						//����
	}String;

	String pstring;
	pstring.line = 0;

	while (!feof(fp))												//ѭ����ȡÿһ�У�ֱ���ļ�β  
	{
		fgets(pstring.string, MAX_LINE, fp);						//��fp��ָ����ļ�һ�����ݶ���strLine������  
																	//printf("%s", pstring.string);								//���������������  
		pstring.line++;
		if (strstr(pstring.string, key))
		{
			printf("\t\t��%d�г����˹ؼ���\"%s\"\n", pstring.line, key);
		}
	}

	/*################### �ر��ļ� ###################*/

	fclose(fp);
}

void dir_search(char*file_loc, int layer, char* key)				//dir_search
{
	struct _finddata_t fileinfo;							//�ļ��洢��Ϣ�ṹ�� 
	long fHandle;											//�����ļ���� 
	int i = 0;												//�ļ�����¼��		

	int Layer;												//���ļ��в�
	char *curr;
	int loc_len, type_len;

	loc_len = strlen(file_loc);
	type_len = strlen("*.*");

	curr = (char*)malloc(loc_len + type_len + 1);
	if (NULL == curr)
	{
		exit(1);
	}

	strcpy(curr, file_loc);
	strcat(curr, "*.*");
	printf("file_add test output: %s\n", curr);

	if ((fHandle = _findfirst(curr, &fileinfo)) != -1L)
	{
		do
		{
			if (strcmp(fileinfo.name, "..") == 0 || strcmp(fileinfo.name, ".") == 0)
				continue;
			for (Layer = 0; Layer < layer; Layer++);
			printf("\t");

			if (_A_SUBDIR != fileinfo.attrib)
			{
				if (type_cmp(fileinfo.name))
				{
					file_search(file_end_change(curr, fileinfo.name), key);
				}
			}
			else												// ��Ŀ¼  
			{
				printf("[Dir]:\t%s\n", fileinfo.name);
				char* curr_n;
				curr_n = (char*)malloc(loc_len + 1 + strlen(fileinfo.name));
				if (NULL == curr_n)
				{
					exit(1);
				}

				strcpy(curr_n, file_loc);
				strcat(curr_n, fileinfo.name);
				strcat(curr_n, "/");
				dir_search(curr_n, layer + 1, key);                  // �ݹ������Ŀ¼ 
			}

		} while (_findnext(fHandle, &fileinfo) == 0);
	}

	_findclose(fHandle);									//�ر��ļ� 

}

int main(void)
{
	printf("##### Program initiating #####\n");
	char* key, *fileloc;

	key = get_key();
	fileloc = get_address();

	dir_search(fileloc, 0, key);

	system("pause");
}