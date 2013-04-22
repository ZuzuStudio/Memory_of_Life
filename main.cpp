#include<iostream>
#include<cstdlib>
#include<ctime>
#include"my_stack.h"
#include"transfer.h"

using namespace std;
using namespace ccg;

struct Life{
	bool *map;
	Node_int **memory;
	int x, y;
};

void Bild(Life &work, bool fl){
	srand(time(0));
	work.map = new bool[work.x*work.y*2];
	work.memory = new Node_int* [work.x*work.y];
	int n = work.x*work.y;
	for(int i = 0; i < n; i++){
		if(rand()%2 == 0 && fl){
			work.map[i] = true;
			work.map[i+n] = true;
		}
		else{
			work.map[i] = false;
			work.map[i+n] = false;
		}
		work.memory[i] = NULL;
	}
}

void Clean_Line(int length , int x, int y){
	SetCurrentPos(x, y);
	for(; length > 0; length--)
		cout << ' ';
}

void Choise_Drow(int length){
	OutS(TOP_LEFT_CORNER);
	for(int i = 0; i < length+1; i++)
		OutS(HORIZONTAL);
	OutS(TOP_RIGHT_CORNER);
	cout << '\n';
		OutS(VERTICAL);
		for(int i = 0; i < length; i++)
			cout << ' ';
		OutS(UP_DOWN_ARROW);
		OutS(VERTICAL);
		cout << '\n';
	OutS(DOWN_LEFT_CORNER);
	for(int i = 0; i < length+1; i++)
		OutS(HORIZONTAL);
	OutS(DOWN_RIGHT_CORNER);
	cout << '\n';
}

int Number_Length(int numb){
	int length = 0;
	while(numb){
		length++;
		numb/=10;
	}
	return length;
}

int Numberik_Work(int max, int min ,int x = 0, int y = 0, int eps = 1){
	SetCurrentPos(x, y);
	int num = min, length = Number_Length(max);
	cout << num;
	while(1){
		switch(Arrows()){
		case 0:
			if(num < max)
				num += eps;
			else num = min;
			break;
		case 3:
			if(num > min)
				num -= eps;
			else num = max;
			break;
		case ENTER+5:
			return num;
			break;
			}
		Clean_Line(length, x, y);
		SetCurrentPos(x, y);
		cout << num;
	}
}

int Text_Size(char work[]){
	int size = 0;
	for(; work[size] != '\0'; size++);
	return size;
}

int Textik_Work(char work[], int length, int x = 0, int y = 0){
	SetCurrentPos(x, y);
	int num = 0, size = (Text_Size(work) / length) - 1;
	for(int i = 0; i < length; i++)
	cout << work[i];
	while(1){
		switch(Arrows()){
		case 0:
			if(num < size)
				num++;
			else
				num = 0;
			break;
		case 3:
			if(num > 0)
				num--;
			else
				num = size;
			break;
		case ENTER+5:
			return num;
			break;
		}
		SetCurrentPos(x, y);
		for(int i = 0; i < length; i++)
		cout << work[num*length+i];
	}
}

void Print_Table(int x, int y){
	OutS(TOP_LEFT_CORNER);
	for(int i = 0; i < x; i++)
		OutS(HORIZONTAL);
	OutS(TOP_RIGHT_CORNER);
	cout << '\n';
	for(int n = 1; n <= y; n++){
		OutS(VERTICAL);
		SetCurrentPos(x+1, n+1);
		OutS(VERTICAL);
		cout << '\n';
	}
	OutS(DOWN_LEFT_CORNER);
	for(int i = 0; i < x; i++)
		OutS(HORIZONTAL);
	OutS(DOWN_RIGHT_CORNER);
}

