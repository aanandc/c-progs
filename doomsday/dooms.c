#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

#ifdef DEBUG
#define LOG(x) printf(x)
#else
#define LOG(x)
#endif
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

int anchorDayOfCentury(int year){
  int anchor = 5;//friday
  if(year < 2099 && year >=2000){
    anchor = 2;//tuesday
  }
  else if(year >= 1900 && year <=  1999){
    anchor = 3;//wednesday
  }
  return anchor;
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
int doomsDayOfYear(int year){
  int anchor = anchorDayOfCentury(year);
  //first find the last two digits of the year
  int dig1 = year - 10*(year/10);
  year = year/10;
  int dig2 = year - 10*(year/10);
  int two_digits = 10*dig2 + dig1;
  int reminder = two_digits%12;
  int ans = (((two_digits/12 + reminder + (reminder/4))  % 7) + anchor) % 7;
  return ans;
}

bool isLeapYear(int year){
  if ( year%4 == 0 && year%400 != 0){
    return true;
  }
  else{
    return false;
  }
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
  int doomsday = doomsDayOfYear(year);
  int ref_day = 0;
  int diff = 0;
  int ans = 0;
  if( (4 == month) || ( 6 ==  month ) || ( 8 ==  month) || ( 10 == month ) || (12 == month))  {
  ref_day = month; // doomsdays are 6-6,8-8,10-10,12-12
  }
  else if(month == 3){
    ref_day = 0;
  }
  else if(month == 2){
    if(isLeapYear(year)){
      ref_day = 29;
    }
    else{
      ref_day = 28;
    }
  }
  else if(month == 1){
    if(isLeapYear(year)){
      ref_day = 4;
    }
    else{
      ref_day = 3;
    }
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

char** splitString(char*  input,char delim);


char** splitString(char*  input,char delim){
  char *c = input;
  int length =   strlen(input) + 1;
  char  **output = NULL;
  char **t = NULL;
  output = malloc(length);//we cannot have more no. of substring than the length of the string
  t = output;
  char *val = NULL;
  while(*c != '\0'){
    val = malloc(length);
    *t =  val;
    while(*c !=  delim && *c != '\0'){
      *val = *c;
      val++;
      c++;
     }
    *val = '\0';
    if(*c == '\0'){
      //we have reached the end of the string,stop the traversal
      t++;
      break;
    }
    c++;//move next char from the delimitor
    t++;
  }
  *t = NULL; //just a marker for us
  
  //print the splitted strings for testing
  t = output;
  while(*t != NULL){
    //printf("split string is %s\n",*t);
    t++;
  }
  return output;
}




int main(int argc,char **argv){
  int GAME=1;
  int format = -1;
  int year = 2019;
  int month = 12;
  int date = 1;
  time_t seconds;
  int userguess = -1;
 do_it_again:
  //printf("%s",argv[1]);
  /*for(int i=1980;i<2030;i++){
  int yeartest = doomsDayOfYear(i);
  printf("year %d , doomsday : %s\n",i,translate_day(yeartest));
  }*/
  if(1 == argc){
    //no  arguments
    //generate  random  year,month,date  and  query the user
    format = GAME;
    seconds = time(NULL);
    srand(seconds);
    LOG("no argument case\n");
    year = 2019;
    month = 1 + (rand() % 12);
    date = 1 + (rand() % 27);
    printf("\nrandom date is %d:%d:%d\n",year,month,date); 
    printf("what is the day ? \n0 - sunday  \n1 - monday");
    printf("\n2 - tuesday \n3  - wednesday \n4 - thursday");
    printf("\n5 - friday \n6 - saturday\n");

    while(1){//loop till the user enters valid input ;-)
    scanf("%d",&userguess);
    if(userguess >= 0 &&  userguess <=6){
      break; 
    }
    else{
      printf("\ninvalid input - please enter a value between 0(sunday) and 6(saturday)");
    }
    }
    
  }
  else if(2 == argc){
    //calculate the day for the date  provided by the user
    //date has to be provided in the format yyyy:mm:dd
    //char** splitted = split(argv
    char** temp = argv;
    *temp++;
    char delim = ':';
    char** ans = splitString(*temp,delim);
    //assume that the user has  given  rh right input in the format yyyy:mm:dd
    year  = atoi(*ans);
    ans++;
    month = atoi(*ans);
    ans++;
    date = atoi(*ans);
  }

  int day = calculate_day(year,month,date);
  if(userguess == -1){
    //2 argument case dont do anything
  }
  else if(userguess == day){
    printf("\ncorrect\n");
  }
  else {
    printf("\nwrong\n");
  }

  printf("%d:%d:%d is a  %s\n " , date , month, year, translate_day(day));
  
  if(format == GAME){
    char again='n';
    printf("Do you want to play again (y/n) ? ");
    scanf(" %c",&again);//sometimes C is pain. Without the space in front of %c , scanf for characters will not work due to leading whitespace
    if (again == 'y' || again =='Y'){
      goto do_it_again;
    }
    else{
      //do nothing 
    }
  }


  return 0;

}
