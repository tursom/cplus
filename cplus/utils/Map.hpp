//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_MAP_H
#define CPLUS_MAP_H

#include <functional>
#include <iostream>
#include "Queue.h"
#include "StringBuilder.h"
#include "../tools/class.h"
#include "../system/Exception.h"
#include "../memory/dark_magic.h"
#include "ArrayStack.hpp"

namespace cplus {
	namespace utils {
		template<typename K, typename V>
		CPlusClass(Map) {
		public:
			
			Map() {}
			
			Map(K *keyArray, V *valueArray, size_t arraySize) : Map() {
				for (size_t i = 0; i < arraySize; ++i) {
					insert(keyArray[i], valueArray[i]);
				}
			}
			
			~Map() {
				std::cout << "~Map()" << std::endl;
				forEach([](K &value) {
					delete &value;
				});
				TreeNode *node = nullptr;
				root->forEach([&node](TreeNode *it) {
					if (node != nullptr)delete node;
					node = it;
				});
				if (node != nullptr)delete node;
			}
			
			bool insert(const K &key, const V &value) {
				if (root == nullptr) root = new TreeNode(false, false, nullptr, key, value);
				else root = root->insert(key, value);
				while (root->getParent() != nullptr)root = root->getParent();
				return true;
			}
			
			K *get(const K &key) {
//				std::cout << "Map: getting: " << key << std::endl;
				auto ret = this->root->find(key);
				return ret;
			}
			
			V *find(const K &value) {
				return this->root->find(value);
			}
			
			void forEach(std::function<void(K &)> func) const {
				TreeNode *state = this->root;
				ArrayStack<TreeNode *> taskQueue;
				while (state != nullptr) {
					auto get = state->get();
					if (get != nullptr) {
						func(*get);
					}
					if (state->getLeft() != nullptr)taskQueue.push(state->getLeft());
					if (state->getRight() != nullptr)taskQueue.push(state->getRight());
					if (!taskQueue.pop(state))break;
				}
			}
			
			lang::String toString() const override {
				StringBuilder sb;
				size_t id = 0;
				sb.append("[ ");
				root->forEach([&sb, &id](TreeNode *it) {
					if (id != 0) {
						sb.append(", ");
					}
					sb.append("{ \"node\":\"");
					sb.append((void *) it);
					sb.append("\", \"parent\":\"");
					sb.append((void *) it->getParent());
					sb.append("\", \"left\":\"");
					sb.append((void *) it->getLeft());
					sb.append("\", \"right\":\"");
					sb.append((void *) it->getRight());
					sb.append("\" }");
					++id;
				});
				sb.append(" ]");
				return sb.toString();
			}
			
			CPlusClass(RBTException), public system::Exception {
			public:
				RBTException() = default;
				
				explicit RBTException(const char *message) : Exception(message) {}
				
				explicit RBTException(const lang::String &message) : Exception(message) {}
			};
		
		private:
			class TreeNode {
			public:
				TreeNode() : isRedColor(true), isLeft(false) {}
				
				explicit TreeNode(bool isLeft) : isRedColor(true), isLeft(isLeft) {}
				
				explicit TreeNode(const K &key, const V &value)
						: key((K *) malloc(sizeof(K))), value((V *) malloc(sizeof(V))), isRedColor(true),
						  isLeft(false) {
					memory::copy(key, *this->key);
					memory::copy(value, *this->value);
				}
				
				TreeNode(bool red, bool isLeft, TreeNode *parent, const K &key, const V &value)
						: isRedColor(red), key((K *) malloc(sizeof(K))), value((V *) malloc(sizeof(V))), isLeft(false),
						  parent(parent) {
					memory::copy(key, *this->key);
					memory::copy(value, *this->value);
				}
				
				void forEach(std::function<void(TreeNode *)> func) {
					TreeNode *state = this;
					ArrayStack<TreeNode *> taskQueue;
					while (state != nullptr) {
						func(state);
						if (state->getLeft() != nullptr)taskQueue.push(state->getLeft());
						if (state->getRight() != nullptr)taskQueue.push(state->getRight());
						if (!taskQueue.pop(state))break;
					}
				}
				
				bool isBlack() { return !isRedColor; }
				
				void isBlack(bool isBlack) { isRedColor = !isBlack; }
				
				bool isRed() { return isRedColor; }
				
				void isRed(bool isRed) { isRedColor = isRed; }
				
				TreeNode *getParent() const { return parent; }
				
				TreeNode *getLeft() const { return left; }
				
				TreeNode *getRight() const { return right; }
				
				K *get() const { return key; }
				
				void setParent(TreeNode *parent) {
					TreeNode::parent = parent;
				}
				
				inline void setLeft(TreeNode *node) {
					left = node;
					if (node != nullptr) {
						node->parent = this;
						node->isLeft = true;
					}
				}
				
				inline void setRight(TreeNode *node) {
					right = node;
					if (node != nullptr) {
						node->parent = this;
						node->isLeft = false;
					}
				}
				
				void setKey(K *key) {
					TreeNode::key = key;
				}
				
				TreeNode *leftRotate() {
					return leftRotate(this);
				}
				
				TreeNode *rightRotate() {
					return rightRotate(this);
				}
				
				TreeNode *insert(const K &key, const V &value) {
					return insert(this, key, value);
				}
				
				V *find(const K &value) {
					auto ret = find(this, value);
					if (ret == nullptr)return nullptr;
					else return ret->value;
				}
				
				static u_int32_t getSize(TreeNode *p) {
					if (p == nullptr)return 0;
					else return p->size;
				}
				
				inline bool isLeftNode() { return isLeft; }
				
				inline bool isRightNode() { return !isLeft; }
				
				static bool isBlack(TreeNode *p) { return p == nullptr || !p->isRedColor; }
				
				static bool isRed(TreeNode *p) { return p != nullptr && p->isRedColor; }
				
				inline static void swapColor(TreeNode *node1, TreeNode *node2) {
					node1->isRedColor ^= node2->isRedColor;
					node2->isRedColor ^= node1->isRedColor;
					node1->isRedColor ^= node2->isRedColor;
				}
				
				static TreeNode *leftRotate(TreeNode *root) {
					if (root == nullptr)return root;
					auto right = root->right;
					//检查是否符合左旋条件
					if (right == nullptr)return nullptr;
					//将 right 传递给 parent
					if (root->parent != nullptr) {
						replaceWith(root, right);
					} else {
						right->parent = nullptr;
					}
					//将 right 的 left 传递给 root
					root->setRight(right->left);
					
					//重设 parent 为 right (1)
					root->parent = right;
					root->parent->left = root;
					root->isLeft = true;
					
					//交换颜色
//					bool isRedColor = root->isRedColor;
//					root->isRedColor = right->isRedColor;
//					right->isRedColor = isRedColor;
					swapColor(root, right);
					
					root->size = getSize(root->left) + getSize(root->right) + 1;
					right->size = root->size + getSize(right->right) + 1;
					
					return right;
				}
				
				static TreeNode *rightRotate(TreeNode *root) {
					if (root == nullptr)return root;
					auto left = root->left;
					//检查是否符合右旋条件
					if (left == nullptr)return nullptr;
					//将 left 传递给 parent
					if (root->parent != nullptr) {
						replaceWith(root, left);
					} else {
						left->parent = nullptr;
					}
					
					//将 left 的 right 传递给 root
					root->setLeft(left->right);
					
					//重设 parent 为 left
					root->parent = left;
					root->parent->right = root;
					root->isLeft = false;
					
					//交换颜色
//					bool isRedColor = root->isRedColor;
//					root->isRedColor = left->isRedColor;
//					left->isRedColor = isRedColor;
					swapColor(root, left);
					
					root->size = getSize(root->right) + getSize(root->left) + 1;
					left->size = root->size + getSize(left->left) + 1;
					
					return left;
				}
				
				static TreeNode *flipColors(TreeNode *root) {
					//在保证黑高不变的情况下对颜色进行翻转
					if (root != nullptr && !root->isRedColor && isRed(root->right) && isRed(root->left)) {
						//要求两个子节点都是红色的，根节点是黑色的
						root->isRed(root->parent != nullptr);
						root->left->isRed(false);
						root->right->isRed(false);
						fixAfterInsertion(root);
					}
					return root;
				}
				
				/**
				 *
				 * @param node
				 * @return
				 */
				static TreeNode *fixAfterInsertion(TreeNode *node) {
					if (node == nullptr)return nullptr;
					else if (node->parent == nullptr) {
						node->isBlack(true);
					}
					if (!node->isRedColor) {
						return node;
					} else {
						//如果 node 是红色，则可确认 parent 不为 nullptr
						if (node->isLeft) {
							if (isRed(node->parent)) {
								//如果有两个红节点相邻
								//TODO 请移步 /cplus/lang/String.cpp 其中专为String优化的Set对应的注释
								node = flipColors(rightRotate(node->parent));
							}
						} else {
							//如果 node 是 parent 的 right 节点 l
							if (isRed(node->parent->left)) {
								//如果兄弟节点也为红色，父节点可以肯定为黑色
								//对父节点执行颜色翻转操作，并执行 fixAfterInsertion 操作
								flipColors(node->parent);
							} else {
								//否则对父节点执行右旋操作，并对原先的父节点（即当前的左节点）
								//执行 fixAfterInsertion 操作
								leftRotate(node->parent);
								node = fixAfterInsertion(node->left);
							}
						}
					}
					return node;
				}
				
				static TreeNode *insert(TreeNode *root, const K &key, const V &value) {
					if (root == nullptr) {
						return new TreeNode(false, false, nullptr, key, value);
					}
					TreeNode *state = root;
					while (state != nullptr) {
						if (key == *state->key) memory::copy(value, *state->value);
						else if (key <= *state->key) {
							if (state->left == nullptr) {
								state->left = new TreeNode(true, true, state, key, value);
								fixAfterInsertion(state->left);
								break;
							} else {
								state = state->left;
							}
						} else {
							if (state->right == nullptr) {
								state->right = new TreeNode(true, false, state, key, value);
								fixAfterInsertion(state->right);
								break;
							} else {
								state = state->right;
							}
						}
					}
					return root;
				}
				
				static TreeNode *find(TreeNode *root, const K &value) {
//					std::cout << "Map: static: finding key: " << key << std::endl;
					TreeNode *state = root;
//					std::cout << "Map: static: state: " << state << std::endl;
					while (state != nullptr) {
						if (value == *state->key) break;
						else if (value <= *state->key) {
							state = state->left;
						} else {
							state = state->right;
						}
//						std::cout << "Map: static: state: " << state << std::endl;
					}
					return state;
				}
				
				inline static void replaceWith(TreeNode *oldNode, TreeNode *newNode) {
					if (oldNode == nullptr)return;
					if (oldNode->parent == nullptr) {
						newNode->parent = nullptr;
					} else if (oldNode->isLeft) {
						oldNode->parent->setLeft(newNode);
					} else {
						oldNode->parent->setRight(newNode);
					}
				}
			
			private:
				bool isLeft;
				bool isRedColor;
				u_int32_t size = 1;
				TreeNode *parent = nullptr;
				TreeNode *left = nullptr;
				TreeNode *right = nullptr;
				K *key = nullptr;
				V *value = nullptr;
			};
			
			TreeNode *root = nullptr;
		};
	}
}

#endif //CPLUS_MAP_H
