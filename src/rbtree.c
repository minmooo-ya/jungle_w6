#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->root = p->nil;
  p->nil->left = p->nil;
  p->nil->right = p->nil;
  p->nil->parent = NULL;
  p->nil->key = 0;
  return p;
}

void left_rotate(rbtree *t, node_t *target){
  node_t *y = target->right; 
  
  target -> right = y -> left;
  if(y->left != t->nil){
    y->left->parent = target;
  }

  y->parent = target ->parent;
  if(target->parent == t->nil){
    t->root = y;
  }else if (target == target->parent->left){
    target->parent->left = y;
  }else{
    target->parent->right = y;
  }

  y->left = target;
  target->parent = y;
}

void right_rotate(rbtree *t, node_t *target){
  node_t *y = target->left; 
  
  target -> left = y -> right;
  if(y->right != t->nil){
    y->right->parent = target;
  }

  y->parent = target ->parent;
  if(target->parent == t->nil){
    t->root = y;
  }else if (target == target->parent->right){
    target->parent->right = y;
  }else{
    target->parent->left = y;
  }

  y->right = target;
  target->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->left) {
      node_t *y = z->parent->parent->right;

      if (y->color == RBTREE_RED) {
        // Case 1: recolor
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          // Case 2: 왼쪽 회전
          z = z->parent;
          left_rotate(t,z);
        }
        // Case 3: 오른쪽 회전
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }

    } else {
      // 위랑 대칭 (부모가 오른쪽일 때)
      node_t *y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        // Case 1: recolor
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          // Case 2: 왼쪽 회전
          z = z->parent;
          right_rotate(t,z);
        }
        // Case 3: 오른쪽 회전
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t == NULL) return;

  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  // 1.	새로운 노드 생성하고 RED로 설정
	// 2.	BST 삽입처럼 위치 찾아서 연결
	// 3.	부모, 왼쪽/오른쪽 자식 설정
	// 4.	fixup 함수 호출해서 트리 성질 복구
	// 5.	삽입한 노드를 리턴

  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;  // 빨간색으로 삽입
  new_node->left = t->nil;
  new_node->right = t->nil;

  node_t *y = t->nil;
  node_t *x = t->root;

  while(x != t->nil){
    y = x;
    if(key < x->key){
      x = x->left;
    }else{
      x = x->right;
    }
  }

  new_node->parent = y;
  if(y == t->nil){
    t->root = new_node;
  }else if(key < y->key){
    y->left = new_node;
  }else{
    y->right = new_node;
  }

  rbtree_insert_fixup(t,new_node);
  
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *cur = t->root;
  while(cur != t->nil){
    if(key == cur->key){
      return cur;
    }else if(key < cur->key){
      cur = cur ->left;
    }else{
      cur = cur->right;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
