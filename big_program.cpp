#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<conio.h>
#include<vector>
#include<iterator>

using namespace std;


//int main(); 

void initial();		//�����ʼ������ 
void save_data(); 		//�������� 

int m_get_order();		//��ȡ�������û����� 
void m_print(int); 		//��ӡ������

void log_desk();		// ��¼���� 
int log_search(string, string); 		//����userlist�����Ӧ�û�
 
void register_desk();		// ע����� 
bool register_legal(string);		//�ж����˺ŵĺϷ��� 

void user_desk(int);		// ���˽��� 
int user_get_order(int);		// ��ȡ���˽����û����� 

void print_title(const string place = "");
void mSleep(long=1000);

bool ensure();



#include"user.h"		//����ȫ�ֱ���userlist 

int main(){
	initial();
	
	int order;
	while ((order=m_get_order())!=2) {
		switch(order) {
			case 0:{		//��½
			    system("cls"); 
				log_desk();
			    system("cls");
				break;
			}
			case 1:{		//ע�����û�
			    system("cls");
				register_desk();
			    system("cls");
				break;
			}
		}
	}
	
	save_data();
	return 0;
} 


void initial(){		//#Ҫ�����ж϶�д�쳣�����# 
	ifstream infile;
	infile.open("user_information.txt");
	
	if (infile.is_open()){
		infile>>u_num;
		for(int i = 0; i< u_num; i++){
			string id, code;
			int order, size;
			infile>>id>>code>>order>>size;
			
			User t(id, code);
			t.set_ord(order);
			
			for(int j = 0; j<size; j++){
				Rec t_rec;
				infile>>t_rec;
				t.reclist.push_back(t_rec);
			}
			
			userlist.push_back(t);
		}
		
		infile.close();
	}
	
}

void save_data(){
	ofstream outfile;
	outfile.open("user_information.txt");
	
	outfile<<u_num<<endl;
	
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++){
		vector<Rec> &t = i->reclist;
		outfile<<i->id<<" "<<i->code<<" "<<i->order<<" "<<t.size()<<endl;
		for(vector<Rec>::iterator j = t.begin(); j!=t.end();j++)
			outfile<<j->print_line()<<endl;
	}
	
	outfile.close();
}

int m_get_order(){
	char w_button=72;
	int mark = 1;
	do {
		switch(w_button){
			case 72:{
				mark  = (mark-1)%3;
				if (mark<0) mark = 2;
				break;
			}
			case 80:{
				mark = (mark+1)%3;
				break;
			}
			case 13:{
				return mark;
				break;
			}
		}	
		if (w_button==72||w_button==80){
			system("cls");
			m_print(mark);
		}
	} while (w_button=getch());
}

void m_print(int m){ 
	print_title();
	
	cout<<setw(28)<<" "<<"--=�������ϵͳ ";
	switch(m){
		case 0:{ cout<<"^��^"; break;}
		case 1:{ cout<<";)"; break;}
		case 2:{ cout<<"��^��"; break;}
	}
	cout<<" =--"<<endl<<endl<<endl;
	/*cout<<setw(23)<<" "
		<<setfill('+')<<setw(30)<<"+"
		<<setfill(' ')<<endl<<endl;*/ 
		
	string order_arr1[]={"     |��¼|     ", "  |ע�����û�|  ", "     |�˳�|     "};
	string order_arr2[]={"   |> ��¼ <|   ", "|> ע�����û� <|", "   |> �˳� <|   "};
	
	for (int i = 0; i < 3; i++)
		if (i == m){
			cout<<setw(30)<<" "
				<<order_arr2[i]<<endl<<endl;
		}
		else cout<<setw(30)<<" "
				 <<order_arr1[i]<<endl<<endl;

	cout<<setw(23)<<" "
		<<"������������������������������"<<endl;
		
	cout<<setw(23)<<" "<<"ע����������ƶ�ѡ�񣬰�Enter��ȷ�ϲ���"; 
}

void log_desk(){	
    print_title(">��¼");

	cout<<setw(30)<<" "<<"--=��¼ϵͳ�˻� >_< =--"<<endl<<endl;
	
	string id, code;
	
	cout<<endl<<setw(23)<<" "<<"�û���: ";
	cin>>id;
	
	cout<<endl<<setw(23)<<" "<<"���룺"; 
	cin>>code;
	
	int order;
	if ((order=log_search(id, code))!=-1) user_desk(order);
	else {
		//#��ʾ�û���������� # 
		return;
	} 
	
}

//���û�����userlist��Ѱ��ƥ����û� 
int log_search(string id, string code){
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++)
		if (i->Log(id, code)) return int(i-userlist.begin());
	return -1;
}

void register_desk(){
    print_title(">ע��");
    
	cout<<setw(30)<<" "<<"--=ע�����û� ^3^ =--"<<endl<<endl;
	
	string id, code;
	
	cout<<endl<<setw(23)<<" "<<"�û���: ";
	cin>>id;
	
	cout<<endl<<setw(23)<<" "<<"���룺"; 
	cin>>code;
	
	if (register_legal(id)){
		User t_user(id, code);
		t_user.set_ord(u_num);
		u_num++;
		userlist.push_back(t_user);
	}
	else {
		//#��ʾ�û����ظ� # 
		return;
	}
	
}

bool register_legal(string id){
	for(vector<User>::iterator i = userlist.begin(); i!=userlist.end(); i++)
		if (i->Log_name(id)) return false;
	return true;
} 

void user_desk(int u_order){
	int order;
	while ((order=user_get_order(u_order))!=2) {
		switch(order) {
			case 0:{		//�����»����¼ 
			    system("cls"); 
				userlist[u_order].new_rec();
			    system("cls");
				break;
			}
			case 1:{		//��ѯ�����¼ 
			    system("cls");
				userlist[u_order].check_rec();
			    system("cls");
				break;
			}
		}
	}
}

int user_get_order(int u_order){
	char w_button=72;
	int mark = 1;
	const string s_today=userlist[u_order].show_today();
	do {
		switch(w_button){
			case 72:{
				mark  = (mark-1)%3;
				if (mark<0) mark = 2;
				break;
			}
			case 80:{
				mark = (mark+1)%3;
				break;
			}
			case 13:{
				return mark;
				break;
			}
		}	
		if (w_button==72||w_button==80){
			system("cls");
			userlist[u_order].u_print(s_today,mark);
		}
	} while (w_button=getch());
}

void print_title(const string place){
	Time now_time;
    cout<<left<<setw(60)<<">��ҳ"+place
    	<<right<<setw(19)<<now_time.print_time()+" "
		<<endl
    	<<"��������������������"
    	<<"��������������������"
    	<<"��������������������"
    	<<"��������������������"
		<<endl;
}

void mSleep(long m_second){

	for(int i = 0; i< m_second; i++){
		for (int j=0; j<480000;j++){
		}
	}
}

bool ensure(){
	cout<<setw(23)<<" "<<"���Ƿ�ȷ�����浱ǰ�޸ģ���\n";
	cout<<setw(23)<<" "<<"���밴'y'���沢�Ƴ�����'n'ֱ���˳�;��\n";
	char choice;
	while(choice=getch()){
		if (choice=='n'){
			cout<<setw(23)<<" "<<"���˳��ɹ�������δ���޸ģ���";
			mSleep(1000);
			return false;
		}
		else if (choice=='y'){
			cout<<setw(23)<<" "<<"���޸ĳɹ�����";
			mSleep(1000);
			return true;
		}
	}
}


