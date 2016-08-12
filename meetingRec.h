#ifndef MEETINGREC_H
#define MEETINGREC_H

#include"mtime.h"


class Rec{
	friend void initial();		//�����ʼ������ 
	friend void save_data(); 		//�������� 
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
			if (temp<begin_t) situation = "δ���";
			else if (temp>end_t) situation = "�����";
			else situation = "������";
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
			
			
			s<<setw(25)<<"��"
			 <<"����������������������������"<<endl;

			s<<setw(25)<<" ["+situation+"]��";

			s<<begin_t.watch_time()<<"-"<<end_t.watch_time()<<" | "
			 <<"theme:"<<name
			 <<"\n"<<setw(25)<<"��"<<setw(14)<<"| "<<"  add:"<<address
			 <<"\n"<<setw(25)<<"��"<<setw(14)<<"| "<<"   ע:"<<remind
			 <<endl;//<<setw(25)<<"��"<<endl;
			 
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
			cout<<setw(23)<<" "<<"����"<<content<<"��"<<data<<endl;
			cout<<setw(23)<<" "<<"�����޸�����(ֱ��Enter���������޸�)��";
			char c;
			while((c = cin.get())!='\n'){
				temp+=c;
				if (temp[0]==' ') temp = "";
			}
			cout<<endl;
			if (temp=="") return data;
			else return temp;
		}
		Time single_edit(const string &content, Time& data){
			cout<<setw(23)<<" "<<"����"<<content<<"��"<<data.print_time()<<endl;
			cout<<setw(23)<<" "<<"�밴������ʱ�ֵ�˳�������޸�����"<<endl;
			cout<<setw(23)<<" "<<"(��ֱ��Enter���������޸�)��";
		
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
			n = single_edit("����", name);
			ad = single_edit("�ص�", address);
			r = single_edit("��ע", remind);
			
			bt = single_edit("��ʼʱ��", begin_t);
			et  = single_edit("����ʱ��", end_t);
			
			if (ensure()) {
				name = n;
				address = ad;
				remind  = r;
				
				begin_t= bt;
				end_t = et;
			}
			
		}
		void print_table(int w){
			
			cout<<left;
			cout<<"��"<<situation<<"��"
		  		<<begin_t.day_time()<<"��"<<end_t.day_time()<<"��";
			int n=0, a=0, r=0;
			ostringstream s;
			//nameǰһ��
			for (n=0; n<name.size();){
				if (name[n]>=0){
					s<<name[n];
					n++;
				}
				else{
					s<<name[n]<<name[n+1];
					n+=2;
				}
				if (n>=10) break;
			}
			cout<<setw(10)<<s.str();
			cout<<"��";
			s.str("");
			//addressǰһ��
			for (a=0; a<address.size();){
				if (address[a]>=0){
					s<<address[a];
					a++;
				}
				else{
					s<<address[a]<<address[a+1];
					a+=2;
				}
				if (a>=10) break;
			}
			cout<<setw(10)<<s.str();
			cout<<"��";
			s.str("");
  		  //remindǰһ��
			for (r=0; r<remind.size();){
				if (remind[r]>=0){
					s<<remind[r];
					r++;
				}
				else{
					s<<remind[r]<<remind[r+1];
					r+=2;
				}
				if (r>=10) break;
			}
			cout<<setw(10)<<s.str();
			cout<<endl;
			s.str("");

			//��ʼ��һ��
			cout<<setw(w+1)<<"";
			cout<<"��      ��  "
				  <<begin_t.watch_time()<<"   ��  "<<end_t.watch_time()<<"   ��";
  			 //name��һ��
			for (; n<name.size();n++){
				s<<name[n];
			}
			cout<<setw(10)<<s.str();
			cout<<"��";
			s.str("");
			//address��һ��
			for (;a<address.size();a++){
				s<<address[a];
			}
			cout<<setw(10)<<s.str();
			cout<<"��";
			s.str("");
			//remind��һ��
			for (; r<remind.size();r++){
				s<<remind[r];
			}
			cout<<setw(10)<<s.str();
			cout<<endl;
			cout<<right;
		}
};


istream &operator>>(istream &input, Rec &rec){
	input>>rec.name>>rec.address>>rec.begin_t>>rec.end_t>>rec.remind;
	rec.renew_situaiton();
	return input;
}

bool operator<(Rec &r1, Rec &r2){
	return r1.begin_t<r2.begin_t;
}
#endif
