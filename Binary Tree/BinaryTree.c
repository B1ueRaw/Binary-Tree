#include "BinaryTree.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 * Dynamically allocate memory for an employee structure
 * with the given name (first input argument).
 * It should also initialize both left_child_ptr and right_child_ptr to NULL.
 */

employee_t *create_employee(char *name) {
  assert(name != NULL);

  employee_t *employee = malloc(sizeof(employee_t));
  assert(employee != NULL);

  employee->name = malloc(strlen(name) + 1);
  assert(employee->name != NULL);
  strcpy(employee->name, name);

  employee->left_child_ptr = NULL;
  employee->right_child_ptr = NULL;

  return employee;
} /* create_employee() */

/*
 * If the root of the tree is NULL, the root should
 * be set to the newly inserted node.
 * The tree should remain a sorted binary tree after insertion.
 * The key to be used for insertion should be the name field of the employee.
 */

void insert_employee(employee_t **root, employee_t *insert) {
  assert(root != NULL);
  assert(insert != NULL);
  assert(insert->right_child_ptr == NULL);
  assert(insert->left_child_ptr == NULL);

  employee_t *employee = *root;
  if (employee == NULL) {
    *root = insert;
  }
  else if (strcmp(insert->name, employee->name) > 0) {
    insert_employee(&employee->right_child_ptr, insert);
  }
  else if (strcmp(insert->name, employee->name) < 0) {
    insert_employee(&employee->left_child_ptr, insert);
  }

} /* insert_employee() */

/*
 * This function should search the tree for a node
 * that has a matching name (second input argument)
 * in the tree given by the root (first input argument)
 * and return a pointer to the node that was found.
 */

employee_t *find_employee(employee_t *root, char *name) {
  assert(name != NULL);

  employee_t *node = root;
  if (node == NULL) {
    return NULL;
  }

  while (node != NULL) {
    if (strcmp(node->name, name) == 0) {
      return node;
    }
    else if (strcmp(node->name, name) > 0) {
      node = node->left_child_ptr;
    }
    else if (strcmp(node->name, name) < 0) {
      node = node->right_child_ptr;
    }
  }
  return NULL;
} /* find_employee() */

/*
 * This function should delete the entire tree
 * given by the root (input argument)
 * and all its associated data recursively.
 * After the function deletes all of the data,
 * the pointer for the root of the tree should be set to NULL.
 */

void delete_tree(employee_t **root) {
  assert(root != NULL);

  if ((*root) == NULL) {
    return;
  }

  delete_tree(&(*root)->left_child_ptr);
  delete_tree(&(*root)->right_child_ptr);

  free((*root)->name);
  (*root)->name = NULL;
  free(*root);
  *root = NULL;
} /* delete_tree() */

/*
 * This function should traverse the tree from the root (first input argument)
 * using the specified traversal order (second input argument)
 * and return the kth (third input argument)
 * employee using that traversal order.
 */

employee_t *traverse_employees(employee_t *root , int order, int index) {
  assert((order >= PREFIX) && (order <= REVERSE));
  assert(index >= 0);

  if (root == NULL) {
    return NULL;
  }

  static int g_count = -1;
  employee_t *employee = NULL;

  if (order == PREFIX) {
    g_count++;
    if (g_count == index) {
      g_count = -1;
      return root;
    }
    employee = traverse_employees(root->left_child_ptr, order, index);
    if (employee != NULL) {
      return employee;
    }
    employee = traverse_employees(root->right_child_ptr, order, index);
  }
  else if (order == POSTFIX) {
    employee = traverse_employees(root->left_child_ptr, order, index);
    if (employee != NULL) {
      return employee;
    }
    employee = traverse_employees(root->right_child_ptr, order, index);
    if (employee != NULL) {
      return employee;
    }
    g_count++;
    if (g_count == index) {
      g_count = -1;
      return root;
    }
  }
  else if (order == INORDER) {
    employee = traverse_employees(root->left_child_ptr, order, index);
    if (employee != NULL) {
      return employee;
    }
    g_count++;
    if (g_count == index) {
      g_count = -1;
      return root;
    }
    employee = traverse_employees(root->right_child_ptr, order, index);
  }
  else if (order == REVERSE) {
    employee = traverse_employees(root->right_child_ptr, order, index);
    if (employee != NULL) {
      return employee;
    }
    g_count++;
    if (g_count == index) {
      g_count = -1;
      return root;
    }
    employee = traverse_employees(root->left_child_ptr, order, index);
  }

  return employee;
} /* traverse_employees() */

/*
 * This function should return the employee in the tree (first argument)
 * that occurs just before the employee with
 * the given name (second argument) in sorted order.
 */

employee_t *previous_employee(employee_t *root, char *name) {
  assert(name != NULL);

  int count = 0;
  employee_t *employee = root;
  while (1) {
    employee = traverse_employees(root, 3, count);
    if (strcmp(name, employee->name) == 0) {
      break;
    }
    count++;
  }

  if (count == 0) {
    return NULL;
  }
  employee = traverse_employees(root, 3, count - 1);
  return employee;
} /* previous_employee() */