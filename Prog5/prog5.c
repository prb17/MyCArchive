/*
  CSE 109: Fall 2017
  Peter Brady
  prb315
  Single Linked List
  Program #5
*/

#include<stdio.h>
#include"ListFile.h"
#include<stdlib.h>

int main(int argc, char** argv)
{

  /*if(argc != 3)
    {
      printf("not exact file arguments");
      exit(1);
    }
  */
  struct ListFile* testList = makeList();
  char *fileName1 = "file1.txt";
  char *fileName2 = "file2.txt";
  char *fileName3 = "file3.txt";
  char *fileName4 = "file4.txt";
  
  insert(testList, "apple", (void *)5, 5);
  insert(testList, "banana", (void *)6, 6);
  insert(testList, "cat", (void *)3, 3);
  insert(testList, "bait", (void *)3, 3);
  insert(testList, "ants", (void *)3, 3);
  insert(testList, "abb", (void *)3, 3);
  insert(testList, "caa", (void *)3, 3);
  removeByName(testList, "apple");
  //fprintf(stdout, "%s\n", toString(testList));

  //fprintf(stdout, "%s\n", toString(testList));

  struct ListFile* testReadList1 = readFile(fileName1); ////////////////////
  struct ListFile* testReadList2 = readFile(fileName2); ///////////////////
  //char *string1 = toString(testReadList1); //////////////////
  //char *string2 = toString(testReadList2); /////////////////
  //fprintf(stdout, "%s\n", string1);
  //fprintf(stdout, "%s\n", string2);

  struct ListFile* testAppendList1 = copyList(testReadList1);
  appendFromFile(testAppendList1, fileName3);
  //char *string3 = toString(testAppendList1);///////////////////
  //fprintf(stdout, "%s\n", string3);

  saveToFile(testAppendList1, fileName4);
  struct ListFile* testSaveFile = readFile(fileName4); //////////
  //char *string4 = toString(testSaveFile); /////////////
  //fprintf(stdout, "%s\n", string4);
  
  destroyList(testSaveFile);
  
  //printf("%s\n", toString(testReadList1));
  //printf("%s\n", toString(testReadList2));

  char *inputFile1 = "file1.txt";
  char *inputFile2 = "file2.txt";
  char *outputFile = "output.txt";
  
  saveToFile(testReadList1, inputFile1);
  saveToFile(testReadList2, inputFile2);
  
  struct ListFile *testerList1 = readFile(inputFile1);
  struct ListFile *testerList2 = readFile(inputFile2);

  //printf("%s\n", toString(testerList1));
  //printf("%s\n", toString(testerList2));

  //printf("//////////////\n");
  saveToFile(testerList1, outputFile);
  struct ListFile* outputReader = readFile(outputFile);
  //printf("%s\n", toString(outputReader));
  saveToFile(testerList2, outputFile);
  appendFromFile(outputReader, outputFile);
  //printf("%s\n", toString(outputReader));
  saveToFile(outputReader, outputFile);
  removeByName(outputReader, "banana");
  
  destroyList(testReadList1);
  destroyList(testReadList2);
  destroyList(testList);
  destroyList(testerList1);
  destroyList(testerList2);
  destroyList(outputReader);
  destroyList(testAppendList1);

  return 0;
}
