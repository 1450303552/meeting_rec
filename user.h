#ifndef USER_H
#define USER_H

#include<vector> 
#include"mtime.h"
#include"meetingRec.h"

class User;
vector<User> userlist;
int u_num;

class User{
	friend void initial();		//载入初始化数据 
    friend void save_data(); 		//保存数据 
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
		void show_today(){
			cout<<setfill('+')<<setw(80)<<"+"
				<<setfill(' ')<<endl;

			cout<<"+"<<setw(79)<<"+"<<endl;
			
			for(vector<Rec>::iterator i = reclist.begin(); i!=reclist.end();i++){
				if(i->is_today()){
					cout<<"+    "
						<<left<<setw(70)<<i->short_of()<<right
						<<"    +"<<endl;
					
					cout<<"+"<<setw(79)<<"+"<<endl;
				}
			}
			
			cout<<setfill('+')<<setw(80)<<"+"
				<<setfill(' ')<<endl;
		}
		void u_print(int m){
			Time now_time;
			ostringstream s, t;
			t<<now_time;
			s<<">主页>登录> "<<id<<" 个人主页";
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<t.str()+" " 
				<<endl
				<<setfill('-')<<setw(80)<<"-"
				<<setfill(' ')
				<<endl;
	
			cout<<endl<<setw(30)<<" "<<"--=个人主页 ";
			switch(m){
				case 0:{ cout<<"＋ｏ＋"; break;}
				case 1:{ cout<<"＞ｏ＜"; break;}
				case 2:{ cout<<"o＿O"; break;}
			}
			cout<<" =--"<<endl<<endl;
			
			show_today();
			
			cout<<endl;
			/*cout<<setw(23)<<" "
				<<setfill('+')<<setw(30)<<"+"
				<<setfill(' ')<<endl<<endl;*/ 
		
			string order_arr1[]={"  |创建会议记录|  ", "    |查询记录|    ", "      |退出|      "};
			string order_arr2[]={"|> 创建会议记录 <|", "  |> 查询记录 <|  ", "    |> 退出 <|    "};
	
			for (int i = 0; i < 3; i++)
				if (i == m){
					cout<<setw(29)<<" "
						<<order_arr2[i]<<endl<<endl;
				}
				else cout<<setw(29)<<" "
						 <<order_arr1[i]<<endl<<endl;

			cout<<endl
				<<setw(23)<<" "
				<<setfill('_')<<setw(30)<<"_"
				<<setfill(' ')<<endl;		
		
			cout<<setw(23)<<" "<<"注：按方向键移动选择，按Enter键确认操作"; 
		}
		void new_rec(){
			Time now_time;
			ostringstream s, t;
			t<<now_time;
			s<<">主页>登录>"<<id<<"个人主页>新会议记录";
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<t.str()+" " 
				<<endl
				<<setfill('-')<<setw(80)<<"-"
				<<setfill(' ')
				<<endl;
			
			string n, ad, r;
			Time bt, et; 
			
			cout<<endl<<setw(29)<<" "<<"会议名称：";
			cin>>n;
			
			cout<<endl<<setw(29)<<" "<<"会议地点：";
			cin>>ad;
			
			cout<<endl<<setw(29)<<" "<<"开始时间：";
			cin>>bt;
			
			cout<<endl<<setw(29)<<" "<<"结束时间：";
			cin>>et;
			
			cout<<endl<<setw(29)<<" "<<"备注：";
			cin>>r;
			
			reclist.push_back(Rec(n, ad, bt, et, r));
		}
		void check_rec(){
			Time now_time;
			ostringstream s, t;
			t<<now_time;
			s<<">主页>登录>"<<id<<"个人主页>查看记录";
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<t.str()+" " 
				<<endl
				<<setfill('-')<<setw(80)<<"-"
				<<setfill(' ')
				<<endl;
				
			for(vector<Rec>::iterator i = reclist.begin(); i!=reclist.end(); i++){
				cout<<*i<<" "<<i->situation<<endl; 
			}
			char t_c=getch();
		}
};

ostream &operator<<(ostream &output, User user){
	output<<"账号 "<<user.id<<" | 编号 "<<user.order;
	return output;
}
#endif
