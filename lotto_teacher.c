#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define counterFile "counter.bin"
#define operatorFile "operator_id.bin"
#define maxLottoNum 7
#define maxLottoNumSet 5

void init_file() {  //判斷有無counter.bin 
	int writeArray[1] = {0};
	FILE* fp = fopen(counterFile, "r");  //先打開(唯讀) 
	if(fp == NULL) {  //若無此檔案 
		FILE* tmpfp = fopen(counterFile, "wb+");  //開一個新的 
		fwrite(writeArray, sizeof(int), 1, tmpfp);  //寫進去"No.0" 
		fclose(tmpfp);
	} else {  //若有 
		fclose(fp);  //直接關掉，不做改變 
	}
}

int get_counter() {  //讀取counter.bin(寫入readArray[0]) 
	int readArray[1];
	FILE* tmpfp = fopen(counterFile, "rb");  //唯讀 
	fread(readArray, sizeof(int), 1, tmpfp);  //將讀取counter.bin(tmpfp)的結果寫入counterArray 
	fclose(tmpfp);
	return readArray[0];
}

int num_in_numset(int num, int numSet[], int Len) {  //檢查是否重複 
	int ret = 0;
	for(int i = 0 ; i < Len ; i++) {
		if(num == numSet[i]) {
			ret = 1;
			break;  //跳出for迴圈 
		}
	}
	return ret;  //1:True  0:False 
}

void print_lotto_row(FILE* tmpfp, int n) {
	int numSet[maxLottoNum];
	
	//generate lotto row 產生號碼(亂數) 
	fprintf(tmpfp, "[%d] : ", n);
	for(int i = 0 ; i < maxLottoNum-1 ; ) {  //普通數字 
		int num = rand() % 69 + 1;
		if(num_in_numset(num, numSet, maxLottoNum-1)) {  //(下一個函式)
			continue;  //重複就繼續for迴圈 
		} else {
			numSet[i] = num;  //放進陣列 
			i++;  //下一輪 
		}
	}
	for(int i = 0 ; i < 1 ; ) {  //特別數字 
		int num = rand() % 10 + 1;
		if(num_in_numset(num, numSet, maxLottoNum-1)) {
			continue;
		} else {
			numSet[maxLottoNum-1] = num;
			i++;
		}
	}
	
	//sorting lotto row 排序 
	for(int i = 0 ; i < maxLottoNum-1 ; ++i) {
		for(int j = 0 ; j < i ; ++j) {
			if(numSet[j] > numSet[i]) {
				int temp = numSet[j];
				numSet[j] = numSet[i];
				numSet[i] = temp;
			}
		}
	}
	
	//output lotto row 印號碼 
	for(int i = 0 ; i < maxLottoNum ; i++) {  
		fprintf(tmpfp, "%02d ", numSet[i]);
	}
	fprintf(tmpfp, "\n");
}

void print_lottofile(int numSet, int counter, char lottoFile[], int operator_id) {
	time_t curtime;
	time(&curtime);
	
	FILE* tmpfp = fopen(lottoFile, "w+");  //lottoFile[32]
	fprintf(tmpfp, "========= lotto649 =========\n");
	fprintf(tmpfp, "========+ No.%05d +========\n", counter);
	fprintf(tmpfp, "= %.*s =\n", 24, ctime(&curtime));  //印目前時間，限制寫24格
	
	for(int i = 0 ; i < maxLottoNumSet ; i++) {  //印中間五行 
		if(i < numSet) {
			print_lotto_row(tmpfp, i+1);
		} else {
			fprintf(tmpfp, "[%d] : -- -- -- -- -- -- --\n", i+1);
		}
	}
	
	fprintf(tmpfp, "========* Op.%05d *========\n", operator_id);
	fprintf(tmpfp, "========= csie@CGU =========\n");
	fclose(tmpfp);
}

void set_operatorID(int operator_id) {
	int opArray[1];
	opArray[0] = operator_id;
	FILE* tmpfp = fopen(operatorFile, "wb");
	fwrite(opArray, sizeof(int), 1, tmpfp);
	fclose(tmpfp);
}

void do_lotto_main(int counter) {  //開頭 
	char lottoFile[32];  //記錄檔名 
	int numSet = 0;  //買幾組 
	int operator_id;  //ID
	snprintf(lottoFile, 32, "lotto[%05d].txt", counter);  //把後面的檔案名複製到lottoFile 
	printf("歡迎光臨長庚樂透彩購買機台\n");
	printf("請輸入操作人員ID : ");
	scanf("%d", &operator_id);
	printf("請問您要購買幾組(1~5) : ");
	scanf("%d", &numSet);
	print_lottofile(numSet, counter, lottoFile, operator_id);
	set_operatorID(operator_id);
	printf("已為您購買的 %d 組樂透組合輸出至 %s\n", numSet, lottoFile);
}





void set_counter(int counter) {  //記錄counter++ 
	int writeArray[1];
	writeArray[0] = counter;
	FILE* tmpfp = fopen(counterFile, "wb");
	fwrite(writeArray, sizeof(int), 1, tmpfp);
	fclose(tmpfp);
}

int main() {
	int counter;
	init_file();  //初始化記錄檔 
	counter = get_counter();  //讀取記錄檔 
	do_lotto_main(++counter);  //中間那大串 
	set_counter(counter);  //記錄counter++ 
	return 0; 
} 
