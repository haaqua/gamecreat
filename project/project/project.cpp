#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct Stat {
	const char* name;
	int value;
};
struct Stat stat[] =
{
	{"level", 1},
	{"hp", 30},
	{"str",0},
	{"dex",0},
	{"wis",0},
	{"cha",0}
};

struct CLASS {
	char pl_class[20];
};
struct CLASS player_class;

struct SKILL {
	const char* name;
	const char* use_stat;
	const char* effect;
};
struct SKILL skill[] = {
	{"강타", "str", "두배의 데미지를 준다"},
	{"기절 타격", "str", "상대의 행동을 방해한다"},
	{"갑옷 부수기"," str", "상대의 갑옷을 부숴서 데미지를 더 받게 한다"},
	{"잡기", "str", "다음 공격을 무조건 맞춘다"},

	{"연속행동", "dex", "한번 더 행동한다"},
	{"도주","dex","배틀에서 도망친다"},
	{"은신", "dex", "상대의 시야에서 벗어난다"},

	{"분석", "wis", "상대의 스탯을 확인한다. 또는 아이템을 확인한다"},
	{"파이어볼","wis", "화염구를 던저 공격합니다"},
	{""}
};

void level_up(int up_stat) {
	stat[0].value += 5;
	up_stat += 1;
}
void character_creat() {
	printf("player의 스탯을 정하시오\n");

	srand(time(NULL));
	int hap = 0;
	for (int j = 2; j < 6; j++) {
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
	printf("클래스를 정하시오\n");
	printf("주사위 굴리기 1d4  ");
	system("pause");
	int class_dice = (rand() % 4) + 1;
	printf("나온 수 : %d\n", class_dice);
	if (class_dice == 1) {
		printf("player의 클래스 : 전사\n");
		strcpy_s(player_class.pl_class, "전사");
	}
	else if (class_dice == 2) {
		printf("player의 클래스 : 궁수\n");
		strcpy_s(player_class.pl_class, "궁수");
	}
	else if (class_dice == 3) {
		printf("player의 클래스 : 마법사\n");
		strcpy_s(player_class.pl_class, "마법사");
	}
	else if (class_dice == 4) {
		printf("player의 클래스 : 사제\n");		
		strcpy_s(player_class.pl_class, "사제");
	}
	system("pause");
}
void status_check(){
	printf("\n★전체 스탯★\n");
	printf("%s\n",player_class.pl_class);
	for (int i = 0; i < 6; i++) {
		printf("%s : %d\n", stat[i].name, stat[i].value);
	}
}


int main() {
	character_creat();
	status_check();

	return 0;
}