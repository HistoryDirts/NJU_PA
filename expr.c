#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BUF_SIZE 65536

static char buf[BUF_SIZE] = {}; //存放产生的字符串
static int buf_end_pos = 0; //字符串结尾的位置

void gen(char c);
uint32_t choose(int range);

/*
 *	向字符串结尾添加一个随机整数
 */
void gen_num(){
	//srand(time(NULL)); //在整个函数执行前初始化种子
	int rand_num = rand();
	char num_char[32];
	int i = 0;
//	printf("rand_num = %d\n", rand_num);
	if (rand_num == 0) {
		gen('0');
	}else {
		while (rand_num) {
			num_char[i++] = (rand_num % 10 + 48);//取出最低位
			rand_num /= 10;	
		}
	}
	if (i < 32) {
		num_char[i] = '\0';//给字符串结尾加上‘\0’
	}
	//num_char中存放的是随机数的逆序字符
	//print_char_array(num_char, sizeof(num_char)/sizeof(num_char[0]));
	i--; //让 i 指向最后一个字符
	while (i >= 0) {
		gen(num_char[i]);
		i--;
	}  
}

/*
 *	向字符串结尾添加一个字符c
 * */
void gen(char c){
	if  (buf_end_pos < BUF_SIZE - 1){
		buf[buf_end_pos] = c;
		buf_end_pos ++;
		buf[buf_end_pos] = '\0';
	}else {
		printf("无法插入字符！已到达字符长度极限。");
	} 
}

/**
 *	向字符串结尾添加一个随机操作符（+，-，*，/）
 */
void gen_rand_op(){
	switch (choose(3)){
		case 0 : gen('+'); break;
		case 1 : gen('-'); break;
		case 2 : gen('*'); break;
		case 3 : gen('/'); break;
		default : break;
	}
}

/**
 * 产生[0,range]的随机整数
 */
uint32_t choose(int range){
	range++;
	if (range <= 1) {
		return -1;	//不合法的输入，range应当大于1
 	}
//	uint64_t max = range * ((RAND_MAX + 1u) / range);
//	printf("uint64_t max(dec) = %d\n", max);
//	printf("uint64_t max(hex) = %x\n", max);	
//	printf("uint64_t (int)max(dec) = %d\n",(int)max);
//	printf("uint64_t (int)max(hex) = %x\n", (int)max);
	uint32_t x = range;
	//srand(time(NULL)); 请在执行此函数之前初始化种子
/*
	int random_number = rand();
	while (random_number >= max) {
		random_number = rand();
	}
*/	
	//官方实现
	while (x > range - 1) {
		x = rand() / ((RAND_MAX + 1u) / range);
	}
	return x;
}

void gen_rand_expr() {
   switch (choose(2)) {
    case 0: gen_num(); break;
    case 1: gen('('); gen_rand_expr(); gen(')'); break;
    default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}

/*
 *	打印字符数组中的内容
 */
void print_char_array(const char* array, const int legnth){
	int i = 0;
	while (i < legnth) {
		if (array[i] == '\0') {
			printf("\n");
			return;
		}
		printf("%c", array[i++]);
	}
}


int main(){

//	printf("RAND_MAX = %d\n", RAND_MAX);
//	printf("random numbers: \n");
	srand(time(NULL));
	printf("****start****\n");
	
//	char num_ch[5] = { '3','2','7','6','\0'};
//	for (int i=0; i<10; i++) {
//		printf("%d ",(int)choose(3));	
//	}
	print_char_array(buf, sizeof(buf)/sizeof(buf[0]));
//	unsigned result = gen_rand_expr();
//	printf(" = %u\n", result);

	printf("\n**** end ****\n");
	
	return 0;
}
