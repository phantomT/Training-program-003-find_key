#pragma warning(disable:4996) //VS 编译声明？

#include<functions.h>

struct _finddata_t;

char* get_name(void)											//不定长输入
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
	printf("##### 输入文件夹地址(./****/) #####\n");								//文件地址
	file_loc = get_name();
	return file_loc;
}

char* get_key(void)
{
	char * key;
	printf("##### 输入关键词 #####\n");								//关键词
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
	
	for(i=0;i<4;i++)
		printf("%c", type[i]);

	printf("\n");

	if (strcmp(type, ".txt"))
		return 1;
	else
		return 0;
}

void file_search(char*file_loc, char *key)
{
	printf("%s\n",file_loc);
}

void dir_search(char*file_loc, int layer, char* key)				//dir_search
{
	struct _finddata_t fileinfo;							//文件存储信息结构体 
	long fHandle;											//保存文件句柄 
	int i = 0;												//文件数记录器		

	int Layer;												//子文件夹层
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
			if (strcmp(fileinfo.name, "..") == 0)
				continue;
			if (strcmp(fileinfo.name, ".") == 0)
				continue;
			for (Layer = 0; Layer < layer; Layer++);
			printf("%d", Layer);

			if (_A_SUBDIR == fileinfo.attrib)              // 是目录  
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
				dir_search(curr_n, layer + 1, key);                  // 递归遍历子目录  
			}
			else if(type_cmp(fileinfo.name))
			{
				file_search(fileinfo.name,key);
			}

		} while (_findnext(fHandle, &fileinfo) == 0);
	}

	_findclose(fHandle);									//关闭文件 

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