/* Source Code From Laure Gonnord and Bernard Carré
 * Modified by Walter Rudametkin
 */

#include "trees.h"

//construction of a tree by return value
//struct node * cons(int val, struct node *left, struct node *right)
//{
//    PtNode new = malloc(sizeof(Node));
//    new->val=val;
//    new->left=left;
//    new->right=right;
//    return new;
//}

// construction of a tree by pointer
void cons_tree(struct node ** ptr_tree, int val, struct node *left, struct node *right)
{
	*ptr_tree = malloc(sizeof(Node));
	(*ptr_tree)->val = val;
	(*ptr_tree)->left = left;
	(*ptr_tree)->right = right;
}

// create an empty tree by return value
//struct node * mk_empty_tree()
//{
//	return NULL;
//}

// initialize un empty tree
void mk_empty_tree(struct node ** ptr_tree)
{
	*ptr_tree = NULL;
}

// tree is empty?
bool is_empty(struct node *tree)
{
	return tree==NULL;
}

// t is a leaf?
bool is_leaf(struct node *tree)
{
	return(!is_empty(tree) && is_empty(tree->left) && is_empty(tree->right));
}

// add x in a bst wtr its value.
void add(struct node **ptr_tree, int x)
{
	if (is_empty(*ptr_tree)) cons_tree(ptr_tree, x, NULL, NULL);
	else {
		if (x <= (*ptr_tree)->val) add(&(*ptr_tree)->left, x);
		else add(&(*ptr_tree)->right, x);
	}
}

// print values of tree in ascendant order (left-value-right)
void print_tree(struct node *tree)
{
	if (!is_empty(tree)) {
		print_tree(tree->left);
		printf("%d\n", tree->val);
		print_tree(tree->right);
	}
}

// build a tree "add"ing values of the file fp
void load_tree(FILE *fp, struct node **ptr_tree)
{
	int entier = 0;

    while (fscanf(fp, "%d", &entier) != EOF) {
        add(ptr_tree, entier);
    }
}

// Free all memory used by the tree
void free_tree(struct node **ptr_tree)
{
	if (!is_empty(*ptr_tree)) {
		free_tree(&(*ptr_tree)->left);
		free_tree(&(*ptr_tree)->right);
		free(*ptr_tree);
		*ptr_tree = NULL;
	}
}

// print pairs (father =L/R=> son)
void print_rec_edges(struct node *tree)
{
	if (!is_empty(tree)) {
		if (!is_empty(tree->left)) {
			printf("%d -> %d\n", tree->val, tree->left->val);
			print_rec_edges(tree->left);
		}
		if (!is_empty(tree->right)) {
			printf("%d -> %d\n", tree->val, tree->right->val);
			print_rec_edges(tree->right);
		}
	}
}

//PART II

// recursively prints arcs of the tree <value,left,right> into the file fp:
// "value -> left;"  if it exists
// "value -> right;" if it exists
// check for: !is_empty(t) & !is_leaf(t)
void recursive_dot(struct node *tree, FILE *fp)
{
	if (!is_empty(tree) && !is_leaf(tree)) {
		if (!is_empty(tree->left)) {
			fprintf(fp, "\t%d -> %d\n", tree->val, tree->left->val);
			recursive_dot(tree->left, fp);
		}
		if (!is_empty(tree->right)) {
			fprintf(fp, "\t%d -> %d\n", tree->val, tree->right->val);
			recursive_dot(tree->right, fp);
		}
	}
}

// generate a .dot file for the tree
// limits (no arcs) :
//   is_empty(t) => "empty" digraph
//   is_leaf(t) => only one node
// general case :
//   calls recursive_dot which prints arcs
void generate_dot (struct node *t, FILE *fp)
{
	fprintf (fp, "digraph G {\n");
	if (!is_empty(t))
	{
		if (is_leaf(t))
		{
			fprintf(fp, "\t%d", t->val);
		}
		else
		{
			recursive_dot(t,fp);
		}
	}
	fprintf (fp, "}\n");
}
