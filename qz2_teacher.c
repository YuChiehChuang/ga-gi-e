#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
 
typedef struct lotto_record {
	int lotto_no;
	int lotto_receipt;
	int emp_id;
	char lotto_date[16];
	char lotto_time[16];
} lotto_record_t;
 
typedef struct stat {
	int lotto_counter;
	int lotto_numset;
	int lotto_receipt;
	char lotto_date[16];
} stat_t;
 
int check_date_in_table(lotto_record_t r, stat_t stat_table[], int table_size) {
	int i = -1;
	for(i = 0 ; i <table_size; i++) {
		if(strcmp(r.lotto_date, stat_table[i].lotto_date) == 0) {
			break;
		}
	}
 
	if(i >= table_size) {
		return -1;
	}
	return i;
}
 
void print_reportfile(stat_t stat_table[], int table_size) {
	int total = 0;
	int total_num = 0;
	int total_numset = 0;
	int total_receipt = 0;
	time_t timer;
	char t_buffer[12];
	timer = time(NULL);
	strftime(t_buffer, 12, "%Y%m%d", localtime(&timer));
 
	FILE* wfp = fopen("report.txt", "w+");
	fprintf(wfp, "========= lotto649 Report =========\n");
	fprintf(wfp, "- Date ------ Num. ------ Receipt -\n");
	for(int i = 0 ; i < table_size ; i++) {
		fprintf(wfp, "%s\t\t%d/%d\t\t\t%d\n", stat_table[i].lotto_date,
												stat_table[i].lotto_counter,
												stat_table[i].lotto_numset,
												stat_table[i].lotto_receipt);
		total++;
		total_num += stat_table[i].lotto_counter;
		total_numset += stat_table[i].lotto_numset;
		total_receipt += stat_table[i].lotto_receipt;		
	}
	fprintf(wfp, "-----------------------------------\n");
	fprintf(wfp, "%d\t\t%d/%d\t\t%d\n", total,
											total_num,
											total_numset,
											total_receipt);
	fprintf(wfp, "========= %s Printed =========\n", t_buffer);
	fclose(wfp);
}
 
int main() {
	lotto_record_t r;
	int table_index = 0;
	int date_index = -1;
	stat_t stat_table[128] = {0};
	FILE* rfp = fopen("records.bin", "rb");
 
	while(fread(&r, sizeof(lotto_record_t), 1, rfp)) {
		if((date_index = check_date_in_table(r, stat_table, 128)) < 0) {
			date_index = table_index++;
			strcpy(stat_table[date_index].lotto_date, r.lotto_date);
		}
		stat_table[date_index].lotto_counter++;
		stat_table[date_index].lotto_receipt += r.lotto_receipt;
		stat_table[date_index].lotto_numset += (r.lotto_receipt / 55);
	}
	fclose(rfp);
 
	print_reportfile(stat_table, table_index);
	return 0;
} 
