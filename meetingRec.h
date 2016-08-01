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
		Rec(string n, string ad, Time bt, Time et, string r){
			name = n;
			address = ad;
			begin_t = bt;
			end_t = et;
			remind = r;
			
			Time temp;
			if (temp<bt) situation = "未完成";
			else if (temp>et) situation = "已完成";
			else situation = "进行中";
		}
		Rec(){
		}
		bool is_today(){
			return begin_t.is_today();
		}
		string short_of(){
			ostringstream s;
			s<<begin_t.watch_time()<<"-"<<end_t.watch_time()<<" "
			 <<name<<"(add:"<<address<<") "
			 <<"注:"<<remind;
			 
			return s.str();
		}
};

ostream &operator<<(ostream &output, Rec rec){
	output<<rec.name<<" "<<rec.address<<" "<<rec.begin_t<<" "<<rec.end_t<<" "<<rec.remind;
	return output;
}

istream &operator>>(istream &input, Rec &rec){
	input>>rec.name>>rec.address>>rec.begin_t>>rec.end_t>>rec.remind;
	Time temp;
	if (temp<rec.begin_t) rec.situation = "未完成";
		else if (temp>rec.end_t) rec.situation = "已完成";
		else rec.situation = "进行中";
	return input;
}
#endif
