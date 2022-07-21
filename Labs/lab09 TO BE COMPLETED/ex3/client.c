#include "treePublic.h"
#define OK 1
#define KO 0

int
main (
  void
   )
{
  node_t *root, *tmp;
  data_t d;
  int retValue, end = 0;
  char row[MAXC];
  FILE *fp = NULL;

  root = NULL;
  root = createEmptyTree();
  int *array = (int *) calloc(3,sizeof(int));
  int *array2 = (int *) calloc(10,sizeof(int));
  int np = 0,length = 0;
  while (!end) {
    fprintf (stdout, "User selection\n");
    fprintf (stdout, "\t1) Insert one single node\n\t2) Cancel one single node\n\t3) Search a node\n");
    fprintf (stdout, "\t4) Print BST on stdout\n\t5) Write BST on file\n\t6) Read BST from file\n");
    fprintf (stdout, "\t7) Compute min and max\n\t8) End\n");
    fprintf (stdout, "\t9) CountNode\n\t10) CountLevel\n");
    fprintf (stdout, "\t11) CountPath\n\t12) Visit\n\t> ");
    scanf ("%s", row);

    switch (atoi(row)) {

      case 1:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	root = insert (root, d);
	break;

      case 2:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	root = delete (root, d);
	break;

      case 3:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }

	tmp = searchI (root, d);
	if (tmp != NULL) {
	  fprintf (stdout, "Iterative Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Iterative Search: Not Found\n");
        }
	tmp = searchR (root, d);
	if (tmp  != NULL) {
	  fprintf (stdout, "Recursive Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Recursive Search: Not Found\n");
        }
	break;

      case 4:
	writeTree (stdout, root, INORDER);
	break;

      case 5:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

        if (strcmp (row, "stdout") == 0) {
          fp = stdout;
        } else {
   	  fp = fopen (row, "w");fprintf(stdout,"Found node with 2 children!\n");
        }

        if (fp == NULL) {
         fprintf (stderr, "Error Opening File %s\n", row);
         break;
	}

	writeTree (fp, root, PREORDER);

        if (strcmp (row, "stdout") != 0) {
	  fclose(fp);
	}
	break;

      case 6:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

	fp = fopen (row, "r");
	if (fp == NULL) {
	  fprintf (stderr, "Error Opening File %s\n", row);
	} else {
	  freeTree (root);
	  root = readTree (fp);
	}
	break;

      case 7:
        fprintf (stdout, "Tree minimum iterative: ");
        tmp = treeMinI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree minimum recursive: ");
        tmp = treeMinR (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum iterative: ");
        tmp = treeMaxI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum recursive: ");
        tmp = treeMaxR (root);
        writeData (stdout, getData(tmp));
	break;

      case 8:
	end = 1;
	break;
      case 9:
        countNode(root,array);
        for(int i=0;i<3;i++)
            fprintf(stdout,"%d children: %d\n",i,array[i]);
        break;
      case 10:
          countLevel(root,array2,0);
          for(int i=0;i<10;i++)
            fprintf(stdout,"Number of children at level %d: %d\n",i,array2[i]);
          break;
      case 11:
          countPath(root,&np,&length);
          fprintf(stdout,"Number of paths: %d\nTotal length: %d\n",np,length);
          break;
      case 12:
        break;
      default:
	fprintf (stderr, "Unknown Option.\n");
	break;
    }
  }

  freeTree(root);

  return (OK);
}



