

#include <stdio.h>


#define DEBUG true


  char   days_arr[7][10]={
	       "sunday",
	       "monday",
	       "tuesday",
	       "wednesday",
	       "thursday",
	       "friday",
	       "saturday"
  };

// 0 is sunday
char* translate_day(int day){
  return days_arr[day];
}

/*
return integers representing 
0 - sunday 
1 - monday
2 - tuesday
3 - wednesday
4 - thursday
5 - friday
6  - saturday
 */
int  calculate_day(int year,int month,int day){
  //lets do for 2019 first
  //doomsday for 2019 is 4 - thursday
  int doomsday = 4;
  int ref_day = 0;
  int diff = 0;
  int ans = 0;
  if( ( 6 ==  month ) || ( 8 ==  month) || ( 10 == month ) || (12 == month))  {
  ref_day = month; // doomsdays are 6-6,8-8,10-10,12-12
  }
  else if(month == 5){
    ref_day =  9;
  }
  else if(9 == month) {
    ref_day = 5;
  }
  else if( 7 == month){
    ref_day = 11;
  }
  else if( 11 == month){
    ref_day = 7;
  }

if(day > ref_day){
    diff = (day - ref_day)%7;
    ans = (doomsday + diff)%7;
  }
  else{
    diff =  (ref_day - day)%7;
    ans = (doomsday + (7 - diff))%7;
  }
  return ans;
  
}

int main(){
  int year = 2019;
  int month = 5;
  for(int i = 1;i<10;i++){
  int day = calculate_day(year,month,i);
  printf("%d:%d:%d %s\n " , i , month, year, translate_day(day));
  }
  return 0;

}
