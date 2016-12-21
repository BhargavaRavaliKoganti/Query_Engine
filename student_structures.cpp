// student_structures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student_marks{
	int student_id;
	int marks[6];
	struct student_marks * next_student;
};

struct student_details{
	int student_id;
	char location[50];
	char gender[10];
	struct student_details * next_studnet_detials;
};

struct student_marks * studentMarks = NULL;
struct student_details * studentDetails = NULL;
void insert(char[50][50], int);
void average_of_students(char *);
void min_of_students(char *);
void max_of_students(char *);
void avg_of_gender(char *);
char** queries();
int checkQuery(char **, char*);
void displayAll(char *);

int main(){
	FILE *fp;
	fp = fopen("input.txt", "r");
	char ch;
	int flag = 0;
	int index = 0;
	int open = 0;
	int close = 0;
	int count = 0;
	int buffer_i = 0;
	char buffer[50];
	char strings[50][50];
	char *str = (char *)malloc(sizeof(char) * 40);
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\t' || ch == '\n' || ch == ' ' || ch == '-' || ch == ',') {
			continue;
		}
		else if (ch == '{') {
			open++;
			count++;
		}
		else if (ch == '}') {
			close++;
			count--;
			if (open == close) {
				insert(strings, index);
				index = 0;
			}
		}
		else if (ch == '\"' && flag == 0) {
			flag = 1;
		}
		else if (flag == 1 || int(ch) >= 48 && int(ch) <= 57){
			if (int(ch) >= 48 && int(ch) <= 57) {
				buffer_i = 0;
				buffer[buffer_i++] = ch;
				while ((ch = fgetc(fp)) != EOF) {
					if (ch == '\"' || ch == ',')
						break;
					if (ch == ' ' || ch == '-')
						continue;
					buffer[buffer_i++] = ch;
				}
				buffer[buffer_i] = '\0';
				strcpy(strings[index++], buffer);
				buffer_i = 0;
				flag = 0;
			}
			else {
				buffer[buffer_i++] = ch;
				while ((ch = fgetc(fp)) != 'EOF' && ch != '\"') {
					if (int(ch) >= 48 && int(ch) <= 57)
						continue;
					buffer[buffer_i++] = ch;
				}
				buffer[buffer_i] = '\0';
				strcpy(strings[index++], buffer);
				buffer_i = 0;
				flag = 0;
			}
		}
	}
	while (1){
		struct student_marks *ptr1 = studentMarks;
		struct student_details *ptr2 = studentDetails;
		while (ptr1){
			ptr1 = ptr1->next_student;
			ptr2 = ptr2->next_studnet_detials;
		}
		printf("Enter query\n");
		gets(str);
		char** student_queries = queries();
		int choice = checkQuery(student_queries, str);
		char* location = '\0';
		char * gender = '\0';
		switch (choice){
		case 1:
			location = str + 25;
			//printf("%s\n", location);
			average_of_students(location);
			break;
		case 2:
			location = str + 25;
			min_of_students(location);
			break;
		case 3:
			location = str + 25;
			max_of_students(location);
			break;
		case 4:
			gender = str + 26;
			avg_of_gender(gender);
			break;
		case 5:
			location = str + 14;
			displayAll(location);
			break;
		default:
			printf("please Enter a valid input\n");
			exit(0);
		}
	}
	return 0;
}
char ** queries(){
	char **str = (char **)malloc(sizeof(char *) * 4);
	for (int i = 0; i < 10; i++){
		str[i] = (char *)malloc(sizeof(char) * 40);
	}
	str[0] = "avg marks of students in";
	str[1] = "min marks of students in";
	str[2] = "max marks of students in";
	str[3] = "avg marks based on gender";
	str[4] = "select * from";
	return str;
}

int checkQuery(char **queries, char * str){
	for (int i = 0; i < 5; i++){
		if (strstr(str, queries[i]))
			return i + 1;
	}
	return 0;
}

