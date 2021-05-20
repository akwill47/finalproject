#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 50
#define MAXSTD 2000
#define MAXC 100
#define MAXENROLL 5000

typedef struct Students{
int id;
char fname[MAXLEN];
char lname[MAXLEN];
int dob;
int mob;
int yob;
}Students;

typedef struct Courses{
char cid[MAXLEN];
char cname[MAXLEN];
float tcredit;
}Courses;

typedef struct Enrollments{
int id;
char cid[MAXLEN];
char semester[MAXLEN];
float score;
}Enrollments;

void loadStudents(Students st[], int *numStudents);
int loadEnrollment(Enrollments ArrayOfEnrollments[]);
int loadCourses(Courses ArrayOfCourses[]);
void printInfo(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls,int id);
void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);
char grade(float score);
void addCourse(Courses course[],int *amountCourses);
void searchStudents(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);
void searchCourses(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);
void count(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);
void sort(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);

int main(void) {
  Students ArrayOfStudents[MAXSTD];
  Courses  ArrayOfCourses[MAXC];
  Enrollments ArrayOfEnrollments[MAXENROLL];
  int numStudents;
  int numEnrollments;
  int numCourses;
  loadStudents(ArrayOfStudents,&numStudents);
  numEnrollments=loadEnrollment(ArrayOfEnrollments);
  numCourses=loadCourses(ArrayOfCourses);

  menu(ArrayOfStudents, numStudents, ArrayOfCourses, &numCourses, ArrayOfEnrollments, numEnrollments);
  
  
  return 0;
}

void loadStudents(Students st[], int *numStudents){
  FILE *fp = fopen("students.txt","r");
  int id=0;int dob=0;int mob=0;int yob=0;int numStudent=0;
  char fname[MAXLEN];
  char lname[MAXLEN];
  while(fscanf(fp,"%d %s %s %d %d %d",&id, fname, lname,&dob,&mob,&yob )!=EOF){
  strcpy(st[numStudent].fname,fname);
  strcpy(st[numStudent].lname,lname);
  st[numStudent].id=id;
  st[numStudent].dob=dob;
  st[numStudent].mob=mob;
  st[numStudent].yob=yob;
  numStudent++;
  }
  *numStudents=numStudent;
  fclose(fp);
}
int loadEnrollment(Enrollments en[]){
  FILE *fp = fopen("enrollment.txt","r");
  int id=0;float score;int numEnroll=0;
  char cid[MAXLEN];
  char semester[MAXLEN];
  while(fscanf(fp,"%d %s %s %f",&id, cid, semester,&score)!=EOF){
    strcpy(en[numEnroll].cid,cid);
    strcpy(en[numEnroll].semester,semester);
    en[numEnroll].id=id;
    en[numEnroll].score=score;
    numEnroll++;
  }
  fclose(fp);
  return numEnroll;
}
int loadCourses(Courses course[]){
  FILE *fp = fopen("courses.txt","r");
  int id=0;float score;int numCourses=0;
  char cid[MAXLEN];
  char cname[MAXLEN];
  float tcredit;
  while(fscanf(fp,"%s %s %f",cid,cname,&tcredit)!=EOF){
    strcpy(course[numCourses].cid,cid);
    strcpy(course[numCourses].cname,cname);
    course[numCourses].tcredit=tcredit;
    numCourses++;
  }
  fclose(fp);
  return numCourses;
}

void printInfo(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls,int id){
  
  for(int i=0;i<amountStudents;i++){
    if(id==ArrayOfStudents[i].id){
      printf("%d %s %s %d/%d/%d\n",ArrayOfStudents[i].id,ArrayOfStudents[i].fname,ArrayOfStudents[i].lname,ArrayOfStudents[i].mob,ArrayOfStudents[i].dob,ArrayOfStudents[i].yob);
      
      for(int j=0;j<amountEnrolls;j++){
        if(id==ArrayOfEnrollments[j].id)
          
          for(int k=0;k<*amountCourses;k++){
            if(strcmp(ArrayOfEnrollments[j].cid,ArrayOfCourses[k].cid)==0)
            printf("%s %s %s %0.0f %c\n",ArrayOfEnrollments[j].cid,ArrayOfCourses[k].cname,ArrayOfEnrollments[j].semester,ArrayOfEnrollments[j].score,grade(ArrayOfEnrollments[j].score));
          }
          
      }
    }
  }
}

