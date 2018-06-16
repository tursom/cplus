//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_SET_H
#define CPLUS_SET_H

#include <functional>
#include <iostream>
#include "../tools/class.h"
#include "../system/Exception.h"
#include "../memory/dark_magic.h"
#include "Queue.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(Set) {
		public:
			
			Set() {}
			
			~Set() {
				forEach([](T &value) {
					delete &value;
				});
			}
			
			bool insert(const T &value) {
				if (root == nullptr) root = new Tree(false, value);
				else root = root->insert(value);
				while (root->getParent() != nullptr)root = root->getParent();
				return true;
			}
			
			T *get(const T &value) {
//				std::cout << "Set: getting: " << value << std::endl;
				auto ret = this->root->find(value);
				if (ret == nullptr) {
//					std::cout << "Set: not find value, inserting" << std::endl;
					insert(value);
					ret = this->root->find(value);
				}
				return ret;
			}
			
			T *find(const T &value) {
				return this->root->find(value);
			}
			
			void forEach(std::function<void(T &)> func) const {
				Tree *state = this->root;
				Queue<Tree *> taskQueue;
				while (state != nullptr) {
					auto get = state->get();
					if (get != nullptr) {
						func(*get);
					}
					if (state->getLeft() != nullptr)taskQueue.offer(state->getLeft());
					if (state->getRight() != nullptr)taskQueue.offer(state->getRight());
					auto sstate = taskQueue.pool();
					if (sstate == nullptr)break;
					else state = *sstate;
				}
			}
			
			CPlusClass(RBTException), public system::Exception {
			public:
				RBTException() = default;
				
				explicit RBTException(const char *message) : Exception(message) {}
				
				explicit RBTException(const lang::String &message) : Exception(message) {}
			};
		
		private:
			class Tree {
			public:
				Tree() = default;
				
				explicit Tree(const T &key) : value((T *) malloc(sizeof(T))) {
					memory::copy(key, *this->value);
				}
				
				Tree(bool red, const T &key) : red(red), value((T *) malloc(sizeof(T))) {
					memory::copy(key, *this->value);
				}
				
				bool isBlack() { return !red; }
				
				void isBlack(bool isBlack) { red = !isBlack; }
				
				bool isRed() { return red; }
				
				void isRed(bool isRed) { red = isRed; }
				
				Tree *getParent() const { return parent; }
				
				Tree *getLeft() const { return left; }
				
				Tree *getRight() const { return right; }
				
				T *get() const { return value; }
				
				void setParent(Tree *parent) {
					Tree::parent = parent;
				}
				
				void setLeft(Tree *left) {
					Tree::left = left;
				}
				
				void setRight(Tree *right) {
					Tree::right = right;
				}
				
				void setKey(T *key) {
					Tree::value = key;
				}
				
				Tree *leftRotate() {
					return leftRotate(this);
				}
				
				Tree *rightRotate() {
					return rightRotate(this);
				}
				
				Tree *insert(const T &value) {
					return insert(this, value);
				}
				
				T *find(const T &value) {
					auto ret = find(this, value);
					if (ret == nullptr)return nullptr;
					else return ret->value;
				}
				
				static u_int32_t getSize(Tree *p) {
					if (p == nullptr)return 0;
					else return p->size;
				}
				
				static bool isBlack(Tree *p) { return p == nullptr || !p->red; }
				
				static bool isRed(Tree *p) { return p != nullptr && p->red; }
				
				static Tree *leftRotate(Tree *root) {
					if (root == nullptr)return root;
					auto right = root->right;
					//将 right 传递给 parent
					if (root->parent != nullptr) {
						if (root->parent->left == root) {
							root->parent->left = right;
						} else {
							root->parent->right = right;
						}
					}
					right->parent = root->parent;
					
					//将 right 的 left 传递给 root
					root->right = right->left;
					if (root->right != nullptr) root->right->parent = root;
					
					//重设 parent 为 right (1)
					root->parent = right;
					root->parent->left = root;
					
					//交换颜色
					bool red = root->red;
					root->red = right->red;
					right->red = red;
					
					root->size = getSize(root->left) + getSize(root->right) + 1;
					right->size = root->size + getSize(right->right) + 1;
					
					return right;
				}
				
				static Tree *rightRotate(Tree *root) {
					if (root == nullptr)return root;
					auto left = root->left;
					//将 left 传递给 parent
					left->parent = root->parent;
					if (root->parent != nullptr) {
						if (root->parent->right == root) {
							left->parent->right = left;
						} else {
							left->parent->left = left;
						}
					}
					
					//将 left 的 right 传递给 root
					root->left = left->right;
					if (root->left != nullptr) root->left->parent = root;
					
					//重设 parent 为 left
					root->parent = left;
					root->parent->right = root;
					
					//交换颜色
					bool red = root->red;
					root->red = left->red;
					left->red = red;
					
					root->size = getSize(root->right) + getSize(root->left) + 1;
					left->size = root->size + getSize(left->left) + 1;
					
					return left;
				}
				
				static Tree *flipColors(Tree *root) {
					if (root != nullptr && isRed(root->right) && isRed(root->left)) {
						//如果两个子节点都是红色的
						root->isRed(root->parent != nullptr);
						root->left->isRed(false);
						root->right->isRed(false);
						check(root->parent);
					}
					return root;
				}
				
				static Tree *check(Tree *root) {
					if (isBlack(root)) {
						//如果 root 是黑色的，做一次颜色变换后直接返回
						return flipColors(root);
					}
					//如果 root 是红色，则可确认 parent 不为 nullptr
					if (root == root->parent->left) {
						//如果 root 是 parent 的 left 节点
						if (isRed(root->right)) {
							//如果 right 和 root 都是红色的
							leftRotate(root);
							root = root->parent;
							root = check(root);
						} else if (isRed(root->left)) {
							//如果 left 和 root 都是红色的
							if (isRed(root->parent->right)) {
								//如果 parent 的 right 也是红色的
								root = flipColors(root->parent);
							} else {
								root = rightRotate(root->parent);
								root->parent;
								root = flipColors(root);
							}
						}
					} else if (root == root->parent->right) {
						//如果 root 是 parent 的 right 节点
						root = leftRotate(root->parent);
						check(root);
					}
					return root;
				}
				
				static Tree *insert(Tree *root, const T &value) {
					if (root == nullptr) {
						return new Tree(false, value);
					}
					Tree *state = root;
					while (state != nullptr) {
						if (value == *state->value) break;
						else if (value <= *state->value) {
							if (state->left == nullptr) {
								state->left = new Tree(value);
								state->left->parent = state;
								check(state);
								break;
							} else {
								state = state->left;
							}
						} else {
							if (state->right == nullptr) {
								state->right = new Tree(value);
								state->right->parent = state;
								check(state);
								break;
							} else {
								state = state->right;
							}
						}
					}
					return root;
				}
				
				static Tree *find(Tree *root, const T &value) {
//					std::cout << "Set: static: finding value: " << value << std::endl;
					Tree *state = root;
//					std::cout << "Set: static: state: " << state << std::endl;
					while (state != nullptr) {
						if (value == *state->value) break;
						else if (value <= *state->value) {
							state = state->left;
						} else {
							state = state->right;
						}
//						std::cout << "Set: static: state: " << state << std::endl;
					}
					return state;
				}
			
			private:
				bool red = true;
				u_int32_t size = 1;
				Tree *parent = nullptr;
				Tree *left = nullptr;
				Tree *right = nullptr;
				T *value = nullptr;
			};
			
			Tree *root = nullptr;
		};
	}
}

#endif //CPLUS_SET_H
