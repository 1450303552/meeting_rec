#ifndef MEETINGREC_H
#define MEETINGREC_H

#include"mtime.h"


class Rec{
	friend void initial();		//载入初始化数据 
	friend void save_data(); 		//保存数据 
	friend ostream &operator<<(ostream &output, Rec rec);
	friend istream &operator>>(istream &input, Rec &rec);
	private:
		string name;
		string address;
		Time begin_t;
		Time end_t;
		string remind;
	public:
		string situation; 
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
			
			
			s<<setw(23)<<" "
			 <<setfill('_')<<setw(30)<<"_"
			 <<setfill(' ')<<endl;

			s<<setw(25)<<"["+situation+"] ";

			s<<begin_t.watch_time()<<"-"<<end_t.watch_time()<<" | "
			 <<name<<"(add:"<<address<<") "
			 <<"\n"<<setw(39)<<" | "<<"注:"<<remind;
			 
			return s.str();
		}
		string print_line(){
			ostringstream s;
			s<<name<<" "<<address<<" "
			 <<begin_t.print_time()<<" "
			 <<end_t.print_time()<<" "
			 <<remind<<" "
			 <<situation;

			return s.str();
		}
};

ostream &operator<<(ostream &output, Rec rec){
	output<<rec.name<<" "<<rec.address<<" "<<rec.begin_t<<" "<<rec.end_t<<" "<<rec.remind;
	return output;
}

istream &operator>>(istream &input, Rec &rec){
	input>>rec.name>>rec.address>>rec.begin_t>>rec.end_t>>rec.remind;
	rec.renew_situaiton();
	return input;
}
#endif
