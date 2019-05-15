#include <string.h>
#include <stdio.h>
int main(int argc,  char **argv) {
	int version_number;
	int temporary_len;
	int number_of_exclusion;
	int number_of_lines;
	int number_of_keywords;
	int number_of_sorted_words;
	int i;
	char the_two_colon[200];
	char tmp[200];
	char exclusionwords[50][50];
	char lines_number[100][100];
	char keywords[100][100];
	char sorted_line[100][100];
	scanf("%d",&version_number); // This is for checking the version number of the txt
	scanf("%s",the_two_colon); // this is for reading the two colons
	number_of_exclusion = 0;
	while(scanf("%s\n", exclusionwords[number_of_exclusion]) == 1) {     
        if(strcmp (exclusionwords[number_of_exclusion], the_two_colon) == 0) {break;} // if the thing it read is "::", then we break the loop
        number_of_exclusion = number_of_exclusion + 1;
    }
	number_of_lines = 0;
	number_of_keywords = 0;
	
	while(fgets(lines_number[number_of_lines], 1000, stdin)) {
        temporary_len = strlen(lines_number[number_of_lines]);
        if(lines_number[number_of_lines][temporary_len-1] == '\n') {lines_number[number_of_lines][temporary_len-1]='\0';}
        strcpy(tmp, lines_number[number_of_lines]);
		divide_lines(number_of_keywords, keywords, number_of_exclusion, exclusionwords, tmp);
        number_of_lines = number_of_lines + 1;
    }
	
	sorting(keywords,number_of_keywords);
    number_of_sorted_words = 0;
    change_word(keywords, number_of_keywords, lines_number, number_of_lines, sorted_line, &number_of_sorted_words);
    for(i=0;i<number_of_sorted_words;i++) printf("%s\n",sorted_line[i]); 
    return 0;
}

void divide_lines(int *a, char b[100][100], int c, char d[50][50], char *e) {
    char *tokenization = strtok(e," ");
    while(tokenization != NULL) {
        if(keywords_checking(tokenization, *a, b) == 0 && exclusion_checking(tokenization, c, d) == 0) strcpy(b[(*a)++], tokenization);
        tokenization = strtok(NULL," ");
    }
}

int exclusion_checking(int n, char *b, char a[100][100]){
    int count;
    for(count=0;count<n;count++) {if(strcmp(b,a[i])==0) return 1;}
    return 0;
}

int keywords_checking(char *b, int keywords_number, char ky[100][100])
{
    int i;
    for(i=0;i<keywords_number;i++){
        if(strcmp(b,ky[i]) == 0){
            return 1;
		}
	} return 0;
}

void sorting(char keywords[100][100], int nb_of_keywords)
{
    char tmp[100];
    int i,j;
    for(i=0;i<nb_of_keywords-1;i++)
    {
        for(j=0;j<nb_of_keywords-1-i;j++)
        {
            if(strcmp(keywords[j],keywords[j+1])>0)
            {
                strcpy(tmp,keywords[j]);
                strcpy(keywords[j],keywords[j+1]);
                strcpy(keywords[j+1],tmp);
            }
        }
    }
}

int check_in_line(char* key, char* line)
{
    int len_key,len_line,cnt,start,i,j;
    start=-1;
    len_key=strlen(key);
    len_line=strlen(line);
    for(i=0;i<=len_line-len_key;i++)
    {
        if(i==0||line[i-1]==' ')
        {
            cnt=0;
            for(j=0;j<len_key;j++)
            {
                if(key[j]==line[i+j])
                    cnt++;
            }
            if(cnt==len_key)
            {
                start=i;
                break;
            }
        }

    }
    return start;
}

//change the keyword in the lines and store the sorted new lines into sorted_line array
void change_word(char keywords[100][100], int nb_of_keywords, char lines[100][71], int nb_of_lines, char sorted_line[100][71], int* nb_of_sorted)
{
    int start,len_key,i,j,k;
    for(i=0;i<nb_of_keywords;i++)
    {
        len_key=strlen(keywords[i]);
        for(j=0;j<nb_of_lines;j++)
        {
            start=check_in_line(keywords[i],lines[j]);
            if(start!=-1)
            {
                strcpy(sorted_line[*nb_of_sorted],lines[j]);
                for(k=start;k<start+len_key;k++)
                {
                    if(sorted_line[*nb_of_sorted][k]>='a' && sorted_line[*nb_of_sorted][k]<='z')
                        sorted_line[*nb_of_sorted][k]=sorted_line[*nb_of_sorted][k]-'a'+'A';
                }
                (*nb_of_sorted)++;
            }
        }
    }
}
