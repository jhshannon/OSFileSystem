#include <string.h>

struct sf_root{
  char path[30];
  struct user *head;
};

struct user{
  struct user *next;

  char username[8];
  char hash[13];
  int dsc;
  int dcc;
  int dmc;
  int dw;
  int de;
  int dd;
  void* reserved;
};

struct sf_root* sf_tree_init(char *path){
  struct sf_root *sf_i;
  sf_i = (struct sf_root*)malloc(sizeof(struct sf_root));
  if(sf_i==NULL) return NULL;
  strcpy(sf_i->path, path);
  return sf_i;
}

int sf_tree_destroy(struct sf_root *sf){
  struct user *del = sf->head, *temp;
  while(del){
    temp = del->next;
    free(del);
    del = temp;
  }
  free(sf);
  return 0;
}

int sf_tree_add_user(struct sf_root *sf, char* username){
  struct user *u, *temp;
  u = (struct user *)malloc(sizeof(struct user));
  if(u==NULL) return -1; // not able to allocate memory
  if(strlen(username)>8) return -2; // name too long 
  strcpy(u->username, username);
  u->dsc = 0;
  u->dcc = 0;
  u->dmc = 99999;
  u->dw = 7;

  if(sf->head){
    temp = sf->head;
    while(temp->next){
      temp = temp->next;
      return 0;
    }
    temp->next = u;
  }else{
    sf->head = u;
    return 0;
  }
  
}

int sf_tree_delete_user(struct sf_root *sf, char* username){
  struct user *del, *temp;
  del = sf->head;
  if(strcmp(del->username, username)==0){
    sf->head = del->next;
    free(del);
    return 0;
  }
  while(del->next){
    if(strcmp((del->next)->username, username)==0){
      temp = del->next;
      del->next= temp->next;
      free(temp);
      return 0;
    }
    del = del->next;
  }
  return -1; // not found
}
void* find_user(struct sf_root *sf, char* username){
  struct user *current = sf->head;
  while(current){
    if(strcmp(current->username, username)==0) return (void*)current;
    current = current->next;
  }
  return (void*)NULL;
}

int update_username(struct sf_root *sf, char* username, char* newname){
  struct user* cuser;
  if(cuser= (struct user*)find_user(sf, username)){
    if(strlen(newname)>8) return -1;
    strcpy(cuser->username, newname);
    return 0;
  }else return -1;
}

int update_daysSinceChanged(struct sf_root *sf, char* username, int dsc){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->dsc = dsc;
    return 0; 
  }else return -1;    
}

int update_daysUntilCanChange(struct sf_root *sf, char* username, int dcc){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->dcc = dcc;
    return 0;
  }else return -1;
}

int update_daysUntilMustChange(struct sf_root *sf, char* username, int dmc){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->dmc = dmc;
    return 0;
  }else return -1;
}

int update_daysBeforeWarning(struct sf_root *sf, char* username, int dw){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->dw = dw;
    return 0;
  }else return -1;
}

int update_daysUntilExpiration(struct sf_root *sf, char* username, int de){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->de = de;
    return 0;
  }else return -1;
}

int update_daysSinceDeactivation(struct sf_root *sf, char* username, int dd){
  struct user* cuser;
  if(cuser = (struct user*)find_user(sf, username)){
    cuser->dd = dd;
    return 0;
  }else return -1;
}
