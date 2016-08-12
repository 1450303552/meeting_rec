#ifndef MTIME_H
#define MTIME_H

#include<ctime>
class Time{
	friend class Record; 
	friend ostream &operator<<(ostream &output, Time t);
	friend istream &operator>>(istream &input, Time &t);
	friend bool operator==(Time, Time);
	friend bool operator<=(Time, Time);
	friend bool operator>=(Time, Time);
	friend bool operator>(Time, Time);
	friend bool operator<(Time, Time);
	private:
		int day;		//日 
		int month;		//月 
		int year;		//年 
		int hour;		//时 
		int minute;		//分 
	//	int second;		//秒 
	public:
		Time();
		Time(int,int,int,int,int);
		string watch_time();
		string day_time();
		bool is_today();
		string print_time();
		void zero(){
			year = month = day = hour = minute = 0;
		}
		void max(){
			year = 99999;
		}
		int user_input();
		int get_year();
		int get_month();
		int get_day();
		int get_hour();
		int get_minute();
};

//Time相关函数 
Time::Time(){ 
	time_t now = time(NULL);
	tm *breaktime = localtime(&now);
	day = breaktime->tm_mday;
	month = breaktime->tm_mon+1;
	year = breaktime->tm_year+1900;
	hour = breaktime->tm_hour;
	minute = breaktime->tm_min;
//	second = breaktime->tm_sec;
}
Time::Time(int y, int m, int d, int h, int min){
	year = y;
	month = m;
	day = d;
	hour = h;
	minute = min;
}
string Time::watch_time(){
	ostringstream s;
	s<<right<<setfill('0')<<setw(2)<<hour<<':'<<setw(2)<<minute;
	return s.str();
}
string Time::day_time(){
	ostringstream s;
	s<<year<<'/'<<month<<'/'<<day;
	ostringstream ss;
	ss<<left<<setw(10)<<s.str();
	return ss.str();
}
bool Time::is_today(){
	Time now;
	return (now.year==year&&now.month==month&&now.day==day);
}
string Time::print_time(){
	ostringstream s;
	s<<year<<'/'<<month<<'/'<<day<<' ';
	s<<right<<setfill('0')<<setw(2)<<hour<<':'<<setw(2)<<minute;//<<':'<<setw(2)<<t.second;
	s<<setfill(' ');
	return s.str();
}
int Time::user_input(){
	//输入时间及检测输入合法性
			int data[5];
			string str;
			int m = 0;
			char c;
			while((c=cin.get())!='\n'){
				if (c!=' '&&!isdigit(c)){
					cout<<setw(23)<<" "<<"检测到非法字符"<<c<<"，请重新输入\n";
					cout<<setw(23)<<" "<<"输入修改内容(直接Enter跳过该项修改)：";
					return -1;
				}
				if (c==' ') {
					if (str!=""){

						if (m>=4) {
							cout<<setw(23)<<" "<<"检测到多余输入，请重新输入\n";
							cout<<setw(23)<<" "<<"输入修改内容(直接Enter跳过该项修改)：";
							return -1;
						}
						istringstream s(str);
						s>>data[m];
						m++;
						str="";
					}
				}
				else str+=c;

			}
			if (m==0) {
				return 0;
    		}
   			if (m<4) {
    			cout<<setw(23)<<" "<<"保持年月日于同一行，请重新输入\n";
    			cout<<setw(23)<<" "<<"输入修改内容(直接Enter跳过该项修改)：";
				return -1;
    		}
			istringstream s(str);
			s>>data[m];
			year = data[0];
			month = data[1];
			day = data[2];
			hour = data[3];
		 	minute = data[4];
		 	return 1;
}
int Time::get_year(){
	return year;
}
int Time::get_month(){
	return month;
}
int Time::get_day(){
	return day;
}
int Time::get_hour(){
	return hour;
}
int Time::get_minute(){
	return minute;
}
ostream &operator<<(ostream &output, Time t){		//时间输出
	output<<t.year<<' '<<t.month<<' '<<t.day<<' '<<t.hour<<' '<<t.minute;
	return output;
}
istream &operator>>(istream &input, Time &t){		//时间输入
	input>>t.year>>t.month>>t.day>>t.hour>>t.minute;//>>k>>t.second;
	return input;
}
bool operator==(Time t1, Time t2){
	if (/*t1.second == t2.second&& */t1.minute == t2.minute&&t1.hour==t2.hour&&t1.day == t2.day&&t1.month==t2.month&&t1.year == t2.year) return true;
	return false;
}
bool operator>=(Time t1, Time t2){
	return t1>t2||t1==t2;
}
bool operator<=(Time t1, Time t2){
	return t1<t2||t1==t2;
}
bool operator>(Time t1, Time t2){
	if (t1.year > t2.year) return true;
	if (t1.year < t2.year) return false;
	if (t1.month>t2.month) return true;
	if (t1.month<t2.month) return false;
	if (t1.day>t2.day) return true;
	if (t1.day<t2.day) return false;
	if (t1.hour>t2.hour) return true;
	if (t1.hour<t2.hour) return false;
	if (t1.minute>t2.minute) return true;
	if (t1.minute<t2.minute) return false;
	return false;
}
bool operator<(Time t1, Time t2){
	if (t1>t2||t1==t2) return false;
	else return true;
}
#endif
