//
//  Data.h
//  SimpleDb
//
//  Created by Malek Elsaka on 05/08/2022.
//


#include "SimpleDb.h"
#include <stdlib.h>

bool SDB_isFull(void)
{
    if (count==10)
    {
        return True;
    }
    else
    {
        return False;
    }
}


unit8 SDB_GetUSedSize(void)
{
    return count;
}



bool SDB_AddEntry(unit8 Id, unit8 year, unit8*subjects, unit8*grades, node**listhead)
{
    if(count==10)
    {
        printf("no sufficient space\n");
        return False;
    }
    
    unit8 * temp=grades;
    for (unit8 i=0; i<3; i++)
    {
        if (*temp<0 || *temp>100)
        {
            printf("grades out of range\n");
            return False;
        }
        
        if(i==2){break;}
        temp++;
    }
    
    node*newnode=( node*)malloc(sizeof(node));
    newnode->next=NULL;
    
    newnode->data.stu_ID=Id;
    newnode->data.stu_year=year;
    
    newnode->data.course1_ID=*subjects;
    ++subjects;
    
    newnode->data.course2_ID=*subjects;
    ++subjects;
    
    newnode->data.course3_ID=*subjects;
    
    newnode->data.course1_grade=*grades;
    ++grades;
    
    newnode->data.course2_grade=*grades;
    ++grades;
    
    newnode->data.course3_grade=*grades;
    
    ++count;
    
    node*curr=*listhead;
    
    if(curr==NULL)
    {
        *listhead=newnode;
        return True;
    }
    
    while (curr->next != NULL)
    {
        curr=(curr->next);
    }
        curr->next=newnode;
    
    return True;
    
}



void SDB_DeleteEntry(unit8 Id, node**listhead )
{
    node*curr=*listhead;
    node*prev=*listhead;
    
    if (curr==NULL)
    {
        printf("Database is empty\n");
        return;
    }
    
    while (curr->data.stu_ID != Id && curr!=NULL)
    {
        prev=curr;
        curr=(curr->next);
    }
    
    if (curr==NULL)
    {
        printf("Not found\n");
        return;
    }
    
    if(curr==*listhead)
    {
        free(*listhead);
        *listhead=(curr->next);
        count--;
        return;
    }
    
    
    if ((curr->next)==NULL)
    {
            free(curr);
            prev->next=NULL;
            count--;
    }
    else
    {
        prev->next = curr->next;
        free(curr);
        count--;
    }
    return;
    
}



bool SDB_ReadEntry(unit8 Id, unit8*year, unit8*subjects, unit8*grades, node**listhead)
{
    node * curr=*listhead;
    
    if( curr==NULL)
    {
    printf("Database is empty\n");
    return False;
    }
    
    while(curr!=NULL && curr->data.stu_ID!=Id)
    {
        curr=curr->next;
    }
    
    if( curr==NULL)
    {
    printf("Not found\n");
    return False;
    }
    else
    {
        *year=(curr->data.stu_year);
        
        *subjects=curr->data.course1_ID;
        subjects++;
        
        *subjects=curr->data.course2_ID;
        subjects++;
        
        *subjects=curr->data.course3_ID;
    
        *grades=(curr->data.course1_grade);
        grades++;
        
        *grades=(curr->data.course2_grade);
        grades++;
        
        *grades=(curr->data.course3_grade);
        
    
        
        return True;
    }
        
}




void SDB_PrintList(node**listhead)
{
    node*curr=*listhead;
    while(curr!=NULL)
    {
        printf("Student ID: %d\n", curr->data.stu_ID);
        printf("Student Year: %d\n", curr->data.stu_year);
        printf("Course1 ID: %d\n", curr->data.course1_ID);
        printf("Course1 Grade: %d\n", curr->data.course1_grade);
        printf("Course2 ID: %d\n", curr->data.course2_ID);
        printf("Course2 Grade: %d\n", curr->data.course2_grade);
        printf("Course3 ID: %d\n", curr->data.course3_ID);
        printf("Course3 Grade: %d\n\n", curr->data.course3_grade);
        
        curr=curr->next;
        
    }
    
}

bool SDB_IsExist(unit8 ID, node**ListHead)
{
    node * curr=*ListHead;
    
    if(curr==NULL)
    {
        return False;
    }
    
    while(curr!=NULL && curr->data.stu_ID!=ID)
    {
        curr=curr->next;
    }
    
    if (curr==NULL)
    {
        return False;
    }
    else
    {
        return True;
    }
    
}

void SDB_GetIdList(unit8 * Count, unit8 **IDlist, node ** ListHead )
{
    node*curr=*ListHead;
    *Count=count;
    *IDlist=(unit8*)malloc(count*sizeof(unit8));
    
    for (unit8 i=0; i<count; i++)
    {
        (*IDlist)[i]=(curr->data.stu_ID);
        curr=curr->next;
    }
    
}

int main()
{
    bool x;
    simpleDb database;
    node*ptr=database.database.Head=NULL;
    unit8 cnt=0;
    unit8 * IDlist=NULL;
    
    unit8 Id=122, year=2002;
    unit8 subs[]={12, 3, 22};
    unit8 grades[]={100, 20, 80};
    
    unit8 Id2=1012, year2=1999;
    unit8 subs2[]={11, 32, 32};
    unit8 grades2[]={70, 20, 80};
   
    unit8 Id3=1112, year3=1999;
    unit8 subs3[]={11, 32, 32};
    unit8 grades3[]={71, 20, 80};
   
    
    x=SDB_AddEntry(Id, year, subs, grades, &ptr);
    x=SDB_AddEntry(Id2, year2, subs2, grades2, &ptr);
    x=SDB_AddEntry(Id3, year3, subs3, grades3, &ptr);
    
    SDB_PrintList(&ptr);
    
    SDB_GetIdList(&cnt, &IDlist, &ptr);
    printf("**************************\n");
   
    
    
    for (unit8 i=0; i<cnt; i++)
    {
        printf("%d\n", *IDlist);
        IDlist++;
    }
    return 0;
}
