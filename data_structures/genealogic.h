#include <bits/stdc++.h>
using namespace std;

class Tree{
private:

    typedef struct Node{
        int id;
        string nome;
        vector<struct Node *> children;
    }Node;

    Node * root;

    static Node * initialize(int id, string nome){
        Node * newNode = new Node;
        newNode->id = id;
        newNode->nome = nome;
        return newNode;
    }

    int __find(Node ** root, string nome){
        if((*(root))->nome.compare(nome) == 0)
            return (*(root))->id;
        else{
            for(size_t i=0;i<(*(root))->children.size();i++){
                int id = __find(&(*(root))->children[i], nome);
                if(id != -1)
                    return id;
            }
        }
        return -1;
    }

    void __changeValue(Node ** root, int id, string new_name){
        if((*(root))->id == id){
            (*(root))->nome = new_name;
            return;
        }else{
            for(size_t i = 0;i<(*(root))->children.size();i++){
                __changeValue(&(*(root))->children[i], id, new_name);
            }
        }
    }

    void __insert(Node ** root, int id, string nome, int id_parent){
        if(*(root) == NULL) {
            *(root) = initialize(id, nome);
            return;
        }else if((*(root))->id == id_parent) {
            (*(root))->children.push_back(initialize(id, nome));
            return;
        }else{
            for(size_t i=0;i<(*(root))->children.size();i++){
                __insert(&(*(root))->children[i], id, nome, id_parent);
            }
        }
    }

    void __clear(Node ** root){
        if(*root == NULL)
            return;
        vector<Node *> temp;
        for(size_t i=0;i<(*(root))->children.size();i++){
            if((*(root))->children[i] != NULL)
                temp.push_back((*(root))->children[i]);
        }
        (*(root))->children = temp;
        for(size_t i=0;i<(*(root))->children.size();i++)
            __clear(&(*(root))->children[i]);
    }

    void __erase(Node ** root, int id){
        if(id == (*(root))->id){
            delete *root;
            *root = NULL;
            return;
        }else{
            for(size_t i=0;i<(*(root))->children.size();i++){
                __erase(&(*(root))->children[i], id);
            }
        }
    }

    void dfs(Node * root){
        if(root == NULL)
            return;
        cout << root->id << endl;
        for(size_t i=0;i<root->children.size();i++){
            dfs(root->children[i]);
        }
    }
public:

    Tree(){
        root = NULL;
    }

    void _insert(int id, string nome, int id_parent){
        __insert(&root, id, nome, id_parent);
    }

    int _find(string nome){
        return __find(&root, nome);
    }

    void _changeValue(int id, string new_name){
        __changeValue(&root, id, new_name);
    }

    void _erase(int id) {
        __erase(&root, id);
        __clear(&root);
    }

    bool _empty(){
        return root == NULL;
    }

};

class ArvoreGenealogica{
private:
    Tree arvore;
    int nextIndex;

    void add_membro(string nome, int parente){
        arvore._insert(nextIndex, nome, parente);
        nextIndex++;
    }

    void remove_membro(int id){
        arvore._erase(id);
    }

    void mudar_nome(int id, string new_name){
        arvore._changeValue(id, new_name);
    }

    static string normalizar(string nome){
        string result;
        for(char c : nome){
            c = tolower(c);
            if((c >= 'a' && c <= 'z') || (c == ' '))
                result += c;
        }
        return result;
    }
public:
    ArvoreGenealogica(){
        nextIndex = 1;
    }

    void add_membro(){
        string nome;
        if(arvore._empty()){
            cout << "\nInsira o primeiro membro da família: ";
            getline(cin, nome);
            add_membro(normalizar(nome), -1);
        }else{
            string parente;
            cout << "\nInsira o nome do parente: ";
            getline(cin, parente);
            int id_parent = arvore._find(normalizar(parente));
            if(id_parent == -1){
                cout << "\nParente inexistente!\n\n";
            }else{
                cout << "\nInsira o nome do novo membro: ";
                getline(cin, nome);
                int id = arvore._find(normalizar(nome));
                if(id == -1) {
                    add_membro(normalizar(nome), id_parent);
                    cout << "\nMembro inserido!\n\n";
                }else{
                    cout << "\nEsse nome já existe na árvore genealógica!\n\n";
                }
            }
        }
    }

    void remove_membro(){
        if(arvore._empty()){
            cout << "\nNão há membros na árvore!\n\n";
        }else{
            string nome;
            cout << "\nInsira o nome do membro: ";
            getline(cin, nome);
            int id = arvore._find(normalizar(nome));
            if(id == -1){
                cout << "\nMembro inexistente!\n\n";
            }else{
                remove_membro(id);
                cout << "\nMembro e sub-árvore genealógica removidos!\n\n";
            }
        }
    }

    void mudar_nome(){
        if(arvore._empty()){
            cout << "\nNão há membros na árvore!\n\n";
        }else{
            string nome;
            cout << "\nInsira o nome do membro: ";
            getline(cin, nome);
            int id = arvore._find(normalizar(nome));
            if(id == -1){
                cout << "\nMembro inexistente!\n\n";
            }else{
                string new_name;
                cout << "\nInsira o novo nome para o membro: ";
                getline(cin, new_name);
                if(arvore._find(normalizar(new_name)) == -1){
                    mudar_nome(id, normalizar(new_name));
                    cout << "\nNome alterado!\n\n";
                }else{
                    cout << "\nJá existe alguém com esse nome!\n\n";
                }
            }
        }
    }

    void procurar_membro(){
        if(arvore._empty()){
            cout << "\nNão há membros na árvore!\n\n";
        }else{
            string nome;
            cout << "\nInsira o nome do membro: ";
            getline(cin, nome);
            int id = arvore._find(normalizar(nome));
            if(id == -1){
                cout << "\nMembro inexistente!\n\n";
            }else{
                cout << "Membro encontrado! (Id " << id << ")\n\n";
            }
        }
    }

};

