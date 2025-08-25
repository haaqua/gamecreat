#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct Stat {
	const char* name;
	int value;
};

struct CLASS {
	char warrier;
	char archer;
	char magician;
	char prist;
};


struct Stat stat[] =
{
	{"hp", 30},
	{"str",0},
	{"dex",0},
	{"wis",0},
	{"cha",0}
};
void level_up(int up_stat) {
	stat[0].value += 5;
	up_stat += 1;
}
void character_creat() {
	printf("player의 스탯을 정하시오\n");

	srand(time(NULL));
	int hap = 0;
	for (int j = 1; j < 6; j++) {
		printf("주사위 굴리기 2d8 ");
		system("pause");
		for (int i = 0; i < 2; i++) {
			int dice = (rand() % 8) + 1;
			hap += dice;
			printf("나온 수 : %d\n", dice);
		}
		stat[j].value = hap;
		printf("%s : %d\n",stat[j].name, stat[j].value);
		hap = 0;
	}
	printf("\n★전체 스탯★\n");
	for (int i = 0; i < 5; i++) {
		printf("%s : %d\n", stat[i].name, stat[i].value);
	}
	printf("클래스를 정하시오\n");
	printf("주사위를 굴리시오 1d4");
	system("pause");
	
}

int main() {
	character_creat();

	return 0;
}