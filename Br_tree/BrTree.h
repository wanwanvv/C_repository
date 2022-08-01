/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-06 11:57:19
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-11 11:01:31
 */
#ifndef BR_TREE_H
#define BR_TREE_H
#include <utility>
#include "assert.h"
// struct BRTreeNode{
//     BRTreeNode* _left;
//     BRTreeNode* _right;
//     BRTreeNode* _parent;
//     std::pair<int,int> _kv;
//     int _bf;
//     BRTreeNode():_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0){}
//     BRTreeNode(const std::pair<int,int>& kv):_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0),_kv(kv){}
// };

enum Color{
    red,
    black,
};

template<typename k_t, typename v_t>
struct BRTreeNode{
    BRTreeNode<k_t,v_t>* _left;
    BRTreeNode<k_t,v_t>* _right;
    BRTreeNode<k_t,v_t>* _parent;
    std::pair<k_t,v_t> _kv;
    Color _color;
    BRTreeNode():_left(nullptr),_right(nullptr),_parent(nullptr),_color(red){}
    BRTreeNode(const std::pair<k_t,v_t>& kv):_left(nullptr),_right(nullptr),_parent(nullptr),_color(red),_kv(kv){}
};

template<typename k_t, typename v_t>
class BRTree{
public:
    typedef BRTreeNode<k_t,v_t> TreeNode;
    typedef std::pair<k_t,v_t> NodePair;

    //***********************constructors*******************
    BRTree():_root(nullptr){}
    
    //***********************interfaces*******************
    bool isBRTree(){
        if(!_root) return true;
        //根结点是否为黑色
        if(_root->_color==red){
            std::cout<<"根节点为红色!"<<std::endl;
            return false;
        }
        //黑色结点数量各路径上相同
        //先走一条得到基准值
        TreeNode* cur=_root;
        int blacknum=0;
        while(cur){
            if(cur->_color==black) ++blacknum;
            cur=cur->_left;
        }
        //检查子树
        return _isBRTree(_root,blacknum,0);
    }
    
    bool insert(const NodePair& kv){
        //先找到插入节点 
        if(_root==nullptr){
            _root=new TreeNode(kv);
            return true;
        }
        TreeNode* cur=_root;
        TreeNode* parent=nullptr;
        while(cur){
            if(kv.first<cur->_kv.first){
                parent=cur;
                cur=cur->_left;
            }else if(kv.first>cur->_kv.first){
                parent=cur;
                cur=cur->_right;
            }else{
                cur->_kv.second=kv.second;
                return false;
            }
        }
        //插入节点
        cur=new TreeNode(kv);
        if(kv.first<parent->_kv.first){
            parent->_left=cur;
            cur->_parent=parent;
        }else if(kv.first>parent->_kv.first){
            parent->_right=cur;
            cur->_parent=parent;
        }else{
            assert(false);
        }
        //旋转
        while(parent&&parent->_color==red){
            TreeNode* grandParent=parent->_parent;
            if(parent==grandParent->_left){
                TreeNode* uncle=grandParent->_right;
                if(uncle&&uncle->_color==red){//直接更改颜色
                    parent->_color=black;
                    uncle->_color=black;
                    grandParent->_color=red;
                    cur=grandParent;
                    grandParent=grandParent->_parent;
                }else{
                    if(cur==parent->_left){//单旋+变色
                        rotateR(grandParent);
                        parent->_color=black;
                        grandParent->_color=red;
                    }else{//双旋+变色
                        rotateL(parent);
                        rotateR(grandParent);
                        cur->_color=black;
                        grandParent->_color=red;
                    }
                    break;
                }
            }else{
                TreeNode* uncle=grandParent->_left;
                if(uncle&&uncle->_color==red){//变色
                    uncle->_color=parent->_color=black;
                    grandParent->_color=red;
                    cur=grandParent;
                    parent=grandParent->_parent;
                }else{
                    if(cur==parent->_right){//单旋+变色
                        rotateR(grandParent);
                        parent->_color=black;
                        grandParent->_color=red;
                    }else{//双旋+变色
                        rotateR(parent);
                        rotateL(grandParent);
                        cur->_color=black;
                        grandParent->_color=red;
                    }
                    break;
                }
            }
        }
        //确保根结点为黑
        _root->_color=black;
        return true;
    }

    void rotateL(TreeNode* parent){
        TreeNode* grandParent=parent->_parent;
        TreeNode* cur=parent->_right;
        TreeNode* curL=cur->_left;
        parent->_right=curL;
        if(curL) curL->_parent=parent;
        cur->_left=parent;
        parent->_parent=cur;
        if(parent==_root){
            _root=cur;
            cur->_parent=nullptr;
        }else{
            if(parent==grandParent->_left){
                grandParent->_left=cur;
                cur->_parent=grandParent;
            }else if(parent==grandParent->_right){
                grandParent->_right=cur;
                cur->_parent=grandParent;
            }
        }
    }

    void rotateR(TreeNode* parent){
        TreeNode* grandParent=parent->_parent;
        TreeNode* cur=parent->_left;
        TreeNode* curR=cur->_right;
        parent->_left=curR;
        if(curR) curR->_parent=parent;
        cur->_right=parent;
        parent->_parent=cur;
        if(parent==_root){
            _root=cur;
            cur->_parent=nullptr;
        }else{
            if(parent==grandParent->_left){
                grandParent->_left=cur;
                cur->_parent=grandParent;
            }else if(parent==grandParent->_right){
                grandParent->_right=cur;
                cur->_parent=grandParent;
            }
        }
    }
    
    void in_traverse(){
        _in_traverse(_root);
        std::cout<<std::endl;
    }

private:
    //******************************variables*********************
    TreeNode* _root;

    //******************************functions*********************
    bool _isBRTree(TreeNode* root, int blacknum,int count){
        if(!root){
            if(blacknum==count) return true;
            std::cout << "各路径上黑色节点个数不同" << std::endl;
            return false;
        }
        //子节点为红则检查父节点是否为红
        if(root->_color==red&&root->_parent&&root->_parent->_color==red){
            std::cout << "存在连续红色节点!" << std::endl;
            return false;
        }
        //计数黑节点
        if(root->_color==black) ++count;
        return _isBRTree(root->_left,blacknum,count)&&_isBRTree(root->_right,blacknum,count);
    }

    void _in_traverse(TreeNode* root){
        if(!root) return;
        _in_traverse(root->_left);
        std::cout<<"("<<root->_kv.first<<","<<root->_kv.second<<") ";
        _in_traverse(root->_right);
    }

    void clear(TreeNode* root){
        if(!root) return;
        clear(root->_left);
        clear(root->_right);
        delete root;
        return;
    }
};

#endif