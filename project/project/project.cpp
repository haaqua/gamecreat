#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define _CRT_SECURE_NO_WARNINGS

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
	{"luck",0}
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

struct ITEM {
	const char* name;
	const char* effect;
};
struct ITEM item[]{
	{"금화","화패"},
	{"철갑옷", "받는 데미지 -1, 민첩-1"},
	{"일회용 죽창", "상대에게 공격시 무조건 사살,그 후 아이템 파괴"},
	{""}
};
struct ITEM player_item[10];

struct Monster {
	const char* name;
	int hp;
	const char* skill;
};
struct Monster monster[]{
	{"슬라임",8,"회복"},
	{"오크",15,"강타"},
	{"데스나이트",20,"오러블레이드"},
	{"드래곤",30,"용의 숨결"}
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
		printf("🎲주사위 굴리기 2d8 ");
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
	printf("🎲주사위 굴리기 1d4  ");
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


void use_skill_str(const char* skill_naming) {
	printf("🎲주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d", dice);
	if (stat[2].value < dice) {
		printf("%s 사용\n",skill_naming);
	}
	else {
		printf("실패");
	}
}
void use_skill_dex(const char* skill_naming) {
	printf("🎲주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d", dice);
	if (stat[3].value < dice) {
		printf("%s 사용\n", skill_naming);
	}
	else {
		printf("실패");
	}
}
void use_skill_wis(const char* skill_naming) {
	printf("🎲주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d", dice);
	if (stat[4].value < dice) {
		printf("%s 사용\n", skill_naming);
	}
	else {
		printf("실패");
	}
}

void store() {
	printf("상점이 있습니다");
}
void battle(int difficult) {
	char action;
	int skill_used[3] = { 0,0,0 };
	struct Monster* current = NULL;
	printf("몬스터 출현!  ");
	if (difficult <= 5) {
		current = &monster[0];
		printf("%s\n", monster[0].name);
	}
	else if (difficult > 5 && difficult <= 10) {
		current = &monster[1];
		printf("%s\n", monster[1].name);
	}
	else if (difficult>10 && difficult <= 15) {
		current = &monster[2]; 
		printf("%s\n", monster[2].name);
	}
	else if (difficult>15 && difficult <= 20) {
		current = &monster[3];
		printf("%s\n", monster[3].name);
	}
	current->hp += difficult;

	while (current->hp > 0 && stat[0].value > 0) {
		printf("\n행동을 선택하시오. Q : 공격, W : 스킬 사용, E : 아이템 사용, R : 상태확인\n");
		printf("입력 : ");
		scanf_s("%c", &action, 1);

		switch (action) {
		case 'Q':
		case 'q':
		{
			printf("🎲공격 다이스 d20 : ");
			system("pause");
			int attack_dice = (rand() % 20) + 1;
			printf("%d", attack_dice);
			if (attack_dice < stat[2].value && attack_dice != 1) {
				printf("\n데미지 다이스 d6 ");
				system("pause");
				int damage_dice = (rand() % 6) + 1;
				current->hp -= damage_dice;
			}
			else if (attack_dice == 1) {
				printf("!");
				printf("\n치명타!");
				current->hp -= 6;
			}
			else {
				printf("공격 실패");
			}
			break;
		}
		case'W':
		case'w':
		{
			printf("스킬 목록");
			for (int i = 0; i < 3; i++) {
				printf("%s : %s : %s", player_skill[i].name, player_skill[i].use_stat, player_skill[i].effect);
				if (skill_used[i]) {
					printf("[사용완료");
				}
				printf("\n");
			}
			int skill_choice;
			printf("1번째 스킬을 사용할려면 1, 2번째 스킬을 사용하려면 2, 3번째 스킬을 사용하려면 3을 누르시오");
			scanf_s("%d", &skill_choice);
			if (skill_choice < 0 || skill_choice>3) {
				printf("범위를 벗어났습니다 다시 입력하세요\n");
				break;
			}
			int idx = skill_choice - 1;
			struct SKILL selected_skill = player_skill[idx];

			if (strcmp(selected_skill.name, "강타") == 0) {
				printf("강타 사용\n");
				printf("🎲공격 다이스 d20 : ");
				system("pause");
				int smash_dice = (rand() % 20) + 1;
				printf("%d", smash_dice);
				if (smash_dice < stat[2].value && smash_dice != 1) {
					printf("\n데미지 다이스 d6 ");
					system("pause");
					int damage_dice = ((rand() % 6) + 1) * 2;
					current->hp -= damage_dice;
				}
				else if (smash_dice == 1) {
					printf("!");
					printf("\n치명타!");
					current->hp -= 12;
				}
				else {
					printf("공격 실패");
				}
			}
			else if (strcmp(selected_skill.name, "기절 타격") == 0) {
				use_skill_str("기절 타격");
			}
			else if (strcmp(selected_skill.name, "갑옷 부수기") == 0) {
				use_skill_str("갑옷 부수기");
			}
			else if (strcmp(selected_skill.name, "잡기") == 0) {
				use_skill_str("잡기");
			}
			else if (strcmp(selected_skill.name, "연속행동") == 0) {
				use_skill_dex("연속행동");
			}
			else if (strcmp(selected_skill.name, "도주") == 0) {
				use_skill_dex("도주");
			}
			else if (strcmp(selected_skill.name, "은신") == 0) {
				use_skill_dex("은신");
			}
			else if (strcmp(selected_skill.name, "암살") == 0) {
				use_skill_dex("암살");
			}
			else if (strcmp(selected_skill.name, "분석") == 0) {
				use_skill_wis("분석");
			}
			else if (strcmp(selected_skill.name, "마법 공격") == 0) {
				use_skill_wis("마법 공격");
			}
			else if (strcmp(selected_skill.name, "순간이동") == 0) {
				use_skill_wis("순간이동");
			}
			else if (strcmp(selected_skill.name, "힐") == 0) {
				use_skill_wis("힐");
			}
		}
		}
	}

}

int main() {
	character_creat();
	skill_choice();
	status_check();

	while (stat[0].value != 20) {
		printf("주사위를 굴리시오\n");
		int action_dice = (rand() % 20 + 1);
		system("pause");
		printf("%d\n", action_dice);
		if (action_dice < stat[5].value && action_dice <= 10) {
			store();
		}
		system("pause");
		if (action_dice > stat[5].value) {
			battle(action_dice - stat[5].value);
		}
		system("pause");
	}

	return 0;
}