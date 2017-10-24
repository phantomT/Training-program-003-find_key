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

void file_search(char*file_loc, char *key)
{
	printf("test\n");
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
	type_len = strlen("*.txt");

	curr = (char*)malloc(loc_len + type_len + 1);
	if (NULL == curr)
	{
		exit(1);
	}

	strcpy(curr, file_loc);
	strcat(curr, "*.txt");
	printf("file_add test output: %s\n", curr);

	if ((fHandle = _findfirst(curr, &fileinfo)) != -1L)
	{
		do
		{
			if (strcmp(fileinfo.name, "..") == 0)
				continue;
			if (strcmp(fileinfo.name, ".") == 0)
				continue;
			for (Layer = 0; Layer < layer; Layer++);
			printf("%d", Layer);

			if (_A_SUBDIR == fileinfo.attrib)              // ��Ŀ¼  
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
			else
			{
				file_search(curr,key);
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