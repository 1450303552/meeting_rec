#ifndef MTIME_H
#define MTIME_H

#include<ctime>
class Time{
	friend class Record; 
	friend ostream &operator<<(ostream &output, Time t);
	friend istream &operator>>(istream &input, Time &t);
	friend bool operator==(Time, Time);
	friend bool operator>(Time, Time);
	friend bool operator<(Time, Time);
	private:
		int day;		//�� 
		int month;		//�� 
		int year;		//�� 
		int hour;		//ʱ 
		int minute;		//�� 
	//	int second;		//�� 
	public:
		Time();
		string watch_time();
		bool is_today();
};

//Time��غ��� 
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
string Time::watch_time(){
	ostringstream s;
	s<<right<<setfill('0')<<setw(2)<<hour<<':'<<setw(2)<<minute;
	return s.str();
}
bool Time::is_today(){
	Time now;
	return (now.year==year&&now.month==month&&now.day==day);
}
ostream &operator<<(ostream &output, Time t){		//ʱ����� 
	output<<right<<setfill('0')<<setw(4)<<t.year<<'/'<<setw(2)<<t.month<<'/'<<setw(2)<<t.day<<' ';
	output<<right<<setfill('0')<<setw(2)<<t.hour<<':'<<setw(2)<<t.minute;//<<':'<<setw(2)<<t.second;
	output<<setfill(' ');
	return output;
}
istream &operator>>(istream &input, Time &t){		//ʱ������ 
	char k;
	input>>t.year>>k>>t.month>>k>>t.day>>k>>t.hour>>k>>t.minute;//>>k>>t.second;
	return input;
}
bool operator==(Time t1, Time t2){
	if (/*t1.second == t2.second&& */t1.minute == t2.minute&&t1.hour==t2.hour&&t1.day == t2.day&&t1.month==t2.month&&t1.year == t2.year) return true;
	return false;
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