// goagent�л�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

#define DEBUG 0

int RestartGoagent()
{
	system("taskkill /im goagent.exe");
	system("taskkill /im python27.exe");
	system("C:\\goagent3.2\\local\\goagent.exe");
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{
	errno_t err;
	FILE *rewrite = NULL;
	
#if DEBUG
	err = fopen_s(&rewrite, "e://proxy.ini", "r+");
#else
	err = fopen_s(&rewrite, "c://goagent3.2/local/proxy.ini", "r+");
#endif // DEBUG
	if (err != 0)
	{
		MessageBox(NULL, L"�Բ���δ�ҵ������ļ�", L"����", MB_OK);
		return 0;
	}

	WCHAR Line[1024];
	bool isFind = false;
	while (!feof(rewrite))
	{
		fpos_t file_postion;
		fgetpos(rewrite, &file_postion);
		fgetws(Line, 1024, rewrite);
		if (Line[0] == 'i' &&
			Line[1] == 'p' &&
			Line[2] == 'v' &&
			Line[3] == '6')
		{
			int len = wcsnlen(Line, 1024);
			int Statues=-1;
			for (size_t i = 0; i < len; i++)
			{
				if (Line[i] == '1') {
					Line[i] = '0';
					Statues = 0;
					isFind = true;
					break;
				}
				if (Line[i] == '0') {
					Line[i] = '1';
					Statues = 1;
					isFind = true;
					break;
				}
			}
			if (!isFind) {
				MessageBox(NULL, L"�����ļ���ʽ����ȷ,����·��", L"����", MB_OK);
				fclose(rewrite);
				return 0;
			}

			fsetpos(rewrite, &file_postion);
			if (fwprintf(rewrite, Line)<0)
			{
				MessageBox(NULL, L"�ļ�����д", L"����", MB_OK);
				fclose(rewrite);
				return 0;
			}
			else {
				if (Statues==1)
					MessageBox(NULL, L"�����л��ɹ�,��ǰ�Ĺ���ģʽΪipv6", L"֪ͨ", MB_OK);
				if (Statues==0)
					MessageBox(NULL, L"�����л��ɹ�,��ǰ�Ĺ���ģʽΪipv4", L"֪ͨ", MB_OK);
				fclose(rewrite);
				break;
			}
		}
	}
	if (!isFind) MessageBox(NULL, L"δ�ҵ�����λ��", L"����", MB_OK);
	RestartGoagent();
	return 0;
}
