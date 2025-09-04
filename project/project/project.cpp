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
	{"전사","전투의 아이","str 스탯 다이스의 수 -3"},
	{"도적","민첩한","dex 스탯 사용시 다이스 -3"},
	{"마법사","똑똑한 두뇌","wis 스탯 사용시 다이스 -3"},
	{"사제","신의 축복","가끔 신의 축복이 내려온다"}
};
struct Class_skill player_class_skill;

int coin = 0;
int player_item_count;
struct ITEM {
	const char* name;
	const char* effect;
	int cost;
};
struct ITEM item[]{
	{"죽창", "상대에게 공격시 무조건 죽입니다",50},
	{"회복약","hp를 1~6까지 상승한다",5},
	{"힘의 물약","str을 1~6까지 상승한다",5},
	{"신속의 물약","dex를 1~6까지 상승한다", 5},
	{"지혜의 물약","wis를 1~6까지 상승한다",5},
	{"마왕의 힘","영구적으로 모든 스탯을 20으로 만든다.마왕을 이길 경우 당신은 ᗪᗩᗷᗷ ᗰᗩᗯᗩᝪ Ꮍ ᗪᗴᗰᙢᔕ.ᘜᗴᎥᗰᗴOᐯᗴᖇ(뜻을 모르는 글자가 나열되어 있다)",0}
};
struct ITEM player_item[10];


struct Monster {
	const char* name;
	int hp;
	char skill[20];
};
struct Monster monster[]{
	{"슬라임",8,"자가치유"},
	{"오크",15,"강타"},
	{"데스나이트",20,"오러블레이드"},
	{"드래곤",30,"드래곤 브래스"},
	{"마왕", 0,"악의 일격"}
};

int demon_ = 0;

