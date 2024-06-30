#pragma once
#include "heap.h"
#include "BST.h"
#include "assert.h"
#include "menu.h"

using namespace std;

int main() {
//    int n;
//    cout<<"Enter nodes quantity:\n";
//    cin>>n;
    ///{5,10,15,16,22,30}
    /// {15,10,5,22,16,30}
    vector<int> in = {1,5,6,7,8,20,25,30,50,60,65,70,72,75,90,100};
    vector<int> klp = {50,20,5,1,6,7,8,30,25,75,70,60,65,72,100,90};
//    cout<<"Enter inorder and preorder traversal:\n";
//    for (int i = 0; i < n; ++i) {
//        cin>>in[i];
//    }
//    for (int i = 0; i < n; ++i) {
//        cin>>klp[i];
//    }
    BST<int> testing = BST(in, klp);
    testing.delete_element(50);
    for(int i = 0; i < 15; ++i){
        testing.delete_element(testing.getRoot());
        vector<int> in_test1 = testing.inorderTraversal();
        vector<int> pre_test1 = testing.preorderTraversal();
        vector<int> post_test1 = testing.postorderTraversal();
        for(auto& el : in_test1){
            cout<< el<< ' ';
        }
        cout<<endl;
        for(auto& el : pre_test1){
            cout<< el<< ' ';
        }
        cout<<endl;
        for(auto& el :post_test1){
            cout<< el<< ' ';
        }
        cout<<endl<<endl<<endl;
    }



    test();
    menu();
    return 0;
}
