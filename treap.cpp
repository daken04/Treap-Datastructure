#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>

using namespace std;

template <typename T>
class treap
{
private:
    struct node
    {
        T key;
        int priority;
        int cont;
        int minimum;
        bool rvs;
        node *left;
        node *right;
        node(T val)
        {
            key = val;
            priority = rand();
            cont = 1;
            minimum = val;
            rvs = false;
            left = NULL;
            right = NULL;
        }
    };

    typedef node *pnode;
    pnode root;
    int sz;

    void delete_treap(node *root)
    {
        if (root)
        {
            delete_treap(root->left);
            delete_treap(root->right);
            delete root;
        }
    }

    void split(pnode root, int k, pnode &left, pnode &right)
    {
        if (!root)
        {
            left = right = NULL;
            return;
        }
        push(root);
        int cur_key = cont(root->left);
        if (cur_key < k)
        {
            split(root->right, k - cur_key - 1, root->right, right);
            left = root;
        }
        else
        {
            split(root->left, k, left, root->left);
            right = root;
        }
        upd_cont(root);
        upd_minimum(root);
    }

    void merge(pnode &root, pnode T1, pnode T2)
    {
        push(T1);
        push(T2);

        if (T1 == NULL || T2 == NULL)
        {
            root = T1 ? T1 : T2;
            return;
        }
        if (T1->priority > T2->priority)
        {
            merge(T1->right, T1->right, T2);
            root = T1;
        }
        else
        {
            merge(T2->left, T1, T2->left);
            root = T2;
        }

        upd_cont(root);
        upd_minimum(root);
    }

    void push(pnode &root)
    {
        if (root && root->rvs)
        {
            root->rvs = false;
            swap(root->left, root->right);
            if (root->left != NULL)
            {
                root->left->rvs ^= true;
            }

            if (root->right != NULL)
            {
                root->right->rvs ^= true;
            }
        }
    }

    int cont(pnode &root)
    {
        if (!root)
        {
            return 0;
        }
        return root->cont;
    }

    void upd_cont(pnode &root)
    {
        if (root == NULL)
        {
            return;
        }

        if (root)
        {
            root->cont = 1 + cont(root->left) + cont(root->right);
        }
    }

    int minimum(pnode &root)
    {
        if (root == NULL)
        {
            return INT_MAX;
        }
        return root->minimum;
    }

    void upd_minimum(pnode &root)
    {
        if (root == NULL)
        {
            return;
        }

        if (root)
        {
            int x = min(minimum(root->left), minimum(root->right));
            root->minimum = min(root->key, x);
        }
    }

public:
    treap()
    {
        root = NULL;
        sz = 0;
    }