void level_up() {
	int want_stat;
	stat[0].value += 1; 
	printf("원하는 스탯을 번호를 눌러 올리세요\n(1~5까지 순서대로 체력, 근력, 민첩, 지능, 운)");
	scanf_s("%d", &want_stat);
	stat[want_stat].value += 1;
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

int skill_success;
void use_skill_str(const char* skill_naming) {
	printf("주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d\n", dice);
	if (strcmp(player_class.pl_class, "전사")) {
		dice -= 3;
	}
	if (stat[2].value > dice) {
		printf("%s 사용\n",skill_naming);
		skill_success = 1;
	}
	else {
		printf("실패");
		skill_success = 0;
	}
}
void use_skill_dex(const char* skill_naming) {
	printf("주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d\n", dice);
	if (strcmp(player_class.pl_class, "도적")) {
		dice -= 3;
	}
	if (stat[3].value > dice) {
		printf("%s 사용\n", skill_naming);
		skill_success = 1;
	}
	else {
		printf("실패");
		skill_success = 0;
	}
}
void use_skill_wis(const char* skill_naming) {
	printf("주사위 굴리기");
	system("pause");
	int dice = (rand() % 20) + 1;
	printf("주사위 : %d\n", dice);
	if (strcmp(player_class.pl_class, "마법사")) {
		dice -= 3;
	}
	if (stat[4].value > dice) {
		printf("%s 사용\n", skill_naming);
		skill_success = 1;
	}
	else {
		printf("실패");		
		skill_success = 0;
	}
}
int holy_stack;
void holy() {
	if (holy_stack != 1) {
		if (strcmp(player_class.pl_class, "사제") == 0) {
			printf("기적이 일어납니다\n");
			printf("주사위 굴리기 d6");
			system("pause");
			int holy_dice = (rand() % 4) + 1;
			printf("주사위 결과 : %d\n", holy_dice);
			if (holy_dice == 1) {
				printf("당신은 작은 돈을 얻었습니다\n");
				coin += 10;
			}
			else if (holy_dice == 2) {
				printf("당신은 자그마한 행운을 얻었습니다\n");
				stat[5].value += 5;
			}
			else if (holy_dice == 3) {
				printf("당신은 나아갈 체력을 얻었습니다\n");
				stat[1].value += 5;
			}
			else if (holy_dice == 4) {
				printf("당신은 신의 무기를 손에 넣었습니다\n");
				int place = 0;
				for (int i = 0; i < 10; i++) {
					if (player_item[i].name == NULL) {
						player_item[i] = item[0];
						place = 1;
						break;
					}
				}
				if (!place) {
					printf("자리가 없어서 받지 못했습니다\n");
				}
			}
		}
		else {
			return;
		}
		holy_stack += 1;
	}
}

void store() {
	holy();
	char want;
	printf("상점이 있습니다");
	printf("물건을 사시겠습니까?");
	struct ITEM store_item;
	printf("Y / N   ");
	scanf_s(" %c", &want, 1);
	switch (want) {
		case'Y':
		case'y': {
			int store_item = sizeof(item) / sizeof(item[0]);
			int choice[3];
			srand(time(NULL));
			for (int i = 0; i < 3; i++) {
				choice[i] = rand() % store_item;
			}
			printf("현재 상점에 입고된 아이템은 이렇게 3개 입니다\n");
			for (int i = 0; i < 3; i++) {
				printf("%d . %s - %s (가격 : %d)\n",i+1, item[choice[i]].name, item[choice[i]].effect, item[choice[i]].cost);
			}
			printf("구입할 물건을 고르시오(1~3. 0을 고를 시 상점을 나갑니다)");
			int want_item;
			scanf_s("%d", &want_item);
			if (want_item >= 1 && want_item <= 3) {
				struct ITEM selected = item[choice[want_item - 1]];
				if (coin >= selected.cost) {
					int place = 0;
					for (int i = 0; i < 10; i++) {

						if (player_item[i].name == NULL) {
							player_item[i] = selected;
							coin -= selected.cost;
							printf("%s를(을) 구매했습니다\n", selected.name);
							place = 1;
							break;
						}
					}
					if (!place) {
						printf("아이템 창이 가득 찼습니다\n");
					}
				}
				else {
					printf("가진 돈이 부족합니다\n");
				}
			}
			else {
				printf("상점을 나왔습니다\n");
			}
		}
		case'N':
		case'n': {
			printf("당신은 상점을 지나쳤습니다\n");
			break;
		}
		default:
			printf("다시 입력하시오");
	}
}
void battle(int difficult) {
	int stunn = 0;
	int armor_break = 0;
	int grap = 0;
	int repeat = 0;
	int hide = 0;
	char action;
	int turn = 0;

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
	else if (difficult == 100) {
		current = &monster[4];
		printf("%s\n", monster[4].name);
	}
	current->hp += difficult;

	while (current->hp > 0 && stat[1].value > 0) {
		if (!turn) {
			holy();
			printf("\n\n행동을 선택하시오. Q : 공격, W : 스킬 사용, E : 아이템 사용, R : 상태확인\n");
			printf("입력 : ");
			scanf_s(" %c", &action, 1);

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
					printf("%d 데미지 !\n", damage_dice);
					current->hp -= damage_dice;
				}
				else if (attack_dice == 1) {
					printf("!");
					printf("\n치명타!");
					current->hp -= 20;
					printf("20데미지 !!!");
				}
				else if (grap==1) {
					printf("상대를 잡아놓아 무조건 공격합니다");
					printf("\n데미지 다이스 d6 ");
					system("pause");
					int damage_dice = (rand() % 6) + 1;
					printf("%d 데미지 !\n", damage_dice);
					current->hp -= damage_dice;
				}
				if (armor_break) {
					printf("부숴진 갑옷에 의해 상대는 데미지를 입었습니다\n");
					int damage_dice = (rand() % 4) + 1;
					printf("%d 데미지 \n", damage_dice);
					current->hp -= damage_dice;
				}
				else {
					printf("공격 실패");
				}
				hide = 0;
				break;
			}

			case'W':
			case'w':
			{
				printf("스킬 목록\n");
				for (int i = 0; i < 3; i++) {
					printf("%s : %s : %s", player_skill[i].name, player_skill[i].use_stat, player_skill[i].effect);
					printf("\n");
				}
				int skill_choice;
				printf("1번째 스킬을 사용할려면 1, 2번째 스킬을 사용하려면 2, 3번째 스킬을 사용하려면 3을 누르시오  ");
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
						printf("%d\n", damage_dice);
						current->hp -= damage_dice;
					}
					else if (smash_dice == 1) {
						printf("치명타!");
						current->hp -= 12;
					}
					else {
						printf("공격 실패");
					}
				}

				else if (strcmp(selected_skill.name, "기절 타격") == 0) {
					use_skill_str("기절 타격");
					if (skill_success) {
						int damage_dice = ((rand() % 4) + 1) * 2;
						printf("%d의 데미지\n", damage_dice);
						current->hp -= damage_dice;
						stunn = 1;
					}
				}

				else if (strcmp(selected_skill.name, "갑옷 부수기") == 0) {
					use_skill_str("갑옷 부수기");
					if (skill_success) {
						armor_break = 1;
					}
				}

				else if (strcmp(selected_skill.name, "잡기") == 0) {
					use_skill_str("잡기");
					if (skill_success) {
						grap = 1;
					}
				}

				else if (strcmp(selected_skill.name, "연속행동") == 0) {
					use_skill_dex("연속행동");
					if (skill_success) {
						repeat = 2;
					}
				}

				else if (strcmp(selected_skill.name, "도주") == 0) {
					use_skill_dex("도주");
					if (skill_success) {
						printf("도주 성공\n");
						return;
					}
				}

				else if (strcmp(selected_skill.name, "은신") == 0) {
					use_skill_dex("은신");
					if (skill_success) {
						hide = 2;
					}
				}

				else if (strcmp(selected_skill.name, "암살") == 0) {
					use_skill_dex("암살");
					if (skill_success) {
						printf("데미지 다이스");
						system("pause");
						int damage = (rand() % 6) + 1;
						damage *= 2;
						printf("%d의 데미지 !\n", damage);
						current->hp -= damage;
					}
				}

				else if (strcmp(selected_skill.name, "분석") == 0) {
					use_skill_wis("분석\n");
					if (skill_success) {
						printf("이름 : %s\nhp : %d\n스킬 : %s\n", current->name, current->hp, current->skill);
					}
				}

				else if (strcmp(selected_skill.name, "마법 공격") == 0) {
					use_skill_wis("마법 공격");
					if (skill_success) {
						printf("데미지 다이스 d8");
						system("pause");
						int dice = (rand() % 8) + 1;
						printf("%d의 데미지 !\n", dice);
						current->hp -= dice;
					}
				}

				else if (strcmp(selected_skill.name, "순간이동") == 0) {
					use_skill_wis("순간이동");
					if (skill_success) {
						printf("도주 성공\n");
						return;
					}
				}

				else if (strcmp(selected_skill.name, "힐") == 0) {
					use_skill_wis("힐");
					if (skill_success) {
						printf("치유 다이스 d6");
						system("pause");
						int dice = (rand() % 6) + 1;
						printf("%d만큼 회복\n", dice);
						stat[0].value += dice;
					}
				}
				hide -= 1;
				break;
			}

			case'E':
			case'e': {
				int item_choice;
				printf("플레이어의 인벤토리\n");
				for (int i = 0; i <= player_item_count; i++) {
					if (player_item[i].name != NULL) {
						printf("%d . %s - %s\n", i + 1, player_item[i].name, player_item[i].effect);
					}
					else {
						printf("%d . (빈 슬롯)\n", i + 1);
					}
				}
				printf("사용하고 싶은 아이템의 숫자를 입력하시오(첫번째 아이템은 1번,두번째 아이템은 2번)  ");
				scanf_s("%d", &item_choice);
				if (item_choice < 0 || item_choice > 10) {
					printf("범위를 벗어났습니다. 다시 고르세요");
					break;
				}
				int idx = item_choice - 1;
				struct ITEM selected_item = player_item[idx];

				if (player_item[idx].name == NULL) {
					printf("당신은 아이템을 사용하려 하였으나 그곳에는 아무것도 없었습니다");
				}
				else if (strcmp(selected_item.name, "죽창") == 0) {
					printf("당신은 죽창을 들고 상대에게 꽃았습니다");
					current->hp = 0;
				}
				else if (strcmp(selected_item.name, "회복약") == 0) {
					printf("당신은 회복약을 마셨습니다");
					int heal = (rand() % 6) + 1;
					stat[1].value += heal;
				}
				else if (strcmp(selected_item.name, "힘의 물약") == 0) {
					printf("당신은 힘의 물약을 마셨습니다");
					int heal = (rand() % 6) + 1;
					stat[2].value += heal;
				}
				else if (strcmp(selected_item.name, "신속의 물약") == 0) {
					printf("당신은 신속의 물약을 마셨습니다");
					int heal = (rand() % 6) + 1;
					stat[3].value += heal;
				}
				else if (strcmp(selected_item.name, "지혜의 물약") == 0) {
					printf("당신은 지혜의 물약을 마셨습니다");
					int heal = (rand() % 6) + 1;
					stat[4].value += heal;
				}
				else if (strcmp(selected_item.name, "마왕의 힘") == 0) {
					printf("당신은 결국 마왕의 힘을 사용했습니다");
					for (int i = 0; i < 6; i++) {
						stat[i].value = 20;
					}
					demon_ += 1;
				}
				break;
			}

			case'R':
			case'r':
			{
				printf("플레이어의 상태\n");
				status_check();
				break;
			}
			}
			turn = 1;
		}

		if (repeat) {
			printf("추가 행동이 가능합니다");
			repeat -= 1;
			turn = 0;
		}

		if (stunn) {
			printf("%s는(은) 기절한 상태 입니다\n", current->name);
			stunn = 0;
			turn = 0;
		}
		
		if (turn) {
			int monster_action = (rand() % 3) + 1;
			if (hide == 1) {
				printf("몬스터는 당신을 발견하지 못했다\n");
				turn = 0;
				continue;
			}
			if (monster_action > 1) {
				printf("몬스터의 공격\n");
				printf("회피 다이스");
				system("pause");
				int avoid = (rand() % 20) + 1;
				printf("%d\n", avoid);
				if (avoid < stat[3].value) {
					printf("회피 성공");
				}
				else {
					printf("회피 실패!");
					if (strcmp(current->name, "슬라임") == 0) {
						int damage = (rand() % 4) + 1;
						printf("%d데미지!", damage);
						stat[1].value -= damage;
					}
					else if (strcmp(current->name, "오크") == 0) {
						int damage = (rand() % 6) + 1;
						printf("%d데미지!", damage);
						stat[1].value -= damage;
					}
					else if (strcmp(current->name, "데스나이트") == 0) {
						int damage = (rand() % 10) + 1;
						printf("%d데미지!", damage);
						stat[1].value -= damage;
					}
					else if (strcmp(current->name, "드래곤") == 0) {
						int damage = (rand() % 20) + 1;
						printf("%d데미지!", damage);
						stat[1].value -= damage;
					}
				}
			}
			else {
				if (strcmp(current->skill, "자가치유") == 0) {
					printf("슬라임이 자가치유를 사용했다!\n");
					int heal = (rand() % 4) + 1;
					current->hp += heal;
					printf("몬스터의 체력이 %d만큼 회복되었다\n", heal);
				}
				else if (strcmp(current->skill, "강타")==0) {
					printf("오크가 강타를 사용했다!");
					printf("회피 다이스");
					system("pause");
					int avoid = (rand() % 20) + 1;
					if (avoid < stat[3].value) {
						printf("회피 성공");
					}
					else {
						int damage = ((rand() % 6) + 1) * 2;
						printf("오크의 공격!\n");
						printf("%d만큼의 데미지를 받았습니다\n", damage);
						stat[1].value -= damage;
					}
				}
				else if (strcmp(current->skill, "오러블레이드")==0) {
					printf("데스나이트가 오러블레이드를 사용했다!");
					printf("회피 다이스");
					system("pause");
					int avoid = (rand() % 20) + 1;
					if (avoid < stat[3].value) {
						printf("회피 성공");
					}
					else {
						int damage = ((rand() % 20) + 1) * 2;
						printf("데스나이트의 공격!\n");
						printf("%d만큼의 데미지를 받았습니다\n", damage);
						stat[1].value -= damage;
					}
				}
				else if (strcmp(current->skill, "드래곤 브래스")==0) {
					printf("드래곤이 드래곤 브래스를 사용했다!");

					for (int i = 0; i < 3; i++) {
						printf("회피 다이스");
						system("pause");
						int avoid = (rand() % 20) + 1;
						if (avoid < stat[3].value) {
							printf("\n회피!");
						}
						else {
							int damage = ((rand() % 20) + 1);
							printf("몬스터의 공격!\n");
							printf("%d만큼의 데미지를 받았습니다\n", damage);
							stat[1].value -= damage;
						}
					}
				}
			}
			turn = 0;
		}
			}

	if (current->hp <= 0) {
		printf("\n몬스터를 쓰러트렸습니다\n");
		coin += difficult * 10;
		level_up();		
		printf("당신은 레밸을 올렸습니다\n");
		printf("%d만큼의 coin을 얻었습니다\n", difficult * 10);

	}
	if (stat[1].value <= 0) {
		printf("당신은 쓰러졌습니다\n");
		printf("당신은 교회에서 부활했습니다\n");
		stat[1].value = 30;
	}
	else if (stat[1].value == 0 && strcmp(current->name, "마왕")==0) {
		printf("당신은 마왕에게 패배하였습니다\n");
		demon_ += 1;
		printf("당신은 교회에서 부활했습니다\n");
		stat[1].value = 30;
	}
}
void traning() {
	holy();
	printf("당신은 잠시 아르바이트를 합니다\n");
	printf("원하는 아르바이트를 선택하시오 1번, 2번, 3번\n");
	int rand_stat_up;
	scanf_s("%d", &rand_stat_up, 1);
	if (rand_stat_up == 1) {
		printf("당신은 건설 알바로 돈을 벌었습니다. 근력을 올렸습니다\n");
		stat[2].value += 1;
		int earn_coin = ((rand() % 10) + 1)*5;
		coin += earn_coin;
		printf("%d 만큼의 coin을 얻었습니다\n", earn_coin);
	}
	if (rand_stat_up == 2) {
		printf("당신은 배달 알바로 돈을 벌었습니다. 민첩을 올렸습니다\n");
		stat[3].value += 1;
		int earn_coin = ((rand() % 10) + 1) * 5;
		coin += earn_coin;
		printf("%d 만큼의 coin을 얻었습니다\n", earn_coin);

	}	
	if (rand_stat_up == 3) {
		printf("당신은 건설 알바로 돈을 벌었습니다. 지능을 올렸습니다\n");
		stat[4].value += 1;
		int earn_coin = ((rand() % 10) + 1) * 5;
		coin += earn_coin;
		printf("%d 만큼의 coin을 얻었습니다\n", earn_coin);

	}
	stat[0].value += 1;
}
void break_time() {
	printf("당신은 오랜만에 쉬었다\n");
	stat[1].value += 10;
	printf("hp가 10 회복되었다\n");
}

