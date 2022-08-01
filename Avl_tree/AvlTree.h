/*
 * @Descripttion: 
 * @version: 
 * @Author: wanwanvv
 * @Date: 2022-07-06 11:15:57
 * @LastEditors: wanwanvv
 * @LastEditTime: 2022-07-08 10:12:00
 */
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <assert.h>
#include <math.h>

template<typename k_t, typename v_t>
struct AVLTreeNode{
    AVLTreeNode<k_t,v_t>* _left;
    AVLTreeNode<k_t,v_t>* _right;
    AVLTreeNode<k_t,v_t>* _parent;
    std::pair<k_t,v_t> _kv;
    int _bf;//平衡因子值=右子树的高度-左子树高度
    AVLTreeNode():_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0){}
    AVLTreeNode(const std::pair<k_t,v_t>& kv):_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0),_kv(kv){}
};

template<typename k_t,typename v_t>
class AVLTree{
public:
    typedef AVLTreeNode<k_t,v_t> TreeNode;  
    typedef std::pair<k_t,v_t> NodePair;

    AVLTree():_root(nullptr){}
    ~AVLTree(){
        clear(_root);
    }

    bool insert(const NodePair& kv ){
        if(!_root){
            _root=new TreeNode(kv);
            return true;
        }
        //找到要插入的位置
        TreeNode* cur=_root;
        TreeNode* parent=nullptr;
        while (cur)
        {
            if(kv.first<cur->_kv.first){
                parent=cur;
                cur=cur->_left;
            }else if(kv.first>cur->_kv.first){
                parent=cur;
                cur=cur->_right;
            }else{
                cur->_kv.second=kv.second;//update value
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
        //更新平衡因子，直到更新到根节点或者节点平衡因子为0
        while(parent){
            if(cur==parent->_left) --parent->_bf;
            else ++parent->_bf;
            if(parent->_bf==0) break;
            else if(parent->_bf==1||parent->_bf==-1){
                cur=parent;
                parent=parent->_parent;
            }else if(parent->_bf==2||parent->_bf==-2){
                //旋转
                if(parent->_bf==2&&cur->_bf==1){//左旋
                    rotate_left(parent);
                }else if(parent->_bf==-2&&cur->_bf==-1){
                    rotate_right(parent);
                }else if(parent->_bf==-2&&cur->_bf==1){
                    rotate_lr(parent);
                }else if(parent->_bf==2&&cur->_bf==-1){
                    rotate_rl(parent);
                }
                break;
            }else{
                assert(false);
            }
        }
        return true;
    }

    void in_traverse(){
        _in_traverse(_root);
        std::cout<<std::endl;
    }

    int get_height(){
        return _get_height(_root);
    }

    bool is_balance(){
        return _is_balance(_root);
    }

private:
    TreeNode* _root;

    void rotate_left(TreeNode* parent){
        TreeNode* p_parent=parent->_parent;
        TreeNode* cur=parent->_right;
        TreeNode* curL=cur->_left;
        parent->_right=curL;
        if(curL) curL->_parent=parent;
        cur->_left=parent;
        parent->_parent=cur;
        if(parent==_root){
            _root=cur;
            _root->_parent=nullptr;
        }else{
            if(p_parent->_left==parent){
                p_parent->_left=cur;
                cur->_parent=p_parent;
            }else if(p_parent->_right==parent){
                p_parent->_right=cur;
                cur->_parent=p_parent;
            }else{
                assert(false);
            }
        }
        parent->_bf=0;
        cur->_bf=0;
    }

    void rotate_right(TreeNode* parent){
        TreeNode* p_parent=parent->_parent;
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
            if(p_parent->_left==parent){
                p_parent->_left=cur;
                cur->_parent=p_parent;
            }else if(p_parent->_right==parent){
                p_parent->_right=cur;
                cur->_parent=p_parent;
            }else{
                assert(false);
            }
        }
        parent->_bf=0;
        cur->_bf=0;
    }

    void rotate_lr(TreeNode* parent){
        TreeNode* subL=parent->_left;
        TreeNode* subLR=parent->_right;
        int bf=subLR->_bf;
        rotate_left(parent->_left);
        rotate_right(parent);
        if(bf==0){
            parent->_bf=0;
            subLR->_bf=0;
            subL->_bf=0;
        }else if(bf==-1){
            parent->_bf=1;
            subL->_bf=0;
            subLR->_bf=0;
        }else if(bf==1){
            parent->_bf=0;
            subLR->_bf=0;
            subL->_bf=-1;
        }
    }

    void rotate_rl(TreeNode* parent){
        TreeNode* subR=parent->_right;
        TreeNode* subRL=subR->_left;
        int bf=subRL->_bf;
        rotate_right(parent->_right);
        rotate_left(parent);
        if(bf==0){
            parent->_bf=0;
            subR->_bf=0;
            subRL->_bf=0;
        }else if(bf==1){
            parent->_bf=-1;
            subRL->_bf=0;
            subR->_bf=0;
        }else if(bf==-1){
            subR->_bf=1;
            parent->_bf=0;
            subRL->_bf=0;
        }else{
            assert(false);
        }
    }

    void _in_traverse(TreeNode* root){
        if(!root) return;
        _in_traverse(root->_left);
        std::cout<<"("<<root->_kv.first<<","<<root->_kv.second<<") ";
        _in_traverse(root->_right);
    }

    int _get_height(TreeNode* root){
        if(!root) return 0;
        int left_height=_get_height(root->_left);
        int right_height=_get_height(root->_right);
        return std::max(left_height,right_height)+1;
    }

    bool _is_balance(TreeNode* root){
        if(!root) return true;
        int left_height=_is_balance(root->_left);
        int right_height=_is_balance(root->_right);
        return abs(left_height-right_height)<2&&_is_balance(root->_left)&&_is_balance(root->_right);
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