#ifndef USER_H
#define USER_H

#include<vector> 
#include"mtime.h"
#include"meetingRec.h"

class User;
vector<User> userlist;
int u_num;

class User{
	friend void initial();		//�����ʼ������ 
    friend void save_data(); 		//�������� 
	friend ostream &operator<<(ostream &output, User user);
	private:
		string id;
		string code;
		int order;
		vector<Rec> reclist;
	public:
		User(){
			id = "0000";
			code = "0000";
			order = 0;
		}
		User(string i, string c){
			id = i;
			code = c;
			order = 0;
		}
		~User(){
		}
		
		void print_title(const string place=""){
			Time now_time;
			ostringstream s;
			s<<">��ҳ>��¼> "<<id<<" ������ҳ"<<place;
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<now_time.print_time()+" "
				<<endl
				<<setfill('-')<<setw(80)<<"-"
				<<setfill(' ')
				<<endl;
		}
		void set_ord(int ord){
			order = ord;
		}
		bool Log(string i, string c){
			if (i==id&&c==code) return true;
			return false;
		}
		bool Log_name(string i){
			if (i==id) return true;
			return false;
		}
		string show_today(){
			ostringstream s;
			
			int mark = 0;
			for(vector<Rec>::iterator i = reclist.begin(); i!=reclist.end();i++){
				i->renew_situaiton();
				if(i->is_today()){
					
					mark = 1;
					
					//cout<<i->for_short();
					s<<i->for_short();
				}
			}
			if (mark==0){
				//cout<<endl<<endl<<setw(23)<<" "
				//	<<":����û�л��飬�ú���Ϣ��Ϣ�����°��ȥ�������ֽ^3^��\n\n\n";
				s<<endl<<endl<<setw(23)<<" "
					<<"������û�л��飬�ú���Ϣ��Ϣ�����°��ȥ�������ֽ^3^����\n";
			}
			else {
				//cout<<endl<<endl<<setw(23)<<" "
				//	<<":���ܣ����屻�Ϳ�_(:3J<)_��MDZZ��\n\n\n";
				s<<endl<<endl<<setw(23)<<" "
					<<"���о������屻�Ϳ�_(:3J<)_��MDZZ����\n";
			}
			return s.str();
		}
		void u_print(const string show_today,int m){
			print_title();

			string ico[]={"���","���","o��O"};
   			cout<<setw(32)<<" "<<"--=o("<<ico[m]<<")o=--"<<endl;

			cout<<show_today;

			cout<<endl;
			/*cout<<setw(23)<<" "
				<<setfill('+')<<setw(30)<<"+"
				<<setfill(' ')<<endl<<endl;*/ 
		
			string order_arr1[]={"  |���������¼|  ", "    |��ѯ��¼|    ", "      |�˳�|      "};
			string order_arr2[]={"|> ���������¼ <|", "  |> ��ѯ��¼ <|  ", "    |> �˳� <|    "};
	
			for (int i = 0; i < 3; i++)
				if (i == m){
					cout<<setw(29)<<" "
						<<order_arr2[i]<<endl<<endl;
				}
				else cout<<setw(29)<<" "
						 <<order_arr1[i]<<endl<<endl;

		}
		int print_chose_time(const string have_set,int f_order,int s_order, int size, int mark){
			print_title(">�»����¼");
			cout<<have_set;
			
			//ȷ��ѡ����ʾ��Χ
			static int begin;
			static int end;
			if (mark == 1){
				begin = s_order;
				end = begin+4;
			}
			else if (s_order == 0){
				begin= 0;
				end = 4;
			}
			else if (s_order == size-1){
				begin = s_order-4;
				end = s_order;
			}
			else if (s_order>end){
				begin++;
				end++;
			}
			else if (s_order<begin) {
				begin--;
				end--;
			}
			
			Time now;
			const int year = now.get_year();
			int f_button[]={year, 1, 1, 0, 0};
			int arr_pace[] = {1, 1, 1, 1, 5};
			int pace = arr_pace[f_order];
			
			int wid=0;
			for (int i= have_set.size()-1; i>=0; i--){
				if (have_set[i]=='\n') break;
				else wid++;
			}
			
			//��¼��һ������ʾ��ֵ
			int button = begin*pace+f_button[f_order], return_num;
			for (int i= begin; i<=end; i++){

				if (i!=begin) {
					cout<<setw(wid)<<" ";
					button+=pace;
				}
				
				if (s_order == i){
					cout<<">"<<button<<endl;
					return_num = button;
				}
				else cout<<button<<endl;
				
			}

			return return_num;
		}
		Time chose_time(const string what_time){
			char w_button=' ';
			int size[] = {5, 12, 31, 24, 12};
			int f_order = 0, s_order = 0;
			int time_data[5];
			string word[]={"/", "/", " ", ":", ""};
			string have_set=what_time;
			
			do {
				switch(w_button){
					case 72:{
						s_order  = (s_order-1)%size[f_order];
						if (s_order<0) s_order = size[f_order]-1;
						break;
					}
					case 80:{
						s_order = (s_order+1)%size[f_order];
						break;
					}
					case 13:{
						
						if (f_order == 1){
							int &day = size[2];
							int year = time_data[f_order-1],
								mon = time_data[f_order];
								
							if (mon==2){
								if (year%4==0&&year%100!=0) day = 29;
								else if (year % 400==0) day = 29;
								else day = 28;
							}
							else if(mon<=7){
								if (mon%2==0) day = 30;
								else day = 31;
							}
							else if (mon>7){
								if (mon%2==0) day = 31;
								else day = 30;
							}
						}

						ostringstream s;
						s<<setfill('0')
						 <<setw(2)<<time_data[f_order]
						 <<word[f_order]
						 <<setfill(' ');
						have_set +=s.str();
						
						Time now;
						int f_place[] = {0, now.get_month()-1,
											now.get_day()-1,
											now.get_hour(),
											now.get_minute()/5};
						s_order = f_place[f_order+1];
						f_order++;
						break;
					}//end case 13:
				}//end switch();
				
				system("cls");
				int k=0;        //�����ж��Ƿ�ȷ�����ļ�ֵ
				if (w_button==13) k = 1;
				time_data[f_order] =
					print_chose_time(have_set, f_order, s_order, size[f_order], k);
				
				if(f_order==5){
				  Time t(time_data[0],
						   time_data[1],
						   time_data[2],
						   time_data[3],
						   time_data[4]);
				  return t;
				}
			} while (w_button=getch());
		}
		void new_rec(){
			print_title(">�»����¼");

			string n, ad, r;
			Time bt, et; 
			
			cout<<setw(23)<<" "<<"�������⣺";
			cin>>n;
			
			cout<<setw(23)<<" "<<"����ص㣺";
			cin>>ad;
			
			ostringstream copy_desk;
			copy_desk<<setw(23)<<" "<<"�������⣺"<<n<<endl;
			copy_desk<<setw(23)<<" "<<"����ص㣺"<<ad<<endl;
			copy_desk<<setw(23)<<" "<<"���鿪ʼʱ�䣺";

			//system("cls");
			bt = chose_time(copy_desk.str());
			copy_desk<<bt.print_time()<<endl;
			copy_desk<<setw(23)<<" "<<"�������ʱ�䣺";
			et = chose_time(copy_desk.str());
			copy_desk<<et.print_time()<<endl;
			system("cls");
			
			print_title(">�»����¼");
			cout<<copy_desk.str();
			cout<<setw(37)<<" "<<"��ע��";
			cin>>r;
			cout<<endl;
			//ȷ�ϱ���
			if (ensure()){
				reclist.push_back(Rec(n, ad, bt, et, r));
				sort_reclist();
			}
		}
		void print_edit(int n, int mark){
			print_title(">�鿴��¼>�༭");

			int wid=0, size=mark+1;
			while(size) {
				size /= 10;
				wid++;
			}
			cout<<endl
				<<" "<<setw(wid)<<"No"
				<<left
				<<" ��¼״̬ "
				<<"    ��ʼʱ��    ~    ����ʱ��    "<<" "
				<<setw(10)<<"����"<<setw(10)<<"�ص�"<<setw(20)<<"��ע"
		 		<<right<<endl;
			cout<<reclist[n]<<endl;

			string order_arr1[]={"  |ɾ����ǰ��¼|  ", "    |�޸ļ�¼|    ", "      |�˳�|      "};
			string order_arr2[]={"|> ɾ����ǰ��¼ <|", "  |> �޸ļ�¼ <|  ", "    |> �˳� <|    "};

			for (int i = 0; i < 3; i++)
				if (i == mark){
					cout<<setw(29)<<" "
						<<order_arr2[i]<<endl<<endl;
				}
				else cout<<setw(29)<<" "
						 <<order_arr1[i]<<endl<<endl;
		}
		void edit_rec(int n){
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
						if (mark == 2) return;
						else if (mark == 1) {
							system("cls");
							print_title(">�鿴��¼>�༭");
							reclist[n].edit();
							sort_reclist();
						}
						else if (mark == 0) {
							system("cls");
							print_title(">�鿴��¼>�༭");
							cout<<endl<<endl;
							if(ensure()) {
								reclist.erase(reclist.begin()+n);
								return;
							}
						}
						break;
					}
				}
				if (w_button==72||w_button==80||w_button==13){
					system("cls");
					print_edit(n, mark);
				}

			} while (w_button=getch());
		}
		void print_check(int mark){
			print_title(">��ѯ�����¼");
			
			cout<<endl;
			string order_arr1[]={"   |���м�¼|   ", "  |�Զ���ɸѡ|  ", "     |�˳�|     "};
			string order_arr2[]={" |> ���м�¼ <| ", "|> �Զ���ɸѡ <|", "   |> �˳� <|   "};
			for (int i = 0; i < 3; i++)
				if (i == mark){
					cout<<setw(30)<<" "
						<<order_arr2[i]<<endl<<endl;
				}
				else cout<<setw(30)<<" "
						 <<order_arr1[i]<<endl<<endl;


		}
		void search_rec(const string title, string key, Time b, Time e){
			int num=1;
			print_title(title);
			while(num!=0){
				int size = reclist.size();
				int wid=0;
				while(size!=0){
					size/=10;
					wid++;
				}
				cout<<endl
					<<" "<<setw(wid)<<"No"
					<<left
					<<" ��¼״̬ "
					<<"    ��ʼʱ��    ~    ����ʱ��    "<<" "
					<<setw(10)<<"����"<<setw(10)<<"�ص�"<<setw(20)<<"��ע"
		 			<<right<<endl;

				bool *mark = new bool[reclist.size()];
				
				for (vector<Rec>::iterator i = reclist.begin(); i!=reclist.end(); i++){
					int n =i-reclist.begin();
					if (i->match_key(key)&&i->match_time(b, e)){
						cout<<" "<<setfill('0')<<setw(wid)<<n+1
							<<setfill(' ')
							<<" "<<*i<<endl;
							mark[n] = true;
					}
					else mark[n]  = false;
				}

				cout<<endl<<setw(23)<<" "<<"��������Ӧ��ţ��༭��Ӧ��¼(����0�˳�)��";
				do{

					if(num>reclist.size()||num<0)
						if (num!=0&&!mark[num])
							cout<<setw(23)<<" "<<"�����ڸñ�ţ�����������(0�˳�)��";
					while(!(cin>>num)){
						cin.clear();
						while(cin.get()!='\n') continue;
						cout<<setw(23)<<" "<<"��⵽�Ƿ��ַ�������������(0�˳�)��";
					}
				}while (num>=reclist.size()||num<0);
				if (num==0) return;
			    else {
					edit_rec(num-1);
					system("cls");
				}
				
				delete []mark;
			}
			
		}
		void condition_rec(){
			system("cls");
			print_title(">��ѯ�����¼>�Զ���");
			
			cin.clear();
			cin.sync();
			string key;
			cout<<setw(23)<<" "<<"������ɸѡ�ؼ���(ֱ��Enter��������):";
			char c;
			while ((c=cin.get())!='\n') key+=c;
			cout<<endl;
			
			Time temp_b, temp_e;
			cout<<setw(23)<<" "<<"�����뿪ʼʱ��(ֱ��Enter��������):";
			
			int m;
			while ((m = temp_b.user_input())==-1) continue;
			cout<<endl;
			if (m == 0) temp_b.zero();
			
			cout<<setw(23)<<" "<<"���������ʱ��:";
			
			while ((m = temp_e.user_input())==-1) continue;
			cout<<endl;
			if (m == 0) temp_e.max();
			
			system("cls");
			search_rec(">��ѯ��¼>�Զ���", key, temp_b, temp_e);
			system("cls");
		}
		void check_rec(){
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
						system("cls");
						if (mark == 0) {
							Time b,e;
							b.zero();
							e.max();
							search_rec(">��ѯ��¼>���м�¼", "", b, e);
						}
						else if (mark == 1) condition_rec();
						else if (mark == 2) return;
						mark = 0;
						break;
					}
				}
				if (w_button==72||w_button==80||w_button==13){
					system("cls");
					print_check(mark);
				}
				
			} while (w_button=getch());
		}
		void sort_reclist(){
			int size = reclist.size();
			for (int i = 1; i<size; i++){
				int p = i;
				Rec t = reclist[i];
				while (p>=1 && t<reclist[p-1]){
					reclist[p] = reclist[p-1];
					p--;
				}
				reclist[p] = t;
			}
		}
};

ostream &operator<<(ostream &output, User user){
	output<<"�˺� "<<user.id<<" | ��� "<<user.order;
	return output;
}
#endif
