//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "String.h"
#include <set>
#include <iostream>
#include <cstring>
#include <memory>
#include "ByteArray.h"
#include "CPlusString.h"
#include "../utils/Set.hpp"
#include "../utils/StringBuilder.h"
#include "../utils/ArrayStack.hpp"


namespace cplus {
	namespace lang {
		void escapeString(char *buffer, const char *oldStr, size_t strSize) {
			size_t index = 0;
			for (size_t i = 0; i < strSize; ++i) {
				switch (oldStr[i]) {
					case '\a':
						buffer[index++] = '\\';
						buffer[index++] = 'a';
						break;
					case '\b':
						buffer[index++] = '\\';
						buffer[index++] = 'b';
						break;
					case '\f':
						buffer[index++] = '\\';
						buffer[index++] = 'f';
						break;
					case '\n':
						buffer[index++] = '\\';
						buffer[index++] = 'n';
						break;
					case '\r':
						buffer[index++] = '\\';
						buffer[index++] = 'r';
						break;
					case '\t':
						buffer[index++] = '\\';
						buffer[index++] = 't';
						break;
					case '\v':
						buffer[index++] = '\\';
						buffer[index++] = 'v';
						break;
					case '\\':
						buffer[index++] = '\\';
						buffer[index++] = '\\';
						break;
					case '\?':
						buffer[index++] = '\\';
						buffer[index++] = '\?';
						break;
					case '\'':
						buffer[index++] = '\\';
						buffer[index++] = '\'';
						break;
					case '\"':
						buffer[index++] = '\\';
						buffer[index++] = '\"';
						break;
					default:
						buffer[index++] = oldStr[i];
						break;
				}
			}
			buffer[index] = 0;
		}
		
