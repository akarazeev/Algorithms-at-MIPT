#ifndef BTree_HEAD_H_2015_03_31
#define BTree_HEAD_H_2015_03_31

namespace akarazeev {

    template <typename Key, typename Value, int(*Compare)(const Key* key1, const Key* key2)>
    class CBTree {
    public:
        
        class Node {
        public:
            
            Node(int branching, bool is_leaf);
            
            void traverse();
            int find_key_index(const Key& key);
            
            void remove_key(const Key& key);
            void remove(const Key& key, const Value& value);
            
            void remove_from_leaf(int index);
            void remove_from_non_leaf(int index);
            std::pair<Key, Value> get_predecessor(int index);
            std::pair<Key, Value> get_successor(int index);
            void fill(int index);
            void borrow_from_prev(int index);
            void borrow_from_next(int index);
            
            void merge(int index);
            
            Node* search(const Key& key);
            Node* search_key_val(const Key& key, const Value& value);
            Value get_value(const Key& key);
            
            void insert_non_full(const Key& key, const Value& value);
            void split_child(int index, CBTree<Key, Value>::Node* node);
            
            std::pair<Key, Value>* values;
            CBTree<Key, Value>::Node** children;
            
            int num_keys_;
            int branching_;
            bool is_leaf_;
        };
        
        class CException {
        public:
            
            CException()
            {
            }
        };
        
        CBTree(int branching) : branching_(branching), root_(NULL) {
            
        }
        
        bool add(const Key& key, const Value& value);
        bool remove(const Key& key, const Value& value);
        
        CBTree<Key, Value>::Node* find(const Key& key, const Value& value) {
            if (root_ == NULL) {
                return NULL;
            } else {
                return root_->search_key_val(key, value);
            }
        }
        
        Value get_value(const Key& key) {
            if (root_ == NULL) {
                return NULL;
            } else {
                return root_->get_value(key);
            }
        }
        
//        CBTree()
//        {
//        }
//
//        bool add(T* pElement)
//        {
//        }
//
//        T* find(const T& pElement)
//        {
//        }
//
//        bool remove(const T& element)
//        {
//        }
// ---------------------------------
//        virtual ~CBTree()
//        {
//        }
//        bool update(T* pElement)
//        {
//        }
//        void clear()
//        {
//        }
    private:
        
        int branching_;
        CBTree<Key, Value>::Node* root_;
        
        void traverse() {
            if (root_ != NULL) {
                root_->traverse();
            }
        }
        
        CBTree<Key, Value>::Node* search(const Key& key) {
            if (root_ == NULL) {
                return NULL;
            } else {
                return root_->search(key);
            }
        }
        
        bool remove_key(const Key& key);
    };

    ////////////////////
    // Implementation //
    ////////////////////
    
    template <typename Key, typename Value>
    CBTree<Key, Value>::Node::Node(int branching, bool is_leaf) : is_leaf_(is_leaf), branching_(branching) {
        values = new std::pair<Key, Value> [2 * branching_ - 1];
        children = new CBTree<Key, Value>::Node* [2 * branching_];
        num_keys_ = 0;
    }
    
