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
			cout<<endl;
			
			int mark = 0;
			for(vector<Rec>::iterator i = reclist.begin(); i!=reclist.end();i++){
				i->renew_situaiton();
				if(i->is_today()){
					mark = 1;
					
					cout<<i->for_short()
						<<endl;
				}
			}
			if (mark==0){
				/*cout<<endl
					<<setw(23)<<" "
					<<setfill('_')<<setw(30)<<"_"
					<<setfill(' ')<<endl;*/
				cout<<endl<<setw(23)<<" "
					<<":今天没有会议，好好休息休息或者下班后去勾搭勾搭妹纸^3^！\n\n\n";
			}
			else {
				/*cout<<endl
					<<setw(23)<<" "
					<<setfill('-')<<setw(30)<<"-"
					<<setfill(' ')<<endl;*/
				cout<<endl<<setw(23)<<" "
					<<":感觉，身体被掏空_(:3J<)_！MDZZ！\n\n\n";
			}
			
			/*cout<<setw(23)<<" "
				<<setfill('-')<<setw(30)<<"-"
				<<setfill(' ')<<endl;*/
		}
		void u_print(int m){
			Time now_time;
			ostringstream s;
			s<<">主页>登录> "<<id<<" 个人主页";
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<now_time.print_time()+" "
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
			cout<<" =--"<<endl;
			
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
		
			cout<<setw(23)<<" "<<"注：上下方向键控制选择，按Enter键确认操作";
		}
		void new_rec(){
			Time now_time;
			ostringstream s;
			s<<">主页>登录>"<<id<<"个人主页>新会议记录";
    		cout<<left<<setw(40)<<s.str()
	            <<right<<setw(40)<<now_time.print_time()+" "
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
			ostringstream s;
			s<<">主页>登录>"<<id<<"个人主页>查看记录";
    		cout<<left<<setw(40)<<s.str()
    			<<right<<setw(40)<<now_time.print_time()+" "
				<<endl
				<<setfill('-')<<setw(80)<<"-"
				<<setfill(' ')
				<<endl;
				
			for(vector<Rec>::iterator i = reclist.begin(); i!=reclist.end(); i++){
				cout<<i->print_line()<<endl;
			}
			char t_c=getch();
		}
};

ostream &operator<<(ostream &output, User user){
	output<<"账号 "<<user.id<<" | 编号 "<<user.order;
	return output;
}
#endif
