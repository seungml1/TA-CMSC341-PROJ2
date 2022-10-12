// UMBC - CMSC 341 - Fall 2022 - Proj2
#include "streak.h"

Streak::Streak(){
  m_root = nullptr;
}

Streak::~Streak(){
  clear();
}

void Streak::insert(const Tiger& tiger){
  if(inBounds(tiger.m_id)) {
    m_root = insertRecursive(tiger, m_root);
  }
}

void Streak::clear(){
  if (!isEmpty(m_root)) {
    m_root = clearRecursively(m_root);
  }
}

void Streak::remove(int id){
  if (inBounds(id) && !isEmpty(m_root)) {
    m_root = removeTigerWithID(id, m_root);
  }
}

void Streak::updateHeight(Tiger* aTiger){
  if (!isEmpty(aTiger)) {
    aTiger = setHeightRecursive(aTiger);
  }
}

int Streak::checkImbalance(Tiger* aTiger){
  if (isEmpty(aTiger) || isLeaf(*aTiger)) {
    return 0;
  }
  else if (hasLeftChildOnly(*aTiger)) {
    return aTiger -> m_left -> getHeight();
  }
  else if (hasRightChildOnly(*aTiger)) {
    return -1 * (aTiger -> m_right -> getHeight());
  }
  else {
    return aTiger -> m_left -> getHeight()
         - aTiger -> m_right -> getHeight();
  }
}

Tiger * Streak::rebalance(Tiger * aTiger){
  int imbalance = checkImbalance(aTiger);
  //Left heavy
  if (imbalance > 1) {
    if (hasLeftChild(*(aTiger -> m_left))) {
      aTiger = singleRightRotation(aTiger);
    }
    else {
      aTiger = doubleLeftRightRotation(aTiger);
    }
    return aTiger;
  }
  //Right heavy
  else if (imbalance < -1) {
    if (hasRightChild(*(aTiger -> m_right))) {
      aTiger = singleLeftRotation(aTiger);
    }
    else {
      aTiger = doubleRightLeftRotation(aTiger);
    }
    return aTiger;
  }
  //Balanced
  else {
    return aTiger;
  }
}

void Streak::dumpTree() const {dump(m_root);}

void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

void Streak::listTigers() const {
  if (!isEmpty(m_root)) {
    cout << concatInOrder(*m_root);
  }
}