void insert(char strings[50][50], int index){
	struct student_marks * cur1 = (struct student_marks*)malloc(sizeof(struct student_marks));
	struct student_details * cur2 = (struct student_details *)malloc(sizeof(struct student_details));
	for (int i = 0; i < index; i++){
		if (!(strcmp(strings[i], "id"))){
			cur1->student_id = atoi(strings[++i]);
			cur2->student_id = atoi(strings[i]);
		}
		else if (!(strcmp(strings[i], "marks"))){
			for (int j = 0; j < 6; j++){
				cur1->marks[j] = atoi(strings[++i]);
			}
		}
		else if (!(strcmp(strings[i], "location"))){
			strcpy(cur2->location, strings[++i]);
		}
		else if (!(strcmp(strings[i], "gender"))){
			strcpy(cur2->gender, strings[++i]);
		}
	}
	cur1->next_student = studentMarks;
	cur2->next_studnet_detials = studentDetails;
	studentMarks = cur1;
	studentDetails = cur2;
	return;
}

void average_of_students(char * location){
	struct student_marks *temp1 = studentMarks;
	struct student_details *temp2 = studentDetails;
	int count = 0;
	int avgMarks[6] = { 0 };
	while (temp1){
		if (!strcmp(temp2->location, location)){
			count++;
			for (int i = 0; i < 6; i++){
				avgMarks[i] += temp1->marks[i];
			}
		}
		temp1 = temp1->next_student;
		temp2 = temp2->next_studnet_detials;
	}
	for (int i = 0; i < 6; i++){
		avgMarks[i] = avgMarks[i] / count;
		printf("%d\n", avgMarks[i]);
	}
	return;
}

void min_of_students(char * location){
	struct student_marks *temp1 = studentMarks;
	struct student_details *temp2 = studentDetails;
	int min_marks = 0;
	int sum = 0;
	while (temp1){
		//printf("%s %s\n", temp2->location, loca);
		if (!strcmp(temp2->location, location))
			for (int i = 0; i < 6; i++){
			sum += temp1->marks[i];
			}
		if (min_marks == 0)
			min_marks = sum;
		if (sum <= min_marks){
			min_marks = sum;
		}
		temp1 = temp1->next_student;
		temp2 = temp2->next_studnet_detials;
		sum = 0;
	}
	printf("%d\n", min_marks);
	return;
}

void max_of_students(char * location){
	struct student_marks *temp1 = studentMarks;
	struct student_details *temp2 = studentDetails;
	int max_marks = 0;
	int sum = 0;
	while (temp1){
		if (!strcmp(temp2->location, location))
			for (int i = 0; i < 6; i++){
			sum += temp1->marks[i];
			}
		if (max_marks == 0)
			max_marks = sum;
		if (sum >= max_marks){
			max_marks = sum;
		}
		temp1 = temp1->next_student;
		temp2 = temp2->next_studnet_detials;
		sum = 0;
	}
	printf("%d\n", max_marks);
	return;
}

void avg_of_gender(char *gender){
	int avgMarks[6] = { 0 };
	struct student_marks *temp1 = studentMarks;
	struct student_details *temp2 = studentDetails;
	int count = 0;
	while (temp1){
		if (strcmp(temp2->gender, gender)){
			count++;
			for (int i = 0; i < 6; i++){
				avgMarks[i] += temp1->marks[i];
			}
		}
		temp1 = temp1->next_student;
	}
	for (int i = 0; i < 6; i++){
		if (avgMarks != 0)
			avgMarks[i] = avgMarks[i] / count;
		printf("%d\n", avgMarks[i]);
	}
	return;
}

void displayAll(char *location){
	struct student_marks *temp1 = studentMarks;
	struct student_details *temp2 = studentDetails;
	printf("id\tsub1\tsub2\tsub3\tsub4\tsub5\tsub6\tgender\n");
	printf("----------------------------------------------------------------\n");
	while (temp1){
		if (!strcmp(temp2->location, location)){
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t %s\n", temp1->student_id, temp1->marks[0], temp1->marks[1], 
				temp1->marks[2], temp1->marks[3], temp1->marks[4], temp1->marks[5], temp2->gender);
			//printf("%s\n", temp2->gender);
		}
		temp1 = temp1->next_student;
		temp2 = temp2->next_studnet_detials;
	}
	return;
}