void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  char option[MAXLEN];
  
  while(2){
    printf("==================\n");
    scanf("%s",option);
    if(strcmp(option,"exit")==0){
      printf("------------------\n");
      printf("Bye!"); 
      break;
    }
    if(strcmp(option,"search_students")==0)
      searchStudents(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
    if(strcmp(option,"search_course")==0)
      searchCourses(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
    if(strcmp(option,"add_course")==0){
      addCourse(ArrayOfCourses,amountCourses);
      *amountCourses=loadCourses(ArrayOfCourses);
  }
    if(strcmp(option,"count")==0)
      count(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
    if(strcmp(option,"sort")==0)
      sort(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls);
  }

} 

char grade(float score){
  if(score>=90)
    return 'A';
  if(score>=80 & score<=89.99)
    return 'B';
  if(score>=70 & score<=79.99)
    return 'C';
  if(score>=60 & score<=69.99)
    return 'D';
  if(score<=59.99)
    return 'F';
  else
  return 'e';
}

void addCourse(Courses ArrayOfCourses[],int *amountCourses){
  FILE *fp = fopen("courses.txt","a");
  char cid[MAXLEN];
  char cname[MAXLEN];
  float credit;
  scanf("%s %s %f",cid,cname,&credit);
  printf("------------------\n");
  int count=0;
  for(int i=0;i<*amountCourses;i++){
    if(strcmp(cid,ArrayOfCourses[i].cid)==0){
      printf("\"violation of course id uniqueness. Cannot add the record.\"\n");
      printf("------------------\n");
      count++;
      return;
    }
  }
  if(count==0){
  fprintf(fp,"\n%s %s %0.0f",cid,cname,credit);
  printf("record added\n");
  printf("------------------\n");
 
  }
  
  fclose(fp);

}

void searchStudents(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  char option[MAXLEN];
  int id;
  scanf("%s",option);

  if(strcmp(option,"lname")==0){
    scanf("%s",option);
    int count=0;
    printf("------------------\n");
    for (int i=0;i<amountStudents;i++){
      if(strcmp(option,ArrayOfStudents[i].lname)==0){
        printInfo(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls,ArrayOfStudents[i].id);
        printf("------------------\n");
        count++;
      }
    }
    if(count==0){
      printf("not found\n");
      printf("------------------\n");
    }
  }
  
  if(strcmp(option,"fname")==0){
    scanf("%s",option);
    int count=0;
    printf("------------------\n");
    for (int i=0;i<amountStudents;i++){
      if(strcmp(option,ArrayOfStudents[i].fname)==0){
        printInfo(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls,ArrayOfStudents[i].id);
        printf("------------------\n");
        count++;
      }
    }
    if(count==0){ 
      printf("not found\n");
      printf("------------------\n");
    }
  }
  
  if(strcmp(option,"id")==0){
    scanf("%d",&id);
    int count=0;
    printf("------------------\n");
    for (int i=0;i<amountStudents;i++){
      if(id==ArrayOfStudents[i].id){
        printInfo(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls,ArrayOfStudents[i].id);
        printf("------------------\n");
        count++;
      }
    }
    if(count==0){
      printf("not found\n");
      printf("------------------\n");
    }
  }
  
  if(strcmp(option,"byear")==0){
    scanf("%d",&id);
    int count=0;
    printf("------------------\n");
    for (int i=0;i<amountStudents;i++){
      if(id==ArrayOfStudents[i].yob){
        printInfo(ArrayOfStudents, amountStudents, ArrayOfCourses, amountCourses, ArrayOfEnrollments, amountEnrolls,ArrayOfStudents[i].id);
        printf("------------------\n");
        count++;
      }
    }
    if(count==0){
      printf("not found\n");
      printf("------------------\n");
    }
  }
}

void searchCourses(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  char option[MAXLEN];
  
  scanf("%s",option);
  if(strcmp(option,"cid")==0){
      int count=0;
      scanf("%s",option);
      printf("------------------\n");
      for(int i=0;i<*amountCourses;i++){
        if(strcmp(option,ArrayOfCourses[i].cid)==0){
          printf("%s %0.0f\n",ArrayOfCourses[i].cname,ArrayOfCourses[i].tcredit);
          count++;
        }
      }  
          for(int j=0;j<amountEnrolls;j++){
            if(strcmp(option,ArrayOfEnrollments[j].cid)==0)
              
              for(int k=0;k<amountStudents;k++){
                if(ArrayOfEnrollments[j].id==ArrayOfStudents[k].id)
                  printf("%s %s %s %0.0f %c\n",ArrayOfStudents[k].fname,ArrayOfStudents[k].lname,ArrayOfEnrollments[j].semester,ArrayOfEnrollments[j].score,grade(ArrayOfEnrollments[j].score));
              }     
          } 
    if(count==0)
      printf("not found\n");
    printf("------------------\n");    
  }
  
  if(strcmp(option,"cid_semester")==0){
    char option2[MAXLEN];
    int count=0;
    scanf("%s %s",option, option2);
    printf("------------------\n");
    for(int i=0;i<*amountCourses;i++){
      if(strcmp(option,ArrayOfCourses[i].cid)==0){
        printf("%s %0.0f\n",ArrayOfCourses[i].cname,ArrayOfCourses[i].tcredit);
        count++;
      }
    }      
        for(int j=0;j<amountEnrolls;j++){
          if(strcmp(option2,ArrayOfEnrollments[j].semester)==0 && strcmp(option,ArrayOfEnrollments[j].cid)==0)
              
            for(int k=0;k<amountStudents;k++){
              if(ArrayOfEnrollments[j].id==ArrayOfStudents[k].id)
                printf("%s %s %s %0.0f %c\n",ArrayOfStudents[k].fname,ArrayOfStudents[k].lname,ArrayOfEnrollments[j].semester,ArrayOfEnrollments[j].score,grade(ArrayOfEnrollments[j].score));              
              }
          }
    if(count==0)
      printf("not found\n");
    printf("------------------\n");
  }
}

void count(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  char option[MAXLEN];
  int count;
  scanf("%s",option);
  if(strcmp(option,"students")==0){
    printf("------------------\n");
    printf("total students %d\n",amountStudents);
    printf("------------------\n");
  } 

  if(strcmp(option,"students_course")==0){
    printf("------------------\n");
    for(int i=0;i<*amountCourses;i++){
      count=0;
      for(int j=0;j<amountEnrolls;j++){
        if(strcmp(ArrayOfCourses[i].cid,ArrayOfEnrollments[j].cid)==0)
          count++;
      }
      printf("%s %d\n",ArrayOfCourses[i].cid,count);
    }
    printf("------------------\n");
  } 

  if(strcmp(option,"students_semester")==0){
    char semesters[MAXC][MAXLEN];
    int semestercount[MAXC];
    int maxsemesters=1;
    semestercount[0]=0;
    strcpy(semesters[0],ArrayOfEnrollments[0].semester);
    printf("------------------\n");
  
    for(int i=0;i<amountEnrolls;i++){
      int j;
      for(j=0;j<maxsemesters;j++){
        if(strcmp(ArrayOfEnrollments[i].semester,semesters[j])==0){
          semestercount[j]++;
          break;
        }
      }
     if(maxsemesters==j && i!=0){
        strcpy(semesters[maxsemesters],ArrayOfEnrollments[i].semester);
        semestercount[maxsemesters]=1; 
        maxsemesters++;
      }
    }    
    for(int i=0;i<maxsemesters;i++){
      printf("%s %d\n",semesters[i],semestercount[i]);  
    }
    printf("------------------\n");
  } 
}
void sort(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int *amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  int min_idx,i,j,k,temp;
  int order[amountStudents];
  printf("------------------\n");
  for(int k=0;k<amountStudents;k++){
    order[k]=ArrayOfStudents[k].id;
  }
  for(i=0;i<amountStudents-1;i++){
    
    min_idx = i; 
      for (j = i+1; j < amountStudents; j++) 
        if (order[j] < order[min_idx]) 
            min_idx = j; 

    temp=order[min_idx];
    order[min_idx]=order[i];
    order[i]=temp;
  }
  for(int l=0;l<amountStudents;l++){
    for(int p=0;p<amountStudents;p++){
      if(order[l]==ArrayOfStudents[p].id){
        printf("%d %s %s %d/%d/%d\n",ArrayOfStudents[p].id,ArrayOfStudents[p].fname,ArrayOfStudents[p].lname,ArrayOfStudents[p].mob,ArrayOfStudents[p].dob,ArrayOfStudents[p].yob);
      }
    }
  }
  printf("------------------\n");
}