		CPlusClass(StringSet) {
		public:
			StringSet() = default;
			
			~StringSet() {
				if (toCStringBuffer != nullptr)free(toCStringBuffer);
				forEach([](CPlusString *value) {
//					std::cout << "StringSet: ~StringSet(): deleting: " << &key << " :" << key.getStr() << std::endl;
					delete value;
				});
				TreeNode *state = root;
				utils::ArrayStack<TreeNode *> taskQueue;
				while (true) {
					if (state->getLeft() != nullptr)taskQueue.push(state->getLeft());
					if (state->getRight() != nullptr)taskQueue.push(state->getRight());
					delete state;
					if (!taskQueue.pop(state))break;
				}
			}
			
			CPlusString *insert(CPlusString &value) {
				TreeNode *ist;
				if (root == nullptr) {
					ist = new TreeNode(false, false, nullptr, value);
					root = ist;
				} else ist = root->insert(value);
				while (root->getParent() != nullptr) {
					root = root->getParent();
				}
				return ist->get();
			}
			
			CPlusString *get(CPlusString &value) {
//				std::cout << "Set: getting: " << key << std::endl;
				auto ret = this->root->find(value);
				if (ret == nullptr) {
//					std::cout << "Set: not find key, inserting" << std::endl;
					ret = insert(value);
				}
				return ret;
			}
			
			void forEach(const std::function<void(CPlusString *)> &func) const {
				if (root != nullptr)
					root->forEach([&func](TreeNode *value) {
						if (value->get() == nullptr)return;
						else func(value->get());
					});
			}
			
			char *toCString() const {
				if (toCStringBuffer != nullptr) return toCStringBuffer;
				utils::StringBuilder sb;
				size_t stringID = 0;
				sb.append("[");
				
				root->forEach([&sb, &stringID](TreeNode *value) {
					if (stringID != 0) {
						sb.append(",");
//					}
					} else {
						++stringID;
					}

//					sb.append("{\"StringID\":");
//					sb.append(stringID++);
//					sb.append(R"(,"str":")");
					
					sb.append(R"({"str":")");
					
					auto strSize = value->getSize();
					auto *buffer = new char[strSize * 2];
					auto str = value->get()->getStr();
					escapeString(buffer, value->get()->getStr(), strSize);
					sb.append(buffer);
					delete buffer;
					sb.append(R"(","color":")");
					sb.append(value->isRed() ? "RED" : "BLACK");
					sb.append("\"}");
				});
				sb.append("]");
				auto swap = CPlusString(sb.c_str());
				toCStringBuffer = swap.getStr();
				swap.setToNull();
				return toCStringBuffer;
			}
			
			char *getStruction() const {
				utils::StringBuilder sb = utils::StringBuilder();
				size_t id = 0;
				sb.append("[");
				root->forEach([&sb, &id](TreeNode *it) {
					if (id != 0) {
						sb.append(",");
					}
					sb.append(R"({"node":")");
					sb.append((void *) it);
					sb.append(R"(","parent":")");
					sb.append((void *) it->getParent());
					sb.append(R"(","left":")");
					sb.append((void *) it->getLeft());
					sb.append(R"(","right":")");
					sb.append((void *) it->getRight());
					sb.append(R"(","color":")");
					sb.append(it->isRed() ? "RED" : "BLACK");
					sb.append(R"(","size":")");
					sb.append((unsigned long) it->getSize());
					sb.append(R"(","leftOrRight":")");
					sb.append(it->isLeftNode() ? "LEFT" : "RIGHT");
					sb.append(R"(","value":")");
					
					auto strSize = it->get()->getSize();
					auto *buffer = new char[strSize * 2];
					auto str = it->get()->getStr();
					escapeString(buffer, it->get()->getStr(), strSize);
					sb.append(buffer);
					delete buffer;
					
					sb.append("\"}");
					++id;
				});
				sb.append("]");
				auto swap = CPlusString(sb.c_str());
				struction = swap.getStr();
				swap.setToNull();
				return struction;
			}
			
			size_t usedSize() {
				size_t strSize = 0;
				forEach([&strSize](CPlusString *value) {
					strSize += value->getBufferSize();
				});
				return sizeof(*this) + sizeof(*root) * root->getSize() + root->getSize() * sizeof(CPlusString) +
				       strSize;
			}
			
			class RBTException : public system::Exception {
			public:
				RBTException() = default;
				
				explicit RBTException(const char *message) : Exception(message) {}
				
				explicit RBTException(const lang::String &message) : Exception(message) {}
			};
		
		private:
			class TreeNode {
			public:
				TreeNode() : isRedColor(true), isLeft(false) {
					if (toCStringBuffer != nullptr)free(toCStringBuffer);
					toCStringBuffer = nullptr;
					struction = nullptr;
				}
				
				TreeNode(bool red, bool isLeft, TreeNode *parent, CPlusString &key)
						: isRedColor(red), value((CPlusString *) malloc(sizeof(CPlusString))), isLeft(isLeft),
						  parent(parent) {
					if (toCStringBuffer != nullptr)free(toCStringBuffer);
					toCStringBuffer = nullptr;
					struction = nullptr;
					
					this->value->setStr(key.getStr(), key.getBufferSize());
					key.setToNull();
				}
				
				void isRed(bool isRed) { isRedColor = isRed; }
				
				bool isRed() { return isRedColor; }
				
				inline TreeNode *getParent() const { return parent; }
				
				inline TreeNode *getLeft() const { return left; }
				
				TreeNode *getRight() const { return right; }
				
				CPlusString *get() const { return value; }
				
				TreeNode *insert(CPlusString &value) {
					return insert(this, value);
				}
				
				CPlusString *find(const CPlusString &value) {
					auto ret = find(this, value);
					if (ret == nullptr)return nullptr;
					else return ret->value;
				}
				
				void forEach(const std::function<void(TreeNode *)> &func) const {
					auto *state = const_cast<TreeNode *>(this);
					utils::ArrayStack<TreeNode *> taskQueue;
					while (true) {
						func(state);
						if (state->getLeft() != nullptr)taskQueue.push(state->getLeft());
						if (state->getRight() != nullptr)taskQueue.push(state->getRight());
						if (!taskQueue.pop(state))break;
					}
				}
				
				inline bool isLeftNode() { return isLeft; }
				
				inline bool isRightNode() { return !isLeft; }
				
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
				
				u_int32_t getSize() {
					return getSize(this);
				}
				
				static u_int32_t getSize(TreeNode *p) {
					if (p == nullptr)return 0;
					else return p->size;
				}
				
				static bool isBlack(TreeNode *p) { return p == nullptr || !p->isRedColor; }
				
				static bool isRed(TreeNode *p) { return p != nullptr && p->isRedColor; }
				
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
					bool red = root->isRedColor;
					root->isRedColor = right->isRedColor;
					right->isRedColor = red;
					
					root->size = getSize(root->left) + getSize(root->right) + 1;
					right->size = root->size + getSize(right->right) + 1;
					
					return right;
				}
				
				static TreeNode *rightRotate(TreeNode *node) {
					if (node == nullptr)return nullptr;
					//检查是否符合右旋条件
					if (node->left == nullptr)return nullptr;
					auto left = node->left;
					//将 left 传递给 parent
					if (node->parent != nullptr) {
						replaceWith(node, left);
					} else {
						left->parent = nullptr;
					}
					
					//将 left 的 right 传递给 node
					node->setLeft(left->right);
					
					//重设 parent 为 left
					node->parent = left;
					node->parent->right = node;
					node->isLeft = false;
					
					//交换颜色
					bool red = node->isRedColor;
					node->isRedColor = left->isRedColor;
					left->isRedColor = red;
					
					node->size = getSize(node->right) + getSize(node->left) + 1;
					left->size = node->size + getSize(left->left) + 1;
					
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
				 * @param node 新插入的节点
				 */
				static void fixAfterInsertion(TreeNode *node) {
					if (node == nullptr)return;
					else if (node->parent == nullptr) {
						node->isRedColor = false;
						return;
					}
					if (!node->isRedColor) {
						return;
					} else {
						//如果 node 是红色，则可确认 parent 不为 nullptr
						if (node->isLeft) {
							if (isRed(node->parent)) {
								//如果 root 是 parent 的 left 节点
								//并且 left 和 root 都是红色的
//						if (isRed(root->right)) {
//							//如果 right 和 root 都是红色的 //不存在的
//							leftRotate(root);
//							root = root->parent;
//							root = fixAfterInsertion(root);
//						} else if (isRed(root->left)) {
//						//如果 left 和 root 都是红色的
//							if (isRed(root->parent->right)) {
//								//如果 parent 的 right 也是红色的 //不存在的
//								root = flipColors(root->parent);
//							} else {
								/**
								 * 由于禁止右节点出现红色节点，所以这里的代码可以大幅缩减
								 * 比如这里，原来还要判断右边的那个兄弟节点是否为红色
								 * 但是现在完全可以确认右面的兄弟节点一定是黑色，
								 * 所以直接对父节点进行右旋操作，然后一波颜色翻转带走就可以了
								 */
								flipColors(rightRotate(node->parent->parent));
//							}
//						}
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
								fixAfterInsertion(node->left);
							}
						}
					}
				}
				
				static TreeNode *insert(TreeNode *root, CPlusString &value) {
					if (root == nullptr) {
						return new TreeNode(false, false, nullptr, value);
					}
					TreeNode *state = root;
					TreeNode *ist = nullptr;
					while (state != nullptr) {
						if (value == *state->value) break;
						else if (value <= *state->value) {
							if (state->left == nullptr) {
								state->left = ist = new TreeNode(true, true, state, value);
								fixAfterInsertion(ist);
								break;
							} else {
								state = state->left;
							}
						} else {
							if (state->right == nullptr) {
								state->right = ist = new TreeNode(true, false, state, value);
								fixAfterInsertion(ist);
								break;
							} else {
								state = state->right;
							}
						}
					}
					return ist;
				}
				
				static TreeNode *find(TreeNode *root, const CPlusString &value) {
//					std::cout << "Set: static: finding key: " << key << std::endl;
					TreeNode *state = root;
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
				
				static TreeNode *del(TreeNode *node) {
					if (node == nullptr)return nullptr;
					else if (node->left == nullptr) {
						replaceWith(node, node->right);
					} else if (node->right == nullptr) {
						replaceWith(node, node->left);
					} else {
						auto rtMin = rightMin(node);
						replaceWith(rtMin, nullptr);
						rtMin->left = node->left;
						rtMin->right = node->right;
						replaceWith(node, rtMin);
					}
					return node;
				}
				
				static TreeNode *rightMin(TreeNode *node) {
					if (node == nullptr)return nullptr;
					else if (node->right == nullptr)return node;
					else {
						node = node->right;
						while (node->left != nullptr) {
							node = node->left;
						}
					}
					return node;
				}
				
				/**
				 *
				 * @param node 已经删除的节点
				 * @return
				 */
				static TreeNode *colorFixup(TreeNode *node) {
					if (node == nullptr)return nullptr;
					else if (node->isRedColor) {
						return node->parent;
					} else if (node->parent == nullptr) {
					
					}
				}
				
				inline static void replaceWith(TreeNode *oldNode, TreeNode *newNode) {
					if (oldNode == nullptr)return;
					if (oldNode->parent == nullptr)return;
					if (oldNode->isLeft) {
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
				CPlusString *value = nullptr;
			};
			
			TreeNode *root = nullptr;
			static char *toCStringBuffer;
			static char *struction;
		};
		
		char *StringSet::toCStringBuffer = nullptr;
		char *StringSet::struction = nullptr;

//		StringSet *stringSet = new StringSet();
		StringSet stringSet;
		
		String &String::operator=(const String &string) {
			value = string.value;
			return *this;
		}
		
		String String::toString() const {
			return *this;
		}
		
		String::String(const std::string &str) {
//			if (stringSet == nullptr) stringSet = new StringSet();
			auto string = CPlusString(str);
//			CPlusString *index = stringSet->get(string);
			CPlusString *index = stringSet.get(string);
			value = index;
			this->value->inCited();
		}
		
		String::String(const char *str) {
//			if (stringSet == nullptr) stringSet = new StringSet();
			auto string = CPlusString(str);
//			CPlusString *index = stringSet->get(string);
			CPlusString *index = stringSet.get(string);
			value = index;
			this->value->inCited();
		}
		
		String::String() : String("") {}
		
		String operator+(const std::string &str1, const String &str2) {
			return String(str1 + str2.value->getStr());
		}
		
		String String::operator+(const std::string &str1) {
			return String(value->getStr() + str1);
		}
		
		bool String::operator==(const String &rhs) const {
			return value == rhs.value;
		}
		
		bool String::operator!=(const String &rhs) const {
			return !(rhs == *this);
		}
		
		String::String(const ByteArray &buffer) {
//			if (stringSet == nullptr) stringSet = new StringSet();
			auto string = CPlusString(buffer);
//			const CPlusString *index = stringSet->get(string);
			CPlusString *index = stringSet.get(string);
			value = index;
			this->value->inCited();
		}
		
		
		const char *String::c_str() const {
			return value->getStr();
		}
		
		std::string String::stdString() const {
			return std::string(value->getStr());
		}
		
		String::String(const String &str) : value(str.value) {
			this->value->inCited();
		}
		
		String::~String() {
			this->value->unCited();
		}
		
		char *String::allString() {
			return stringSet.toCString();
		}
		
		size_t String::usedSize() {
			return stringSet.usedSize();
		}
		
		char *String::bufferStruct() {
			return stringSet.getStruction();
		}
	}
}