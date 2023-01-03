#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

typedef char bool_t;
typedef struct cliArgs{

    char basepath[50];
    bool_t k_flag;
    bool_t t_flag;
    int t_flag_value;
    bool_t r_flag;
    char arg[50];
} cliArgs;
char *fmtname(char *path) {
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
  return buf;
}

void parseArgs(int argc, char* argv[], cliArgs* command){

    for (int i=1;i<argc;i++){
        // printf(1,"%s\n","in outer for");
        for(char* ptr=argv[i];*ptr !='\0';ptr++){
            // printf(1,"%s\n","in inner for");
            // int length=strlen(argv[i]);
            // printf(1,"%s ",argv[i]);
            // printf(1,"%d\n",length);
            int isKSet=strcmp(argv[i],"-k");
            int isTSet=strcmp(argv[i],"-t");
            int isRSet=strcmp(argv[i],"-r");
            if (isKSet==0){
                command->k_flag='1';
                }
            if (isTSet==0){
                command->t_flag='1';
                // char tflagValue=*argv[i+1];
                //int threshValue=atoi(argv[i+1]);
                //if(threshValue==0){
                int threshValue=atoi(argv[i+1]);
                if(threshValue==0){
                    printf(1,"check usage.\n");
                    exit();
                }
                command->t_flag_value=atoi(argv[i+1]);
                // printf(1,"LINE 40%s\n",argv[i+1]);
                }
            if (isRSet==0){
                // printf(1,"in if rflag\n");
                command->r_flag='1';
                }

        }
        
            
    }
    /*
    printf(1,"kflag: %c\n",command->k_flag);
    printf(1,"tflag: %c\n",command->t_flag);
    printf(1,"tflagvalue: %d\n",command->t_flag_value);
    printf(1,"rflag: %c\n",command->r_flag);
    printf(1,"exit line 57\n");
    */
}
void t1(char*path, int argc, char*argv[], int value) {
  char buf[512], *p;
  int fd;
  int c11;
  struct dirent de;
  struct stat st;
  if ((fd = open(path, 0)) < 0) {
    printf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "du: cannot stat %s\n", buf);
        continue;
      }
      c11 = value;
      if(st.size > c11){
          printf(1, "%d %s \n", st.size, fmtname(buf) );
      }
      
    }
    break;
  }
  close(fd);
}
void both(char*path, int argc, char*argv[],int value) {
  char buf[512], *p;
  int fd;
  int c11;
  struct dirent de;
  struct stat st;
  if ((fd = open(path, 0)) < 0) {
    printf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "du: cannot stat %s\n", buf);
        continue;
      }
      c11 = value;
      if(st.size > c11){
          printf(1, "%d %s \n", st.size/512, fmtname(buf) );
      }
      
    }
    break;
  }
  close(fd);
}
void test(char *path) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    printf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "du: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%d %s \n", st.size/512, fmtname(buf) );
    }
    break;
  }
  close(fd);
}
void file(char*path, int argc, char*argv[]) {
  char buf[512], *p;
  int fd;
  int qw;
  struct dirent de;
  struct stat st;
  qw = 0;

  if ((fd = open(path, 0)) < 0) {
    printf(2, "check usage.\n");
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }
  switch (st.type) {
  case T_FILE:
    printf(1, "%d %s\n", st.size,fmtname(path));
    printf(1, "%d %s\n", st.size,fmtname(path));
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      qw += st.size;
      printf(1, "%d %s \n",st.size, fmtname(buf));
      printf(1, "%d %s \n",qw, fmtname(buf));
      //printf(1,argv[1]);
      //printf(1, "%s\n",fmtname(buf));
    }
    break;
  }
  close(fd);
}
void filetest(char*path, int argc, char*argv[],int value) {
  char buf[512], *p;
  int fd;
  int qw;
  struct dirent de;
  struct stat st;
  int ee;
  qw = 0;
  ee = value;

  if ((fd = open(path, 0)) < 0) {
    printf(2, "check usage.\n");
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }
  switch (st.type) {
  case T_FILE:
    printf(1, "%d %s\n", st.size,fmtname(path));
    printf(1, "%d %s\n", st.size,fmtname(path));
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      qw += st.size;
      if(st.size > ee){
          printf(1, "%d %s \n",st.size, fmtname(buf));
          printf(1, "%d %s \n",qw, fmtname(buf));
      }
      
      //printf(1,argv[1]);
      //printf(1, "%s\n",fmtname(buf));
    }
    break;
  }
  close(fd);
}
void final(char*path, int argc, char*argv[], int value) {
  char buf[512], *p;
  int fd;
  int qw;
  int c11;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    printf(2, "check usage.\n");
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }
printf(1,"%s: %d\n","st.type", st.type);
  switch (st.type) {
  case T_FILE:
    printf(1, "%d %s\n", st.size,fmtname(path));
    printf(1, "%d %s\n", st.size,fmtname(path));
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      c11 = value;
      if(st.size > c11){
          printf(1, "%d %s \n", st.size/512, fmtname(buf) );
      }
      qw = 0;
      qw += st.size;
      printf(1, "%d %s \n",st.size, fmtname(buf));
      printf(1, "%d %s \n",qw, fmtname(buf));
      //printf(1,argv[1]);
      //printf(1, "%s\n",fmtname(buf));
    }
    break;
  }
  close(fd);
}
void du(char *path) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  int sum=0;
  if ((fd = open(path, 0)) < 0) {
    printf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch (st.type) {
  case T_FILE:
    printf(1, "%s %d\n", fmtname(buf), st.size);
    sum+=st.size;
    break;

  case T_DIR:
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "du: cannot stat %s\n", buf);
        continue;
      }
    //   printf(1, "%s %d\n", fmtname(buf), st.size);
      printf(1, "%d %s/%s\n", st.size, path,fmtname(buf));
      sum+=st.size;
    }
    break;
  }
  printf(1, "%d .\n", sum );
  close(fd);
}

