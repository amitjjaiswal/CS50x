/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

struct node
{
    bool is_word;
    struct node *children[27];
};

struct node *root;
int count=0;

bool clearall(struct node *);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //printf("Word to check:%s\n",word);
    // TODO
    struct node *temp;
    int len,i;
    len = strlen(word);
    temp = root;
    
    /*
    i=0;
    while(word[i]) 
    {
        word[i] = tolower(word[i]);
        i++;
    }
    */
    
    for(i=0;i<len;i++)
    {
        //printf("tolower(word[%d])=%c\n",i,tolower(word[i]));
        if(tolower(word[i]) == '\'')
        {
            //printf("I'm here\n");
            if(temp->children[26] == NULL)
                return false;
            else
            {
                temp = temp->children[26];
                if(i == len-1)
                {
                    if(temp->is_word)
                        return true;
                    else
                        return false;
                }
            }
        }
        else
        {
            if(temp->children[tolower(word[i])-97] == NULL)
                return false;
            else
            {
                temp = temp->children[tolower(word[i])-97];
                if(i == len-1)
                {
                    if(temp->is_word)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        //unload();
        return false;
    }
    
    struct node *temp;
    root = malloc(sizeof(struct node));
    for(int j=0;j<27;j++)
    {
        root->children[j]=NULL;
        root->is_word=false;
    }
    
    if(root == NULL)
    {
        //unload();
        return false;
    }
    
    char line[LENGTH+2];
    int i;

    while (fgets(line, sizeof(line), fp)) 
    {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        line[strlen(line)-1]='\0';
        //printf("word=%s length=%d\n", line,(int)strlen(line)); 
        int len;
        len = strlen(line);

        i=0;
        while(line[i]) 
        {
            line[i] = tolower(line[i]);
            i++;
        }
        
        temp = root;
        for(i=0;i<len;i++)
        {
            if(line[i] == '\'')
            {
                if(temp->children[26] == NULL)
                {
                    temp->children[26]=malloc(sizeof(struct node));
                    if(temp->children[26] == NULL)
                    {
                        unload();
                        return false;
                    }
                    
                    for(int j=0;j<27;j++)
                    {
                        temp->children[26]->children[j]=NULL;
                        temp->children[26]->is_word=false;
                    }
                        
                }
                temp = temp->children[26];
            }
            else
            {
                if(temp->children[line[i]-97] == NULL)
                {
                    temp->children[line[i]-97]=malloc(sizeof(struct node));
                    if(temp->children[line[i]-97] == NULL)
                    {
                        unload();
                        return false;
                    }
                    
                    for(int j=0;j<27;j++)
                    {
                        temp->children[line[i]-97]->children[j]=NULL;
                        temp->children[line[i]-97]->is_word=false;
                    }
                    
                }
                temp = temp->children[line[i]-97];
            }
            if(i==len-1)
                    temp->is_word = true;
        }
        if(len>0)
            count++;
        
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

void calc_size(struct node *temp)
{
    if(temp->is_word)
        count++;
    for(int i=0;i<27;i++)
    {
        if(temp->children[i]!=NULL)
            calc_size(temp->children[i]);
    }
}
 
 
unsigned int size(void)
{
    // TODO
    //struct node *temp;
    //temp =  root;
    //calc_size(temp);
    return (count);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    struct node *temp;
    temp = root;
    return(clearall(temp));
    // TODO
    return false;
}


bool clearall(struct node *temp)
{
    for(int i=0;i<27;i++)
    {
        if(temp->children[i]!=NULL)
            clearall(temp->children[i]);
    }
    free(temp);
    return(true);
}