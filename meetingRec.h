#ifndef MEETINGREC_H
#define MEETINGREC_H

#include"mtime.h"


class Rec{
	friend void initial();		//载入初始化数据 
	friend void save_data(); 		//保存数据 
	friend ostream &operator<<(ostream &output, Rec rec);
	friend istream &operator>>(istream &input, Rec &rec);
	friend bool operator<(Rec &, Rec &);
	private:
		string name;
		string address;
		Time begin_t;
		Time end_t;
		string remind;
	public:
		string situation; 
		bool match_key(const string& key){
			if (name.find(key)>=0||address.find(key)>=0
				||remind.find(key)>=0||situation.find(key)>=0)
				return true;
			return false;
		}
		bool match_time(Time &b, Time &e){
			if (begin_t>=b&&end_t<=e) return true;
			return false;
		}
		void renew_situaiton(){
			Time temp;
			if (temp<begin_t) situation = "未完成";
			else if (temp>end_t) situation = "已完成";
			else situation = "进行中";
		}
		Rec(string n, string ad, Time bt, Time et, string r){
			name = n;
			address = ad;
			begin_t = bt;
			end_t = et;
			remind = r;
			
            Time temp;
            renew_situaiton();
		}
		Rec(){
		}
		bool is_today(){
			if (begin_t.is_today()) return true;
			else if (end_t.is_today()) return true;
			else {
				Time now;
				if (now>begin_t&&end_t>now) return true;
				return false;
			}
		}
		string for_short(){
			ostringstream s;
			
			
			s<<setw(25)<<"│"
			 <<"──────────────"<<endl;

			s<<setw(25)<<" ["+situation+"]┼";

			s<<begin_t.watch_time()<<"-"<<end_t.watch_time()<<" | "
			 <<"theme:"<<name
			 <<"\n"<<setw(25)<<"│"<<setw(14)<<"| "<<"  add:"<<address
			 <<"\n"<<setw(25)<<"│"<<setw(14)<<"| "<<"   注:"<<remind
			 <<endl;//<<setw(25)<<"│"<<endl;
			 
			return s.str();
		}
		string print_line(){
			ostringstream s;
			s<<name<<" "<<address<<" "
			 <<begin_t<<" "
			 <<end_t<<" "
			 <<remind;

			return s.str();
		}
		string single_edit(const string &content, string& data){
			string temp;
			cout<<setw(23)<<" "<<"会议"<<content<<"："<<data<<endl;
			cout<<setw(23)<<" "<<"输入修改内容(直接Enter跳过该项修改)：";
			char c;
			while((c = cin.get())!='\n'){
				temp+=c;
				if (temp[0]==' ') temp = "";
			}
			if (temp=="") return data;
			else return temp;
		}
		Time single_edit(const string &content, Time& data){
			cout<<setw(23)<<" "<<"会议"<<content<<"："<<data.print_time()<<endl;
			cout<<setw(23)<<" "<<"请按年月日时分的顺序输入修改内容"<<endl;
			cout<<setw(23)<<" "<<"(或直接Enter跳过该项修改)：";
		
			Time temp;
			int m;
			while ((m = temp.user_input())==-1) continue;
			cout<<endl;
			if (m==0) return data;
			else return temp;
		}
		void edit(){
            string n, ad, r;
			Time bt, et;
			
			cin.clear();
			cin.sync();
			n = single_edit("主题", name);
			ad = single_edit("地点", address);
			r = single_edit("备注", remind);
			
			bt = single_edit("开始时间", begin_t);
			et  = single_edit("结束时间", end_t);
			
			if (ensure()) {
				name = n;
				address = ad;
				remind  = r;
				
				begin_t= bt;
				end_t = et;
			}
			
		}
};

ostream &operator<<(ostream &output, Rec rec){
	output<<left
		  <<" ["<<rec.situation<<"] "
		  <<rec.begin_t.print_time()<<"~"<<rec.end_t.print_time()<<" "
		  <<setw(10)<<rec.name<<setw(10)<<rec.address<<setw(20)<<rec.remind
		  <<right;
	return output;
}

istream &operator>>(istream &input, Rec &rec){
	input>>rec.name>>rec.address>>rec.begin_t>>rec.end_t>>rec.remind;
	rec.renew_situaiton();
	return input;
}

bool operator<(Rec &r1, Rec &r2){
	return r1.begin_t<r2.begin_t;
}
#endif