void duWithParams(char *path,cliArgs* flagStruct,int argc,char* argv[]) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;


  int sum=0;
  if ((fd = open(path, 0)) < 0) {
    printf(2, "du: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "du: cannot stat %s\n", path);
    close(fd);
    return;
  }
  if(flagStruct->k_flag == '1' && argc == 2){
      test(".");
      exit();
  }
  if(flagStruct->t_flag == '1' && argc ==3){
      t1(".",argc,argv,flagStruct->t_flag_value);
      exit();
  }
  if(flagStruct->t_flag == '1' && flagStruct->k_flag == '1' && argc < 5){
      both(".",argc,argv,flagStruct->t_flag_value);
      exit();
  }
  if(flagStruct->t_flag == '1' && flagStruct->k_flag == '1' && argc == 5){
      filetest(argv[4],argc,argv,flagStruct->t_flag_value);
      exit();
  }
  
   
  else{
    file(argv[1],argc,argv);
    exit();
  }
  switch (st.type) {
  case T_FILE:
  printf(1,"in file\n");
    printf(1, "%s %d\n", fmtname(buf), st.size);
    sum+=st.size;
    break;

  case T_DIR:
  printf(1,"in dir\n");
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "du: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0) {
        printf(1, "du: cannot stat %s\n", buf);
        continue;
      }
    //   printf(1, "%s %d\n", fmtname(buf), st.size);
      printf(1, "%d %s/%s\n", st.size, path,fmtname(buf));
      sum+=st.size;
    }
    break;
  }
  printf(1, "SUM: %d .\n", sum );
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    du(".");
    exit();
  }
struct cliArgs argsToStruct;
parseArgs(argc,argv,&argsToStruct);
duWithParams(*argv,&argsToStruct,argc,argv);
/*
printf(1,"kflag: %c\n",argsToStruct.k_flag);
    printf(1,"tflag: %c\n",argsToStruct.t_flag);
    printf(1,"tflagvalue: %d\n",argsToStruct.t_flag_value);
    printf(1,"rflag: %c\n",argsToStruct.r_flag);
    */
  exit();
}