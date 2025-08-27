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
	int number;
};
struct SKILL skill[] = {
	{"강타", "str", "두배의 데미지를 준다",0},
	{"기절 타격", "str", "상대의 행동을 방해한다",1},
	{"갑옷 부수기"," str", "상대의 갑옷을 부숴서 데미지를 더 받게 한다",2},
	{"잡기", "str", "다음 공격을 무조건 맞춘다",3},

	{"연속행동", "dex", "한번 더 행동한다",4},
	{"도주","dex","전투에서 도망친다",5},
	{"은신", "dex", "상대의 시야에서 벗어난다",6},
	{"암살","dex","두배의 데미지를 준다",7},

	{"분석", "wis", "상대의 스탯을 확인한다. 또는 아이템을 확인한다",8},
	{"마법 공격","wis", "지능 대결",9},
	{"순간이동", "wis", "전투에서 벗어난다",10},
	{"힐","wis","아군을 치유한다",11}
};
struct SKILL player_skill[3];

struct Class_skill {
	const char* cl_name;
	const char* sk_name;
	const char* effect;
};
struct Class_skill class_skill[] {
	{"전사","전투의 아이","전투시 다이스의 수 -3"},
	{"도적","소매치기","상대의 물건을 훔친다"},
	{"마법사","똑똑한 두뇌","wis 스탯을 사용하는 상황시 다이스 -3"},
	{"사제","신의 축복","가끔 신의 축복이 내려온다"}
};
struct Class_skill player_class_skill;

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
		strcpy_s(player_class.pl_class, "전사");
	}
	else if (class_dice == 2) {
		strcpy_s(player_class.pl_class, "도적");
	}
	else if (class_dice == 3) {
		strcpy_s(player_class.pl_class, "마법사");
	}
	else if (class_dice == 4) {		
		strcpy_s(player_class.pl_class, "사제");
	}
	printf("플레이어의 클래스 : %s\n", player_class.pl_class);
	for (int i = 0; i < 4; i++) {
		if (strcmp(player_class.pl_class, class_skill[i].cl_name)==0) {
			player_class_skill = class_skill[i];
			break;
		}
	}

	system("pause");
}
void status_check(){
	printf("\n★전체 스탯★\n");
	printf("%s\n",player_class.pl_class);
	printf("클래스 능력 : %s , %s\n", player_class_skill.sk_name, player_class_skill.effect);
	for (int i = 0; i < 6; i++) {
		printf("%s : %d\n", stat[i].name, stat[i].value);
	}
	for (int i = 0; i < 3; i++) {
		printf("%s : %s : %s\n", player_skill[i].name, player_skill[i].use_stat, player_skill[i].effect);
	}
}
void skill_choice() {
	int pl_skill_num[3];
	printf("원하는 스킬의 번호를 적으시오\n\n");
	printf("스킬 : 사용스탯 : 효과 : 숫자\n\n");
	for (int i = 0; i < 12; i++) {
		printf("%s : %s : %s : %d\n", skill[i].name, skill[i].use_stat, skill[i].effect, skill[i].number);
	}
	
	for (int j = 0; j < 3; j++) {
		int found = 0;
		printf("\n");
		printf("입력 : ");
		scanf_s("%d", &pl_skill_num[j]);

		for (int i = 0; i < 12; i++) {
			if (skill[i].number == pl_skill_num[j]) {
				player_skill[j] = skill[i];
				found = 1;
				break;
			}

		}	
		if (!found) {
			printf("없는 스킬입니다. 다시 선택하십시오\n");
			j--;
		}
			
	}
}

int main() {
	character_creat();
	skill_choice();
	status_check();
	return 0;
}