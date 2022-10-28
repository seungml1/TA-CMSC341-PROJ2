// UMBC - CMSC 341 - Fall 2022 - Proj2
#ifndef STREAK_H
#define STREAK_H
#include <iostream>
using namespace std;
class Grader; // this class is for grading purposes, no need to do anything
class Tester; // this is your tester class, you add your test functions in this class
class STREAK; // this is the class that you implement
enum STATE {ALIVE, DEAD};
enum AGE {CUB, YOUNG, OLD};
enum GENDER {MALE, FEMALE, UNKNOWN};
const int MINID = 10000;
const int MAXID = 99999;
#define DEFAULT_HEIGHT 0
#define DEFAULT_ID 0
#define DEFAULT_STATE ALIVE
#define DEFAULT_AGE CUB
#define DEFAULT_GENDER UNKNOWN

class Tiger{
    public:
    friend class Grader;
    friend class Tester;
    friend class Streak;
    Tiger(int id, AGE age = DEFAULT_AGE, GENDER gender = DEFAULT_GENDER, STATE state = DEFAULT_STATE)
        :m_id(id),m_age(age),m_gender(gender),m_state(state) {
            m_left = nullptr;
            m_right = nullptr;
            m_height = DEFAULT_HEIGHT;
        }
    Tiger(){
        m_id = DEFAULT_ID;
        m_state = DEFAULT_STATE;
        m_age = DEFAULT_AGE;
        m_gender = DEFAULT_GENDER;
        m_left = nullptr;
        m_right = nullptr;
        m_height = DEFAULT_HEIGHT;
    }
    int getID() const {return m_id;}
    STATE getState() const {return m_state;}
    string getStateStr() const {
        string text = "";
        switch (m_state)
        {
        case DEAD:text = "DEAD";break;
        case ALIVE:text = "ALIVE";break;
        default:text = "UNKNOWN";break;
        }
        return text;
    }
    AGE getAge() const {return m_age;}
    string getAgeStr() const {
        string text = "";
        switch (m_age)
        {
        case CUB:text = "CUB";break;
        case YOUNG:text = "YOUNG";break;
        case OLD:text = "OLD";break;
        default:text = "UNKNOWN";break;
        }
        return text;
    }
    GENDER getGender() const {return m_gender;}
    string getGenderStr() const {
        string text = "";
        switch (m_gender)
        {
        case MALE:text = "MALE";break;
        case FEMALE:text = "FEMALE";break;
        case UNKNOWN:text = "UNKNOWN";break; 
        default:text = "UNKNOWN";break;
        }
        return text
        ;
    }
    int getHeight() const {return m_height;}
    Tiger* getLeft() const {return m_left;}
    Tiger* getRight() const {return m_right;}
    void setID(const int id){m_id=id;}
    void setState(STATE state){m_state=state;}
    void setAge(AGE age){m_age=age;}
    void setGender(GENDER gender){m_gender=gender;}
    void setHeight(int height){m_height=height;}
    void setLeft(Tiger* left){m_left=left;}
    void setRight(Tiger* right){m_right=right;}
    private:
    int m_id;
    AGE m_age;
    GENDER m_gender;
    STATE m_state;
    Tiger* m_left;//the pointer to the left child in the BST
    Tiger* m_right;//the pointer to the right child in the BST
    int m_height;//the height of node in the BST
};

class Streak{
    public:
    friend class Grader;
    friend class Tester;
    Streak();
    ~Streak();
    void insert(const Tiger& tiger);
    void clear();
    void remove(int id);
    void dumpTree() const;
    void listTigers() const;
    bool setState(int id, STATE state);
    void removeDead();//remove all dead tigers from the tree
    bool findTiger(int id) const;//returns true if the tiger is in tree
    int countTigerCubs() const;// returns the # of cubs in the streak
    private:
    Tiger* m_root;//the root of the BST

    void dump(Tiger* aTiger) const;//helper for recursive traversal
    void updateHeight(Tiger* aTiger);
    int checkImbalance(Tiger* aTiger);
    Tiger* rebalance(Tiger* aTiger);

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************

    bool isEmpty(Tiger *) const;
    bool isLeaf(Tiger) const;
    bool hasLeftChild(Tiger) const;
    bool hasLeftChildOnly(Tiger) const;
    bool hasRightChild(Tiger) const;
    bool hasRightChildOnly(Tiger) const;
    bool hasBothChildren(Tiger) const;
    int calculateHeight(Tiger) const;
    Tiger * setHeight(Tiger *);
    Tiger * setHeightRecursive(Tiger *);
    int max(int, int) const;
    uint abs(int) const;
    string concatInOrder(Tiger) const;
    string printTiger(Tiger) const;
    Tiger * getTigerWithId(int, Tiger *) const;
    bool inBounds(int) const;
    uint foldNumTigerCubs(Tiger *) const;
    Tiger * singleLeftRotation(Tiger *);
    Tiger * singleRightRotation(Tiger *);
    Tiger * doubleLeftRightRotation(Tiger *);
    Tiger * doubleRightLeftRotation(Tiger *);
    Tiger * tiltLeft(Tiger *);
    Tiger * tiltRight(Tiger *);
    Tiger * constructTiger(Tiger *, Tiger *, Tiger *);
    Tiger * extractMin(Tiger *);
    Tiger * extractMin(Tiger *, Tiger *);
    Tiger * extractMax(Tiger *);
    Tiger * extractMax(Tiger *, Tiger *);
    Tiger * insertRecursive(const Tiger &, Tiger *);
    Tiger * removeTigerWithID(int, Tiger *);
    Tiger * removeDeadTigers(Tiger *);
    Tiger * clearRecursively(Tiger *);
    Tiger * remove(Tiger *);
    bool isDeadTiger(Tiger) const;
    Tiger * addr(Tiger) const;
    Tiger rebalance(Tiger);
    Tiger * copyTiger(const Tiger &);
    Tiger * removeCurrReplaceWithSuccessor(Tiger *);
    pair<Tiger *, Tiger *> extractMinNew(Tiger *, Tiger *);
    Tiger * removeCurrReplaceWithPredecessor(Tiger *);
    pair<Tiger *, Tiger *> extractMaxNew(Tiger *, Tiger *);
    Tiger * replace(Tiger * tiger);
    uint countNumTigers();
    uint countNumTigers(Tiger *);
};
#endif