void Input_Map(Life &work){
	CleanConsol();
	cout << "Input bloks\n";
	Print_Table(work.x,work.y);
	int pos = 0, old_pos=0;
	int x=1,y=2, end=work.x*work.y;
	int old_x=1,old_y=2;
	for(bool fl = true; fl;){
		SetCurrentPos(old_x,old_y);
		work.map[old_pos+end] = work.map[old_pos];
		if(work.map[old_pos+end])
			OutS(FULL_BLOCK);
		else
			cout << ' ';
		old_pos = pos;
		old_x=x;
		old_y=y;
		SetCurrentPos(x,y);
		OutS(LIGHT_SHADE);
		SetCurrentPos(x,y);
		switch(Arrows()){
			case UP:
				if(pos - work.x > 0){
					pos -= work.x;
					y--;
				}
				break;
			case LEFT:
				if((pos-1)/work.x == pos/work.x){
					pos--;
					x--;
				}
				break;
			case RIGHT:
				if((pos+1)/work.x == pos/work.x){
					pos++;
					x++;
				}
				break;
			case DOWN:
				if(pos + work.x < end){
					pos += work.x;
					y++;
				}
				break;
			case ENTER+5:
				fl = false;
				break;
			case SPACE+5:
				work.map[pos] = !work.map[pos];
				break;
		}
	}
}

void Print_Field(Life work){
	for(int n = 0; n < work.y; n++){
		SetCurrentPos(1, n+2);
		for(int i = 0; i < work.x; i++)
			if(work.map[work.x*n+i])
				OutS(FULL_BLOCK);
			else
				cout << ' ';
	}
}

int Number_nabers (Life work, int pos){
    int nabers=0;
	int line = pos / work.x -1; 
	int fpos = pos - 1 - work.x;
    for (int i=0; i<3; ++i){
		for (int n = 0; n < 3; ++n){
			int mpos = fpos + n + work.x*i;
			if (line + i == mpos / work.x && mpos < work.x * work.y && mpos != pos && work.map[mpos]== 1 )
			++nabers;
		}
    }
	return nabers;
}

void Update_Map(Life &work){
	int mapEnd = work.x * work.y, bufEnd = mapEnd * 2;
	for(int i = mapEnd, pos = 0; i < bufEnd; i++,pos++)
		work.map[pos] = work.map[i];
}

void Survival(Life &work){
	int mapEnd = work.x * work.y, bufEnd = mapEnd * 2;
	int memory, nabers;
	for(int i = mapEnd, pos = 0; i < bufEnd; i++,pos++){
		memory = OnTop(work.memory[pos]);
		if(memory == -1) memory = 3;
		nabers = Number_nabers(work, pos);
		if(work.map[pos]){
			if(nabers < memory - 1){
				if(nabers == memory-2)Push(work.memory[pos],memory<8 ? memory+1 : memory);
				else Pop(work.memory[pos]);
				work.map[i] = false;
			}
			else if(nabers > memory){
				if(nabers == memory + 1)Push(work.memory[pos],memory>2 ? memory-1 : memory);
				else Pop(work.memory[pos]);
				work.map[i] = false;
			}
		}
		else if(nabers == memory)
			work.map[i] = true;
	}
	Update_Map(work);
}

void Start_Life(Life &map, int time){
	CleanConsol();
	cout << time << '\n';
	int length = Number_Length(time);
	Print_Table(map.x, map.y);
	Print_Field(map);
	for(; 0 <= time; time--){
		Survival(map);
		Clean_Line(length, 0, 0);
		SetCurrentPos(0,0);   
		cout << time;
		sleep(100);
		Print_Field(map);

	}
}

void Delete(Life &work){
	delete [] work.map;
	for(int i = 0; i < work.x*work.y; i++)
		Clear(work.memory[i]);
	delete [] work.memory;
}

void Menu(){
	int time;
	bool fl;
	Life map;
	char *YN = "NO YES";
	cout << "Input width:\n";
	Choise_Drow(5);
	cout << '\n';
	cout << "Input Length:\n";
	Choise_Drow(5);
	cout << '\n';
	cout << "Input namber of staps:\n";
	Choise_Drow(7);
	cout << '\n';
	cout << "You want imput map yourself?\n";
	Choise_Drow(5);
	cout << '\n';
	map.x = Numberik_Work(100,5,1,2,1); 
	map.y = Numberik_Work(100,5,1,7,1);
	time = Numberik_Work(10000,0,1,12,100);
	fl = Textik_Work(YN, 3, 1, 17);
	Bild(map, !fl);
	if(fl) Input_Map(map);
	Start_Life(map, time);
	Delete(map);
	SetCurrentPos(0, map.y+3);
	Pause();
}

int main(){
	Menu();
	
	
}