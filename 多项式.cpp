#include <iostream>
using namespace std;

// 定义链表节点
struct Node {
    int expn;        // 指数
    double coef;     // 系数
    Node* next;      // 指向下一个节点
};

// 创建多项式链表
void CreateList(Node* &poly, int terms) {
    Node* temp, *newNode;
    poly = new Node;  // 创建头结点
    poly->next = nullptr;
    
    for (int i = 0; i < terms; i++) {
        newNode = new Node;
        cout << "输入第" << i+1 << "项的系数和指数（例如：3 2 表示 3x^2）：";
        cin >> newNode->coef >> newNode->expn;
        newNode->next = nullptr;

        // 插入到链表尾部
        temp = poly;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 打印多项式
void PrintList(Node* poly) {
    Node* temp = poly->next;
    while (temp) {
        cout << temp->coef << "x^" << temp->expn;
        if (temp->next) cout << " + ";
        temp = temp->next;
    }
    cout << endl;
}

// 多项式相加（合并指数相同的项）
Node* AddPolynomials(Node* Pa, Node* Pb) {
    Node* p1 = Pa->next;  // p1 指向 Pa 的第一个节点
    Node* p2 = Pb->next;  // p2 指向 Pb 的第一个节点
    Node* p3 = Pa;        // p3 用于构建结果多项式，指向 Pa 的头结点
    Node* temp;           // 临时指针用于删除节点

    while (p1 && p2) {
        if (p1->expn == p2->expn) {  // 指数相同
            p1->coef += p2->coef;    // 合并系数
            if (p1->coef != 0) {     // 如果系数不为零，保留
                p3->next = p1;
                p3 = p1;
            } else {  // 系数为零，删除该节点
                p3->next = p1->next;
                delete p1;
            }
            temp = p2;
            p2 = p2->next;
            delete temp;  // 删除 p2 对应的结点
            p1 = p3->next;
        } else if (p1->expn < p2->expn) {
            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        } else {
            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
    }

    // 插入剩余项
    p3->next = (p1 != nullptr) ? p1 : p2;

    delete Pb;  // 释放 Pb 的头结点
    return Pa;
}

// 主函数测试
int main() {
    Node *Pa, *Pb;

    int terms1, terms2;
    cout << "输入第一个多项式的项数：";
    cin >> terms1;
    CreateList(Pa, terms1);

    cout << "输入第二个多项式的项数：";
    cin >> terms2;
    CreateList(Pb, terms2);

    cout << "第一个多项式为：";
    PrintList(Pa);

    cout << "第二个多项式为：";
    PrintList(Pb);

    Node* result = AddPolynomials(Pa, Pb);

    cout << "相加后的多项式为：";
    PrintList(result);

    return 0;
}