int main() {
	character_creat();
	skill_choice();
	status_check();

	while (stat[0].value != 20) {
		printf("\n주사위를 굴리시오\n");
		int action_dice = (rand() % 20 + 1);
		system("pause");
		printf("%d\n", action_dice);
		if (action_dice <= stat[5].value && action_dice > 10) {
			store();
		}
		if (action_dice <= stat[5].value && action_dice <= 5 ) {
			break_time();
		}
		if (action_dice <= stat[5].value && action_dice <= 10) {
			traning();
		}
		else if (action_dice > stat[5].value) {
			battle(action_dice);
		}
		system("pause");
	}
	if (stat[0].value == 20) {
		printf("당신의 여정에 끝이 보이기 시작한다\n");
		printf("당신은 마왕 앞에 서 있다");
		battle(100);
	}
	printf("당신은 마왕을 죽이고 이 세상의 평화를 가져왔습니다\n");
	if (demon_ == 0) {
		printf("                    HAPPY END");
	}
	else if (demon_ >= 1) {
		printf("                    HAPPY END?");
		system("pause");
		printf("당신은 마왕과 싸웠던 마지막 장소에 와 있습니다\n");
		printf("당신은 마왕이 앉았던 그 왕좌에 앉았습니다\n");
		printf("당신의 몸에 있는 씨앗은 결국 피어났습니다\n\n");
		printf("당신은 마왕이 되었습니다\n\n");
		printf("                     BAD END");
	}
	return 0;
}