    // Function 1: bool empty()
    bool empty()
    {
        if (sz == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Function 2: int size()
    int size()
    {
        return sz;
    }

    // Function 3: void clear()
    void clear()
    {
        delete_treap(root);
        root = NULL;
        sz = 0;
    }

    // Function 4: int insert(T val)
    int insert(T val)
    {
        pnode new_node = new node(val);
        pnode left, right;
        int idx = 0;
        if (root)
        {
            split(root, lower_bound(val), left, right);
            merge(left, left, new_node);
            merge(root, left, right);
            idx = lower_bound(val);
        }
        else
        {
            root = new_node;
        }
        sz++;
        return idx;
    }

    // Function 5: bool erase(int index)
    bool erase(int index)
    {
        if (index < 0 || index >= sz)
        {
            return false;
        }

        pnode left, right;

        split(root, index, left, right);

        pnode to_delete = right;

        split(right, 1, to_delete, right);
        delete to_delete;
        merge(root, left, right);
        sz = sz - 1;

        return true;
    }

    // Function 6: int indexOf(T val)
    int indexOf(T val)
    {
        int index = 0;
        pnode current = root;
        while (current)
        {
            push(current);

            if (current->key == val)
            {
                // We found the value, and the left subtree contains the elements less than the value
                if (current->left)
                {
                    index = index + cont(current->left);
                }
                break;
            }
            else if (current->key < val)
            {
                // The value is in the right subtree
                if (current->left)
                {
                    index = index + cont(current->left) + 1; // Add the size of the left subtree and the current node
                }
                else
                {
                    index = index + 1; // Add the current node
                }

                current = current->right;
            }
            else
            {
                // The value is in the left subtree
                current = current->left;
            }
        }

        if (current != NULL)
        {
            return index;
        }
        else
        {
            return -1;
        }
    }

    // Function 7: T atIndex(int index)
    T atIndex(int index)
    {
        if (index < 0 || index >= sz)
        {
            return T();
        }
        
        pnode current = root;

        while (current)
        {
            push(current);
            int cur_index = cont(current->left);

            if (cur_index == index)
            {
                return current->key;
            }
            else if (cur_index < index)
            {
                index = index - cur_index + 1;
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return T();
    }

    // Function 8: treap<T>* merge(treap<T>* t2)
    treap<T> *merge(treap<T> *t2)
    {
        treap<T> *new_treap = new treap<T>();

        new_treap->root = NULL;
        new_treap->sz = sz + t2->sz;

        merge(new_treap->root, root, t2->root);
        root = NULL;

        t2->root = NULL;
        return new_treap;
    }

    // Function 9: pair<treap<T>*, treap<T>*> split(int index)
    pair<treap<T> *, treap<T> *> split(int index)
    {
        treap<T> *left_treap = new treap<T>();

        treap<T> *right_treap = new treap<T>();
        pnode left, right;

        split(root, index, left, right);
        left_treap->root = left;
        left_treap->sz = index;

        right_treap->root = right;
        right_treap->sz = sz - index;

        return make_pair(left_treap, right_treap);
    }

    // Function 10: bool erase(int first, int last)
    bool erase(int first, int last)
    {
        if (last >= sz || first < 0 || first > last)
        {
            return false;
        }

        pnode left1, right1;
        split(root, first, left1, right1);
        pnode left2, right2;
        split(right1, last - first + 1, left2, right2);
        delete_treap(left2);

        merge(left1, left1, right2);

        root = left1;
        sz = sz - (last - first + 1);
        return true;
    }

    // Function 11: treap<T>* slice(int first, int last)
    treap<T> *slice(int first, int last)
    {
        if (first < 0 || last >= sz || first > last)
        {
            return NULL;
        }

        treap<T> *new_treap = new treap<T>();
        pnode left1, right1;
        split(root, first, left1, right1);

        pnode left2, right2;
        split(right1, last - first + 1, left2, right2);

        merge(left1, left1, right2);
        root = left1;
        sz = sz - (last - first + 1);

        new_treap->root = left2;
        new_treap->sz = last - first + 1;

        return new_treap;
    }

    // Function 12: int lower_bound(T val)
    int lower_bound(T val)
    {
        int count = 0;
        pnode current = root;
        while (current)
        {
            push(current);
            if (current->key < val)
            {
                count = count + 1 + cont(current->left);
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }

        return count;
    }

    // Function 13: int upper_bound(T val)
    int upper_bound(T val)
    {
        int count = 0;
        pnode current = root;

        while (current)
        {
            push(current);

            if (current->key <= val)
            {
                count = count + 1 + cont(current->left);
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }

        return count;
    }

    // Function 14: int count(T val)
    int count(T val)
    {
        int count = 0;
        pnode current = root;

        while (current)
        {
            push(current);

            if (current->key == val)
            {
                count = count + 1;
                current = current->right;
            }
            else if (current->key < val)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }

        return count;
    }

    // Function 15: vector<T> to_array()
    vector<T> to_array()
    {
        vector<T> values;
        inorder_traversal(root, values);
        return values;
    }

    void inorder_traversal(pnode node, vector<T> &values)
    {
        if (node == NULL)
        {
            return;
        }

        push(node);
        inorder_traversal(node->left, values);
        values.push_back(node->key);
        inorder_traversal(node->right, values);
    }

    // Destructor
    ~treap()
    {
        delete_treap(root);
    }
};

int main()
{
    treap<int> T;
    cout << "Is treap empty? " << (T.empty() ? "true" : "false") << endl;

    int idx1 = T.insert(5);
    cout << "Inserted 1 at index: " << idx1 << endl;
    cout << T.insert(2) << endl;
    cout << T.insert(8) << endl;
    T.insert(1);
    T.insert(6);
    cout << T.insert(8) << endl;
    cout << T.insert(8) << endl;

    cout << "Treap size: " << T.size() << endl;

    // Function 1: bool empty()
    cout << "Is treap empty? " << (T.empty() ? "true" : "false") << endl;

    // Function 2: int size()

    // Function 15: vector<T> to_array()
    vector<int> arr = T.to_array();
    cout << "Elements in sorted order: ";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    bool erased = T.erase(6);
    arr = T.to_array();
    cout << "Erased element at index 6: " << (erased ? "true" : "false") << endl;

    cout << "Elements in sorted order: ";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Function 3: void clear()
    // T.clear();
    // cout << "Cleared the treap." << endl;

    // Function 5: bool erase(int index)
    erased = T.erase(0);
    cout << "Erased element at index 0: " << (erased ? "true" : "false") << endl;

    arr = T.to_array();
    cout << "Elements in sorted order: ";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Function 6: int indexOf(T val)
    int idx2 = T.indexOf(15);
    cout << "Index of 15: " << idx2 << endl;

    // Function 7: T atIndex(int index)
    int value = T.atIndex(3);
    cout << "Value at index 3: " << value << endl;

    // Function 8: treap<T>* merge(treap<T>* t2)
    treap<int> T2;
    T2.insert(10);
    T2.insert(20);
    T2.insert(20);
    T2.insert(30);
    treap<int> *mergedTreap = T.merge(&T2);
    cout << "Merged two treaps." << endl;

    // Print the elements of the merged treap
    vector<int> mergedArr = mergedTreap->to_array();
    cout << "Elements in the merged treap: ";
    for (int i = 0; i < mergedArr.size(); i++)
    {
        cout << mergedArr[i] << " ";
    }
    cout << endl;

    // Function 9: pair<treap<T>*, treap<T>*> split(int index)
    pair<treap<int> *, treap<int> *> split_result = mergedTreap->split(3);

    cout << "Split treap at index 2." << endl;

    // Print the elements of the left treap
    vector<int> leftArr = split_result.first->to_array();
    cout << "Elements in the left treap: ";
    for (int i = 0; i < leftArr.size(); i++)
    {
        cout << leftArr[i] << " ";
    }
    cout << endl;

    // Print the elements of the right treap
    vector<int> rightArr = split_result.second->to_array();
    cout << "Elements in the right treap: ";
    for (int i = 0; i < rightArr.size(); i++)
    {
        cout << rightArr[i] << " ";
    }
    cout << endl;

    // Function 10: bool erase(int first, int last)
    // bool erased_range = split_result.second->erase(0, 1);
    // cout << "Erased elements in the range [0, 1]: " << (erased_range ? "true" : "false") << endl;
    // rightArr = split_result.second->to_array();
    // cout << "Elements in the right treap: ";
    // for (int i = 0; i < rightArr.size(); i++) {
    //     cout << rightArr[i] << " ";
    // }
    // cout << endl;

    // Function 11: treap<T>* slice(int first, int last)
    // treap<int>* sliced_treap = split_result.second->slice(0, 1);
    // cout << "Sliced treap from index 0 to 1." << endl;

    // vector<int> sliceArr = sliced_treap->to_array();
    // cout << "Elements in the slice treap: ";
    // for (int i = 0; i < sliceArr.size(); i++) {
    //     cout << sliceArr[i] << " ";
    // }
    // cout << endl;

    treap<int> T3;
    T3.insert(5);
    T3.insert(3);
    T3.insert(1);
    T3.insert(3);
    T3.insert(1);
    T3.insert(7);

    bool erased_range = T3.erase(1, 4);
    cout << "Erased elements in the range [0, 1]: " << (erased_range ? "true" : "false") << endl;
    rightArr = T3.to_array();
    cout << "Elements in the right treap: ";
    for (int i = 0; i < rightArr.size(); i++)
    {
        cout << rightArr[i] << " ";
    }
    cout << endl;

    // Function 12: int lower_bound(T val)
    int lb = split_result.second->lower_bound(20);
    cout << "Lower bound of 20: " << lb << endl;

    // Function 13: int upper_bound(T val)
    int ub = split_result.second->upper_bound(20);
    cout << "Upper bound of 20: " << ub << endl;

    // Function 14: int count(T val)
    int count_val = split_result.second->count(20);
    cout << "Count of 20: " << count_val << endl;

    return 0;
}