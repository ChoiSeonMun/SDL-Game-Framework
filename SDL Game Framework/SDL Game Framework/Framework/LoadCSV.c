#include "stdafx.h"
#include "LoadCSV.h"

bool CSVInit(const char* filename, SceneData* data)
{
	FILE* p_file = NULL;

	if (0 == fopen_s(&p_file, filename, "r")) {

		char one_line_string[256], str[32], * p_pos;
		if (NULL != fgets(one_line_string, 256, p_file)) {
			while (NULL != fgets(one_line_string, 256, p_file)) 
			{

				p_pos = GetNextString(one_line_string, ',', str);
				data->index = atoi(str);

				p_pos = GetNextString(p_pos, ',', data->BGMFileName);

				p_pos = GetNextString(p_pos, ',', data->BackGroundFileName);

				p_pos = GetNextString(p_pos, ',', str);
				data->imageTime = atoi(str);

				p_pos = GetNextString(p_pos, ',', str);
				data->imageEffect = atoi(str);

				p_pos = GetNextString(p_pos, ',', str);
				data->textTime = atoi(str);

				p_pos = GetNextString(p_pos, ',', str);
				data->textSpeed = atoi(str);

				p_pos = GetNextString(p_pos, ',', str);
				data->textpos = atoi(str);

				p_pos = GetNextString(p_pos, ',', str);
				data->textEffect = atoi(str);

				p_pos = GetNextString(p_pos, ',', data->textFileName1);
				p_pos = GetNextString(p_pos, ',', data->textFileName2);
				p_pos = GetNextString(p_pos, ',', data->textFileName3);
				p_pos = GetNextString(p_pos, ',', data->select1);
				p_pos = GetNextString(p_pos, ',', str);
				data->select1Value = atoi(str);
				p_pos = GetNextString(p_pos, ',', data->select2);
				p_pos = GetNextString(p_pos, ',', str);
				data->select2Value = atoi(str);
				p_pos = GetNextString(p_pos, ',', data->select3);
				p_pos = GetNextString(p_pos, ',', str);
				data->select3Value = atoi(str);

				data++;
			}


		}
		fclose(p_file);
		return true;
	}
	return false;
}




char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer)
{
	
	while (*ap_src_str && *ap_src_str != a_delimiter) *ap_buffer++ = *ap_src_str++;

	
	if (*(ap_buffer - 1) == '\n') *(ap_buffer - 1) = 0;
	else *ap_buffer = 0;

	
	if (*ap_src_str == a_delimiter) ap_src_str++;

	
	return ap_src_str;
}