bool Streak::setState(int id, STATE state){
  if (inBounds(id)) {
    Tiger * tiger = getTigerWithId(id, m_root);
    if (!isEmpty(tiger)) {
      tiger -> setState(state);
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

void Streak::removeDead(){
  if (!isEmpty(m_root)) {
    m_root = removeDeadTigers(m_root);
  }
}

bool Streak::findTiger(int id) const {
  return !isEmpty(getTigerWithId(id, m_root));
}

int Streak::countTigerCubs() const{
  return (int) foldNumTigerCubs(m_root);
}

//Private functions below

bool Streak::isEmpty(Tiger * tiger) const {
  return tiger == nullptr;
}

bool Streak::isLeaf(Tiger tiger) const {
  return isEmpty(tiger.m_left) && isEmpty(tiger.m_right);
}

bool Streak::hasLeftChild(Tiger tiger) const {
  return !isEmpty(tiger.m_left);
}

bool Streak::hasLeftChildOnly(Tiger tiger) const {
  return !isEmpty(tiger.m_left) && isEmpty(tiger.m_right);
}

bool Streak::hasRightChild(Tiger tiger) const {
  return !isEmpty(tiger.m_right);
}

bool Streak::hasRightChildOnly(Tiger tiger) const {
  return isEmpty(tiger.m_left) && !isEmpty(tiger.m_right);
}

bool Streak::hasBothChildren(Tiger tiger) const {
  return !isEmpty(tiger.m_left) && !isEmpty(tiger.m_right);
}

int Streak::calculateHeight(Tiger tiger) const {
  if (isLeaf(tiger)) {
    return 0;
  }
  else if (hasLeftChildOnly(tiger)) {
    return tiger.m_left -> getHeight() + 1;
  }
  else if (hasRightChildOnly(tiger)) {
    return tiger.m_right -> getHeight() + 1;
  }
  else {
    return max(tiger.m_left -> getHeight()
              ,tiger.m_right -> getHeight())
           + 1;
  }
}

Tiger * Streak::setHeight(Tiger * tiger) {
  if (!isEmpty(tiger)) {
    tiger -> m_height = calculateHeight(*tiger);
    return tiger;
  }
  else {
    return tiger;
  }
}

Tiger * Streak::setHeightRecursive(Tiger * tiger) {
  if (isEmpty(tiger) || isLeaf(*tiger)) {
    return setHeight(tiger);
  }
  else {
    return setHeight(constructTiger
      ( (setHeightRecursive(tiger -> m_left))
      , tiger
      , setHeightRecursive(tiger -> m_right)));
  }
}

int Streak::max(int one, int two) const {
  if (one > two) {
    return one;
  }
  else {
    return two;
  }
}

uint Streak::abs(int num) const {
  if (num < 0) {
    return -1 * num;
  }
  else {
    return num;
  }
}

string Streak::concatInOrder(Tiger tiger) const {
  string tigerInfo = printTiger(tiger).append("\n");
  if (isLeaf(tiger)) {
    return tigerInfo;
  }
  else if(hasLeftChildOnly(tiger)) {
    return concatInOrder(*tiger.m_left)
           .append(tigerInfo);
  }
  else if (hasRightChildOnly(tiger)) {
    return tigerInfo
           .append(concatInOrder(*tiger.m_right));
  }
  else {
    return concatInOrder(*tiger.m_left)
           .append(tigerInfo)
           .append(concatInOrder(*(tiger.m_right)));
  }
}

string Streak::printTiger(Tiger tiger) const {
  return std::to_string(tiger.getID()).append(":").append(tiger.getAgeStr()).append(":").append(tiger.getGenderStr()).append(":").append(tiger.getStateStr());
}

//-------
Tiger * Streak::getTigerWithId(int id, Tiger * tiger) const {
  if (isEmpty(tiger)) {
    return nullptr;
  }
  else if (tiger -> getID() == id) {
    return tiger;
  }
  else if (id < tiger -> getID()) {
    return getTigerWithId(id, tiger -> m_left);
  }
  else {
    return getTigerWithId(id, tiger -> m_right);
  }
}


bool Streak::inBounds(int value) const {
  return value >= MINID && value <= MAXID;
}

uint Streak::foldNumTigerCubs(Tiger * tiger) const {
  if (!isEmpty(tiger)) {
    if (tiger -> getAge() == CUB) {
      return 1 + foldNumTigerCubs(tiger -> m_left) + foldNumTigerCubs(tiger -> m_right);
    }
    else {
      return foldNumTigerCubs(tiger -> m_left) + foldNumTigerCubs(tiger -> m_right);
    }
  }
  else {
    return 0;
  }
}

Tiger * Streak::singleLeftRotation(Tiger * tiger) {
  if (!isEmpty(tiger) && hasRightChild(*tiger)) {
    Tiger * newTiger = tiger -> m_right;
    Tiger * oldTiger = setHeight(constructTiger
      ( tiger -> m_left
      , tiger
      , newTiger -> m_left));
    return setHeight(constructTiger
      ( oldTiger
      , newTiger
      , newTiger -> m_right));
  }
  else {
    return tiger;
  }
}

Tiger * Streak::singleRightRotation(Tiger * tiger) {
  if (!isEmpty(tiger) && hasLeftChild(*tiger)) {
    Tiger * newTiger = tiger -> m_left;
    Tiger * oldTiger = setHeight(constructTiger
      ( newTiger -> m_right
      , tiger
      , tiger -> m_right));
    return setHeight(constructTiger
      ( newTiger -> m_left
      , newTiger
      , oldTiger));
  }
  else {
    return tiger;
  }
}

Tiger * Streak::doubleLeftRightRotation(Tiger * tiger) {
  return singleRightRotation(constructTiger
    ( singleLeftRotation(tiger -> m_left)
    , tiger
    , tiger -> m_right));
}

Tiger * Streak::doubleRightLeftRotation(Tiger * tiger) {
  return singleLeftRotation(constructTiger
    ( tiger -> m_left
    , tiger
    , singleRightRotation(tiger -> m_right)));
}

Tiger * Streak::constructTiger(Tiger * left, Tiger * parent, Tiger * right) {
  parent -> m_left = left;
  parent -> m_right = right;
  return parent;
}

Tiger * Streak::insertRecursive(const Tiger & tiger, Tiger * curr) {
  if (isEmpty(curr)) {
    return copyTiger(tiger);
  }
  else if (tiger.getID() < curr -> getID()) {
    return rebalance(setHeight(constructTiger
      ( insertRecursive(tiger, curr -> m_left)
      , curr
      , curr -> m_right)));
  }
  else if (tiger.getID() > curr -> getID()) {
    return rebalance(setHeight(constructTiger
      ( curr -> m_left
      , curr
      , insertRecursive(tiger, curr -> m_right))));
  }
  else {
    return curr;
  }
}

Tiger * Streak::removeTigerWithID(int id, Tiger * tiger) {
  if (isEmpty(tiger)) {
    return tiger;
  }
  else if (id == tiger -> getID()) {
    return remove(tiger);
  }
  else if (id < tiger -> getID()) {
    return rebalance(setHeight(constructTiger
      ( removeTigerWithID(id, tiger -> m_left)
      , tiger
      , tiger -> m_right)));
  }
  else if (id > tiger -> getID()) {
    return rebalance(setHeight(constructTiger
      ( tiger -> m_left
      , tiger
      , removeTigerWithID(id, tiger -> m_right))));
  }
  else {
    return tiger;
  }
}

Tiger * Streak::removeDeadTigers(Tiger * tiger) {
  if (isEmpty(tiger)) {
    return tiger;
  }
  else if (isDeadTiger(*tiger)) {
    tiger = rebalance(setHeight(constructTiger
      ( removeDeadTigers(tiger -> m_left)
      , tiger
      , removeDeadTigers(tiger -> m_left))));
    return remove(tiger);
  }
  else {
    return rebalance(setHeight(constructTiger
      ( removeDeadTigers(tiger -> m_left)
      , tiger
      , removeDeadTigers(tiger -> m_left))));
  }
}

Tiger * Streak::clearRecursively(Tiger * tiger) {
  if (isEmpty(tiger) || isLeaf(*tiger)) {
    return remove(tiger);
  }
  else {
    return remove(constructTiger
      ( clearRecursively(tiger -> m_left)
      , tiger
      , clearRecursively(tiger -> m_right)));
  }
}

/* Removes the current Tiger, while doing the necessary administrative work:
 * - updates heights accordingly
 * - 
 * */
Tiger * Streak::remove(Tiger * tiger) {
  if (isEmpty(tiger) || isLeaf(*tiger)) {
    delete tiger;
    return nullptr;
  }
  else if (hasLeftChildOnly(*tiger)) {
    Tiger * newTiger = extractMax(tiger -> m_left);
    delete constructTiger
      ( nullptr
      , tiger
      , nullptr);
    return newTiger;
  }
  else if (hasRightChildOnly(*tiger)) {
    Tiger * newTiger = extractMin(tiger -> m_right);
    delete constructTiger
      ( nullptr
      , tiger
      , nullptr);
    return newTiger;
  }
  else if (hasLeftChild(*tiger)) {
    Tiger * newTiger = constructTiger
      ( tiger -> m_left
      , extractMax(tiger -> m_left)
      , tiger -> m_right);
    delete constructTiger
      ( nullptr
      , tiger
      , nullptr);
    return newTiger;
  }
  else {
    Tiger * newTiger = constructTiger
      ( tiger -> m_left
      , extractMin(tiger -> m_right)
      , tiger -> m_right);
    delete constructTiger
      ( nullptr
      , tiger
      , nullptr);
    return newTiger;
  }
}

bool Streak::isDeadTiger(Tiger tiger) const {
  return tiger.m_state == DEAD;
}

Tiger * Streak::copyTiger(const Tiger & tiger) {
  return new Tiger
    ( tiger.m_id
    , tiger.m_age
    , tiger.m_gender
    , tiger.m_state);
}

Tiger * Streak::extractMin(Tiger * tiger) {
  if (isEmpty(tiger)) {
    return tiger;
  }
  else {
    return extractMin(tiger, tiger -> m_left);
  }
}

/* This can be implemented in two ways: prev is never null, or curr is
 * never null. Prev never being null means that I have to account for
 * a leaf left child being passed in TODO. Curr never being
 *
 * */
Tiger * Streak::extractMin(Tiger * prev, Tiger * curr) {
  if (isEmpty(curr)) {
    //We return a nullptr because the only time this will happen is
    //if this is the first iteration before any recursive calls, which
    //means that prev does not have a left child, thus it does not have
    //a min replacement.
    return nullptr;
  }
  else if (!hasLeftChild(*curr)) {
    prev = rebalance(setHeight(constructTiger
      ( nullptr
      , prev
      , prev -> m_right)));
    return curr;
  }
  else {
    return extractMin(curr, curr -> m_left);
  }
}

Tiger * Streak::extractMax(Tiger * tiger) {
  if (isEmpty(tiger)) {
    return tiger;
  }
  else {
    return extractMax(tiger, tiger -> m_right);
  }
}

Tiger * Streak::extractMax(Tiger * prev, Tiger * curr) {
  if (isEmpty(curr)) {
    //We return a nullptr because the only time this will happen is
    //if this is the first iteration before any recursive calls, which
    //means that prev does not have a left child, thus it does not have
    //a min replacement.
    return nullptr;
  }
  else if (!hasRightChild(*curr)) {
    prev = rebalance(setHeight(constructTiger
      ( nullptr
      , prev
      , prev -> m_right)));
    return curr;
  }
  else {
    return extractMax(curr, curr -> m_right);
  }
}