    template <typename Key, typename Value>
    int CBTree<Key, Value>::Node::find_key_index(const Key &key) {
        int index = 0;
        while (index < num_keys_ && values[index].first < key) {
            ++index;
        }
        return index;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::remove_key(const Key &key) {
        int index = find_key_index(key);
        
        if (index < num_keys_ && values[index].first == key) {
            if (is_leaf_) {
                remove_from_leaf(index);
            } else {
                remove_from_non_leaf(index);
            }
        } else {
            if (is_leaf_) {
                return;
            }
            
            bool flag = ( (index == num_keys_) ? true : false );
            
            if (children[index]->num_keys_ < branching_) {
                fill(index);
            }
            
            if (flag && index > num_keys_) {
                children[index - 1]->remove_key(key);
            } else {
                children[index]->remove_key(key);
            }
        }
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::remove(const Key &key, const Value &value) {
        int index = find_key_index(key);
        
        if (index < num_keys_ && values[index].first == key && values[index].second == value) {
            if (is_leaf_) {
                remove_from_leaf(index);
            } else {
                remove_from_non_leaf(index);
            }
        } else {
            if (is_leaf_) {
                return;
            }
            
            bool flag = ( (index == num_keys_) ? true : false );
            
            if (children[index]->num_keys_ < branching_) {
                fill(index);
            }
            
            if (flag && index > num_keys_) {
                children[index - 1]->remove(key, value);
            } else {
                children[index]->remove(key, value);
            }
        }
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::remove_from_leaf(int index) {
        for (int i = index + 1; i < num_keys_; ++i) {
            values[i - 1] = values[i];
        }
        
        --num_keys_;
        
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::remove_from_non_leaf(int index) {
        std::pair<Key, Value> elem = values[index];
        
        if (children[index]->num_keys_ >= branching_) {
            std::pair<Key, Value> pred = get_predecessor(index);
            values[index] = pred;
            children[index]->remove(pred.first, pred.second);
        } else if (children[index + 1]->num_keys_ >= branching_) {
            std::pair<Key, Value> succ = get_successor(index);
            values[index] = succ;
            children[index + 1]->remove(succ.first, succ.second);
        } else {
            merge(index);
            children[index]->remove(elem.first, elem.second);
        }
        return;
    }
    
    template <typename Key, typename Value>
    std::pair<Key, Value> CBTree<Key, Value>::Node::get_predecessor(int index) {
        CBTree<Key, Value>::Node* cur = children[index];
        while (!cur->is_leaf_) {
            cur = cur->children[cur->num_keys_];
        }
        
        return cur->values[cur->num_keys_ - 1];
    }
    
    template <typename Key, typename Value>
    std::pair<Key, Value> CBTree<Key, Value>::Node::get_successor(int index) {
        CBTree<Key, Value>::Node* cur = children[index + 1];
        while (!cur->is_leaf_) {
            cur = cur->children[0];
        }
        
        return cur->values[0];
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::fill(int index) {
        if (index != 0 && children[index - 1]->num_keys_ >= branching_) {
            borrow_from_prev(index);
        } else if (index != num_keys_ && children[index + 1]->num_keys_ >= branching_) {
            borrow_from_next(index);
        } else {
            if (index != num_keys_) {
                merge(index);
            } else {
                merge(index - 1);
            }
        }
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::borrow_from_prev(int index) {
        CBTree<Key, Value>::Node* child = children[index];
        CBTree<Key, Value>::Node* sibling = children[index - 1];
        
        for (int i = child->num_keys_ - 1; i >= 0; --i) {
            child->values[i + 1] = child->values[i];
        }
        
        if (!child->is_leaf_) {
            for (int i = child->num_keys_; i >= 0; --i) {
                child->children[i + 1] = child->children[i];
            }
        }
        
        child->values[0] = values[index-1];
        
        if (!is_leaf_) {
            child->children[0] = sibling->children[sibling->num_keys_];
        }
        
        values[index - 1] = sibling->values[sibling->num_keys_ - 1];
        
        child->num_keys_ += 1;
        sibling->num_keys_ -= 1;
        
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::borrow_from_next(int index) {
        CBTree<Key, Value>::Node* child = children[index];
        CBTree<Key, Value>::Node* sibling = children[index + 1];
        
        child->values[child->num_keys_] = values[index];
        
        if (child->is_leaf_ == false) {
            child->children[child->num_keys_ + 1] = sibling->children[0];
        }
        
        values[index] = sibling->values[0];
        
        for (int i = 1; i < sibling->num_keys_; ++i) {
            sibling->values[i-1] = sibling->values[i];
        }
        
        if (sibling->is_leaf_ == false)
        {
            for (int i = 1; i <= sibling->num_keys_; ++i) {
                sibling->children[i-1] = sibling->children[i];
            }
        }
        
        child->num_keys_ += 1;
        sibling->num_keys_ -= 1;
        
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::merge(int index) {
        CBTree<Key, Value>::Node* child = children[index];
        CBTree<Key, Value>::Node* sibling = children[index + 1];
        
        child->values[branching_ - 1] = values[index];
        
        for (int i = 0; i < sibling->num_keys_; ++i) {
            child->values[i + branching_] = sibling->values[i];
        }
        
        if (child->is_leaf_ == false) {
            for (int i = 0; i <= sibling->num_keys_; ++i) {
                child->children[i + branching_] = sibling->children[i];
            }
        }
        
        for (int i = index + 1; i < num_keys_; ++i) {
            values[i - 1] = values[i];
        }
        
        for (int i = index + 2; i <= num_keys_; ++i) {
            children[i-1] = children[i];
        }
        
        child->num_keys_ += sibling->num_keys_ + 1;
        --num_keys_;
        
        delete(sibling);
        return;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::traverse() {
        for (int i = 0; i < num_keys_; ++i) {
            if (is_leaf_ == false) {
                children[i]->traverse();
            }
            std::cout << " " << values[i].first << "," << values[i].second << " ";
        }
        
        if (is_leaf_ == false) {
            children[num_keys_]->traverse();
        }
    }
    
    template <typename Key, typename Value>
    typename CBTree<Key, Value>::Node* CBTree<Key, Value>::Node::search(const Key& key) {
        int index = 0;
        while (index < num_keys_ && key > values[index].first) {
            ++index;
        }
        
        if (key == values[index].first) {
            return this;
        }
        
        if (is_leaf_) {
            return NULL;
        }
        
        return children[index]->search(key);
    }
    
    template <typename Key, typename Value>
    typename CBTree<Key, Value>::Node* CBTree<Key, Value>::Node::search_key_val(const Key &key, const Value &value) {
        int index = 0;
        while (index < num_keys_ && key > values[index].first) {
            ++index;
        }
        
        if (key == values[index].first and value == values[index].second) {
            return this;
        }
        
        if (is_leaf_) {
            return NULL;
        }
        
        return children[index]->search_key_val(key, value);
    }
    
    template <typename Key, typename Value>
    Value CBTree<Key, Value>::Node::get_value(const Key& key) {
        int index = 0;
        while (index < num_keys_ && key > values[index].first) {
            ++index;
        }
        
        if (key == values[index].first) {
            return values[index].second;
        }
        
        if (is_leaf_) {
            return NULL;
        }
        
        return children[index]->get_value(key);
    }
    
    template <typename Key, typename Value>
    bool CBTree<Key, Value>::add(const Key &key, const Value &value) {
        if (root_ == NULL) {
            root_ = new CBTree<Key, Value>::Node(branching_, true);
            root_->values[0] = std::pair<Key, Value>(key, value);
            root_->num_keys_ = 1;
        } else {
            if (root_->num_keys_ == 2 * branching_ - 1) {
                CBTree<Key, Value>::Node* tmp = new CBTree<Key, Value>::Node(branching_, false);
                tmp->children[0] = root_;
                
                tmp->split_child(0, root_);
                
                int index = 0;
                if (tmp->values[0].first < key) {
                    ++index;
                }
                tmp->children[index]->insert_non_full(key, value);
                
                root_ = tmp;
            } else {
                root_->insert_non_full(key, value);
            }
        }
        return true;
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::insert_non_full(const Key &key, const Value &value) {
        int index = num_keys_ - 1;
        
        if (is_leaf_) {
            while (index >= 0 && values[index].first > key) {
                values[index + 1] = values[index];
                --index;
            }
            values[index + 1] = std::pair<Key, Value>(key, value);
            ++num_keys_;
        } else {
            while (index >= 0 && values[index].first > key) {
                --index;
            }
            if (children[index + 1]->num_keys_ == 2 * branching_ - 1) {
                split_child(index + 1, children[index + 1]);
                if (values[index + 1].first < key) {
                    ++index;
                }
            }
            children[index + 1]->insert_non_full(key, value);
        }
    }
    
    template <typename Key, typename Value>
    void CBTree<Key, Value>::Node::split_child(int index, CBTree<Key, Value>::Node* node) {
        CBTree<Key, Value>::Node* tmp = new CBTree<Key, Value>::Node(node->branching_, node->is_leaf_);
        tmp->num_keys_ = branching_ - 1;
        
        for (int i = 0; i < branching_ - 1; ++i) {
            tmp->values[i] = node->values[i + branching_];
        }
        
        if (node->is_leaf_ == false) {
            for (int i = 0; i < branching_; ++i) {
                tmp->children[i] = node->children[i + branching_];
            }
        }
        
        node->num_keys_ = branching_ - 1;
        
        for (int i = num_keys_; i >= index + 1; --i) {
            children[i + 1] = children[i];
        }
        
        children[index + 1] = tmp;
        
        for (int i = num_keys_ - 1; i >= index; --i) {
            values[i + 1] = values[i];
        }
        
        values[index] = node->values[branching_ - 1];
        
        ++num_keys_;
    }
    
    template <typename Key, typename Value>
    bool CBTree<Key, Value>::remove_key(const Key &key) {
        if (!root_) {
            return false;
        }
        
        bool is_exist = search(key) ? true : false;
        
        root_->remove_key(key);
        
        if (root_->num_keys_ == 0) {
            CBTree<Key, Value>::Node* tmp = root_;
            
            if (root_->is_leaf_) {
                root_ = NULL;
            } else {
                root_ = root_->children[0];
            }
            
            delete tmp;
        }
        return is_exist;
    }
    
    template <typename Key, typename Value>
    bool CBTree<Key, Value>::remove(const Key &key, const Value &value) {
        if (!root_) {
            return false;
        }
        
        bool is_exist = find(key, value) ? true : false;
        
        root_->remove(key, value);
        
        if (root_->num_keys_ == 0) {
            CBTree<Key, Value>::Node* tmp = root_;
            
            if (root_->is_leaf_) {
                root_ = NULL;
            } else {
                root_ = root_->children[0];
            }
            
            delete tmp;
        }
        return is_exist;
    }
    
}; // namespace akarazeev

#endif // #define BTree_HEAD_H_2015_03_31
